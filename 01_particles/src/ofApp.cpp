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

    mesh.setMode(OF_PRIMITIVE_POINTS);

    // ---------------------
    // gui
    // ---------------------

    gui.setup();    
    gui.add( particleSystem.parameters);
    gui.add( emitter.parameters);
    gui.add( forceWind.parameters);
    gui.add( forceAttraction.parameters);
    gui.loadFromFile("settings-default.xml");
    gui.minimizeAll();
    
    bDrawGui = true;

    bDrawDebug = false;
}


void ofApp::update()
{
    // ---------------------
    // update particle system
    // ---------------------

    particleSystem.update();
    
    // ---------------------
    // update mesh
    // ---------------------

    // reset
    mesh.clear();

    // only draw alive particles
    int numVertices = particleSystem.getParticleData().countAlive;

    // get a reference to the particles
    const vector<Particle>& particles = particleSystem.getParticleData().particles;

    // add vertices to the mesh
    for (int i = 0; i < numVertices; i++)
    {
        vec3 vertex(
            particles[i].pos.x, 
            particles[i].pos.y, 
            0.0
        );
        mesh.addVertex(vertex);
    }
}


void ofApp::draw()
{       
    // draw particles
    mesh.draw();

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
    default:
        break;
    }
}

