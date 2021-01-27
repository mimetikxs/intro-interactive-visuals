#pragma once
#include "ofMain.h"
#include "SourceWebcam.h"
#include "SourceRecording.h"

class ofApp : public ofBaseApp
{
public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
        
    // ---------------------
    // video
    // ---------------------

    int inputWidth;
    int inputHeight;

    const float videoDownscale = 0.5;
    int scaledWidth;
    int scaledHeight;

    // sources
    //SourceWebcam videoSource;
    SourceRecording videoSource;
    
    ofPixels pixelsScaled;
    ofTexture textureScaled;
    
    
};
