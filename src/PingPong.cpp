//
//  PingPong.cpp
//  WatercolorTest
//
//  Created by Richard Wong on 17/5/17.
//
//

#include "PingPong.hpp"

PingPongFbo::PingPongFbo()
{
    fbo[0] = new ofFbo();
    fbo[0]->allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo[1] = new ofFbo();
    fbo[1]->allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    zOrder[0] = 0;
    zOrder[1] = 1;
}

ofFbo* PingPongFbo::inFbo()
{
    return fbo[zOrder[0]];
}

ofFbo* PingPongFbo::outFbo()
{
    return fbo[zOrder[1]];
}

void PingPongFbo::swapFbos()
{
    zOrder[0] = zOrder[1];
    zOrder[1] = (zOrder[0] == 0) ? 1 : 0;
}

void PingPongFbo::castOutputFbo(ofFbo* addThis, bool bClearPrevious)
{
    outFbo()->begin();
    if (bClearPrevious) ofClear(255);
    addThis->draw(0, 0);
    outFbo()->end();
}

void PingPongFbo::clearFbos()
{
    for (int i = 0; i < 2; i++){
        fbo[i]->begin();
        ofClear(255);
        fbo[i]->end();
    }
}