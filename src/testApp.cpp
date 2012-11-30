#include "testApp.h"
float pos_x = 0;
int numLED = 64;
//--------------------------------------------------------------
void testApp::setup(){
	
	player.loadMovie("fingers.mov");
	player.play();
	led = new ofxLEDsLPD8806(numLED);
	for(int i = 0 ; i< numLED ; i++)
	{
		led->addLED(i,ofVec2f(50+20+(i%8)*40,	100+20+(i/8)*40));
	}
	ofSetFrameRate(25);
	
	serial.setup("/dev/tty.usbmodem5d11", 115200);
	
	ofSetLogLevel(OF_LOG_NOTICE);
	mode = 1;
	grabber.initGrabber(320,240);
}
void testApp::exit()
{
	
}
//--------------------------------------------------------------
void testApp::update(){
	grabber.update();
	pos_x = int(ofGetElapsedTimef()*32);//sin(ofGetElapsedTimef())*32+32;
	player.update();
	
	led->clear(0);
	led->clear(ofColor::black);
	led->renderBuffer.begin();
	
	//draw video as 8px width,height
	//draw line by line horizontally
	//[8 px first row ][8 px second row ]
	drawGraphic();
	led->renderBuffer.end();
	
	led->encode();
	serial.writeBytes((unsigned char*)led->txBuffer.data(), led->txBuffer.size());
	
}
void testApp::drawGraphic()
{
	switch(mode)
	{
		case 1:
			for(int i = 0 ; i < 8 ; i++)
			{
				player.draw(i*8,-i, 8, 8);
			}
			break;
		case 2:
		{
			ofPushStyle();
			ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			int step = 360/16.0;
			for(int i = 0 ; i < 16 ; i++)
			{
				ofSetColor(ofColor::fromHsb((i*step)%360, 255, 255),200);
				ofCircle(int(pos_x+i*4-16)%64, 0, 3);
			}
			ofDisableBlendMode();
			ofPopStyle();
		}
			break;
			case 3 :
			for(int i = 0 ; i < 8 ; i++)
			{
				grabber.draw(i*8,-i, 8, 8);
			}

			break;
	}
}
//--------------------------------------------------------------
void testApp::draw(){
	
	ofPushMatrix();
	ofScale(10, 10);
	//draw again to preview
	drawGraphic();
	led->encodedBuffer.draw(0,0);
	ofPopMatrix();
	
	ofPushStyle();
	ofNoFill();
	ofSetColor(0, 255, 0);
	ofRect(0,0,640,10);
	ofPopStyle();
	
	led->draw();
	
	//led->draw();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key==27)
	{
		memset(led->txBuffer.data(), 0, led->txBuffer.size());
		serial.writeBytes((unsigned char*)led->txBuffer.data(), led->txBuffer.size());
	}
	mode = key-'0';
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
	
}