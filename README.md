# SunSpec
This is the official repository for the BRCTC Space Team's SunSpec project that will take flight through [NASA's RockSat-X program](https://www.nasa.gov/wallops/stem/rocksatx/) in 2024.


## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Contributors](#contributors)
- [License](#license)

## Introduction

Our project involves gathering spectrometric data from the Sun using a combination of microcontrollers, motors, a camera, and a spectrometer. The launch window is brief, around 5 minutes, with only 20-30 seconds of optimal data capture. The primary objectives are to obtain spectrometric data and pictures of the Sun.

#### Key Components:

Microcontrollers, motors, camera, and spectrometer.
2-axis gimbal system controlled by a Raspberry Pi for solar orientation.
Seamless coordination between the image-capturing system and the spectrometer.

#### Space-Based Approach:
Launching into space provides high-resolution and precision data, an unobstructed view, and eliminates light pollution for accurate analysis of the Sun's spectral features.

#### Subsystems:

##### Spectrometer and Raspberry Pi:
Housed inside an enclosure.
Communicates over serial.
Gathers scientific data.

##### Gimbal, Camera, and Attenuator:

Outside enclosure.
Diagnostics data collected by the camera.
Linked by fiber optic cable and 11-pin ribbon connector.
The project aims to minimize atmospheric distortions, capturing clean spectrometric information for accurate analysis.

**This document is for the software portion of this project.**

## Project Structure

```
Root
|-- bin
|   | -- close_build.sh
|   | -- rx_build.sh
|   | -- tx_build.sh
|   | -- wiringPiInstall.sh
|-- doc
|   | -- USB2000+DataSheet.pdf
|-- etc
|-- include
|   |-- RS232Commands.h
|   |-- logging.h
|   |-- sysutils.h
|-- lib
|   |-- WiringPi
|-- log
|   |-- ERRORS.log
|   |-- CALLS.log
|   |-- RECIEVE.log
|-- src
|   |-- arduino
|       |-- main
            |-- main.ino
|   |-- pitest
|       |-- closeserial.cpp
|       |-- led.cpp
|       |-- testRX.cpp
|       |-- testTX.cpp
|   |-- spectrometer.cpp
```

# Contributors
[@Zekaroni](https://github.com/Zekaroni)

# License

This project is licensed under the terms of the [GPL-3.0 license](LICENSE).

See the [LICENSE](LICENSE) file for details.
