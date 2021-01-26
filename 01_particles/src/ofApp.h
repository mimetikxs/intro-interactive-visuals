#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "ParticleSystem.h"
#include "EmitterRect.h"
#include "ForceWind.h"
#include "ForceAttraction.h"

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
    // particle rendering
    // ---------------------

    ofMesh mesh;

    // ---------------------
    // gui
    // ---------------------

    ofxPanel gui;
    bool bDrawGui;

    bool bDrawDebug;
    void drawDebug();
};
