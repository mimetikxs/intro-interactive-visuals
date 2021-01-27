#pragma once
#include "Render.h"

using namespace glm;

class RenderBasic : public Render
{
public:

    // ...

    void setup(string name) override;
    void update(const ParticleData& pd) override;
    void draw() override;

private:

    // ...
};
