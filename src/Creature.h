#ifndef _CREATURE_
#define _CREATURE_

#include "utilities.h"
#include "ofMain.h"
#include "Map.h"
#include "math.h"
#include "ann.hpp"

#define MAX_HEALTH 100

#define PI 3.14159265358979323846264338

#define HEALTH_DECAY_PER_SEC 1

#define VEL_SCALE 2000
#define OMEGA_SCALE 50

class Creature{

    float angle, vel, omega;

    //for rendering only as of now
    float radius;

    pair<double, double> eye0;
    pair<double, double> eye1;
    pair<double, double> eye2;
    pair<double, double> eye3;

    std::vector<double> inp;
    std::vector<double> outp;

    //this is the 'k' in y(x) = k*x^2, parabolic scaling of food eating rate
    //as a function of food available
    double k;

public:
    float time_alive;
    
    //range [0, 100]
    //increase every time creature eats grass
    //decrease at a constant rate every frame
    float health;

    // Brain::Genome genome;
    Brain::NeuralNet net;

    float position_x, position_y;

    bool alive = true;
    Creature(float x, float y, float v_x, float v_y);

    //to draw the creature
    void draw();

    //for moving
    void act(float dt, float screenW, float screenH);

    //decide outputs for next frame based on current inputs
    void think(float dt, Map &tilemap_input);   //paramaters?

    double eating_rate_per_sec(double available_food);
};

#endif
