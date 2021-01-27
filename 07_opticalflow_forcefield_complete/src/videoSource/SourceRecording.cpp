#include "SourceRecording.h"


void SourceRecording::setup(int width, int height)
{
    player.load("video/clip_34.mp4");
    player.setLoopState(OF_LOOP_NORMAL);
    player.play();
}


void SourceRecording::update()
{
    player.update();
}


bool SourceRecording::isFrameNew()
{
    return player.isFrameNew();
}


void SourceRecording::draw(float x, float y)
{
    player.draw(x, y);
}


ofPixels& SourceRecording::getPixels()
{
    return  player.getPixels();
}
