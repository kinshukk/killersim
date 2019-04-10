#include "Creature.h"
#include "math.h"

Creature::Creature(float x, float y, float initial_angle, float initial_velocity){
    position_x = x;
    position_y = y;
    angle = initial_angle;
    vel = initial_velocity;
    omega = 0.05;
    radius = 20;
    health = MAX_HEALTH/2;
}

//draw the creature, duh
void Creature::draw(){
    //border circle;
    ofSetColor(0);
    ofDrawCircle(position_x, position_y, 10, radius+1);

    ofColor hitpoints;
    hitpoints.r=255-(health*2.55);
    hitpoints.g=health*2.55;
    hitpoints.b=0;
    ofSetColor(hitpoints);
    ofDrawCircle(position_x, position_y, 10, radius);

    ofVec3f tailend;
    tailend.set(position_x,position_y,10);
    ofVec3f headend;
    headend.set(position_x + radius*cos(angle), position_y + radius*sin(angle), 10);
    ofSetColor(255);
    ofDrawArrow(tailend, headend, radius / 4.0);
}

//decide outputs for next frame based on current inputs
void Creature::think(Map &tilemap_input){
    //dummy thinking loop, change to neural net evaluation
    float eye0, eye1, eye2, eye3;

    // cout << "food at centre: " << tilemap_input.tile_value_at(position_x, position_y).value;
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
