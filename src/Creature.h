#include "utilities.h"
#include "ofMain.h"
#include "Map.h"
#include "math.h"
#include "ann.hpp"

#define MAX_HEALTH 100

//per second
#define MAX_EAT_RATE 10

#define PI 3.14159265358979323846264338

class Creature{
    float position_x, position_y;

    float angle, vel, omega;

    //for rendering only as of now
    float radius;

    //range [0, 100]
    //increase every time creature eats grass
    //decrease at a constant rate every frame
    float health;

    pair<double, double> eye0;
    pair<double, double> eye1;
    pair<double, double> eye2;
    pair<double, double> eye3;

    // Brain::Genome genome;
    // Brain::NeuralNet brain;

public:

    bool alive = true;
    Creature(float x, float y, float v_x, float v_y);

    //to draw the creature
    void draw();

    //for moving
    void move(float dt, float screenW, float screenH);

    //decide outputs for next frame based on current inputs
    void think(Map &tilemap_input);   //paramaters?
};
