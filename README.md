# Drone-Control
This repo contains the necessities regarding my drone,

There are several stages of this project and these are as:

1. Transreciever 
    a. Webserver, serving two joysticks, for controlling Throttle, Yaw, Roll and Pitch of the drone, via 'TouchEvent' and 
      'KeyboardActivity'.
    b. NodeMCU or ESP32 as an access point, pulling the data from user inputs.

2. MPU6050 and BMP180 for obtaining Accelometer data, gyro data and altitude, for drone stability.
3. PID Controlling and necessary other filters.
4. Final tuned PID, program.
