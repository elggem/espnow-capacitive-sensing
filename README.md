# espnow-capacitive-sensing

<p align="center">
  <img src="images/hw-top.jpg" width="40%"/><img src="images/hw-bottom.jpg" width="40%"/>
</p>

This repository contains code for experimenting with built-in capacitive touch functionality in ESP32. The implementation sends touch values via the ESPNOW protocol either to another ESP32 or a host computer at 100Hz.

  - firmware: Code that can be compiled with Arduino IDE and flashed to microcontroller.
  - receiver: Receiving code to be compiled on a Linux computer with a monitor-mode enabled Wifi card. 
  - data: Example data collected using the hardware pictured above.

# Visualized example data

<p align="center">
  <img src="images/swiping-plot-filtered.png" width="100%"/>
</p>
