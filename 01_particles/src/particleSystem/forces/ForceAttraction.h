// 
// Gravitational attraction:
// https://natureofcode.com/book/chapter-2-forces/#29-gravitational-attraction
//

#pragma once
#include "Force.h"

using namespace glm;

class ForceAttraction : public Force
{
public:

    ofParameter<float> x;
    ofParameter<float> y;
    ofParameter<float> strength;
    ofParameter<float> mass;
    ofParameter<float> nearDistance;
    ofParameter<float> farDistance;    

    void setup(string name) override;

    void applyForce(Particle& p) override;

    void draw() override;
};
