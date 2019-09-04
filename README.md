# EKI-1-radlogger
Radiation logger for stratospheric capsule EKI-1 

## Pins
SD Card:
- MOSI: 11
- MISO: 12
- PIN_CLOCK: 13
- CS: 10

## Notification code
- Ok -> 2 Blink
- Error -> 3 Blink

First blink serie for serial initialization and second blink serie for SD card initialization.
