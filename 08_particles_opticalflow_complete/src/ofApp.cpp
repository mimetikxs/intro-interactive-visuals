#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(0);

    // ---------------------
    // init video source + processing
    // ---------------------

    videoSource.setup(cameraWidth, cameraHeight);

    int scaledWidth = cameraWidth * videoDownscale;
    int scaledHeight = cameraHeight * videoDownscale;

    // allocate container for the downscaled image
    scaled.allocate(scaledWidth, scaledHeight, OF_IMAGE_COLOR);

    // ---------------------
    // optical flow field
    // ---------------------

    forcefieldFlow.setup(scaledWidth, scaledHeight, screenWidth, screenHeight);

    // ---------------------
    // particle system
    // ---------------------

    // create emmiters
    emitter.setup("emitter");
    emitter.width = screenWidth;
    emitter.height = screenHeight;

    // create forces
    forceWind.setup("wind");
    
    // create system and add emitters and forces
    particleSystem.setup(screenWidth, screenHeight, numParticles);
    particleSystem.addEmitter(&emitter);
    particleSystem.addForce(&forceWind);
    particleSystem.setForcefield(&forcefieldFlow);

    // ---------------------
    // particle rendering
    // ---------------------

    renderLines.setup("render lines");

    layerLines.allocate(screenWidth, screenHeight, GL_RGBA32F);
    
    // ---------------------
    // gui
    // ---------------------

    buildGui();   

    bDrawGui = true;
}


void ofApp::update()
{
    videoSource.update();

    if (videoSource.isFrameNew())
    {
        // downscale our input
        videoSource.getPixels().resizeTo(scaled, OF_INTERPOLATE_BICUBIC);
        scaled.update();

        // convert to grey and blur
        ofxCv::convertColor(scaled, grey, CV_RGB2GRAY);
        ofxCv::blur(grey, blurSize);
        grey.update(); 

        // optical flow field
        if (bResetFlow)
        {
            forcefieldFlow.resetFlow();
            bResetFlow = false;
        }
        forcefieldFlow.calcOpticalFlow(grey);
    }

    particleSystem.update();

    renderLines.update(particleSystem.getParticleData());
}


void ofApp::draw()
{
    // particles
    layerLines.begin();
    {
        ofFill();
        ofSetColor(0, 0, 0, (1.0 - lineTrails) * 255);
        ofDrawRectangle(0, 0, screenWidth, screenHeight);

        renderLines.draw();
    }
    layerLines.end();
    layerLines.draw(0, 0);

    // forcefield
    drawForcefield();

    // input
    grey.draw(1004 - grey.getWidth(), 20);

    // gui
    if (bDrawGui)
    {
        gui.draw();
    }    
}


void ofApp::drawForcefield()
{
    if (bDrawGrid)
    {
        forcefieldFlow.drawGrid();
    }
    if (bDrawVectors)
    {
        forcefieldFlow.drawVectors(vectorDrawSize);
    }
}


void ofApp::keyPressed(int key)
{
    switch (key)
    {
    case 'g':
        bDrawGui = !bDrawGui;
        break;
    case 'r':
        bResetFlow = true;
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
    case '5':
        loadPreset(5);
        break;
    default:
        break;
    }
}


void ofApp::buildGui()
{
    ofParameterGroup groupProcessing;
    groupProcessing.setName("processing");
    groupProcessing.add(blurSize.set("blur size", 2, 0, 15));

    ofParameterGroup groupForcefield;
    groupForcefield.setName("forcefield");
    groupForcefield.add(forcefieldFlow.forceScale);

    ofParameterGroup groupDrawing;
    groupDrawing.setName("drawing");
    groupDrawing.add(bDrawGrid.set("grid", false));
    groupDrawing.add(bDrawVectors.set("vectors", false));
    groupDrawing.add(vectorDrawSize.set("vector size", 50.0, 1.0, 50.0));

    groupForcefield.add(forcefieldFlow.parametersFlow);
    groupForcefield.add(groupDrawing);

    gui.setup();
    gui.add(groupProcessing);
    gui.add(groupForcefield);
    gui.add(particleSystem.parameters);
    gui.add(emitter.parameters);
    gui.add(forceWind.parameters);
    gui.add(renderLines.parameters);
    gui.add(lineTrails.set("line trails", 0.0, 0.0, 1.0));

    gui.minimizeAll();
}


void ofApp::loadPreset(int i)
{
    gui.loadFromFile("settings-" + ofToString(i) + ".xml");
}