#include "RenderLines.h"


void RenderLines::setup(string name)
{
    parameters.setName(name);
    parameters.add( colorBorn.set(  "color born", ofFloatColor(1.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    parameters.add( colorDead.set(  "color dead", ofFloatColor(0.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    
    // load our shader
    shader.load("shaders/renderLines.vert", "shaders/renderLines.frag");
}


void RenderLines::update(const ParticleData& pd)
{
    if (vbo.getNumVertices() != pd.count)
    {
        allocateVbo(pd.count);
    }

    // --------------------------------------
    // copy particle data into vertex buffers
    // --------------------------------------

    // iterate over alive particles
    for (int i = 0; i < pd.countAlive; i++)
    {
        vec2 pPos      = pd.particles[i].pos;
        vec2 pVel      = pd.particles[i].vel;
        float pLifePct = pd.particles[i].elapsedLife / pd.particles[i].maxLife;

        int iTail = i * 2;      //< tail vertex index
        int iHead = i * 2 + 1;  //< head vertex index

        // update tail vertex
        positions[iTail].x = pPos.x - pVel.x;
        positions[iTail].y = pPos.y - pVel.y;
        lifes[iTail]       = pLifePct;
            
        // update head vertex
        positions[iHead].x = pPos.x;
        positions[iHead].y = pPos.y;
        lifes[iHead]       = pLifePct;
    }

    // only alive particles will be rendered
    countVisible = pd.countAlive * 2;
}


void RenderLines::draw()
{
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    shader.begin();
    shader.setUniform4f( "colorBorn", colorBorn);
    shader.setUniform4f( "colorDead", colorDead);
    {
        vbo.updateVertexData( &positions[0], countVisible);
        vbo.updateAttributeData( shader.getAttributeLocation("lifePct"), &lifes[0],  countVisible);
            
        vbo.draw(GL_LINES, 0, countVisible);
    }
    shader.end();

    ofDisableAlphaBlending();
}


void RenderLines::allocateVbo(int numVertices)
{
    // we need 2 vertices per particle to draw a line
    int bufferSize = numVertices * 2;

    // resize buffers
    positions.resize(bufferSize, vec3(0.0));
    lifes.resize(bufferSize, 0.0);

    // ------------------------------
    // register buffers with the vbo
    // ------------------------------

    vbo.setVertexData(&positions[0], bufferSize, GL_DYNAMIC_DRAW);
    shader.begin();
    {
        int lifeLoc = shader.getAttributeLocation("lifePct");
        vbo.setAttributeData(lifeLoc, &lifes[0],  1, bufferSize, GL_DYNAMIC_DRAW, sizeof(float));
    }
    shader.end();
}