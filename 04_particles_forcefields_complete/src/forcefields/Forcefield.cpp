#include "Forcefield.h"


void Forcefield::setup(int cols, int rows)
{
    setup(cols, rows, cols, rows);
}


void Forcefield::setup(int _cols, int _rows, float _width, float _height)
{
    cols = _cols;
    rows = _rows;

    cellSize.x = _width / cols;
    cellSize.y = _height / rows;    
    cellSize.x = glm::max(cellSize.x, 1.0f);
    cellSize.y = glm::max(cellSize.y, 1.0f);

    forces.allocate(cols, rows, 2); //< create a grid of vectors
    forces.set(0);                  //< initialize to 0

    // debug
    texDebug.allocate(cols, rows, GL_RG8);
    texDebug.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
}


vec2 Forcefield::getForceAtCell(int col, int row)
{
    int i = (col + row * cols) * 2;
    vec2 force = vec2(forces[i], forces[i + 1]);
    return force * forceScale.get();
}


vec2 Forcefield::getForceAtPos(vec2& pos)
{
    int col = ceil(pos.x / cellSize.x) - 1;
    int row = ceil(pos.y / cellSize.y) - 1;

    if (col >= 0 && col < cols
        && row >= 0 && row < rows) 
    {
        return getForceAtCell(col, row);
    }

    return vec2(0);
}


void Forcefield::addForcefield(Forcefield& other)
{
    if (rows != other.rows || cols != other.cols)
    {
        ofLogError("Forcefield::addForcefileld()") << "grid sizes don't match";
        return;
    }

    for (int i = 0; i < forces.size(); i++)
    {
        forces[i] += other.forces[i];
    }
}


void Forcefield::drawVectors(float scale)
{
    ofPushStyle();
    ofSetColor(200);

    vec2 halfCellSize = cellSize * 0.5;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            vec2 cellCenter = vec2(x, y) * cellSize + halfCellSize;
            vec2 vec = getForceAtCell(x, y) * scale;
            
            ofDrawLine(cellCenter, cellCenter + vec);
            ofDrawRectangle(cellCenter - vec2(1), 3, 3);
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
            ofDrawRectangle(x * cellSize.x, y * cellSize.y, cellSize.x, cellSize.y);
        }
    }

    ofPopStyle();
}
