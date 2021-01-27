#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ForcefieldFlow.h"

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

    const float videoDownscale = 0.2;

    // source
    #if USE_RECORDING
    SourceRecording videoSource;
    #else
    SourceWebcam videoSource;
    #endif
    
    // ---------------------
    // video processing
    // ---------------------

    ofImage scaled;
    ofImage grey;

    ofParameter<int> blurSize;

    // ---------------------
    // optical flow field
    // ---------------------

    ForcefieldFlow forcefieldFlow;

    bool bResetFlow = false;

    // drawing
    ofParameter<bool> bDrawPixels;
    ofParameter<bool> bDrawVectors;
    ofParameter<bool> bDrawGrid;
    ofParameter<float> vectorDrawSize;

    // ---------------------
    // gui
    // ---------------------

    ofxPanel gui;

    bool bDrawGui;
};
