#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    printf("setup begin\n");

    screenW = ofGetWidth();
    screenH = ofGetHeight();

    printf("got screen size\n");

    tilemap.init(50, 50, screenW, screenH);

    printf("tilemap init done");

    creatures.push_back(Creature(10, 10, 15, 20));

    //for showing FPS
    myFont.load("arial.ttf", 20);

    //match drawing framerate with screen refresh rate
    ofSetVerticalSync(true);
}

//--------------------------------------------------------------
void ofApp::update(){
    //time passed since last frame(seconds, float)
    dt = ofGetLastFrameTime();

    for(int i=0; i<creatures.size(); i++){
        creatures[i].update(dt, screenW, screenH);
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
    myFont.drawString(std::to_string((int)ofGetFrameRate()), ofGetWidth() - 40, 30);
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
