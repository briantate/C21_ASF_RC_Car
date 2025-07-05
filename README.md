# C21_ASF_RC_Car

# Project Status:
Complete

# Description

This project is a remote controlled differential steering car. It uses the [SAMC21 Xplained Pro](https://www.microchip.com/en-us/development-tool/ATSAMC21-XPRO) and [ATZBRF212B Xpro Extension](https://www.microchip.com/en-us/development-tool/ATZB-212B-XPRO) evaluation kits from Microchip, along with the [Arduino Motor Shield Rev3](https://store-usa.arduino.cc/products/arduino-motor-shield-rev3?_gl=1*1kxwhaq*_up*MQ..*_ga*MTE4ODc4NDI2Mi4xNzUxNDEyNTkw*_ga_NEXN8H46L5*czE3NTE0MTI1ODkkbzEkZzAkdDE3NTE0MTI1ODkkajYwJGwwJGgxNTQ2Mzg4Njc4).

The SAMC21 MCU connects to my [R30 RC](https://github.com/briantate/R30_RC) remote control via a Microchip MiWi peer-to-peer network. It receives the control data and drives 2 pairs of motors using a differential steering method similar to a tank. 

I used a car kit that I had laying around from many years ago which was designed to hold an arduino board and has 4 DC Gear motors. I can't find a link of where to buy it but similar kits are available online. 

# To use the docker environment:
## Make sure the docker engine is running -- In windows, this means starting docker desktop and running the engine
## build the docker image using the dockerfile
## enable the DOCKER_BUILDKIT to automatically build the image for the target architecture
* make sure you are in the directory with the Dockerfile
* >DOCKER_BUILDKIT=1 docker build -t cicd-dev .
## run the newly built docker image
* >docker run --rm -it --privileged -v "$(PWD):/home/app" cicd-dev:latest bash

## use the docker image!
* you should see a bash prompt looking something like this:
    * root@8f1800b29b3d:/home/app#
* run the shell script to build/erase/program/etc...
    * root@8f1800b29b3d:/home/app# ./project.sh debug