#include "ofApp.h"

void ofApp::setup()
{
    ofSetVerticalSync(true);
    ofBackground(0);

    // init the video source
    inputWidth = 640; 
    inputHeight = 480;    

    videoSource.setup(inputWidth, inputHeight);

    // allocate container for the downscaled image
    scaledWidth  = inputWidth * videoDownscale;
    scaledHeight = inputHeight * videoDownscale;

    pixelsScaled.allocate(scaledWidth, scaledHeight, OF_PIXELS_RGB);
    textureScaled.allocate(pixelsScaled);
}


void ofApp::update()
{
    videoSource.update();

    if (videoSource.isFrameNew())
    {
        // downscale our input
        videoSource.getPixels().resizeTo(pixelsScaled);

        // upload pixels to gpu
        textureScaled.loadData(pixelsScaled);
    }
}


void ofApp::draw()
{
    videoSource.draw(0, 0);
    ofDrawBitmapStringHighlight("source", 5, 15);

    textureScaled.draw(inputWidth, 0);
    ofDrawBitmapStringHighlight("scaled", inputWidth+5, 15);
}


void ofApp::keyPressed(int key)
{
}

