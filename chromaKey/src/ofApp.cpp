#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("ofxBluescreenApp");
    ofBackground(0,0,0);
    ofSetFrameRate(60);
//    grabber.initGrabber(640, 480);
    grabber.initGrabber(640, 480);
    greenScreen.setPixels(grabber.getPixels());
    
    bShowBg = false;
    for (int i = 0; i < 6; i++){
        bgImgs[i].load(std::to_string(i+1)+".jpg");
    }
    currentBg = bgImgs[0];
    stageNum = 0; //stage for backgrounds
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    if(grabber.isFrameNew()){
        greenScreen.setPixels(grabber.getPixels());
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    if(bShowBg){
//        replaceBg.draw(0, 0);
        float height = ofGetHeight() * currentBg.getWidth() / ofGetWidth();
        currentBg.draw(0, 0, ofGetWidth(), height);
    }
    
    greenScreen.draw(0, 0, ofGetWidth(), ofGetHeight());
    grabber.draw(0, 0, 160, 120);
    greenScreen.drawBgColor();
    
    
}

//--------------------------------------------------------------
void ofApp::stageChange(Stage _stage){
    switch (_stage) {
        case Stage::BG0:
            currentBg = bgImgs[1];
            break;
        case Stage::BG1:
            currentBg = bgImgs[2];
            break;
        case Stage::BG2:
            currentBg = bgImgs[3];
            break;
        case Stage::BG3:
            currentBg = bgImgs[4];
            break;
        case Stage::BG4:
            currentBg = bgImgs[5];
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == OF_KEY_UP)
//        greenScreen.setThreshold(greenScreen.getThreshold()+5);
//    if(key == OF_KEY_DOWN)
//        greenScreen.setThreshold(greenScreen.getThreshold()-5);
    
    if (key == OF_KEY_RIGHT){
        if (stageNum < 5){
            stageChange(static_cast<Stage>(stageNum));
            stageNum ++;
        } else {
            //change back to 1st img
            currentBg = bgImgs[0];
            stageNum = 0;
        }
    }
    
//    if (key == OF_KEY_LEFT){
//        if (stageNum > 0 && stageNum < 5){
//            stageChange(static_cast<Stage>(stageNum));
//            stageNum --;
//        } else {
//            //change back to 1st img
//            currentBg = bgImgs[5];
//            stageNum = 5;
//        }
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' '){
        greenScreen.learnBgColor(grabber.getPixels());
    }
    
    if(key == 'b'){
        bShowBg = !bShowBg;
    }
    
    if(key == 's'){
        time = ofGetCurrentTime();
        saveImg.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        saveImg.save("savedImgs/"+std::to_string(time.getAsSeconds())+".png");
    }
    
    
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
