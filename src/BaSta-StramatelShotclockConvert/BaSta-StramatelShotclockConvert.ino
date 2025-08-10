#include "SoftwareSerial.h"

#include "StramatelProtocolParser.h"

const int Rx1Pin = 2;
const int Tx1Pin = 3;
const int TxControl1Pin = 6;
const int TxControl2Pin = 7;

const int Baudrate = 19200;

SoftwareSerial serialInput(Rx1Pin, Tx1Pin);
StramatelProtocolParser protocolParser;

void setup()
{
  pinMode(TxControl1Pin, OUTPUT);
  digitalWrite(TxControl1Pin, LOW);
  pinMode(TxControl2Pin, OUTPUT);
  digitalWrite(TxControl2Pin, HIGH);

  // Configure serial receive (through SerialInput)
  serialInput.begin(Baudrate);

  Serial.begin(Baudrate);
  Serial.println("setup() done!");
}

void loop()
{
  // RECEIVE
  if (!serialInput.available() > 0)
    return;
  
  // Read next byte from input
  byte value = serialInput.read();
  protocolParser.push(value);

  // PARSE
  if (!protocolParser.isValidMessage())
    return;

  // CONTROL

  // Get both bytes of the shot clock
  byte shotClockHigh = protocolParser.getMessageByte(ShotClockHigh);
  byte shotClockLow = protocolParser.getMessageByte(ShotClockLow);

  if (shotClockLow >= 0x40 && shotClockLow <= 0x49 && (shotClockHigh == 0x20 || shotClockHigh >= 0x30 && shotClockHigh <= 0x39))
  {
    if (shotClockHigh != 0x30)
    {
      protocolParser.setMessageByte(ShotClockLow, shotClockHigh);
      protocolParser.setMessageByte(ShotClockHigh, 0x20);
    }
    else
    {
      protocolParser.setMessageByte(ShotClockLow, shotClockLow - 0x10);
    }
  }

  // OUTPUT

  // Write the final message to the output and dump to monitor
  for (int i = 0; i < MessageSize; i++)
    Serial.write(protocolParser.getMessageByte(i));
}