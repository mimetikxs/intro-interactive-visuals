#pragma once
#include "ofMain.h"
#include "ParticleData.h"
#include "Emitter.h"
#include "Force.h"
#include "Forcefield.h"

class ParticleSystem
{
public:

    ofParameterGroup parameters;
    ofParameter<float> timeStep;
    ofParameter<float> friction;
    ofParameter<float> mass;
    ofParameter<float> massVariation;
    ofParameter<float> life;
    ofParameter<float> lifeVariation;
    
    void setup(float width, float height, int numParticles);
   
    void update();

    void addEmitter(Emitter* emitter);
    void addForce(Force* force);
    void setForcefield(Forcefield* field);

    const ParticleData& getParticleData();

private:

    float width;
    float height;

    ParticleData     particleData;

    vector<Emitter*> emitters;
    vector<Force*>   forces;
    Forcefield*      forcefield;
};

