#pragma once
#include "VideoSource.h"

class SourceWebcam : public VideoSource
{
public:
   
    void setup(int width, int height) override;

    void update() override;

    bool isFrameNew() override;

    void draw(float x, float y) override;

    ofPixels& getPixels() override;

private:

    ofVideoGrabber camera;

};
