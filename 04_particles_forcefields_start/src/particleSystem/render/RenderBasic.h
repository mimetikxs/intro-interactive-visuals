#pragma once
#include "Render.h"

using namespace glm;

class RenderBasic : public Render
{
public:

    ofParameter<ofColor> color;
    ofParameter<int>     pointSize;

    void setup(string name) override;
    void update(const ParticleData& pd) override;
    void draw() override;

private:

    ofVbo        vbo;
    int          countVisible;   //< number of vertices to draw
    vector<vec3> positions;      //< buffer for positions 
    
    void allocateVbo(int numVertices);
};
