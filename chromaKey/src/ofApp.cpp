#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxBluescreenApp");
    ofBackground(0,0,0);
    ofSetFrameRate(60);
    grabber.initGrabber(640, 480);
    bluescreen.setPixels(grabber.getPixels());
    
    bShowBg = false;
    replaceBg.load("bg.jpg");
//    bgWidth = 640 * replaceBg.getHeight() / 480;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew())
        bluescreen.setPixels(grabber.getPixels());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if(bShowBg)
        replaceBg.draw(0, 0);
    bluescreen.draw(0, 0, 640, 480);
    grabber.draw(0, 0, 160, 120);
    bluescreen.drawBgColor();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == OF_KEY_UP)
        bluescreen.setThreshold(bluescreen.getThreshold()+5);
    if(key == OF_KEY_DOWN)
        bluescreen.setThreshold(bluescreen.getThreshold()-5);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' ')
        bluescreen.learnBgColor(grabber.getPixels());
    
    if(key == 'b')
        bShowBg = !bShowBg;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
