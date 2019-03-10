#pragma once

#include "ofMain.h"
#include "Creature.h"
#include "Map.h"
#include "utilities.h"
#include <vector>
#include <string>

class ofApp : public ofBaseApp{
	float screenW, screenH;

	float dt;

	ofTrueTypeFont myFont;

	vector<Creature> creatures;

	Map tilemap;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

};