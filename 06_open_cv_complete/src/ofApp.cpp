#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

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

    scaled.allocate(  scaledWidth, scaledHeight, OF_IMAGE_COLOR);
    
    // allocate for frame difference
    greyPrev.allocate(scaledWidth, scaledHeight, OF_IMAGE_GRAYSCALE);
    diff.allocate(    scaledWidth, scaledHeight, OF_IMAGE_GRAYSCALE);

    // optical flow
    initFlow();    

    // gui
    gui.setup();
    gui.add(thresholdValue.set("threshold value", 50, 0, 255));
    gui.add(blurSize.set("blur size", 2, 0, 15));
    gui.setPosition(10, scaledHeight + 20);

    bDrawGui = true;
}


void ofApp::initFlow()
{
    flow.setPyramidScale(.5);
    flow.setNumLevels(4);
    flow.setWindowSize(15);
    flow.setNumIterations(2);
    flow.setPolyN(7);
    flow.setPolySigma(1.5);

    flowPixels.allocate(scaledWidth, scaledHeight, 2);
    flowTex.allocate(scaledWidth, scaledHeight, GL_RG8);
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
        //videoSource.getPixels().resizeTo(scaled, OF_INTERPOLATE_BICUBIC);

        scaled.update(); //< upload to gpu

        // ---------------------
        // convert to grey and blur
        // ---------------------

        ofxCv::convertColor(scaled, grey, CV_RGB2GRAY);

        if (blurSize > 0)
        {
            ofxCv::blur(grey, blurSize);
        }

        grey.update(); //< upload to gpu

        // ---------------------
        // frame difference
        // ---------------------

        ofxCv::absdiff(grey, greyPrev, diff);
        ofxCv::copy(grey, greyPrev);

        diff.update(); //< upload to gpu

        // ---------------------
        // threshold difference
        // ---------------------

        ofxCv::threshold(diff, diffThresh, thresholdValue);

        diffThresh.update(); //< upload to gpu        

        // ---------------------
        // optical flow
        // ---------------------

        flow.calcOpticalFlow(grey);        

        ofxCv::toOf(flow.getFlow(), flowPixels);
        //ofxCv::blur(flowPixels, 10);

        flowTex.loadData(flowPixels);
    }
}


void ofApp::draw()
{
    float w = scaledWidth;
    float h = scaledHeight;

    scaled.draw(0, 0);
    ofDrawBitmapStringHighlight("source scaled (" + ofToString(videoDownscale * 100) + "%)", 5, 15);

    grey.draw(w, 0);
    ofDrawBitmapStringHighlight("grey + blur", w+5, 15);

    diff.draw(w*2, 0);
    ofDrawBitmapStringHighlight("diff", w*2+5, 15);

    diffThresh.draw(w*2, h);
    ofDrawBitmapStringHighlight("diff threshold", w*2+5, h+15);

    flowTex.draw(w, h);
    ofDrawBitmapStringHighlight("flow pixels", w+5, h + 15);

    flow.draw(w, h*2);
    ofDrawBitmapStringHighlight("flow vectors", w+5, h*2 + 15);

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