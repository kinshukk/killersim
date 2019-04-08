#include "ofMain.h"
#include <iostream>
#include <vector>

#ifndef _MAP_H_
#define _MAP_H_

#define DELTA_FOOD_PER_SEC 1

using namespace std;

struct tile{
    float value;
    float X_topleft, Y_topleft;
};

class Map{
    int rows, columns;
    float width, height;
    float screenW, screenH;

    //100 default since I couldn't get dynamic size initialization to work
    vector<tile> tiles[100];

public:
    void init(int r, int c, int screenWidth, int screenHeight);
    void draw();
    void update(float dt, float screenW, float screenH);
    void regenerate_values();
    float tile_value_at(float x, float y);
};

#endif
