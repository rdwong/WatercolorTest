#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    cv = new Canvas();
    initTouchGui();
    loadShaders();
    
    shader = new PingPongFbo();
    shader->clearFbos();
    
    dilate = new PingPongFbo();
    dilate->clearFbos();
}

//--------------------------------------------------------------
void ofApp::loadShaders()
{
    // Blurs
    blurV.load("shaders/blurV");
    blurH.load("shaders/blurH");
    bUseBlur = false;
    blurAmt = 3;
    blurRadius = 4;
    blurNumPasses = 2;
    
    // White to alpha
    whiteToAlpha.load("shaders/makeWhiteAlpha");
    
}

//--------------------------------------------------------------
void ofApp::initTouchGui()
{
    GUI.loadSettings();
    GUI.setItemWidth(200);
    GUI.setItemHeight(20);
    GUI.setItemSpacer(2);
    GUI.addButton("Save settings");
    GUI.addButton("Reload last save");
    
    GUI.addText("");
    GUI.addTitleText("BRUSH VARIABLES")->setBackgroundVisible(true);
    GUI.addSlider("Brush start radius", &CanvasVariables::startRadius, 0, 200);
    GUI.addSlider("Brush expansion rate", &CanvasVariables::expansionRate, 0, 10);
    GUI.addSlider("Brush expansion decay", &CanvasVariables::expansionDecay, 0.5, 0.999);
    GUI.addSlider("Min duration (frames)", &CanvasVariables::minDuration, 10, 500);
    GUI.addSlider("Max duration (frames)", &CanvasVariables::maxDuration, 200, 1000);
    
    GUI.addText("");
    GUI.addTitleText("BLUR VARIABLES")->setBackgroundVisible(true);
    GUI.addToggleButton("Toggle blur", &bUseBlur);
    GUI.addSlider("Blur strength", &blurAmt, 0, 20);
    GUI.addSlider("Blur radius", &blurRadius, 0, 10);
    GUI.addSlider("Number of Blur Passes", &blurNumPasses, 0, 10);
    
    GUI.addEventListenerAllItems(this);
};

//--------------------------------------------------------------
void ofApp::onGUIChanged(ofxTouchGUIEventArgs& args) {
    
    string buttonLabel = args.target->getLabel();
    if (buttonLabel == "Save settings") {
        GUI.saveSettings();
    }
    
    if (buttonLabel == "Reload last save") {
        GUI.resetFromSettings("settings.xml");
    }
    
}

//--------------------------------------------------------------
void ofApp::applyBlur()
{
    int numPasses = blurNumPasses;
    int amt = blurAmt;
    int radius = blurRadius;
    
    ofSetColor(255);
    for (int i = 0; i < numPasses; i++) {
        
        shader->swapFbos();
        shader->outFbo()->begin();
        blurH.begin();
        blurH.setUniform1f("amt", amt);
        blurH.setUniform1f("radius", radius);
        shader->inFbo()->draw(0, 0);
        blurH.end();
        shader->outFbo()->end();
        
        shader->swapFbos();
        shader->outFbo()->begin();
        blurV.begin();
        blurV.setUniform1f("amt", amt);
        blurV.setUniform1f("radius", radius);
        shader->inFbo()->draw(0, 0);
        blurV.end();
        shader->outFbo()->end();
        
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------

void ofApp::update(){
    
    cv->update();
    shader->castOutputFbo(cv->fbo);
    
    if (bUseBlur) applyBlur();
    
    // DILATE
    dilate->swapFbos();
    
    dilate->outFbo()->begin();
    if (ofGetFrameNum()%3 == 0)
        dilate->inFbo()->draw(-0.5, -0.5, ofGetWidth()+1, ofGetHeight()+1);
    else
        dilate->inFbo()->draw(0, 0);
    whiteToAlpha.begin();
    shader->outFbo()->draw(0, 0);
    whiteToAlpha.end();
    dilate->outFbo()->end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    dilate->outFbo()->draw(0, 0);
    
    GUI.draw();
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 1, ofGetHeight()-2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'c') cv->clear();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    cv->input(float(x), float(y));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

