//
//  Canvas.cpp
//  WatercolorTest
//
//  Created by Richard Wong on 12/5/17.
//
//

#include "Canvas.hpp"

namespace DropVariables
{
    
    float startRadius = 5;
    float expansionRate = 1.0;
    float expansionDecay = 0.96;
    float minDuration = 100;
    float maxDuration = 200;
    
}

// -------------------------------------------------

Drop::Drop(float xp, float yp):ofPoint(xp,yp)
{
    radius = DropVariables::startRadius;
    expansion = DropVariables::expansionRate;
    float min = DropVariables::minDuration;
    float max = MAX(DropVariables::maxDuration, min);
    life = (int)round(ofRandom(min, max));
}

void Drop::update()
{
    if (bDead()) return;
    radius += expansion;
    expansion *= DropVariables::expansionDecay;
    life--;
}

void Drop::draw()
{
    ofSetColor(0, 1);
    ofDrawCircle(x, y, DropVariables::startRadius);
    ofDrawCircle(x, y, DropVariables::startRadius*0.7);
    ofDrawCircle(x, y, DropVariables::startRadius*0.5);
    ofDrawCircle(x, y, DropVariables::startRadius*0.4);
}

// -------------------------------------------------

Canvas::Canvas()
{
    dilate.load("shaders/controlledDilate");
    
    baseFbo = new PingPongFbo();
}

void Canvas::input(float x, float y)
{
    drops.push_back(new Drop(x,y));
}

void Canvas::update()
{
    for (int i = drops.size()-1; i >= 0; i--) {
        
        if (!drops[i]->bDead()) {
            
            drops[i]->update();
            
            baseFbo->swapFbos();
            baseFbo->outFbo()->begin();
            dilate.begin();
            dilate.setUniform2f("wsize", ofVec2f(ofGetWidth(), ofGetHeight()));
            dilate.setUniform2f("dropPos", ofVec2f(drops[i]->x, drops[i]->y));
            dilate.setUniform1f("radius", drops[i]->radius);
            dilate.setUniform1f("amt", 0.5);
            
            baseFbo->inFbo()->draw(0, 0);
            drops[i]->draw();
            
            dilate.end();
            baseFbo->outFbo()->end();
            
        } else {
            
            delete drops[i];
            drops[i] = NULL;
            drops.erase(drops.begin() + i);
            
        }
        
    }
}




