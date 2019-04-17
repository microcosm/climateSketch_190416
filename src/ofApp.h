#pragma once

#include "ofMain.h"
#include "ofxTexturePlane.h"
#include "ofxLayerMask.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    ofxTexturePlane layer1, layer2, layer3;
    ofxTexturePlane mask1, mask2;
    ofxLayerMask mask;
    int count;
};
