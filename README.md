# C21_ASF_RC_Car

This project is a remote controlled differential steering car. It uses the [SAMC21 Xplained Pro](https://www.microchip.com/en-us/development-tool/ATSAMC21-XPRO) and [ATZBRF212B Xpro Extension](https://www.microchip.com/en-us/development-tool/ATZB-212B-XPRO) evaluation kits from Microchip, along with the [Arduino Motor Shield Rev3](https://store-usa.arduino.cc/products/arduino-motor-shield-rev3?_gl=1*1kxwhaq*_up*MQ..*_ga*MTE4ODc4NDI2Mi4xNzUxNDEyNTkw*_ga_NEXN8H46L5*czE3NTE0MTI1ODkkbzEkZzAkdDE3NTE0MTI1ODkkajYwJGwwJGgxNTQ2Mzg4Njc4).

The SAMC21 MCU connects to my [R30 RC](https://github.com/briantate/R30_RC) remote control via a Microchip MiWi peer-to-peer network. It receives the control data and drives 2 pairs of motors using a differential steering method similar to a tank. 

I used a car kit that I had laying around from many years ago which was designed to hold an arduino board and has 4 DC Gear motors. I can't find a link of where to buy it but similar kits are available online. 


