#pragma once

#include "ofMain.h"
#include "ofxParticleSystem.h"
#include "ofxSimpleGuiToo.h"
#include "ofCamera.h"
#include <time.h>

#define WORLDSIZE 800

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void snapFrame();
    
    ofImage img;
    int snapCounter;
    char snapString[255];
    
    void setupGUI();
    void updateGUI();
    
    ofxParticleSystem ps;

    float time, tick;
    bool guiDraw, drawBounds, saveFrame;
    
    ofCamera cam;
    ofVec3f camPos;
    bool camDraw;
//    bool	reset, avoidWalls, interactWithBodies, drawBodies, drawFlock, drawPreds;
//    float separationF, cohesionF, alignF, dragF, personalSpace, boidPerception, predPerception, maxForce, maxSpeed;
//    float worldSize;

    

    
};
