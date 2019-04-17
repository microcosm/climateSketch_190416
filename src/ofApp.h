#pragma once

#include "ofMain.h"
#include "ofxTexturePlane.h"
#include "ofxLayerMask.h"

enum csLoadingMode {
    LOAD_INCREMENTAL,
    LOAD_IDENTICAL
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void loadFiles(string baseFilename, int count, vector<ofxTexturePlane>& collection, csLoadingMode mode=LOAD_INCREMENTAL);
    void update();
    void draw();
    void keyPressed(int key);

    ofxTexturePlane blankSlate;
    vector<ofxTexturePlane> rockLayers;
    vector<ofxTexturePlane> rockMasks;
    vector<ofxTexturePlane> skylineLayers;
    vector<ofxTexturePlane> skylineMasks;
    ofxLayerMask masker;
    int colorFlashCount;
    int skylineNumber;
};
