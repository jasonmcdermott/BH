#pragma once

#include "ofMain.h"
#include "ofxParticle.h"
#include "ofxSimpleGuiToo.h"
#include "ofVbo.h"

#define ATTRACT 0
#define REPEL 1
#define NUM_BILLBOARDS 5000
#define MAX_PARTICLES		500
#define MAX_TRAIL_LENGTH	200

class testApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed  (int key);
    
    void createGUI();
    void updateGUI();
    void addParticles(int n, ofVec3f centre, int type_);
    void snapFrame();
    
    // GLOBAL
    float time, tick;
    bool guiDraw, drawBounds, saveFrame, snappy;

    // PARTICLES
    vector          <ofxParticle> particles;
    ofVec3f         centre, circleLocation;
    float           col, worldSize, torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G, bodyMass, orbitF, maxOrbitForce, ribbonWidth, mass;
    float           ribbonOpacity, separationF, cohesionF, alignF, dragF, personalSpace, pPerception, pForce, attractF, pSpeed, particleMass;
    bool            reset, blending, depth, avoidBoundaries, gravitate, avoidWalls, interactWithBodies, drawBodies, drawFlock, orbit, flocking;
    int             renderMode, particleCount;
    ofFloatColor    color, bgColor;

    // VBO & CAM
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    ofVbo vbo;
    ofShader shader;
    ofEasyCam camera;
    ofTexture texture;
    float camDist;

    // SAVING SCREEN GRABS
    ofImage img;
    int snapCounter;
    char snapString[255];

    
};
