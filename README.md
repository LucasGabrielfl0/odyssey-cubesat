<h1 align="center"> ODYSSEY-CUBESAT</h1>

<p align="center">
  Flight Software for the ODYSSEY 2U CubeSat Prototype
</p>
<p align="center">
<img width="506" height="700" alt="Image" src="https://github.com/user-attachments/assets/a1a89f78-60b3-445f-b946-fd0565dca2b1" />
</p>

## Flight Software
The ODYSSEY is a 2U CubeSat prototype, featuring a full Attitude Determination and Control System (ADCS) in all three axes and a bidirectional telemetry system using LoRa radio.
This repository contains the embedded firmware running on the STM32F411 microcontroller.

## Contents

- [Overview](#system-architecture-overview)
- [Attitude Determination and Control System (ADCS)](#attitude-determination-and-control-system-adcs)
- [Telemetry, Tracking and Command (TT&C)](#telemetry-tracking-and-command-ttc)
- [Project Repositories](#project-repositories)


## System Architecture Overview
blablabal, explain the system

<p align="center">
<img width="555" height="530" alt="Image" src="https://github.com/user-attachments/assets/52a436fa-80e4-46f5-ae13-e0d939efd464" />
</p>

| Subsystem | Component | Model | Function |
| --- | --- | --- | --- |
| **On‑Board Computer (OBC)** | Microcontroller | **STM32F411CEU6** | Runs ADCS, TT&C, motor control, task scheduling. |
| **Attitude Determination** | IMU | **BNO055** | Provides Euler angles, gyro, and accelerometer data with onboard fusion. |
| **Attitude Control** | Reaction Wheel Motors | **Coreless DC 1020** | Actuators for roll, pitch, and yaw control. |
|  | Motor Drivers | **DRV8833 Dual H‑Bridge** | Bidirectional PWM control of each reaction wheel. |
| **Telemetry & Command (TT&C)** | Radio Module | **LoRa E220‑900T22D** | Long‑range bidirectional communication at 915 MHz. |
|  | Antenna | LoRa Helical Antenna | RF link between CubeSat and ground station. |
| **Ground Segment** | Ground Radio | **ESP32 + LoRa Module** | Receives telemetry and sends commands to the CubeSat. |
|  | Dashboard | Python Desktop App | Real‑time visualization, CSV logging, setpoint control. |
| **Power System (EPS)** | Battery Pack | **4× 18650 Li‑ion (2S2P)** | Main power source (7.4–8.4 V). |
|  | Buck Converter | **LM2596** | Regulates 5 V for logic and sensors. |
|  | Buck Converter | **XL4015E** | Adjustable supply for reaction wheel motors. |
|  | Protection Circuit | Zener + Fuse | Over‑voltage and over‑current protection. |
| **Thermal Monitoring** | Temperature Sensor | **LM35DZ** | Measures internal temperature for housekeeping telemetry. |
| **Mechanical Structure** | Frame | Custom 2U Aluminum/PLA | Houses PCBs, wheels, battery, and electronics. |

## Attitude Determination and Control System (ADCS)
The ADCS uses a 3‑axis reaction wheel assembly to control roll, pitch, and yaw.
Orientation is sampled at 100 Hz, and a proportional controller adjusts wheel speeds accordingly.

[VIDEO CONTROLE]

## Telemetry, Tracking and Command (TT&C)
The TT&C subsystem provides a bidirectional LoRa link between the CubeSat and the ground station, enabling real‑time telemetry and command updates. The satellite transmits attitude and housekeeping data while receiving setpoints and mode changes from the base. All communication follows a custom packet frame with CRC validation for reliability.
Packet Structure

### 📦 Attitude Packet (CubeSat → Base, 100 ms)
Contains orientation, acceleration, angular velocity, and a message counter.
| Field | Description | Bytes | Range | Resolution | Unit |
| --- | --- | --- | --- | --- | --- |
| 1 | Roll | 2 | −90 to 90 | 0.0625 | ° |
| 2 | Pitch | 2 | −180 to 180 | 0.0625 | ° |
| 3 | Yaw | 2 | 0 to 360 | 0.0625 | ° |
| 4 | Acc X | 2 | −4000 to 4000 | 1 | mg |
| 5 | Acc Y | 2 | −4000 to 4000 | 1 | mg |
| 6 | Acc Z | 2 | −4000 to 4000 | 1 | mg |
| 7 | Gyro X | 2 | −2000 to 2000 | 0.0625 | °/s |
| 8 | Gyro Y | 2 | −2000 to 2000 | 0.0625 | °/s |
| 9 | Gyro Z | 2 | −2000 to 2000 | 0.0625 | °/s |
| 10 | Counter | 1 | 0–255 | 1 | — |

### 📦 Housekeeping Packet (CubeSat → Base,1 s)
Contains slow‑varying engineering data.
| Field | Description | Bytes | Range | Resolution | Unit |
| --- | --- | --- | --- | --- | --- |
| 1 | Roll Setpoint | 2 | −90 to 90 | 0.1 | ° |
| 2 | Pitch Setpoint | 2 | −180 to 180 | 0.1 | ° |
| 3 | Yaw Setpoint | 2 | 0 to 360 | 0.1 | ° |
| 4 | Status Byte | 1 | 0–255 | — | — |
| 5 | Battery Voltage | 2 | 0–8.4 | 0.1 | V |
| 6 | Temperature | 1 | −10 to 155 | 0.5 | °C |


### 📦 Command Packet (Base → CubeSat)
| Field | Description | Bytes | Range | Resolution | Unit |
| --- | --- | --- | --- | --- | --- |
| 1 | Roll Setpoint | 2 | −90 to 90 | 0.1 | ° |
| 2 | Pitch Setpoint | 2 | −180 to 180 | 0.1 | ° |
| 3 | Yaw Setpoint | 2 | 0 to 360 | 0.1 | ° |
| 4 | Mode | 1 | 0–255 | — | — |



## 🔗 Project Repositories
Here are the links for all the other repositores within this project
| Repository | Description |
|------------|-------------|
| [ODYSSEY-Hardware](https://github.com/LucasGabrielfl0/Cubesat-Hardware) | PCB designs, schematics, manufacturing files, and mechanical structure. |
| [ATLAS-GroundStation](https://github.com/LucasGabrielfl0/Cubesat-GroundStation) | Embedded software responsible for communication with the satellite. |
| [ATLAS-Dashboard](https://github.com/LucasGabrielfl0/Cubesat-Dashboard) | Desktop interface for telemetry visualization and command transmission. |




