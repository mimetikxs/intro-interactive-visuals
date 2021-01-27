#pragma once
#include "Forcefield.h"

class ForcefieldNoise : public Forcefield
{
public:

    ForcefieldNoise();

    ofParameter<float> noiseScale;
    ofParameter<float> noiseSpeed;

    void updateNoise();

private:

    void onNoiseScaleChange(float& value);
};