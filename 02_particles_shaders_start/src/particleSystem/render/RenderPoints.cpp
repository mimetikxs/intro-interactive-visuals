#include "RenderPoints.h"


void RenderPoints::setup(string name)
{
    parameters.setName(name);
    parameters.add( colorBorn.set(  "color born", ofFloatColor(1.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    parameters.add( colorDead.set(  "color dead", ofFloatColor(0.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    parameters.add( pointScale.set( "point scale", 1.0, 1.0, 10.0));

    // load our shader
    // ...
}


void RenderPoints::update(const ParticleData& pd)
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

    // only update particles that are alive
    for (int i = 0; i < countVisible; i++)
    {
        // copy particle data to buffers
        positions[i].x = pd.particles[i].pos.x;
        positions[i].y = pd.particles[i].pos.y;
        // ...
    }
}


void RenderPoints::draw()
{
    // ...
}


void RenderPoints::allocateVbo(int numVertices)
{
    // resize buffers to fit all particles
    positions.resize(numVertices, vec3(0.0));
    // ...

    // ------------------------------
    // register buffers with the vbo
    // ------------------------------

    vbo.setVertexData(&positions[0], numVertices, GL_DYNAMIC_DRAW);

    // ...
}