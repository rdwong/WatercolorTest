//
//  Canvas.hpp
//  WatercolorTest
//
//  Created by Richard Wong on 12/5/17.
//
//

#ifndef Canvas_hpp
#define Canvas_hpp

#include "ofMain.h"

namespace CanvasVariables {
    extern float startRadius;
    extern float expansionRate;
    extern float expansionDecay;
    extern float minDuration;
    extern float maxDuration;
}

class Drop : public ofPoint {
    
public:
    float radius;
    float expansion;
    int life;
    Drop(float xp, float yp);
    void update();
    bool bDead() { return life <= 0; }
    void draw();
    
};

class Canvas
{
public:
    
    vector<Drop*> drops;
    ofFbo* fbo;
    ofFbo* buffer;
    
    Canvas();
    
    void update();
    
    void input(float x, float y);
    void clear();
    
    ofTexture & getTexture();
    
};

#endif /* Canvas_hpp */
