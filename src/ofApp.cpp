#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    screenW = ofGetWidth();
    screenH = ofGetHeight();

    tilemap.init(20, 20, screenW, screenH);

    creatures.push_back(Creature(200,    //X
                                 200,    //Y
                                 60,    //initial_angle
                                 50     //initial_velocity
                                )
                       );

    //for showing FPS
    myFont.load("arial.ttf", 20);

    vsync_flag = true;

    //match drawing framerate with screen refresh rate
    ofSetVerticalSync(vsync_flag);
}

//--------------------------------------------------------------
void ofApp::update(){
    display_text = "";

    //time passed since last frame(seconds, float)
    dt = ofGetLastFrameTime();

    for(int i=0; i<creatures.size(); i++){
        creatures[i].think(tilemap);
        creatures[i].move(dt, screenW, screenH);

        //TODO: make this work with keypress flag
        // display_text += "\n" + i + " " + creatures[i].position_x + ", " + creatures[i].position_y;
    }

    tilemap.update(dt, screenW, screenH);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);  // Clear the screen with a black color
    ofSetColor(255);  // Set the drawing color to white

    tilemap.draw();

    for(int i=0; i<creatures.size(); i++){
        creatures[i].draw();
    }

    //TODO: toggle show info on top right when a key is pressed
    //info other than FPS as well, like delta_food_per_sec, num of creatures on the map, etc.

    //Display FPS on top-right of screen
    display_text = std::to_string((int)ofGetFrameRate()) + "\n" + display_text;

    myFont.drawString(display_text, ofGetWidth() - 40, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'r':
            tilemap.regenerate_values();
            break;
        case 'w':
            tilemap.increase_delta_food();
            break;
        case 's':
            tilemap.decrease_delta_food();
            break;
        case 'v':
            vsync_flag = !vsync_flag;
            ofSetVerticalSync(vsync_flag);
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
