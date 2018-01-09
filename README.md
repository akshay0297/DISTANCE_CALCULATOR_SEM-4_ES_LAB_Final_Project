# DISTANCE_CALCULATOR_SEM-4_ES_LAB_Final_Project

AIM/OBJECTIVE : 
This project aims in developing a long-range highly cost-effective distance calculator using an ULTRASONIC SEONSOR (HC-SR04) and LPC1768 in Keil.

TECHICAL DETAILS : 
The underlying phenomenon is using the Ultrasonic sensing principle.
The ultrasonic waves are sounds of frequencies above 20 kHz, which can’t be heard by humans. The applied methodology is based on measuring the pulse reflection time. The sensor emits the sound waves and becomes quiet in order to receive the object echoes. Once the sound wave hit the obstacle, the reflected waves are echoes.
This sensor cannot be used to detect the object made of a cloth, cotton and wool as these objects absorb majority of the waves.
The time gap between the transmitted wave and the reflected wave is used to calculate the distance of the obstacle from the source using the formula
d=t*v/2
Where d = distance, t = time gap, v = velocity of sound in air.
As velocity of sound in air is affected by the Temperature of the surrounding, it can be given by 
v=331.3+0.606*T
Where v = apparent velocity, T = Room temperature ≈ 24°C

 The sensor HC-SR04 has 4 port pins 1.VCC 2.Trigger 3.Echo 4.Ground
VCC and Ground pins are connected to any two port pins that are provided with active high (1) and active low (0) input respectively. The Trigger pin is connected to the Digital to Analog Converter (DAC) which generates the Transistor-Transistor Logic (TTL) Pulse of 10µs as input to the Trigger pin.  A Transducer present in the sensor converts the electrical signals at the Trigger pin to the mechanical waves and vice versa. As the mechanical waves are generated and transmitter the Timer in the MICROCONTROLLER is started. The Echo pin is attached to the Analog to Digital Converter (ADC) and whenever the reflected signal hits the transducer an analog signal is generated at the Echo pin. The generated signal is then passed through ADC and as the intensity of received signal a sufficient value, an interrupt is generated and the Timer is stopped. The Time is then extracted from the microcontroller and distance is calculated using the formula
d=t*v/2
The Range of the Sensor (HC-SR04) is from 2cm – 4m.
The calculated distance can be displayed using either LCD or LED interface present in LPC-1768 Microcontroller. 

INSTALLATION AND WORKING : 
To see how the project is working,download the zip file from the link https://goo.gl/6EEP2u .After downloading extract the files and run the application MDK470a.exe (if you have LPC1768 microcontroller with you then run the application "Flash Magic VER 7.85".)
After Keil is successfully installed open the "distcal.uvproj" file and if you only want to see the source code open the "distcalc.c" in your favourite editor.
