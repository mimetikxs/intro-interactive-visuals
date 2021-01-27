#pragma once
#include "ofMain.h"
// ...

class ofApp : public ofBaseApp
{
public:

    void setup();
    void update();
    void draw();
        
    // ---------------------
    // video
    // ---------------------

    int inputWidth;
    int inputHeight;

    const float videoDownscale = 0.5;
    int scaledWidth;
    int scaledHeight;

    // sources
    // ...
    
    
};
