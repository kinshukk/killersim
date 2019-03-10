#include "Creature.h"

Creature::Creature(float x, float y, float v_x, float v_y){
    position_x = x;
    position_y = y;
    vel_x = v_x;
    vel_y = v_y;
    radius = 30;
}

//draw the creature, duh
void Creature::draw(){
    ofSetColor(255);
    ofDrawCircle(position_x, position_y, 10, radius);
}

//to calculate movement, behaviour
void Creature::update(float dt, float screenW, float screenH){
    //pos = pos + velocity * delta_time
    position_x = clampVal(position_x + vel_x * dt, screenW);
    position_y = clampVal(position_y + vel_y * dt, screenH);
}
