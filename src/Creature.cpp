#include "Creature.h"

Creature::Creature(float x, float y, float initial_angle, float initial_velocity){
    position_x = x;
    position_y = y;
    angle = initial_angle;
    vel = initial_velocity;
    omega = 0.0;
    radius = 20;
    health = MAX_HEALTH;

    inp = {0, 0, 0, 0, 0};
    outp = {0, 0};

    k = (5.0 * HEALTH_DECAY_PER_SEC) / (255.0);
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

    ofSetColor(0, 0, 255);
    ofDrawCircle(eye0.first, eye0.second, 10, 5);
    ofDrawCircle(eye1.first, eye1.second, 10, 5);
    ofDrawCircle(eye2.first, eye2.second, 10, 5);
    ofDrawCircle(eye3.first, eye3.second, 10, 5);
    ofSetColor(255);
}

double Creature::eating_rate_per_sec(double available_food){
    return k * available_food;
}

//decide outputs for next frame based on current inputs
void Creature::think(float dt, Map &tilemap_input){
    //normalized inputs;
    // std::cout << "Creature.cpp BREAKPOINT 1\n";

    inp[0] = tilemap_input.tile_value_at(eye0.first, eye0.second) / 255.0;
    inp[1] = tilemap_input.tile_value_at(eye1.first, eye1.second) / 255.0;
    inp[2] = tilemap_input.tile_value_at(eye2.first, eye2.second) / 255.0;
    inp[3] = tilemap_input.tile_value_at(eye3.first, eye3.second) / 255.0;
    // std::cout << "Creature.cpp BREAKPOINT 1.5\n";
    inp[4] = health / MAX_HEALTH;

    // std::cout << "Creature.cpp BREAKPOINT 2\n";

    net.evaluate(inp, outp);

    // std::cout << "Creature.cpp BREAKPOINT 3\n";

    cout << "outp vector: " << outp[0] << " " << outp[1] << "\n";

    vel = outp[0] * VEL_SCALE;
    omega = outp[1] * OMEGA_SCALE;

    std::cout << "output of NN: vel: " << vel << " | omega " << omega << "\n";

    double delta_food = eating_rate_per_sec(inp[0]) * dt;

    tilemap_input.decrease_tile_value_at(eye0, delta_food);

    health = health + delta_food - HEALTH_DECAY_PER_SEC * dt;

    if(health < 0.0){
        alive = false;
    }

    if(health > MAX_HEALTH){
        health = MAX_HEALTH;
    }

    // std::cout << "Creature.cpp BREAKPOINT 4\n";
}

//to calculate movement, behaviour
void Creature::act(float dt, float screenW, float screenH){
    angle += omega * dt;

    //pos = pos + velocity * delta_time
    position_x += vel * cos(angle) * dt;
    position_y += vel * sin(angle) * dt;

    position_x = clampValI(position_x, screenW);
    position_y = clampValI(position_y, screenH);

    eye0.first = position_x;
    eye0.second = position_y;

    eye1.first = position_x + (radius + 15) * cos(angle + PI / 6.0);
    eye1.second = position_y + (radius + 15) * sin(angle + PI / 6.0);

    eye2.first = position_x + (radius + 15) * cos(angle - PI / 6.0);
    eye2.second = position_y + (radius + 15) * sin(angle - PI / 6.0);

    eye3.first = position_x - (radius + 15) * cos(angle);
    eye3.second = position_y - (radius + 15) * sin(angle);
}
