#pragma once
#include "ofMain.h"

using namespace glm;

class Forcefield
{
public:

    ofParameter<float> forceScale{ "force scale", 1.0, 0.001, 10.0 };
    
    void setup(int cols, int rows);
    void setup(int cols, int rows, float width, float height);
    
    vec2 getForceAtCell(int col, int row);
    vec2 getForceAtPos(vec2& pos);

    void addForcefield(Forcefield& other);
    
    // debug drawing
    void drawVectors(float scale);
    void drawPixels();
    void drawGrid();

protected:

    int cols;
    int rows;
    vec2 cellSize;

    // for convenience, our force vectors are stored as pixels,
    // we use a 2-channel pixel object to store the 2d vectors
    // red   = force.x
    // green = force.y
    ofFloatPixels forces;

    ofTexture texDebug;
};