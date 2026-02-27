## TM1650 4-digit 7-segment LED display driver for STM32 Nucleo
Lightweight STM32 HAL based driver for 4-digit LED display, based on TM1650 IC.

**Features**

The driver supports common numeric display ranges:

(0 : 9999) - unsigned four-digit integer number
(-999 : 999) - signed three-digit integer
(-99.9 : 99.9) - signed float, 1 decimal place
(-9.99 : 9.99) - signed float, 2 decimal places
(0.0 : 999.9) - unsigned float, 1 decimal place

Additional features:

Configurable brightness (8 levels)
STM32 HAL integration
FreeRTOS-compatible (tested on Nucleo L476RG devboard)

**Hardware requirements**

TM1650-based 4-digit, 7-segment display
I2C interface with external pull-up resistors (4.7kOhm) for SCL and SDA lines.

**Demo**

The repository example project (CMSIS V2) based on Nucleo L476RG devboard

This project is licensed under the MIT License.
See the LICENSE file for details.