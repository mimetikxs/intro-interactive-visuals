#pragma once
#include "Forcefield.h"

class ForcefieldNoise : public Forcefield
{
public:

    ForcefieldNoise();

    ofParameter<float> noiseScale;
    ofParameter<float> noiseSpeed;

    void update() override;

private:

    void onNoiseScaleChange(float& value);
};