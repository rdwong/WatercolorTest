#pragma once

#include "ofMain.h"
#include "Canvas.hpp"
#include "ofxTouchGUI.h"
#include "PingPong.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
    Canvas* cv;
    ofxTouchGui GUI;
    
    
    // GUI STUFF
    void onGUIChanged(ofxTouchGUIEventArgs & args);
    void initTouchGui();
    
    // BLUR STUFF
    ofShader blurV;
    ofShader blurH;
    void loadShaders();
    void applyBlur();
    bool bUseBlur;
    int blurAmt;
    int blurRadius;
    int blurNumPasses;
    
    // ALPHA REMOVAL
    ofShader whiteToAlpha;
    
    // NOISE STUFF
    ofShader noise;
    
    // PING PONG
    PingPongFbo* shader;
    PingPongFbo* dilate;
    
};
