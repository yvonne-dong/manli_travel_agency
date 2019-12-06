#pragma once

#include "ofxChromaKey.h"
#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
        ofxChromaKey greenScreen;
        ofVideoGrabber grabber;
        bool bShowBg;
        ofImage bgImgs[6];
        ofImage currentBg;
        ofImage saveImg;
        ofTime time; // names for saved images
        int stageNum;
        enum Stage {BG0,BG1,BG2,BG3,BG4};
        float bgWidth;
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        void stageChange(Stage _stage);
    
    
};
