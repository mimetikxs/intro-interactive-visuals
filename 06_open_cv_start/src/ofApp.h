#pragma once
#include "ofMain.h"
#include "ofxGui.h"
// ...

#define USE_RECORDING true

#if USE_RECORDING
#include "SourceRecording.h"
#else
#include "SourceWebcam.h"
#endif

class ofApp : public ofBaseApp
{
public:

    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    // ---------------------
    // video source
    // ---------------------

    const float videoDownscale = 0.5;

    int inputWidth;
    int inputHeight;    
    int scaledWidth;
    int scaledHeight;

    // source
    #if USE_RECORDING
    SourceRecording videoSource;
    #else
    SourceWebcam videoSource;
    #endif
    
    ofImage scaled;
    

    // ---------------------
    // video processing
    // ---------------------

    // ...

    // ---------------------
    // optical flow
    // ---------------------

    // ...

    // ---------------------
    // gui
    // ---------------------

    ofxPanel gui;

    bool bDrawGui;
    
};
