#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    printf("setup begin\n");

    screenW = ofGetWidth();
    screenH = ofGetHeight();

    printf("got screen size\n");

    tilemap.init(20, 20, screenW, screenH);

    printf("tilemap init done");

    creatures.push_back(Creature(200,    //X
                                 200,    //Y
                                 60,    //initial_angle
                                 50     //initial_velocity
                                )
                       );

    //for showing FPS
    myFont.load("arial.ttf", 20);

    //match drawing framerate with screen refresh rate
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    display_text = "";

    //time passed since last frame(seconds, float)
    dt = ofGetLastFrameTime();

    for(int i=0; i<creatures.size(); i++){
        creatures[i].think();
        creatures[i].move(dt, screenW, screenH);
        //TODO: make this work with keypress flag
        // display_text += "\n" + i + " " + creatures[i].position_x + ", " + creatures[i].position_y;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);  // Clear the screen with a black color
    ofSetColor(255);  // Set the drawing color to white

    tilemap.draw();

    for(int i=0; i<creatures.size(); i++){
        creatures[i].draw();
    }

    //Display FPS on top-right of screen
    display_text = std::to_string((int)ofGetFrameRate()) + "\n" + display_text;

    myFont.drawString(display_text, ofGetWidth() - 40, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
