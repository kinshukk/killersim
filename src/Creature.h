#include "utilities.h"
#include "ofMain.h"

class Creature{
    float position_x, position_y;
    float vel_x, vel_y;
    float radius;

public:
    Creature(float x, float y, float v_x, float v_y);

    //to draw the creature
    void draw();

    //for deciding movement
    void update(float dt, float screenW, float screenH);
};
