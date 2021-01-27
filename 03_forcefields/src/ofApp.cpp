#include "ofApp.h"


void ofApp::setup()
{
    ofBackground(0);
    ofSetVerticalSync(true);

    // ---------------------
    // forcefield
    // ---------------------

    // system size
    float width = 1024;
    float height = 768;
    float cellSize = 40;

    forcefield.setup(width / cellSize, height / cellSize, width, height);

    // ---------------------
    // gui
    // ---------------------        

    ofParameterGroup groupField;
    groupField.setName("field");
    groupField.add( forcefield.noiseScale);
    groupField.add( forcefield.noiseSpeed);

    ofParameterGroup groupDrawing;
    groupDrawing.setName("drawing");
    groupDrawing.add( bDrawGrid.set("grid", false));
    groupDrawing.add( bDrawVectors.set("vectors", true));
    groupDrawing.add( bDrawPixels.set("pixels", false));
    groupDrawing.add( vectorDrawSize.set("vector size", 50.0, 1.0, 50.0));

    gui.setup();
    gui.add(groupField);
    gui.add(groupDrawing);
    
    bDrawGui = true;
}


void ofApp::update()
{
    forcefield.updateNoise();
}


void ofApp::draw()
{    
    if (bDrawPixels)
    {
        forcefield.drawPixels();
    }
    if (bDrawGrid)
    {
        forcefield.drawGrid();
    }    
    if (bDrawVectors)
    {
        forcefield.drawVectors(vectorDrawSize);
    }

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

