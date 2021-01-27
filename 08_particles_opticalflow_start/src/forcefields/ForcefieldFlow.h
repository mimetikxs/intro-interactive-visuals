#pragma once
#include "Forcefield.h"
#include "ofxCv.h"

class ForcefieldFlow : public Forcefield
{
public:

    ForcefieldFlow();

    // flow parameters
    ofParameterGroup   parametersFlow;
    ofParameter<float> pyrScale;
    ofParameter<int>   levels;
    ofParameter<int>   winsize;
    ofParameter<int>   iterations;
    ofParameter<int>   polyN;
    ofParameter<float> polySigma;
    
    void calcOpticalFlow(ofPixels& pix);

    void resetFlow();

private:

    ofxCv::FlowFarneback flow;

    // parameter listeners
    void pyrScaleChange(float& val)  { flow.setPyramidScale(val); }
    void levelsChange(int& val)      { flow.setNumLevels(val); }
    void winsizeChange(int& val)     { flow.setWindowSize(val); }
    void iterationsChange(int& val)  { flow.setNumIterations(val); }
    void polyNChange(int& val)       { flow.setPolyN(val); }
    void polySigmaChange(float& val) { flow.setPolySigma(val); }

};