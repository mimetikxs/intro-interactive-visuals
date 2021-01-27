#include "RenderPoints.h"


void RenderPoints::setup(string name)
{
    parameters.setName(name);
    parameters.add( colorBorn.set(  "color born", ofFloatColor(1.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    parameters.add( colorDead.set(  "color dead", ofFloatColor(0.0, 1.0), ofFloatColor(0.0, 0.0), ofFloatColor(1.0, 1.0)));
    parameters.add( pointScale.set( "point scale", 1.0, 1.0, 10.0));

    // load our shader
    shader.load("shaders/renderPoints.vert", "shaders/renderPoints.frag");
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
        masses[i]      = pd.particles[i].mass;
        lifes[i]       = pd.particles[i].elapsedLife / pd.particles[i].maxLife;
    }
}


void RenderPoints::draw()
{
    //ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    ofEnablePointSprites();
       
    shader.begin();
    shader.setUniform4f( "colorBorn", colorBorn);
    shader.setUniform4f( "colorDead", colorDead);
    shader.setUniform1f( "pointScale", pointScale);
    {
        // send the buffers to the gpu
        vbo.updateVertexData( &positions[0], countVisible);
        vbo.updateAttributeData( shader.getAttributeLocation("lifePct"), &lifes[0],  countVisible);
        vbo.updateAttributeData( shader.getAttributeLocation("massPct"), &masses[0], countVisible);
            
        // draw the vbo as points 
        vbo.draw(GL_POINTS, 0, countVisible);
    }
    shader.end();

    ofDisablePointSprites();

    ofDisableAlphaBlending();
}


void RenderPoints::allocateVbo(int numVertices)
{
    // resize buffers to fit all particles
    positions.resize(numVertices, vec3(0.0));
    masses.resize(numVertices, 0.0);
    lifes.resize(numVertices, 0.0);

    // ------------------------------
    // register buffers with the vbo
    // ------------------------------

    // "position" is a "default attribute" of our shader
    // and oF provides setVertexData() to register vertex positions easily
    vbo.setVertexData(&positions[0], numVertices, GL_DYNAMIC_DRAW);

    // "life" and "mass" are "custom attributes" defined in our shader
    // they are registered with setAttributeData():
        
    // 1) bind our shader
    shader.begin();
    {            
        // 2) get the location of the attributes in our shader
        int lifeLoc = shader.getAttributeLocation("lifePct");
        int massLoc = shader.getAttributeLocation("massPct");

        // 3) register our buffers using the location
        vbo.setAttributeData(lifeLoc, &lifes[0],  1, numVertices, GL_DYNAMIC_DRAW, sizeof(float));
        vbo.setAttributeData(massLoc, &masses[0], 1, numVertices, GL_DYNAMIC_DRAW, sizeof(float));
    }
    shader.end();
}