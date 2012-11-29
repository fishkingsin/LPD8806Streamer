LPD8806Streamer
===============

build with openframeworks + addons ofxLEDs and arduino SPI bridge test with 64 LEDs
![wiring](http://i.imgur.com/WPyWS.jpg)

![video][https://vimeo.com/54499657]

!Example
```c++
	led->clear(0); //clear the previous frame
	led->clear(ofColor::black); 
	led->renderBuffer.begin(); 
	
	//draw your stuff here
	//remember it only one horizontal pixel 



	led->renderBuffer.end();

	led->encode();
	//send 200 byte (64*3 color pixel (192 byte) + latch heade(4byte) + latch end(4byte))
	serial.writeBytes((unsigned char*)led->txBuffer.data(), led->txBuffer.size());

``` 
