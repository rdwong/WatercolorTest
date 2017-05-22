//
//  PingPong.hpp
//  WatercolorTest
//
//  Created by Richard Wong on 17/5/17.
//
//

#ifndef PingPong_hpp
#define PingPong_hpp

#include "ofMain.h"

class PingPongFbo
{
public:
    
    
    ofFbo* fbo[2];
    int zOrder[2];
    ofFbo* inFbo();
    ofFbo* outFbo();
    void swapFbos();
    void castOutputFbo(ofFbo* addThis, bool bClearPrevious=false);
    void clearFbos();
    
    PingPongFbo();
    
};

#endif /* PingPong_hpp */
