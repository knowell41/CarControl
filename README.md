# CarControl

This Ardiono Sketch file is for ESP8226 nodeMCU.
Twin motor attached using the L291 motor drive module;

IN1 -----------> D0
IN2 -----------> D1
IN3 -----------> D2
IN4 -----------> D3

keep the EN1 and EN2 connetec via jumper.


ESP module will wait for the incomming packet and control the motor according to the data received.

Sample Data;

F,500,500
Direction,R-speed,L-speed

the car will move forwarad with the speed of left and right wheel at 500PWM(half-speed).
By varying the R-speed and L-speed, you can control the car to turn right or left.
