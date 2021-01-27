#pragma once
#include "Forcefield.h"

class ForcefieldNoise : public Forcefield
{
public:

    ofParameter<float> noiseScale{ "noise scale", 0.03, 0.001, 0.15 };
    ofParameter<float> noiseSpeed{ "noise speed", 0.1, 0.001, 0.5 };

    void updateNoise();

};