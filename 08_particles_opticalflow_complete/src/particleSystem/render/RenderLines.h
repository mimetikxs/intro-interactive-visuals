#pragma once
#include "Render.h"

using namespace glm;

class RenderLines : public Render
{
public:

    ofParameter<ofFloatColor> colorBorn;
    ofParameter<ofFloatColor> colorDead;
    ofParameter<float> pointScale; // TODO: line width

    void setup(string name) override;
    void update(const ParticleData& pd) override;
    void draw() override;

private:
       
    ofVbo         vbo;        
    int           countVisible;  
    vector<vec3>  positions;     //< buffers
    vector<float> lifes;         //
    
    void allocateVbo(int numVertices);

    // we use a shader to render 
    ofShader shader;
};
