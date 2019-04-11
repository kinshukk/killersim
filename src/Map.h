#include "ofMain.h"
#include <iostream>
#include <vector>
#include <utility>

#ifndef _MAP_H_
#define _MAP_H_

using namespace std;

struct tile{
    float value;
    float X_topleft, Y_topleft;
};

class Map{
    int rows, columns;
    float width, height;
    float screenW, screenH;

public:
    //100 default since I couldn't get dynamic size initialization to work
    //NOTE: all 100 aren't used always
    vector<tile> tiles[100];
    int delta_food_per_sec;
    void init(int r, int c, int screenWidth, int screenHeight);
    void draw();
    void update(float dt, float screenW, float screenH);
    void regenerate_values();
    float tile_value_at(float x, float y);
    void increase_delta_food();
    void decrease_delta_food();
    void decrease_tile_value_at(std::pair<double, double> coords, double delta);
};

#endif
