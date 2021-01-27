#include "ForcefieldFlow.h"


ForcefieldFlow::ForcefieldFlow()
{
    pyrScale.addListener(   this, &ForcefieldFlow::pyrScaleChange);
    levels.addListener(     this, &ForcefieldFlow::levelsChange);
    winsize.addListener(    this, &ForcefieldFlow::winsizeChange);
    iterations.addListener( this, &ForcefieldFlow::iterationsChange);
    polyN.addListener(      this, &ForcefieldFlow::polyNChange);
    polySigma.addListener(  this, &ForcefieldFlow::polySigmaChange);

    parametersFlow.setName("optical flow");
    parametersFlow.add( pyrScale.set(   "pyrScale", .5, 0, 0.99));
    parametersFlow.add( levels.set(     "levels", 4, 1, 8));
    parametersFlow.add( winsize.set(    "winsize", 15, 4, 64));
    parametersFlow.add( iterations.set( "iterations", 2, 1, 8));
    parametersFlow.add( polyN.set(      "polyN", 7, 5, 10));
    parametersFlow.add( polySigma.set(  "polySigma", 1.5, 1.1, 2));
}


void ForcefieldFlow::calcOpticalFlow(ofPixels& pix)
{
    flow.calcOpticalFlow(pix);

    ofxCv::toOf(flow.getFlow(), forces);
}


void ForcefieldFlow::resetFlow()
{
    flow.resetFlow();
}
