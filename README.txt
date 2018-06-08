Communication between RPI and ESP32 with the help of router


espI2C : I2C communication between 3 encoders(STM32) and esp32.
	Configuration of Encoders with STM32
   
	All the signals pins to be pulled up using 680ohm.

   
	Encoder X-Green to PB8
             White to PB9 
	Encoder Y1-Green to PB12
            White to PB13

   
	Encoder Y5-Green to PB5
             White to PB15

ESP_PI_SERVERL: Communication between RPI and Esp32 using TCP.
		The Gcode is recieved line by line from PI and transmitted to GRBL line by line.

mainCode: Test code to be uploaded on esp32. it will connect you on wifi and assign you IP, then you can use this ip to connect from RPI