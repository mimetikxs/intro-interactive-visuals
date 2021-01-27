#pragma once
#include "ofMain.h"

class VideoSource
{
public:

    virtual void setup(int width, int height) = 0;
    
    virtual void update() = 0;

    virtual bool isFrameNew() = 0;

    virtual void draw(float x, float y) = 0;

    virtual ofPixels& getPixels() = 0;

};
