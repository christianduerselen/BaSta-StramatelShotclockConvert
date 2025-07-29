#include "SoftwareSerial.h"

#include "StramatelProtocolParser.h"

const int Rx1Pin = 2;
const int Tx1Pin = 3;
const int Rx2Pin = 4;
const int Tx2Pin = 5;

const int Baudrate = 19200;

SoftwareSerial serialInput(Rx1Pin, Tx1Pin);
SoftwareSerial serialOutput(Rx2Pin, Tx1Pin);
StramatelProtocolParser protocolParser;

void setup()
{
  // Configure serial receive (through SerialInput)
  serialInput.begin(Baudrate);
  serialOutput.begin(Baudrate);

  Serial.begin(Baudrate);
}

void loop()
{
  // RECEIVE
  if (!serialInput.available() > 0)
    return;
  
  // Read next byte from input
  byte value = serialInput.read();

  Serial.write(value);

  protocolParser.push(value);

  // PARSE
  if (!protocolParser.isValidMessage())
    return;

  // CONTROL

  // Get both bytes of the shot clock
  byte shotClockHigh = protocolParser.getMessageByte(ShotClockHigh);
  byte shotClockLow = protocolParser.getMessageByte(ShotClockLow);

  // Both values must be between 0x30 (0) and 0x49 (.9) to be valid for potential manipulation
  if (shotClockHigh >= 0x30 && shotClockHigh <= 0x49 && shotClockLow >= 0x30 && shotClockLow <= 0x49)
  {
    // Convert data bytes to numerical value and compensate 
    float value = 0;
    if (shotClockLow > 0x39)
    {
      value += (shotClockHigh - 0x30);
      value += (shotClockLow - 0x40) / 10;

      // New value is the ceiling (e.g. 3,3s becomes 4s)
      value = ceil(value);
    }
    else
    {
      value += (shotClockHigh - 0x30) * 10;
      value += (shotClockLow - 0x30);

      // New value is the integer increased by 1 and the maximum value is 24 (e.g. 6s becomes 7s because it represents 6,0 to 6,9 seconds, 24s remains 24s)
      value = min(floor(value) + 1, 24);
    }

    int valueHigh = (int(value) / 10) % 10;
    int valueLow = int(value) % 10;
    protocolParser.setMessageByte(ShotClockHigh, valueHigh + 0x30);
    protocolParser.setMessageByte(ShotClockLow, valueLow + 0x30);
  }

  // OUTPUT

  // Write the final message to the output
  for (int i = 0; i < MessageSize; i++)
  {
    serialOutput.write(protocolParser.getMessageByte(i));
  }
}