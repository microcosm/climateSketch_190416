#include "ofApp.h"

void ofApp::setup(){
    ofToggleFullscreen();
    layer1.setup("rocks1.jpg");
    layer2.setup("rocks2.jpg");
    layer3.setup("rocks3.jpg");

    mask1.setup("rocks-mask1.jpg");
    mask2.setup("rocks-mask1.jpg");

    layer2.incrementTextureOffsetX(-0.04);
    layer3.incrementTextureScale(0.2);
    layer3.incrementTextureOffsetY(0.2);
    layer3.flipTexture(TEXTURE_FLIP_HORIZONTAL);

    mask.setup(3);
    count = 0;
}

void ofApp::update(){
    layer1.incrementTextureOffsetY(0.002);
    layer2.incrementTextureOffsetY(-0.004);
    layer3.incrementTextureOffsetX(-0.001);

    mask1.incrementTextureOffsetY(0.002);
    mask2.incrementTextureOffsetY(-0.002);
}

void ofApp::draw(){
    ofBackground(ofColor::black);

    //Layer 1
    mask.beginLayer(0);
    {
        ofSetColor(ofColor::black);
        if(count > 0) {
            ofSetColor(ofColor::red, count);
            count -= 24;
        } else if(ofRandom(1) < 0.015){
            ofSetColor(ofColor::red);
            count = ofRandom(255);
        }
        else if(ofRandom(1) < 0.025) ofSetColor(ofColor::white);
        layer2.draw();
    }
    mask.endLayer(0);
    
    //Layer 2
    mask.beginLayer(1);
    {
        ofSetColor(255, 0, 0);
        layer3.draw();
    }
    mask.endLayer(1);
    
    mask.beginMask(1);
    {
        mask1.draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        mask2.draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(0, 0, mask.getWidth() * 0.5, mask.getHeight());
    }
    mask.endMask(1);

    //Layer 3
    mask.beginLayer(2);
    {
        ofSetColor(ofColor::red);
        layer3.flipTexture(TEXTURE_FLIP_VERTICAL);
        layer3.draw();
        layer3.flipTexture(TEXTURE_FLIP_VERTICAL);
    }
    mask.endLayer(2);
    
    mask.beginMask(2);
    {
        mask1.draw();
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        mask2.draw();
        ofDisableBlendMode();
        ofSetColor(ofColor::black);
        ofDrawRectangle(mask.getWidth() * 0.5, 0, mask.getWidth(), mask.getHeight());
    }
    mask.endMask(2);

    //Draw it
    mask.draw();
    mask.drawOverlay();
}

void ofApp::keyPressed(int key){
    if(key == ' '){
        mask.toggleOverlay();
    }
}
