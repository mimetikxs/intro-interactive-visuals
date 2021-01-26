#include "Particle.h"


void Particle::setup(vec2 _pos, float _mass, float _maxLife)
{
    pos = _pos;
    vel *= 0;
    accel *= 0;
    mass = _mass;

    elapsedLife = 0;
    maxLife = _maxLife;
}


void Particle::applyForce(vec2 force)
{
    accel += force / mass;
}


void Particle::update(float timeStep)
{
    vel += accel * timeStep;
    vel *= friction;
    pos += vel * timeStep;
    accel *= 0;

    elapsedLife += timeStep;
}
