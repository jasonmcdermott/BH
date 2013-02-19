#pragma once
#include "ofVec3f.h"
#include "ofMain.h"
#include <vector>
#include <math.h>

class ofxBody{
public:
    
    ofVec3f pos;
    float mass, radius;
    int charge;
    ofFloatColor color;
    GLfloat cols[3];
    
    // BRIGHT HEARTS GRADIENTS
    int BHGShapeType, BHGNumSides;
    float BHGBlur, BHGThickness, BHGDiameter;
    float blur, diameter, thickness, Alpha, numSides, middleRadius;
    
    ofxBody(ofVec3f loc_, float mass_, int charge_) {
        pos.set(loc_);
        mass = mass_;
        charge = charge_;
        radius = mass;
        color.set(255,255,255,255);
        BHGNumSides = 60;
        BHGThickness = 10;
        BHGDiameter = mass;
        BHGBlur = 1;
        BHGShapeType = 0;
    }
    
    void update() {}
    
    void addMass(float m) { mass = mass + m; }
    
    void render() { radius = mass; ofSetColor(255); ofSphere(pos,mass); }
    
    void renderVertexArray() { ofSetColor(color); ofSphere(pos.x,pos.y,pos.z,mass); }
    
    void renderBHGradients() {
        if (BHGShapeType == 0) {
            drawGradient(mass - BHGBlur, 0, color.a, 0, BHGNumSides);
            drawGradient(mass, mass - BHGBlur, 0, 0, BHGNumSides);
        } else if (BHGShapeType == 1) {
            drawGradient(mass + BHGThickness - BHGBlur, mass - BHGThickness + BHGBlur, color.a, 0, BHGNumSides);
            drawGradient(mass + BHGThickness, mass + BHGThickness - BHGBlur, 0, 0, BHGNumSides);
            drawGradient(mass - BHGThickness, mass - BHGThickness + BHGBlur, 0, 0, BHGNumSides);
        } else if (BHGShapeType == 2) {
            drawGradient(mass - BHGThickness, mass + BHGThickness, 0, 0, BHGNumSides);
            drawGradient(mass + BHGThickness + BHGThickness * 0.05, mass + BHGThickness, 0, 0, BHGNumSides);
        }
    }
    
    void drawGradient(float opaque_, float transp_, float opac_, float blur_, int ns_) {
        
        ofPushMatrix();
        ofTranslate(pos.x,pos.y,pos.z);
        
        GLfloat* body_ver_coords = new GLfloat[ (ns_+1) * 4];
        GLfloat* body_ver_cols = new GLfloat[ (ns_+1) * 8];
        
        float angle;
        float angleSize =  2*PI/ns_;
        
        //        float Range = abs(opaque-transp);
        
        if (opaque_ < transp_) {
            middleRadius = opaque_ - ((transp_-opaque_)+blur_);
            //            middleradius = ofMap(blur_,0,1,opaque,transp);
        } else {
            middleRadius = opaque_ - ((transp_-opaque_)+blur_);
            //            middleradius = ofMap(blur_,0,1,transp,opaque);
        }
        
        middleRadius = (opaque_ + transp_)/2;
        
        for (int i=0; i< (1+ns_); i++) {
            angle = i* angleSize;
            body_ver_coords[i*4+0] = (opaque_*cos(angle));
            body_ver_coords[i*4+1] = (opaque_*sin(angle));
            body_ver_cols[i*8+0] = color.r;
            body_ver_cols[i*8+1] = color.g;
            body_ver_cols[i*8+2] = color.b;
            body_ver_cols[i*8+3] = opac_;
            body_ver_coords[i*4+2] = (transp_*cos(angle));
            body_ver_coords[i*4+3] = (transp_*sin(angle));
            body_ver_cols[i*8+4] = color.r;
            body_ver_cols[i*8+5] = color.g;
            body_ver_cols[i*8+6] = color.b;
            body_ver_cols[i*8+7] = color.a;
        }
        
        
        glVertexPointer( 2, GL_FLOAT, 0, body_ver_coords);
        glColorPointer(4, GL_FLOAT, 0, body_ver_cols);
        glDrawArrays( GL_TRIANGLE_STRIP, 0, ( ns_ + 1 ) * 2 );
        
        delete[] body_ver_coords;
        delete[] body_ver_cols;
        ofPopMatrix();
    }
    
    void renderPoints() {
        glEnable(GL_POINT_SIZE);
        glPointSize(mass);
        ofSetColor(color);
        glVertex3f(pos.x,pos.y,pos.z);
    }
};




