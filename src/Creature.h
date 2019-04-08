#include "utilities.h"
#include "ofMain.h"
#include "Map.h"

#define MAX_HEALTH 100

class Creature{
    float position_x, position_y;

    float angle, vel, omega;

    //for rendering only as of now
    float radius;

    //range [0, 100]
    //increase every time creature eats grass
    //decrease at a constant rate every frame
    float health;

public:
    Creature(float x, float y, float v_x, float v_y);

    //to draw the creature
    void draw();

    //for moving
    void move(float dt, float screenW, float screenH);

    //decide outputs for next frame based on current inputs
    void think(Map &tilemap_input);   //paramaters?
};
