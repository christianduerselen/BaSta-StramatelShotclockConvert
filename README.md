# BaSta-StramatelShotclockConvert

BaSta-StramatelShotclockConvert is an Arduino program used to convert the shotclock information from an incoming Stramatel protocol. The incoming protocol is expected to have a shotclock information for displays with support for tenths (e.g. 4.5 seconds). This information is converted to be compatible with displays that to not support tenths.

## Examples

- 24 > 24 (No change necessary)
- ...
- 4.9 >  4 (.x is cut off)
- ...
- 0.9 > 09 (. is removed, last second)
- ...
- 0.1 > 01 (0.1 seconds is ceiled to 1 second)
- 0.0 > 00 (0.0 seconds is ceiled to 0 seconds)

## Usage

BaSta-StramatelShotclockConvert is intended to be used on an Arduino Uno board with two RS485 Shields. Since only one SoftwareSerial can be used simultaneously, the output shield is driven through the hardware UART on pins 0 & 1. Furthermore, TX-control is managed for the shields on pins 6 & 7.

- 0 - RX pin for output Shield
- 1 - TX pin for output Shield
- 6 - TX control pin for output Shield
- 2 - RX pin for input Shield
- 3 - TX pin for input Shield
- 7 - TX control pin for input Shield
