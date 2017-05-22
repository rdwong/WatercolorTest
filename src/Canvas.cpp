//
//  Canvas.cpp
//  WatercolorTest
//
//  Created by Richard Wong on 12/5/17.
//
//

#include "Canvas.hpp"

namespace CanvasVariables
{
    float startRadius = 20;
    float expansionRate = 1.0;
    float expansionDecay = 0.96;
    float minDuration = 200;
    float maxDuration = 400;
}

// -------------------------------------------------

Drop::Drop(float xp, float yp):ofPoint(xp,yp)
{
    radius = CanvasVariables::startRadius;
    expansion = CanvasVariables::expansionRate;
    float min = CanvasVariables::minDuration;
    float max = MAX(CanvasVariables::maxDuration, min);
    life = (int)round(ofRandom(min, max));
}

void Drop::update()
{
    radius += expansion;
    expansion *= CanvasVariables::expansionDecay;
    life--;
}

void Drop::draw()
{
    ofSetColor(0, 1);
    ofDrawCircle(x, y, radius);
    ofSetColor(0, 2);
    ofDrawCircle(x, y, radius*0.9);
    ofSetColor(0, 4);
    ofDrawCircle(x, y, radius*0.7);
    ofSetColor(0, 8);
    ofDrawCircle(x, y, radius*0.4);
}

// -------------------------------------------------

Canvas::Canvas()
{
    fbo = new ofFbo();
    fbo->allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    buffer = new ofFbo();
    buffer->allocate(fbo->getWidth(), fbo->getHeight(), GL_RGB);
    
    clear();
}

void Canvas::input(float x, float y)
{
    drops.push_back(new Drop(x,y));
}

void Canvas::update()
{
    // update drops onto fbo
    fbo->begin();
    ofClear(255);
    ofSetColor(255);
    buffer->draw(0, 0);
    
    for (int i = drops.size()-1; i >= 0; i--) {
        if (!drops[i]->bDead()) {
            drops[i]->update();
            drops[i]->draw();
        }
        //if (drops[i]->bDead()) {
        //    delete drops[i];
        //    drops[i] = NULL;
        //    drops.erase(drops.begin()+i);
        //}
    }
    fbo->end();
    
    // Refresh buffer
    buffer->begin();
    ofSetColor(255);
    fbo->draw(0, 0);
    buffer->end();
}

void Canvas::clear()
{
    fbo->begin();
    ofClear(255);
    fbo->end();
    
    buffer->begin();
    ofClear(255);
    buffer->end();
}

ofTexture & Canvas::getTexture()
{
    return fbo->getTexture();
}
