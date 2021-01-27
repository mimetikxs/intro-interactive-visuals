#include "ParticleSystem.h"


void ParticleSystem::setup(float _width, float _height, int numParticles)
{
    width = _width;
    height = _height;

    particleData.generate(numParticles);

    parameters.setName("particle system");
    parameters.add( timeStep.set(      "timeStep",       1.0, 0.0, 1.0));
    parameters.add( friction.set(      "friction",       0.001, 0.0, 1.0));    
    parameters.add( mass.set(          "mass",           1.0, 0.1, 20.0));
    parameters.add( massVariation.set( "mass variation", 1.0, 1.0, 5.0));
    parameters.add( life.set(          "life",           100.0, 1.0, 1000.0));
    parameters.add( lifeVariation.set( "life variation", 1.0, 1.0, 100.0));
}


void ParticleSystem::update()
{
    // ----------------------------------
    // emit (wake particles)
    // ----------------------------------

    for (auto emitter : emitters)
    {
        // pass down global parameters
        emitter->mass =          mass;
        emitter->massVariation = massVariation;
        emitter->life =          life;
        emitter->lifeVariation = lifeVariation;

        emitter->emit(particleData, timeStep);
    }
        
    // ----------------------------------
    // update particles
    // ----------------------------------

    float frictionVal = 1.0 - friction;

    for (int i = 0; i < particleData.countAlive; i++)
    {
        Particle& p = particleData.particles[i];

        // pass down global parameters
        p.friction = frictionVal;

        // accumulate forces
        for (auto force : forces)
        {
            force->applyForce(p);
        }

        // ...

        // update position
        p.update(timeStep);
    }

    // ----------------------------------
    //  kill particles (if too old or out of bounds)
    // ----------------------------------

    for (int i = 0; i < particleData.countAlive; i++)
    {
        Particle& p = particleData.particles[i];

        if (p.elapsedLife > p.maxLife
            || p.pos.x < 0.0
            || p.pos.x > width
            || p.pos.y < 0
            || p.pos.y > height)
        {
            particleData.kill(i);
        }
    }
}


void ParticleSystem::addEmitter(Emitter* emitter)
{
    emitters.push_back(emitter);
}


void ParticleSystem::addForce(Force* force)
{
    forces.push_back(force);
}


const ParticleData & ParticleSystem::getParticleData()
{
    return particleData;
}
