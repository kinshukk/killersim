#pragma once

#include "ofMain.h"
#include "Creature.h"
#include "Map.h"
#include "Population.hpp"
#include "utilities.h"
#include <vector>
#include <string>

#define MAX_FRAME_SKIP 500
#define ITERATION_DURATION 20

class ofApp : public ofBaseApp{
	std::pair<double, int> fittest_till_now;
	float paneW;
	float screenW, screenH;

	float dt;
    int CurrentCreature;

	ofTrueTypeFont myFont;

	std::string display_info;
	std::string display_nn;

	vector<Creature> creatures;
	Population pop;

	Map tilemap;

	bool vsync_flag;


	int frames_to_skip;
	int skipped_frame_count;
	float previousIterationTime;
	bool interlude = false;

	ofFbo buffer;

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
