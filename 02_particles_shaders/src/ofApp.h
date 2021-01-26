#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "ParticleSystem.h"
#include "EmitterRect.h"
#include "ForceWind.h"
#include "ForceAttraction.h"
#include "RenderBasic.h"
#include "RenderPoints.h"
#include "RenderLines.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void update();
	void draw();
		
	void keyPressed(int key);
    void mouseMoved(int x, int y);

    // ---------------------
    // particle system
    // ---------------------
    
    float width;    //< particle system's size
    float height;   //

    ParticleSystem  particleSystem;

    EmitterRect     emitter;

    ForceWind       forceWind;
    ForceAttraction forceAttraction;

    // ---------------------
    // particle rendering
    // ---------------------

    //RenderBasic  renderBasic;
    RenderLines  renderLines;
    RenderPoints renderPoints;

    ofFbo layerLines;
    ofFbo layerPoints;

    ofParameter<float> lineTrails;

    // ---------------------
    // gui
    // ---------------------

    ofxPanel gui;
    bool bDrawGui;

    bool bDrawDebug;
    void drawDebug();

    void loadPreset(int i);
};
