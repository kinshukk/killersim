#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    frames_to_skip = 0;
    skipped_frame_count = 0;

    screenW = ofGetWidth();
    screenH = ofGetHeight();

    buffer.allocate(screenW, screenH);

    tilemap.init(20, 20, screenW, screenH);

    // creatures.push_back(Creature(200,    //X
    //                              200,    //Y
    //                              0,    //initial_angle
    //                              30     //initial_velocity
    //                             )
    //                    );

    pop.initialize_random(2);

    for(int i=0; i<pop.actors.size(); i++){
        pop.actors[i].position_x = 100;
        pop.actors[i].position_y = 100;
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
    // std::cout << "ofApp update() start\n";
    display_text = "";
    display_pos = "";

    //time passed since last frame(seconds, float)
    dt = ofGetLastFrameTime();

    // std::cout << "ofApp.cpp BREAKPOINT 1\n";

    // for(int i=0; i<creatures.size(); i++){
    //     if(creatures[i].alive){
    //         creatures[i].think(dt, tilemap);
    //         creatures[i].act(dt, screenW, screenH);
    //
    //         //TODO: make this work with keypress flag
    //         display_pos += "\n" + std::to_string(i) + " " + std::to_string(creatures[i].position_x) + ", " + std::to_string(creatures[i].position_y);
    //     }
    // }

    for(int i=0; i<pop.actors.size(); i++){
        // std::cout << "ofApp.cpp BREAKPOINT 2\n";
        if(pop.actors[i].alive){
            // std::cout << "ofApp.cpp BREAKPOINT 3\n";
            pop.actors[i].think(dt, tilemap);
            // std::cout << "ofApp.cpp BREAKPOINT 4\n";
            pop.actors[i].act(dt, screenW, screenH);
        }

        // display_pos += "\n" + std::to_string(i) + " " + std::to_string(pop.actors[i].position_x) + ", " + std::to_string(pop.actors[i].position_y);
    }
    // std::cout << "ofApp.cpp BREAKPOINT end\n";

    tilemap.update(dt, screenW, screenH);

    // std::cout << "ofApp update() end\n";
}

//--------------------------------------------------------------
void ofApp::draw(){
    // std::cout << "ofApp draw() start\n";
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
        // cout << skipped_frame_count << endl;
        if(skipped_frame_count > frames_to_skip){
            // cout << "mod" << endl;
            skipped_frame_count %= frames_to_skip;
        }
    }

    // std::cout << "ofApp draw() end\n";
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
