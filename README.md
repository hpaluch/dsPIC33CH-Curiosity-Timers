# dsPIC33CH Curiosity Timers

Here we will show various types of dsPIC33CH Timers and
their usage on Curiosity board.

Hardware Requirements:
- [dsPIC33CH Curiosity Development Board](https://www.microchip.com/en-us/development-tool/DM330028-2)
- Micro USB cable (there is no one included with board!)
- ensure that you downloaded data-sheet from:
  - https://ww1.microchip.com/downloads/en/DeviceDoc/DS50002801%20-%20dsPIC33CH%20Curiosity%20Development%20Board%20Users%20Guide.pdf
- Notice dsPIC type from data-sheet:
  - [dsPIC33CH512MP508](https://www.microchip.com/en-us/product/dsPIC33CH512MP508)

Software Requirements:
- MPLAB X IDE `v6.10` + Updates
  > WARNING! You need to install latest updates when running
  > this verson of MPLAB for the first time. Otherwise 
  > PicKit programmer on board (PKOB) will not work!
- DFP: `dsPIC33CH-MP_DFP v1.7.194`
- XC16 `v2.10`
- recommended: Download official Curiosity board example:
  - download: https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/SoftwareLibraries/Firmware/dspic33ch512_curiosity_demo.zip
  - page: https://www.microchip.com/en-us/development-tool/DM330028-2

For Demos with UART you additionally need:
- 2nd Micro USB cable (not included with Curiosity)
- for Windows < 10 download driver from 
  - https://www.microchip.com/en-us/product/MCP2221A 
  - for example: https://ww1.microchip.com/downloads/en/DeviceDoc/MCP2221_Windows_Driver_2021-02-22.zip

# Curiosity board Notes

Please note that when you create new project you need to select:
- Family: `16-bit DSCs (dsPIC33)`
- Device: `dsPIC33CH512MP508` for Master Core. If you will create also Slave
  project you have to select same CPU with `S1` (Slave) suffix
- Tool: `Starter Kits (PKOB)-SN:BURxxx` (you need to have your Curiosity board 

Here is brief overview of I/O peripherals on Curiosity board - excluding DC/DC converter parts:

| Peripheral | dsPIC33CH pin and/or port |
| --- | --- |
| S1 push-button | RE7 |
| S2 push-button | RE8 |
| S3 push-button | RE9 |
| S4 push-button | /MCLR (reset) |
| R/G/B LED | RD5/RD7/RB14 |
| LED1 red | RE0 |
| LED2 red | RE1 |
| 10kOhm pot | RA0 |

Master core supports  up to f<sub>cy</sub> = 90 MHz (MIPS).
In MCC Tool I have to configure clock this way:
- clock Type: `Primary` (there is accurate 8 MHz clock base on Curiosity board)
- enable PLL and set it to:
- Prescaler: 1:1 -> 8 Mhz
- Feedback: 1:180 -> 1440 MHz
- Postscale1: 1:4 -> 360 MHz
- Postscaler2: 1:1 -> 360 MHz
- output oscillator frequency: f<sub>osc</sub> = 180 MHz
- final instruction cycle frequency:  f<sub>cy</sub> = 90 MHz = 90 MIPS

Also set `Auxiliary Clock` to Primary.

ICD: Ensure that PGC2 and PGD2 are selected (valid for PKOB programmer
debugger on board).

# Project

In this project we will incrementally test various kinds of Timers
and their use cases.

Implemented Functions:
- using only Master Core running at maximum cycle frequency f<sub>cy</sub> = 90 MHz (90 MIPS)
- if any Trap occurs both RED LED1 and RED2 will be lit forever.
- main thread: rotating RGB LED every 1s using `__delay_ms(1000)`: Red -> Green -> Blue -> All off
- TMR1 callback at 1 kHz rate, toggle RB11 at this rate (frequency 500 Hz)
- Flipping RED LED1 at 10 Hz rate => blinking frequency 5 Hz


