#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    loadFiles("rocks", 3, rockLayers);
    loadFiles("rocks-mask", 2, rockMasks, LOAD_IDENTICAL);
    loadFiles("week4skyline", 6, skylineLayers);
    loadFiles("week4skyline", 6, skylineMasks);

    rockLayers[1].incrementTextureOffsetX(-0.04);
    rockLayers[2].incrementTextureScale(0.2);
    rockLayers[2].incrementTextureOffsetY(0.2);
    rockLayers[2].flipTexture(TEXTURE_FLIP_HORIZONTAL);

    masker.setup(4);

    manualSkyline = true;
    colorFlashCount = 0;
    skylineNumber = 0;
}

void ofApp::loadFiles(string baseFilename, int count, vector<ofxTexturePlane>& collection, csLoadingMode mode){
    string fileIndex;
    for(int i = 1; i <= count; i++){
        fileIndex = mode == LOAD_INCREMENTAL ? ofToString(i) : "";
        collection.push_back(blankSlate);
        collection.back().setup(baseFilename + fileIndex + ".jpg");
    }
}

void ofApp::update(){
    rockLayers[0].incrementTextureOffsetY(0.002);
    rockLayers[1].incrementTextureOffsetY(-0.004);
    rockLayers[2].incrementTextureOffsetX(-0.001);

    rockMasks[0].incrementTextureOffsetY(0.002);
    rockMasks[1].incrementTextureOffsetY(-0.002);
}

void ofApp::draw(){
    ofBackground(ofColor::black);

    //Layer 1
    masker.beginLayer(0);
    {
        ofSetColor(ofColor::black);
        if(colorFlashCount > 0) {
            ofSetColor(ofColor::red, colorFlashCount);
            colorFlashCount -= 24;
        } else if(ofRandom(1) < 0.015){
            ofSetColor(ofColor::red);
            colorFlashCount = ofRandom(255);
        }
        else if(ofRandom(1) < 0.025) ofSetColor(ofColor::white);
        rockLayers[1].draw();
    }
    masker.endLayer(0);
    
    //Layer 2
    masker.beginLayer(1);
    {
        ofSetColor(255, 0, 0);
        rockLayers[2].draw();
    }
    masker.endLayer(1);
    
    masker.beginMask(1);
    {
        rockMasks[0].draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        rockMasks[1].draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(0, 0, masker.getWidth() * 0.5, masker.getHeight());
    }
    masker.endMask(1);

    //Layer 3
    masker.beginLayer(2);
    {
        ofSetColor(ofColor::red);
        rockLayers[2].flipTexture(TEXTURE_FLIP_VERTICAL);
        rockLayers[2].draw();
        rockLayers[2].flipTexture(TEXTURE_FLIP_VERTICAL);
    }
    masker.endLayer(2);
    
    masker.beginMask(2);
    {
        rockMasks[0].draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        rockMasks[1].draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(masker.getWidth() * 0.5, 0, masker.getWidth(), masker.getHeight());
    }
    masker.endMask(2);

    if(skylineNumber >= 0 && skylineNumber <= 5){
        masker.beginLayer(3);
        {
            ofBackground(ofColor::black);
            //skylineLayers[ofGetFrameNum() % 6].draw();
            skylineLayers[skylineNumber].draw();
        }
        masker.endLayer(3);
        
        masker.beginMask(3);
        {
            ofBackground(ofColor::black);
            //skylineMasks[ofGetFrameNum() % 6].draw();
            skylineLayers[skylineNumber].draw();
        }
        masker.endMask(3);
    }

    //Draw it
    masker.draw();
    masker.drawOverlay();
}

void ofApp::keyPressed(int key){
    if(key == ' '){
        masker.toggleOverlay();
    }else{
        cout << key - 49 << endl;
        skylineNumber = key - 49;
        manualSkyline = skylineNumber >= 0 && skylineNumber <= 5;
    }
}
