#include "Creature.h"

Creature::Creature(float x, float y, float initial_angle, float initial_velocity){
    position_x = x;
    position_y = y;
    angle = initial_angle;
    vel = initial_velocity;
    omega = 1.0;
    radius = 30;
}

//draw the creature, duh
void Creature::draw(){
    ofSetColor(255);
    ofDrawCircle(position_x, position_y, 10, radius);
}

//decide outputs for next frame based on current inputs
void think(){

}

//to calculate movement, behaviour
void Creature::move(float dt, float screenW, float screenH){
    angle += omega * dt;

    //pos = pos + velocity * delta_time
    position_x += vel * cos(angle) * dt;
    position_y += vel * sin(angle) * dt;

    position_x = clampVal(position_x, screenW);
    position_y = clampVal(position_y, screenH);
}
