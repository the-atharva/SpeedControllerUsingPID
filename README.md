# SpeedControllerUsingPID
Speed of DC motor remains constant if power supply or load requirements are changed. This is achieved using a feedback system. IR sensor is used as tachometer sensor to determine speed of motor. Esp32 is used to calculate instantaneous speed of motor & implement PID controller for real time speed correction. An amplifier is used to drive the motor & an optoisolator to isolate the control circuit and power circuit.\
The program also has code for visualising the speed of the motor in real time.\
The project setup is generalizable for any motor, any rpm & any power supply or load requirements under the constraints of respective components. The PID controller has to be tuned for specific desired rpm.\
The project aims to reduce overshoot & steady state error.\
This project was made as my third year mini project for partial fulfillment of credits.
## Working block diagram
<p align="center">
![block diagram](https://github.com/user-attachments/assets/76ae8bf1-495e-4561-bc74-33e919cecf26)
</p>

## Circuit diagram
<p align="center">
![circuit diagram](https://github.com/user-attachments/assets/dfc47880-1a98-41b3-81a5-c638b774bb11)
</p>
The pin numbers are not accurate according to footprint.

## 3D view of PCB
<p align="center">
![3d circuit view](https://github.com/user-attachments/assets/92edd2b6-5a13-4a26-9f8f-d058ecfd8842)
</p>

## PCB footprint
<p align="center">
![pcb design](https://github.com/user-attachments/assets/01e96f29-ecf6-4859-82fd-980177f293a8)
</p>

## Completed project photo
<p align="center">
![project photo](https://github.com/user-attachments/assets/5e626c73-4d41-4322-9896-427eaf81ba65)
</p>

## Screenshot of real time plotting of the project
<p align="center">
![live plotting screenshot](https://github.com/user-attachments/assets/43cd7920-9deb-4ecd-919c-0770c7b4fff8)
</p>

## Future Scope
1. Calculate peak overshoot(if any), response time, steady state error etc.\
2. Auto tune PID controller.\
3. Implement digital low pass filter.\
4. Use hall effect sensor instead of IR sensor.\
5. Make motor rotation bi directional using H bridge.
