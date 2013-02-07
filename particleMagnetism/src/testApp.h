#pragma once

#include "ofMain.h"
#include <math.h>
#include "ParticleSystem.h"
#include <vector>
#define NUM_PARTICLES 48

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
        void pSetHSV( float h, float s, float v);
        void drawInfoStrings();
        void increaseTime();
    

    float           nextTime, currTime, timeCounter, timeRemainder, D, x, y;
    int             time;
    bool            tick, useViewPort;
    
    ofEasyCam       cam;
    ofMesh          mesh;
    ofLight         light;
    GLfloat         cols[3];

    ofColor         front,back,top, bottom, right, left;
    vector<ofVec3f> positions;
	vector<ofColor> colours;
    ofMatrix4x4     savedPose;
    ofRectangle     viewPort;
    ofImage original;
    
    
    ParticleSystem		particleSystem;
    
};

extern testApp *myApp;