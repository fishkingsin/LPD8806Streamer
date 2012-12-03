#include "testApp.h"
float pos_x = 0;
int row = 1;
int col = 64;
int numLED = col*row;
int SQAURE_ROOT =int(sqrt((float)col));
float ptSize = 5;
//--------------------------------------------------------------
void testApp::setup(){
	
	player.loadMovie("fingers.mov");
	player.play();
	led = new ofxLEDsLPD8806(numLED);
	for(int i = 0 ; i< numLED ; i++)
	{
		float x = 50+20+(i%col)*ptSize;
		float y = 100+20+(i/col)*ptSize;
		led->addLED(i,ofVec2f(x,y));
	}
	ofSetFrameRate(25);
	
	serial.listDevices();
	serial.setup(serial.getDeviceList()[0].getDeviceName(), 115200);
	
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
			for(int i = 0 ; i < SQAURE_ROOT ; i++)
			{
				player.draw(i*SQAURE_ROOT,-i, SQAURE_ROOT, SQAURE_ROOT);
			}
			break;
		case 2:
		{
			ofPushStyle();
			ofEnableBlendMode(OF_BLENDMODE_ALPHA);
			int step = 360.0/SQAURE_ROOT;
			for(int i = 0 ; i < 1 ; i++)
			{
				ofSetColor(ofColor::fromHsb((i*step)%360, 255, 255),200);
				ofCircle(int(pos_x+i*(SQAURE_ROOT)-16)%numLED, 0, SQAURE_ROOT*0.5);
			}
			ofDisableBlendMode();
			ofPopStyle();
		}
			break;
			case 3 :
			for(int i = 0 ; i < SQAURE_ROOT ; i++)
			{
				grabber.draw(i*SQAURE_ROOT,-i, SQAURE_ROOT, SQAURE_ROOT);
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
//	led->encodedBuffer.draw(0,0);
	ofPopMatrix();
	
	ofPushStyle();
	ofNoFill();
	ofSetColor(0, 255, 0);
	ofRect(0,0,numLED*10,10);
	ofPopStyle();
	
	led->draw(ptSize);
	
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