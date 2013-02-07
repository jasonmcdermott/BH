#pragma once

#include "ofMain.h"
#include <math.h>
#include "ofxGrabCam.h"

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
        void setHSB();
    
        void drawGrid(float scale = 10.0f, float ticks = 5.0f, bool labels = false, bool x = true, bool y = true, bool z = true);
        void drawGridPlane(float scale, float ticks = 5.0f, bool labels = false);
        void drawShape(float xOffset, float yOffset, float zOffset, float width, float height, float thick, float orientationX, float orientationZ, float orientationY,ofColor top,ofColor bottom, ofColor front, ofColor back, ofColor left, ofColor right, int shapeType);
        void drawCube(float x_,float y_,float z_,ofColor f_, ofColor back_, ofColor l_, ofColor r_, ofColor t_, ofColor bottom_);
        void pSetHSV( float h, float s, float v);
    
    float           nextTime, currTime, timeCounter, timeRemainder, D, x, y;
    int             time;
    bool            tick, useViewPort;

    
    ofEasyCam       cam;
    ofMesh          mesh;
    ofLight         light;
    GLfloat         cols[3];
    ofxGrabCam      camera;

    ofColor         front,back,top, bottom, right, left;
    vector<ofVec3f> positions;
	vector<ofColor> colours;
    ofMatrix4x4     savedPose;
    ofRectangle     viewPort;
};
