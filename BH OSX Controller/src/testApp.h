#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "192.168.10.6"
#define PORT 7000
#include "ofxSimpleGuiToo.h"

//--------------------------------------------------------
class testApp : public ofBaseApp {

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
    void setupGUI();
    void transmit();
		ofTrueTypeFont font;
		ofxOscSender sender;
    
    string flockMe, gravityMe, avoidMe, resetMe, orbitMe;
    ofVec3f centre, circleLocation;
    
//    ofNode lookAt;
    
    //    ofxBoundary outer;
//    vector <ofxParticle> particles;
//    vector <ofxBody> bodies;
    
    float worldSize, torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G, bodyMass, orbitF, maxOrbitForce, ribbonWidth, scale, ribbonOpacity;
    bool reset = false, blending, depth, drawBounds, avoidBoundaries, gravitate;
    int renderMode = 0, particleCount;
    ofFloatColor	color, bgColor;
    
    ofColor col;
    
    float Red, Green, Blue, Alpha;
    //    renderVertexArray = false, renderPoints = false, renderSphere = false, renderNormal = false, renderVBO = true;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, orbit, flock;
    float separationF, cohesionF, alignF, dragF, personalSpace, perception, force, attractF, speed;
    
    int orbitInt, boundaryInt, resetInt, gravityInt, flockInt;
    //    int blendMode = -1;
    
    // BRIGHT HEARTS GRADIENTS
    int BHGShapeType, BHGNumSides;
    float BHGBlur, BHGThickness, BHGDiameter;
    
    // BRIGHT HEARTS GRADIENTS, BODY ONLY
    int bodyBHGShapeType, bodyBHGNumSides;
    float bodyBHGBlur, bodyBHGThickness, bodyBHGDiameter;

    int mode;
    
    
    // VBO RIBBONS
//    int pTotal		= MAX_PARTICLES;
	int trailIndex	= 0;
    int		posSpread;
    int		velSpread;
//    GLuint	vboRibbon[ MAX_PARTICLES * 2 ];
//    float	posRibbon[ MAX_PARTICLES ][ 3 ];
//    float	velRibbon[ MAX_PARTICLES ][ 3 ];
//    float	colRibbon[ MAX_PARTICLES ][ 4 ];
//    float	trlRibbon[ MAX_PARTICLES ][ 3 * MAX_TRAIL_LENGTH ];		// trail position.
//    float	tvrRibbon[ MAX_PARTICLES ][ 3 * MAX_TRAIL_LENGTH * 2 ];	// trail vertexes.
//    float	tclRibbon[ MAX_PARTICLES ][ 4 * MAX_TRAIL_LENGTH * 2 ];	// trail colour.
    ofVec3f	upAxis;
    float		upAxisRot;
    float		rotateY;

};

