#pragma once
#include "ofMain.h"
#include "ParticleData.h"

class Emitter
{
public:

    ofParameter<float> emitRate{ "emit rate", 40.0, 0.0, 600.0 };
    ofParameterGroup parameters{ "parameters", emitRate };

    // particles will be emited with this parameters
    float mass;
    float massVariation;
    float life;
    float lifeVariation;

    virtual void setup(string name) = 0;    
    
    virtual void emit(ParticleData& pd, float timeStep) = 0;
    
    virtual void draw() = 0;
};
