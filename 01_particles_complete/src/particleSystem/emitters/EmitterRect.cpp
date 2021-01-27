#include "EmitterRect.h"


void EmitterRect::setup(string name)
{
    parameters.setName(name);    
    parameters.add( x.set(     "x",      0.0, 0.0, 2000.0));
    parameters.add( y.set(     "y",      0.0, 0.0, 2000.0));
    parameters.add( width.set( "width",  0.0, 0.0, 2000.0));
    parameters.add( height.set("height", 0.0, 0.0, 2000.0));
}


void EmitterRect::emit(ParticleData& pd, float timeStep)
{
    int maxNewParticles = timeStep * emitRate;
        
    // range of dead particles
    int first = pd.countAlive;
    int last  = std::min(first + maxNewParticles, pd.count - 1);

    for (int i = first; i < last; i++)
    {
        pd.particles[i].setup(
            getRandomPointInRect(),
            mass * ofRandom(1, massVariation),
            life * ofRandom(1, lifeVariation)
        );

        pd.wake(i);
    }
}


vec2 EmitterRect::getRandomPointInRect()
{
    vec2 p;
    p.x = ofRandom(x, x + width);
    p.y = ofRandom(y, y + height);
    return p;
}


void EmitterRect::draw()
{
    ofDrawRectangle(x, y, width, height);

    ofDrawBitmapString(parameters.getName(), x + 5, y + 15);
}