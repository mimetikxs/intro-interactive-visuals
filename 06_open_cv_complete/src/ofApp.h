#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

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

    ofImage  grey;

    ofPixels greyPrev;
    ofImage  diff;

    ofImage diffThresh;

    // ---------------------
    // optical flow
    // ---------------------

    ofxCv::FlowFarneback flow;

    ofFloatPixels flowPixels;
    ofTexture flowTex;

    void initFlow();

    // ---------------------
    // gui
    // ---------------------

    ofParameter<int> blurSize;
    ofParameter<float> thresholdValue;

    ofxPanel gui;

    bool bDrawGui;
    
};
