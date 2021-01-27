//
// Newton's second law of motion:
// force = mass * acceleration
// acceleration = force / mass
// https://natureofcode.com/book/chapter-2-forces/
//
// We use a simple "Euler integration" as our motion model
// velocity = oldVelocity + acceleration * timeStep
// position = oldPosition + velocity * timeStep
// 

#pragma once
#include "ofMain.h"

using namespace glm;

class Particle
{
public:

    vec2  pos;
    vec2  vel;
    vec2  accel;
    float mass     = 1.0;
    float friction = 0.0;

    float maxLife     = 0.0;
    float elapsedLife = 0.0;

    void setup(vec2 pos, float mass, float maxLife);
    void applyForce(vec2 force);
    void update(float timeStep = 1.0);    
};
