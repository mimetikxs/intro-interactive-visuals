#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(0);
    ofSetVerticalSync(true);

    // ---------------------
    // forcefield
    // ---------------------

    // ...

    // ---------------------
    // gui
    // ---------------------        

    // ...

    gui.setup();
    
    bDrawGui = true;
}


void ofApp::update()
{
    // ...
}


void ofApp::draw()
{    
    // ...

    if (bDrawGui)
    {
        gui.draw();
    }
}


void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        bDrawGui = !bDrawGui;
        break;
    default:
        break;
    }
}

