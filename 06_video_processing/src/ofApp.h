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

    ofxPanel gui;
    bool bDrawGui = true;

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
    
    // flow parameters
    ofParameterGroup   parameters;
    ofParameter<float> pyrScale;
    ofParameter<int>   levels;
    ofParameter<int>   winsize;
    ofParameter<int>   iterations;
    ofParameter<int>   polyN;
    ofParameter<float> polySigma;
    ofParameter<bool>  useFarnelGaussian;

    // parameter listeners
    void pyrScaleChange(float& val) { flow.setPyramidScale(val); }
    void levelsChange(int& val) { flow.setNumLevels(val); }
    void winsizeChange(int& val) { flow.setWindowSize(val); }
    void iterationsChange(int& val) { flow.setNumIterations(val); }
    void polyNChange(int& val) { flow.setPolyN(val); }
    void polySigmaChange(float& val) { flow.setPolySigma(val); }
};
