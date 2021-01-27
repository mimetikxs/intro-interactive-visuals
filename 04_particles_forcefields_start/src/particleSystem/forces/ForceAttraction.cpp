#include "ForceAttraction.h"


void ForceAttraction::setup(string name)
{
    parameters.setName(name);
    parameters.add( x.set(            "x",         0.0, 0.0, 2000.0));
    parameters.add( y.set(            "y",         0.0, 0.0, 2000.0));
    parameters.add( strength.set(     "strength",  0.4, -10.0, 10.0));
    parameters.add( mass.set(         "mass",      1.0, 0.1, 100.0));
    parameters.add( nearDistance.set( "near dist", 50.0, 0.0, 500.0));
    parameters.add( farDistance.set(  "far dist",  600.0, 0.0, 2000.0));
    
}


void ForceAttraction::applyForce(Particle& p)
{
    vec2 dir = p.pos - vec2(x, y);
    float dist = clamp(length(dir), nearDistance.get(), farDistance.get());
    float forceStrength = (strength * mass * p.mass) / dist;

    dir /= dist; //< normalized direction

    p.applyForce(-forceStrength * dir);
}


void ForceAttraction::draw()
{
    vec2 c = vec2(x, y);
    ofDrawCircle(c, nearDistance * 0.5);
    ofDrawCircle(c, farDistance * 0.5);
    ofDrawLine(c + vec2(-10, 0), c + vec2(10, 0));
    ofDrawLine(c + vec2(0, -10), c + vec2(0, 10));

    ofDrawBitmapString(parameters.getName(), x + 5, y + 15);
}