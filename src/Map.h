#include "ofMain.h"
#include <stdio.h>
#include <vector>

using std::vector;

struct tile{
    int value;
    float X_topleft, Y_topleft;
};

class Map{
    int rows, columns;
    float width, height;

    //100 default since I couldn't get dynamic size initialization to work
    vector<tile> tiles[100];

public:
    void init(int r, int c, int screenW, int screenH);
    void draw();
    void update(float dt, float screenW, float screenH);
};
