#include "Creature.h"

Creature::Creature(float x, float y, float initial_angle, float initial_velocity){
    position_x = x;
    position_y = y;
    angle = initial_angle;
    vel = initial_velocity;
    omega = 1.0;
    radius = 30;
    health = MAX_HEALTH;
}

//draw the creature, duh
void Creature::draw(){
    //TODO: make color a function of health, as in, redder when low, greener when high health
    ofSetColor(255);

    //TODO: add a border to the circle, and an arrow in the directio the creature is facing
    //according to the angle value
    ofDrawCircle(position_x, position_y, 10, radius);
}

//decide outputs for next frame based on current inputs
void Creature::think(Map &tilemap_input){
    //dummy thinking loop, change to neural net evaluation
    float eye0, eye1, eye2, eye3;
    cout << "thinking" << endl;
}

//to calculate movement, behaviour
void Creature::move(float dt, float screenW, float screenH){
    angle += omega * dt;

    //pos = pos + velocity * delta_time
    position_x += vel * cos(angle) * dt;
    position_y += vel * sin(angle) * dt;

    position_x = clampValI(position_x, screenW);
    position_y = clampValI(position_y, screenH);
}
