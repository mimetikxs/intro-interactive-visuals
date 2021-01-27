#include "Forcefield.h"


void Forcefield::setup(int cols, int rows)
{
    setup(cols, rows, cols, rows);
}


void Forcefield::setup(int _cols, int _rows, float _width, float _height)
{
    // ...
}


vec2 Forcefield::getForceAtCell(int col, int row)
{
    // ...
}


vec2 Forcefield::getForceAtPos(vec2& pos)
{
    // ...
}


void Forcefield::drawVectors(float scale)
{
    ofPushStyle();
    ofSetColor(200);    

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            // ...
        }
    }

    ofPopStyle();
}


void Forcefield::drawPixels()
{
    texDebug.loadData(forces);  //< upload pixels to gpu
    texDebug.draw(0, 0, cellSize.x * cols, cellSize.y * rows);
}


void Forcefield::drawGrid()
{
    ofPushStyle();
    ofSetColor(200);
    ofNoFill();

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            // ...
        }
    }

    ofPopStyle();
}
