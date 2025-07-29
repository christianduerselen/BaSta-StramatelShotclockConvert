# BaSta-StramatelShotclockConvert

BaSta-StramatelShotclockConvert is an Arduino program used to convert the shotclock information from an incoming Stramatel protocol. The incoming protocol is expected to have a shotclock information for displays with support for tenths (e.g. 4.5 seconds). This information is converted to be compatible with displays that to not support tenths.

## Examples

- 24 > 24 (No change necessary)
- 23 > 24 (23 represents 23.0 to 23.9 seconds and is ceiled to 24 seconds)
- ...
- 05 > 06 (05 represents 5.0 to 5.9 seconds and is ceiled to 6 seconds)
- 4.9 > 05 (4.9 seconds is ceiled to 5 seconds)
- ...
- 4.1 > 05 (4.1 seconds is ceiled to 5 seconds)
- 4.0 > 04 (4.0 seconds is ceiled to 4 seconds)
- ...
- 0.9 > 01 (0.9 seconds is ceiled to 1 second)
- ...
- 0.1 > 01 (0.1 seconds is ceiled to 1 second)
- 0.0 > 00 (0.0 seconds is ceiled to 0 seconds)

## Usage

BaSta-StramatelShotclockConvert is intended to be used on an Arduino Uno board with two RS485 Shields. To keep the USB serial interface enabled, the protocol is received and sent through separate Rx- and Tx-pins for each Shield and the SoftwareSerial plugin. Following is the pin usage for an Arduino Uno board:

- 2 - RX1 for SoftwareSerial and Shield 1 (Protocol Input)
- 3 - TX1 for SoftwareSerial and Shield 1 (Protocol Input)
- 4 - RX2 for SoftwareSerial and Shield 2 (Protocol Output)
- 5 - TX2 for SoftwareSerial and Shield 2 (Protocol Output)
