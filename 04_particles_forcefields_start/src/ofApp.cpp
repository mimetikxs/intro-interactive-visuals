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

    forceAttraction.setup("attraction");
    forceAttraction.x = width / 2;
    forceAttraction.y = height / 2;
    forceAttraction.nearDistance = 50;
    forceAttraction.farDistance = 600;

    // forcefield    
    forcefield.setup(width / cellSize, height / cellSize, width, height);
    forcefield.updateNoise();

    // create system and add emitters and forces
    particleSystem.setup(width, height, 50000);
    particleSystem.addEmitter(&emitter);
    particleSystem.addForce(&forceWind);
    particleSystem.addForce(&forceAttraction);
    // ...

    // ---------------------
    // particle rendering
    // ---------------------

    renderLines.setup("render lines");

    layerLines.allocate(width, height, GL_RGBA32F);

    // ---------------------
    // gui
    // ---------------------

    gui.setup();    
    gui.add(particleSystem.parameters);
    gui.add(emitter.parameters);
    gui.add(forceWind.parameters);
    gui.add(forceAttraction.parameters);
    gui.add(renderLines.parameters);
    gui.add(lineTrails.set("line trails", 0.0, 0.0, 1.0));
    
    groupForcefield.setName("forcefield");
    groupForcefield.add(forcefield.noiseScale);
    groupForcefield.add(forcefield.noiseSpeed);
    groupForcefield.add(forcefield.forceScale);
    groupForcefield.add(bDrawGrid.set("draw grid", false));
    groupForcefield.add(bDrawVectors.set("draw vectors", false));
    groupForcefield.add(vectorDrawSize.set("drawn vector size", 10.0, 1.0, 50.0));

    gui.add(groupForcefield);

    gui.minimizeAll();
    
    bDrawGui = true;

    bDrawDebug = false;
}


void ofApp::update()
{
    forcefield.updateNoise();

    particleSystem.update();
    
    renderLines.update(particleSystem.getParticleData());
}


void ofApp::draw()
{  
    layerLines.begin();
    {
        ofFill();
        ofSetColor(0,0,0, (1.0 - lineTrails) * 255);
        ofDrawRectangle(0, 0, width, height);

        renderLines.draw();
    }
    layerLines.end();    
    layerLines.draw(0, 0);

    drawForcefield();
        
    if (bDrawDebug)
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

    if (bDrawGui)
    {
        gui.draw();
    }
}


void ofApp::drawForcefield()
{
    if (bDrawGrid)
    {
        forcefield.drawGrid();
    }
    if (bDrawVectors)
    {
        forcefield.drawVectors(vectorDrawSize);
    }
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
    default:
        break;
    }
}


void ofApp::loadPreset(int i)
{
    gui.loadFromFile("settings-" + ofToString(i) + ".xml");
}
