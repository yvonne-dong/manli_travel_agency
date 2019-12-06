#include "ofxChromaKey.h"

ofxChromaKey::ofxChromaKey():threshold(50),checkForHighest(true) {
//*** bgColor.set(0, 0, 255);
    bgColor.set(0, 255, 0);
}

ofxChromaKey::~ofxChromaKey() {
}

void ofxChromaKey::learnBgColor(ofPixelsRef pixelSource) {
	int dimensions = pixelSource.getWidth() * pixelSource.getHeight();
    //*** pixelSource.getBytesPerPixel() returns 3 channels rgb
//    int numPixels = dimensions * pixelSource.getBytesPerPixel();
    int numPixels = dimensions * 3;
	int r,g,b;
    r = 0;
    g = 0;
    b = 0;
    
    for (int i=0; i<numPixels; i += 3) {
//    for (int i=0; i<numPixels; i += pixelSource.getBytesPerPixel()) {
		r += pixelSource[i];
		g += pixelSource[i+1];
		b += pixelSource[i+2];
	}
	r /= dimensions;
	g /= dimensions;
	b /= dimensions;
	bgColor.set(r, g, b);
	update();
}

void ofxChromaKey::setBgColor(ofColor col) {
	bgColor = col;
	update();
}

//*** if this is deprecated can we remove it?
void ofxChromaKey::setPixels(ofPixelsRef pixels) {
	pixelSource.setFromPixels(pixels.getPixels(), pixels.getWidth(), pixels.getHeight(), OF_IMAGE_COLOR);//pixels.getBitsPerPixel());
	update();
}

void ofxChromaKey::setPixels(unsigned char* pixels, int w, int h) {
	pixelSource.setFromPixels(pixels, w, h, OF_IMAGE_COLOR);
	update();
}

void ofxChromaKey::setThreshold(float thresh) {
	threshold = thresh;
	update();
}

void ofxChromaKey::update() {
	int highestKey = 0;

	float highest = bgColor[highestKey];
	for(int i = 1; i < 3; i ++) {
		if(bgColor[i] > highest) {
			highestKey=i;
			highest = bgColor[i];
		}
	}

	//allocate(pixelSource.getWidth(), pixelSource.getHeight(), OF_IMAGE_COLOR_ALPHA);
	int dimensions = pixelSource.getWidth() * pixelSource.getHeight();
    
    // *** rgba
	int numPixels = dimensions * 4;
	unsigned char* pixels = new unsigned char[numPixels];
	ofColor c;
	int index=0;
    for (int i=0; i< dimensions * 3; i += 3) {
//    for (int i=0; i< dimensions * 3; i+=pixelSource.getBytesPerPixel()) {
		c.set(pixelSource[i], pixelSource[i+1], pixelSource[i+2]);
		int alpha = 255;
		bool chromaIsHighest = true;
		if(checkForHighest)
			chromaIsHighest = ( c[highestKey] > c[(highestKey+1) % 3] && c[highestKey] > c[(highestKey+1) % 3] );
		if(fabs(c.getHue()-bgColor.getHue())<threshold && chromaIsHighest)
			alpha=0;



		pixels[index] = c.r;
		pixels[index+1] = c.g;
		pixels[index+2] = c.b;
		pixels[index+3] = alpha;
		index+=4;
	}
	setFromPixels(pixels, pixelSource.getWidth(), pixelSource.getHeight(), OF_IMAGE_COLOR_ALPHA);
    delete[] pixels;
//***  delete pixels;
}

void ofxChromaKey::drawBgColor(int x, int y, int w, int h) {
	ofFill();
	ofSetColor(bgColor);
	ofDrawRectangle(x, y, w, h);
}

void ofxChromaKey::drawCheckers(int x, int y, int w, int h) {
	int rectSize = 10;
//    ofColor a(30);
//    ofColor b(255);
    ofColor(0, 0, 0, 0);
	ofFill();
	int maxH=h/rectSize;
	int maxW=w/rectSize;
    ofDrawRectangle(0, 0, maxW, maxH);
//    for(int iy=0; iy<maxH; iy++) {
//        for(int ix=0; ix<maxW; ix++) {
//            if(iy%2==0)
//                ix%2==0?ofSetColor(a):ofSetColor(b);
//            else
//                ix%2==0?ofSetColor(b):ofSetColor(a);
//            ofRect(x+ix*rectSize, y+iy*rectSize, rectSize, rectSize);
//        }
//    }
}

void ofxChromaKey::draw(int x, int y, int w, int h, bool checkers) {
	ofEnableAlphaBlending();
	if(checkers)
		drawCheckers(x, y, w, h);
	ofSetColor(255);
	ofImage::draw(x, y, w, h);
}

float ofxChromaKey::getThreshold() {
	return threshold;
}

ofColor ofxChromaKey::getBgColor()
{
	return bgColor;
}
