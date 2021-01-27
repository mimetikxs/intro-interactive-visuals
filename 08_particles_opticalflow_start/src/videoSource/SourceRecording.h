#pragma once
#include "VideoSource.h"

class SourceRecording : public VideoSource
{
public:

    void setup(int width, int height) override;

    void update() override;

    bool isFrameNew() override;

    void draw(float x, float y) override;

    ofPixels& getPixels() override;

private:

    ofVideoPlayer player;

};
