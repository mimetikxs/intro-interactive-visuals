#include "ForcefieldNoise.h"


ForcefieldNoise::ForcefieldNoise()
{
    noiseScale.set( "noise scale", 0.009, 0.001, 0.15);
    noiseSpeed.set( "noise speed", 0.1, 0.001, 0.5);

    noiseScale.addListener(this, &ForcefieldNoise::onNoiseScaleChange);
}


void ForcefieldNoise::update()
{
    float offset = ofGetElapsedTimef() * noiseSpeed;
    
    for (int y = 0; y < rows; y++) 
    {
        for (int x = 0; x < cols; x++) 
        {
            float noise = ofNoise(
                x * noiseScale + offset, 
                y * noiseScale + offset
            );
            noise = ofMap(noise, 0.0, 1.0, 0.0, TWO_PI);       

            int i = (x + y * cols) * 2;
            
            forces[i]     = cos(noise);
            forces[i + 1] = sin(noise);
        }
    }
}


void ForcefieldNoise::onNoiseScaleChange(float & value)
{
    update();
}
