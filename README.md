# SunSpec
This is the offical repository for the BRCTC Space Team's SunSpec project.


## Table of Contents
- [Introduction](#introduction)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Our project involves gathering spectrometric data from the Sun using a combination of microcontrollers, motors, a camera, and a spectrometer. The launch window is brief, around 5 minutes, with only 20-30 seconds of optimal data capture. The primary objectives are to obtain spectrometric data and pictures of the Sun.

#### Key Components:

Microcontrollers, motors, camera, and spectrometer.
2-axis gimbal system controlled by a Raspberry Pi for solar orientation.
Seamless coordination between the image-capturing system and the spectrometer.
Space-Based Approach:
Launching into space provides high-resolution and precision data, an unobstructed view, and eliminates light pollution for accurate analysis of the Sun's spectral features.

#### Subsystems:

Spectrometer and Raspberry Pi:

Housed inside an enclosure.
Communicates over serial.
Gathers scientific data.

#### Gimbal, Camera, and Attenuator:

Outside enclosure.
Diagnostics data collected by the camera.
Linked by fiber optic cable and 11-pin ribbon connector.
The project aims to minimize atmospheric distortions, capturing clean spectrometric information for accurate analysis.

**This document is for the software portion of this project.**

## Project Structure

```
Root
|-- bin
|-- doc
|-- etc
|-- exe
|-- include
|   |-- RS232Commands.h
|-- lib
|   |-- main.cpp
|-- log
|   |-- ERRORS.brctc
|   |-- CALLS.brctc
|-- src
```

# Contributors
@Zekaroni