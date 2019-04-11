#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    num_iterations = 0;

    frames_to_skip = 0;
    skipped_frame_count = 0;

    screenW = ofGetWidth();
    screenH = ofGetHeight();

    buffer.allocate(screenW, screenH);

    tilemap.init(20, 20, screenW, screenH);

    pop.initialize_random(10);

    std::random_device rd;
    std::mt19937 gen(rd()); //mersenne twister
    std::uniform_int_distribution<> random_dis(50, min(screenW, screenH) - 50);

    for(int i=0; i<pop.actors.size(); i++){
        pop.actors[i].position_x = random_dis(gen);
        pop.actors[i].position_y = random_dis(gen);
    }

    //for showing FPS
    myFont.load("arial.ttf", 20);

    vsync_flag = true;
    info_flag=false;
    pos_flag=false;

    //match drawing framerate with screen refresh rate
    ofSetVerticalSync(vsync_flag);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetElapsedTimef() > (num_iterations + 1) * ITERATION_DURATION){
        pop.init_next_generation(2, screenW, screenH);

        std::cout << "initialized next gen, in update function now\n";
        num_iterations += 1;
        tilemap.regenerate_values();
    }

    display_text = "";
    display_pos = "";

    //time passed since last frame(seconds, float)
    dt = ofGetLastFrameTime();

    for(int i=0; i<pop.actors.size(); i++){
        // std::cout << "ofApp.cpp BREAKPOINT 2\n";
        if(pop.actors[i].alive){
            // std::cout << "creature" << i << ": \n";
            // std::cout << "ofApp.cpp BREAKPOINT 3\n";
            pop.actors[i].think(dt, tilemap);
            // std::cout << "ofApp.cpp BREAKPOINT 4\n";
            pop.actors[i].act(dt, screenW, screenH);

            if(pop.actors[i].health <= 0.0){
                cout << i << " died\n";
                pop.actors[i].alive = false;
                pop.actors[i].time_alive = ofGetElapsedTimef() - pop.timeSinceLastIteration;
            }
        }

        // display_pos += "\n" + std::to_string(i) + " " + std::to_string(pop.actors[i].position_x) + ", " + std::to_string(pop.actors[i].position_y);
    }

    tilemap.update(dt, screenW, screenH);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(skipped_frame_count >= frames_to_skip){
        buffer.begin();

        ofBackground(0);  // Clear the screen with a black color
        ofSetColor(255);  // Set the drawing color to white

        tilemap.draw();

        for(int i=0; i<pop.actors.size(); i++){
            if(pop.actors[i].alive){
                pop.actors[i].draw();
            }
        }

        if(pos_flag){
            myFont.drawString(display_pos,ofGetWidth() - 500,100);
        }

        display_info="Number of actors " + std::to_string((int)pop.actors.size()) + "\n" + "Food Decay Rate "+std::to_string((int)tilemap.delta_food_per_sec);

        if(info_flag){
            myFont.drawString(display_info, ofGetWidth() - 900, 30);
        }
        //Display FPS on top-right of screen
        display_text = std::to_string((int)ofGetFrameRate()) + "\n" + display_text;
        myFont.drawString(display_text, ofGetWidth() - 40, 30);

        buffer.end();
    }

    buffer.draw(0, 0);

    if(frames_to_skip > 0){
        skipped_frame_count++;
        if(skipped_frame_count > frames_to_skip){
            skipped_frame_count %= frames_to_skip;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'r':   //randomize tiles
            tilemap.regenerate_values();
            break;
        case 'w':
            tilemap.increase_delta_food();
            break;
        case 's':
            tilemap.decrease_delta_food();
            break;
        case 'v':   //toggle vsync
            vsync_flag = !vsync_flag;
            ofSetVerticalSync(vsync_flag);
            break;
        case 'a':
            frames_to_skip = clampValI(frames_to_skip-1, MAX_FRAME_SKIP);
            break;
        case 'd':
            frames_to_skip = clampValI(frames_to_skip+1, MAX_FRAME_SKIP);
            break;
        case 'i':
            info_flag=!info_flag;
            break;
        case 'p':
            pos_flag=!pos_flag;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
