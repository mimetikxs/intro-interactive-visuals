#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"

#include "ParticleSystem.h"
#include "EmitterRect.h"
#include "ForceWind.h"
#include "RenderLines.h"
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
    // constants
    // ---------------------

    const float cameraWidth = 640;
    const float cameraHeight = 480;

    const float videoDownscale = 0.2;

    const float screenWidth = 1024;
    const float screenHeight = 768;

    const int numParticles = 20000;

    // ---------------------
    // video source
    // ---------------------

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

    ofParameter<bool> bDrawVectors;
    ofParameter<bool> bDrawGrid;
    ofParameter<float> vectorDrawSize;

    bool bResetFlow = false;

    void drawForcefield();

    // ---------------------
    // particle system
    // ---------------------
    
    ParticleSystem particleSystem;
    EmitterRect emitter;
    ForceWind forceWind;
    //ForceAttraction forceAttraction;

    // ---------------------
    // particle rendering
    // ---------------------

    RenderLines renderLines;

    ofFbo layerLines;

    ofParameter<float> lineTrails;

    // ---------------------
    // gui
    // ---------------------

    ofxPanel gui;
    bool bDrawGui;

    void buildGui();

    void loadPreset(int i);
};
