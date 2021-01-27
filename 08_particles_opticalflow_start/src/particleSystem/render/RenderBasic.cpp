#include "RenderBasic.h"


void RenderBasic::setup(string name)
{
    parameters.setName(name);
    parameters.add( color.set(     "color",      ofColor(255, 255), ofColor(0, 0), ofColor(255, 255)));
    parameters.add( pointSize.set( "point size", 1, 1, 5));
}


void RenderBasic::update(const ParticleData& pd)
{
    if (vbo.getNumVertices() != pd.count)
    {
        allocateVbo(pd.count);
    }

    // --------------------------------------
    // copy particle data into vertex buffers
    // --------------------------------------
     
    // only alive particles will be rendered
    countVisible = pd.countAlive;

    // we only need to update particles that are alive
    for (int i = 0; i < countVisible; i++)
    {
        // copy the particle position to the vertex buffer
        positions[i].x = pd.particles[i].pos.x;
        positions[i].y = pd.particles[i].pos.y;
    }
}


void RenderBasic::draw()
{
    ofPushStyle();
    ofSetColor(color);
    glPointSize(pointSize);
        
    // send the buffer to the gpu
    vbo.updateVertexData(&positions[0], countVisible);

    // draw the vbo as points 
    vbo.draw(GL_POINTS, 0, countVisible);

    ofPopStyle();
}


void RenderBasic::allocateVbo(int numVertices)
{
    // resize positions buffer to fit all particles
    positions.resize(numVertices, vec3(0.0));

    // register the buffer with the vbo
    // GL_DYNAMIC_DRAW means we'll update positions every frame
    vbo.setVertexData(&positions[0], numVertices, GL_DYNAMIC_DRAW);
}