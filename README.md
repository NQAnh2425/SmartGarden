# SmartGarden
Automated agriculture with SX12xx LoRa module, MCU(STM32)
An ESP32 development board was used as a gateway between the monitoring system and the Blynk platform for remote monitoring.
# LoRa RA-02 (SX1278) STM32 Project

A low-power LoRa wireless sensor network using STM32F103C8T6 and SX1278 module for environmental monitoring.

## Features
- LoRa communication (RA-02 / SX1278)
- Star topology network
- TDMA-based transmission
- Temperature & humidity sensing
- Blynk cloud monitoring

## Results
- TX current: ~60 mA total
- STM32: ~34 mA
- LoRa module: ~26 mA
- Stable data transmission and network re-join after reset

## Hardware
- STM32F103C8T6
- SX1278 (RA-02)
- AHT30 sensor (temperature & humidity)

## DEMO
- Sensor data successfully sent to gateway
- Real-time display on Blynk platform
- TDMA scheduling and time sync working correctly
- DEMO video:
- DEMO blynk interface: https://www.youtube.com/watch?v=mZzxr0jQyzQ
- DEMO debug interface: https://studio.youtube.com/video/q0S_oU_FBuk
