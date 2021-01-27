#include "SourceWebcam.h"

void SourceWebcam::setup(int width, int height)
{
    //get back a list of devices.
    vector<ofVideoDevice> devices = camera.listDevices();

    for (size_t i = 0; i < devices.size(); i++) {
        if (devices[i].bAvailable) {
            //log the device
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }
        else {
            //log the device and note it as unavailable
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }

    // open the camera
    // make sure you choose the right device id
    camera.setDeviceID(1);
    camera.setDesiredFrameRate(30);
    camera.initGrabber(width, height);
}


void SourceWebcam::update()
{
    camera.update();
}


bool SourceWebcam::isFrameNew()
{
    return camera.isFrameNew();
}


void SourceWebcam::draw(float x, float y)
{
    camera.draw(x, y);
}


ofPixels& SourceWebcam::getPixels()
{
   return  camera.getPixels();
}
