# VoxelHap

VoxelHap is an open-source toolkit, aiming to support VR researchers and developers in constructing highly functional proxy objects providing tactile and kinesthetic haptic feedback. It consists of Voxels and Plates: (1) Voxels are blocks with special functionalities that form the core of each physical proxy, (2) Plates increase a proxy's haptic resolution, such as its shape, texture or weight. Beyond providing physical capabilities to realize haptic sensations, VoxelHap utilizes VR illusion techniques to expand its haptic resolution.

[![VoxelHap](https://github.com/MartinFk/VoxelHap/blob/main/img/preview.png)](https://youtu.be/_2FG0eMlGLQ "VoxelHap")

This work is provided under a MIT License. 

Please adequately cite this work, and show us your amazing projects! VoxelHap was published at the UIST'23 conference.

```
@inproceedings{feick2023VoxelHap,
author = {Feick, Martin and Biyikli, Cihan and Gani, Kiran and Wittig, Anton and Tang, Anthony and Krüger, Antonio},
title = {VoxelHap: A Toolkit for Constructing Proxies Providing Tactile and Kinesthetic Haptic Feedback in Virtual Reality},
year = {2023},
isbn = {979-8-4007-0132-0/23/1},
publisher = {Association for Computing Machinery},
address = {New York, NY, USA},
url = {https://doi.org/10.1145/3586183.3606722},
doi = {10.1145/3586183.3606722},
booktitle = {Proceedings of the 36nd Annual ACM Symposium on User Interface Software and Technology},
location = {San Francisco, CA, USA},
series = {UIST '23}
}
```

## Voxels
<img src="https://github.com/MartinFk/VoxelHap/blob/main/img/voxels.JPG">
<img src="https://github.com/MartinFk/VoxelHap/blob/main/img/overview.png">

## Communication

Voxels communicate using a Master/Slave architecure. Master (Wemos D1 mini) is connected to a host maschine via serial port running Unity3D. BaseVoxels (slaves) communicate to the master wirelessly using PainlessMesh.

The firmware folder contains the arduino files. Master.ino should be uploaded onto the master (Wemos D1 mini), and Slave_VoxelHap_Cubes.ino onto the BaseVoxels.

<img src="https://github.com/MartinFk/VoxelHap/blob/main/renderings/architecture.svg">


## PCB

<img src="https://github.com/MartinFk/VoxelHap/blob/main/renderings/pcbParts.png">

<img src="https://github.com/MartinFk/VoxelHap/blob/main/renderings/pcb_components.png">


## Dependencies 

(1) Voxels use a capacitive touch sensor MPR121. Download Adafruit_MPR121 libray from Arduino IDE. -> https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial/wiring

(2) Voxels require FastLED library to manage LEDs on board. Download FastLED library from Arduino IDE. -> https://fastled.io/

(3) Voxels require ArduinoJson library to send JSON file to the master. Download ArduinoJson library from Arduino IDE. -> https://arduinojson.org/

(4) For Master/Slave communication between Voxels and the master Wemos D1, we use the PainlessMesh library. Download Painlessmesh library from Arduino IDE, specifically namedmesh example. -> https://gitlab.com/painlessMesh/painlessMesh/-/tree/develop/examples/namedMesh?ref_type=heads

(5) For Unity- Master communication establish Serial communication and import the Unity3D package (with .Net4.x frame work in player settings).

## Issues

If you face any problems while using the toolkit, please open an issue here - https://github.com/MartinFk/VoxelHap/issues or contact us under martin.feick@dfki.de 📫.
