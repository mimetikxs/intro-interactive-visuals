#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "ParticleSystem.h"
#include "EmitterRect.h"
#include "ForceWind.h"
#include "ForceAttraction.h"
#include "RenderLines.h"
#include "ForcefieldNoise.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void update();
	void draw();
		
	void keyPressed(int key);

    // ---------------------
    // particle system
    // ---------------------
    
    float width;    //< particle system's size
    float height;   //

    ParticleSystem particleSystem;

    EmitterRect emitter;

    ForceWind forceWind;
    ForceAttraction forceAttraction;

    // ---------------------
    // force fields
    // ---------------------

    ForcefieldNoise forcefield;
    
    const float cellSize = 20;

    ofParameterGroup groupForcefield;
    ofParameter<bool> bDrawVectors;
    ofParameter<bool> bDrawGrid;
    ofParameter<float> vectorDrawSize;

    void drawForcefield();

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

    bool bDrawDebug;

    void loadPreset(int i);
};
