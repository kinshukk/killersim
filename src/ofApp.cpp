#include "ofApp.h"
#include "Creature.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fittest_till_now = std::make_pair(0, 0);
    frames_to_skip = 0;
    skipped_frame_count = 0;

    screenH = ofGetHeight();
    screenW = screenH;
    paneW = ofGetWidth() - screenH;

    buffer.allocate(ofGetWidth(), screenH);

    tilemap.init(40, 40, screenW, screenH);

    pop.initialize_random(10);

    std::random_device rd;
    std::mt19937 gen(rd()); //mersenne twister
    std::uniform_int_distribution<> random_dis(50, min(screenW, screenH) - 50);

    for(int i=0; i<pop.actors.size(); i++){
        pop.actors[i].position_x = random_dis(gen);
        pop.actors[i].position_y = random_dis(gen);
    }

    pop.num_dead = 0;

    //for showing FPS
    myFont.load("arial.ttf", 20);

    vsync_flag = true;
    pos_flag=false;
    //match drawing framerate with screen refresh rate
    ofSetVerticalSync(vsync_flag);

    previousIterationTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
    if(ofGetElapsedTimef() - previousIterationTime > ITERATION_DURATION
        || pop.num_dead >= pop.num_actors){
        std::pair<double, int> fittest_here = pop.getFittestN(1)[0];

        if(fittest_till_now.first < fittest_here.first){
            fittest_till_now = fittest_here;
        }

        pop.init_next_generation(4, screenW, screenH);

        std::cout << "initialized next gen, in update function now\n";
        tilemap.regenerate_values();
        previousIterationTime = ofGetElapsedTimef();
        pop.num_dead = 0;
    }

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
                pop.num_dead++;
            }
        }

    }

    tilemap.update(dt, screenW, screenH);
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(skipped_frame_count >= frames_to_skip){
        buffer.begin();

        ofBackground(0);  // Clear the screen with a black color
        ofSetColor(255);  // Set the drawing color to white
        ofColor black(0,0,0);
        ofColor white(255,255,255);
        tilemap.draw();

        for(int i=0; i<pop.actors.size(); i++){
            if(pop.actors[i].alive){
                pop.actors[i].draw();
            }
        }

        display_info="Number of actors " + std::to_string((int)pop.actors.size()) + "\n" + "Food Growth Rate "+std::to_string((int)tilemap.delta_food_per_sec);
        //Display FPS on top-right of screen
        display_info = std::to_string((int)ofGetFrameRate()) + "\n" + display_info;
        display_info = display_info + "\n\nFittest Creature\n";
        display_info += "Generation: " + std::to_string(fittest_till_now.second);
        display_info += "\nFitness: " + std::to_string(fittest_till_now.first);
        display_info += "\n\nHealth Decay 8 Per Second";
        display_info += "\nEating Rate Multiplier: "+std::to_string(0.000692042);
        display_info += "\nLength of Iteration: "+std::to_string(ofGetElapsedTimef()-previousIterationTime);
        std::cout << display_info << endl;
        ofDrawBitmapStringHighlight(display_info, screenW + 10, 30,black,white);

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
