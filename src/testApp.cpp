#include "testApp.h"
float pos_x = 0;
//--------------------------------------------------------------
void testApp::setup(){

	player.loadMovie("fingers.mov");
	player.play();
	led = new ofxLEDsLPD8806(64);
	for(int i = 0 ; i< 64 ; i++)
	{
		led->addLED(i,ofVec2f(50+20+(i%8)*40,	100+20+(i/8)*40));
	}
	ofSetFrameRate(25);
	
	serial.setup("/dev/tty.usbmodem5d11", 115200);

	ofSetLogLevel(OF_LOG_NOTICE);

}
void testApp::exit()
{
	
}
//--------------------------------------------------------------
void testApp::update(){
	pos_x = sin(ofGetElapsedTimef())*32+32;
	player.update();
	
	led->clear(0);
	led->clear(ofColor::black);
	led->renderBuffer.begin();
	for(int i = 0 ; i < 8 ; i++)
	{
		player.draw(i*8,-i, 8, 8);
	}
	
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofCircle(pos_x, 0, 5);
	
	ofPopStyle();
	led->renderBuffer.end();
	
	led->encode();
	serial.writeBytes((unsigned char*)led->txBuffer.data(), led->txBuffer.size());

}
//--------------------------------------------------------------
void testApp::draw(){

	ofPushMatrix();
	ofScale(10, 10);

	for(int i = 0 ; i < 8 ; i++)
	{
		player.draw(i*8,-i, 8, 8);
	}
	ofPushStyle();
	ofSetColor(255, 0, 0);
	ofCircle(pos_x, 0, 5);
	
	ofPopStyle();
	
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
		std::vector<uint8_t> latch(led->txBuffer.size(), 0);
		serial.writeBytes((unsigned char*)latch.data(), latch.size());
	}
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