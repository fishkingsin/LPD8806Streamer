LPD8806Streamer
===============

build with openframeworks + addons ofxLEDs and arduino SPI bridge test with 64 LEDs]
# Wiring #

![wiring](http://i.imgur.com/WPyWS.jpg)

# Video #
![video][https://vimeo.com/54499657]

# Example #
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

## Last but not least ##
I am try to find out how many led can the code support 
please give me feed back when you have any problem and suggestion
many thanks

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/fishkingsin/lpd8806streamer/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

