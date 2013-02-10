#pragma once
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>


class ofxBody{
public:
    
    ofVec3f pos;
    float mass, radius;
    int charge;
    ofFloatColor	color;
    
    ofxBody(ofVec3f loc_, float mass_, int charge_) {
        pos.set(loc_);
        mass = mass_;
        charge = charge_;
        radius = mass;
        color.set(255,255,255,255);
    }
    
    void update() {

    }
    
    void addMass(float m) {
        mass = mass + m;
    }
    
    void render() {
        radius = mass;
        ofSetColor(255);
        ofSphere(pos,radius);
    }
    
    void renderVertexArray() {
        ofSetColor(color);
        ofSphere(pos.x,pos.y,pos.z,radius/10);
    }
    
    void renderPoints() {
        glEnable(GL_POINT_SIZE);
        glPointSize(mass);
        ofSetColor(color);
        glVertex3f(pos.x,pos.y,pos.z);
    }
};




