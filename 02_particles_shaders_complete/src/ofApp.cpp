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

    //renderBasic.setup("render basic");

    renderLines.setup("render lines");
    renderPoints.setup("render points");

    layerLines.allocate(width, height, GL_RGBA32F);
    layerPoints.allocate(width, height);

    // ---------------------
    // gui
    // ---------------------

    gui.setup();    
    gui.add(particleSystem.parameters);
    gui.add(emitter.parameters);
    gui.add(forceWind.parameters);
    gui.add(forceAttraction.parameters);
    //gui.add(renderBasic.parameters);
    gui.add(renderLines.parameters);
    gui.add(renderPoints.parameters);
    gui.add(lineTrails.set("line trails", 0.0, 0.0, 1.0));
    gui.minimizeAll();    
    
    bDrawGui = true;

    bDrawDebug = false;

    // load preset
    loadPreset(1);
}


void ofApp::update()
{
    particleSystem.update();
    
    //renderBasic.update(particleSystem.getParticleData());
    renderLines.update(particleSystem.getParticleData());
    renderPoints.update(particleSystem.getParticleData());
}


void ofApp::draw()
{    
    //renderBasic.draw();

    layerLines.begin();
    {
        ofFill();
        ofSetColor(0,0,0, (1.0 - lineTrails) * 255);
        ofDrawRectangle(0, 0, width, height);

        renderLines.draw();
    }
    layerLines.end();    
    layerLines.draw(0, 0);

    layerPoints.begin();
    {
        ofClear(0.0);
        renderPoints.draw();
    }
    layerPoints.end();
    layerPoints.draw(0, 0);

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
    case '1':
        loadPreset(1);
        break;
    case '2':
        loadPreset(2);
        break;
    case '3':
        loadPreset(3);
        break;
    case '4':
        loadPreset(4);
        break;
    default:
        break;
    }
}


void ofApp::mouseMoved(int x, int y)
{
    if (ofGetKeyPressed(OF_KEY_SHIFT))
    {
        forceAttraction.x = x;
        forceAttraction.y = y;

        emitter.x = x - emitter.width / 2;
        emitter.y = y - emitter.height / 2;
    }
}



void ofApp::loadPreset(int i)
{
    gui.loadFromFile("settings-" + ofToString(i) + ".xml");

    vec2 screenCenter(width / 2, height / 2);
    
    forceAttraction.x = screenCenter.x;
    forceAttraction.y = screenCenter.y;

    emitter.x = screenCenter.x - emitter.width / 2;
    emitter.y = screenCenter.y - emitter.height / 2;
}