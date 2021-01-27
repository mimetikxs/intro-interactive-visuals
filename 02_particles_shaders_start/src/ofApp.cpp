#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(0);
    ofSetVerticalSync(true);

    // ---------------------
    // particle system
    // ---------------------

    // system size
    width = 1024;
    height = 768;

    // create emmiters
    emitter.setup("emitter");
    emitter.width = width;
    emitter.height = height;
    
    // create forces
    forceWind.setup("wind");
    forceWind.force = vec2(0.0, 0.1);

    forceAttraction.setup("attraction");
    forceAttraction.x = width / 2;
    forceAttraction.y = height / 2;
    forceAttraction.nearDistance = 50;
    forceAttraction.farDistance = 600;

    // create system and add emitters and forces
    particleSystem.setup(width, height, 50000);
    particleSystem.addEmitter(&emitter);
    particleSystem.addForce(&forceWind);
    particleSystem.addForce(&forceAttraction);

    // ---------------------
    // particle rendering
    // ---------------------

    // ...

    // ---------------------
    // gui
    // ---------------------

    gui.setup();    
    gui.add(particleSystem.parameters);
    gui.add(emitter.parameters);
    gui.add(forceWind.parameters);
    gui.add(forceAttraction.parameters);
    // ...
    
    bDrawGui = true;

    bDrawDebug = false;

    // ...
}


void ofApp::update()
{
    particleSystem.update();
    
    // ...
}


void ofApp::draw()
{    
    // ...

    if (bDrawDebug)
    {
        drawDebug();
    }

    if (bDrawGui)
    {
        gui.draw();
    }
}


void ofApp::drawDebug()
{
    ofPushStyle();
    ofNoFill();
    ofSetColor(ofColor::green);
    emitter.draw();
    ofSetColor(ofColor::magenta);
    forceWind.draw();
    forceAttraction.draw();
    ofPopStyle();
}


void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        bDrawGui = !bDrawGui;
        break;
    case 'd':
        bDrawDebug = !bDrawDebug;
        break;
    // ...
    default:
        break;
    }
}


void ofApp::mouseMoved(int x, int y)
{
    // ...
}
