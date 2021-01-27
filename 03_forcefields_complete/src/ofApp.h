#pragma once
#include "ofMain.h"
#include "ofxGui.h"

#include "Forcefield.h"
#include "ForcefieldNoise.h"

class ofApp : public ofBaseApp
{
public:

	void setup();
	void update();
	void draw();    

    void keyPressed(int key);

    // ---------------------
    // forcefield
    // ---------------------
    
    //Forcefield forcefield;
    ForcefieldNoise forcefield;

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
