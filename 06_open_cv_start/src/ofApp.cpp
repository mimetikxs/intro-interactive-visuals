#include "ofApp.h"


void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(80);

    // init the video source
    inputWidth = 640; 
    inputHeight = 480;    

    videoSource.setup(inputWidth, inputHeight);

    // allocate container for the downscaled image
    scaledWidth  = inputWidth * videoDownscale;
    scaledHeight = inputHeight * videoDownscale;

    scaled.allocate(scaledWidth, scaledHeight, OF_IMAGE_COLOR);
    
    // ...

    // gui
    gui.setup();
    gui.setPosition(10, scaledHeight + 20);

    bDrawGui = true;
}


void ofApp::update()
{
    videoSource.update();

    if (videoSource.isFrameNew())
    {
        // ---------------------
        // downscale our input
        // ---------------------

        videoSource.getPixels().resizeTo(scaled);

        scaled.update(); //< upload to gpu

        // ...
    }
}


void ofApp::draw()
{
    float w = scaledWidth;
    float h = scaledHeight;

    scaled.draw(0, 0);
    ofDrawBitmapStringHighlight("source scaled (" + ofToString(videoDownscale * 100) + "%)", 5, 15);

    // ...

    ofDrawBitmapString(ofToString(ofGetFrameRate()), ofGetWidth() - 70, ofGetHeight() - 20);

    if (bDrawGui)
    {
        gui.draw();
    }    
}


void ofApp::keyPressed(int key)
{
    if (key == 'g')
    {
        bDrawGui = !bDrawGui;
    }
}