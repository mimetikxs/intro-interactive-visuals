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

    scaled.allocate(scaledWidth, scaledHeight, OF_IMAGE_COLOR);
    
    greyPrev.allocate(scaledWidth, scaledHeight, OF_IMAGE_GRAYSCALE);
    diff.allocate(scaledWidth, scaledHeight, OF_IMAGE_GRAYSCALE);

    // optical flow

    initFlow();

    flowPixels.allocate(scaledWidth, scaledHeight, 2);
    flowTex.allocate(scaledWidth, scaledHeight, GL_RG32F);

    // gui

    gui.setup();
    gui.add(parameters);
}


void ofApp::update()
{
    videoSource.update();

    if (videoSource.isFrameNew())
    {
        // ---------------------
        // downscale our input
        // ---------------------

        videoSource.getPixels().resizeTo(scaled, OF_INTERPOLATE_BICUBIC);

        scaled.update(); //< upload to gpu

        // ---------------------
        // convert to grey and blur
        // ---------------------

        ofxCv::convertColor(scaled, grey, CV_RGB2GRAY);

        int blurAmount = 2;
        ofxCv::blur(grey, 2);

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

        float thresholdValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);
        threshold(diff, diffThresh, thresholdValue);

        diffThresh.update(); //< upload to gpu        


        // optical flow
        flow.calcOpticalFlow(grey);

        toOf(flow.getFlow(), flowPixels);
        flowTex.loadData(flowPixels, GL_RG);
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


    flow.draw(w, h);

    flowTex.draw(w, h*2);

    if (bDrawGui)
    {
        gui.draw();
    }    
}


void ofApp::keyPressed(int key)
{
}



void ofApp::initFlow()
{
    parameters.setName("optical flow");
    parameters.add(pyrScale.set("pyrScale", .5, 0, 1));
    parameters.add(levels.set("levels", 4, 1, 8));
    parameters.add(winsize.set("winsize", 8, 4, 64));
    parameters.add(iterations.set("iterations", 2, 1, 8));
    parameters.add(polyN.set("polyN", 7, 5, 10));
    parameters.add(polySigma.set("polySigma", 1.5, 1.1, 2));
    parameters.add(useFarnelGaussian.set("FARNEBACK_GAUSSIAN", false));

    pyrScale.addListener(this, &ofApp::pyrScaleChange);
    levels.addListener(this, &ofApp::levelsChange);
    winsize.addListener(this, &ofApp::winsizeChange);
    iterations.addListener(this, &ofApp::iterationsChange);
    polyN.addListener(this, &ofApp::polyNChange);
    polySigma.addListener(this, &ofApp::polySigmaChange);
}