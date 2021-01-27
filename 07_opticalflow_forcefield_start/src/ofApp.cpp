#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(80);

    // init the video source
    int cameraWidth = 640;
    int cameraHeight = 480;

    videoSource.setup(cameraWidth, cameraHeight);

    // allocate container for the downscaled image
    int scaledWidth  = cameraWidth * videoDownscale;
    int scaledHeight = cameraHeight * videoDownscale;

    scaled.allocate(scaledWidth, scaledHeight, OF_IMAGE_COLOR);

    // optical flow field
    // ...
    
    // gui
    ofParameterGroup groupProcessing;
    groupProcessing.setName("processing");
    groupProcessing.add( blurSize.set("blur size", 2, 0, 15));
    
    ofParameterGroup groupForcefield;
    groupForcefield.setName("forcefield");
    groupForcefield.add( forcefieldFlow.forceScale);

    ofParameterGroup groupDrawing;
    groupDrawing.setName("drawing");
    groupDrawing.add( bDrawGrid.set("grid", false));
    groupDrawing.add( bDrawVectors.set("vectors", true));
    groupDrawing.add( bDrawPixels.set("pixels", false));
    groupDrawing.add( vectorDrawSize.set("vector size", 50.0, 1.0, 50.0));

    // ...
    groupForcefield.add( groupDrawing);

    gui.setup();
    gui.add(groupProcessing);
    gui.add(groupForcefield);

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
        // ...
    }
}


void ofApp::draw()
{
    if (bDrawPixels)
    {
        forcefieldFlow.drawPixels();
    }
    if (bDrawGrid)
    {
        forcefieldFlow.drawGrid();
    }
    if (bDrawVectors)
    {
        forcefieldFlow.drawVectors(vectorDrawSize);
    }

    grey.draw(1004 - grey.getWidth(), 20);

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
    case 'r':
        forcefieldFlow.resetFlow();
        break;
    default:
        break;
    }
}
