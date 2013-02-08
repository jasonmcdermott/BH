#pragma once
#include "ofxParticle.h"
#include "ofxBody.h"
#include "ofxBoundary.h"

#define ATTRACT 0
#define REPEL 1


class ofxParticleSystem {
public:
    ofVec3f centre;
    ofxBoundary outer;
    vector <ofxParticle> particles;
    vector <ofxBody> bodies;

    float col, worldSize;
    int particleCount;
    bool reset = false, renderVertexArray = false, renderPoints = true, renderSphere = false;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, drawPreds, interactWithPredators;
    float separationF, cohesionF, alignF, dragF, personalSpace, pPerception, predPerception, predSpeed, predForce, pForce, evadeForce, attractF;
    ofFloatColor	color;
    float pSpeed;
    bool renderVA = true, flock, drawBounds;
    ofVec3f circleLocation;
    float torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, bodyChargeF;
    float bodyMass;
    
    ofxParticleSystem() {
        worldSize = 800;
        centre.set(ofGetWidth()/2,ofGetHeight()/2,0);
        circleLocation.set(centre);
        bodies.push_back(ofxBody( ofVec3f(centre.x,centre.y,centre.z), 10, 0));
        outer.setDims(centre,worldSize);
        addParticles(50, outer, centre,0);
    }
    
    void update() {
        for(int i=0;i<particles.size();i++) {
            particles[i].run(particles, outer, bodies);
        }
        if (reset == true) {
            reset = false;
        }
        if (torusInnerRadius > torusOuterRadius) {
            torusOuterRadius = torusInnerRadius + 5;
        }
        if (torusOuterRadius < torusInnerRadius) {
            torusInnerRadius = torusOuterRadius - 5;
        }
    }
        
    void render() {

        
        if (renderSphere) {
            for (int i=0;i<particles.size();i++) {
//                particles[i].renderSphere();
            }
            
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
//                    bodies[i].renderSphere();
                }
            }
        }
        
        if (renderPoints) {
            static GLfloat attenuate[3] = { 0.0, 0.0, 0.01 };  //Const, linear, quadratic

//            glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, attenuate);
            glEnable(GL_POINT_SIZE);
            glPointSize(10);

            glBegin(GL_POINTS);

            for (int i=0;i<particles.size();i++) {
                particles[i].renderPoints();
            }

            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
                    bodies[i].renderPoints();
                }
            }

            glEnd();
        }

        if (renderVertexArray) {
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
//                    bodies[i].renderVA();
                }
            }
            glEnableClientState(GL_VERTEX_ARRAY);
            for(int i=0;i<particles.size();i++) {
                particles[i].renderVertexArray();
            }
            glDisableClientState(GL_VERTEX_ARRAY);
        }
        
        
        if (drawBounds) {
            ofFill();
            ofSetColor(125);
            ofSphere(circleLocation, torusInnerRadius * 0.45);
            ofNoFill();
            ofSetColor(125);
            ofSphere(circleLocation, torusOuterRadius * 0.55);
            outer.draw();
        }

    }
    
    void addParticles(int n, ofxBoundary outer, ofVec3f centre, int type_) {
        for(int i=0;i<n;i++) {
            particles.push_back(ofxParticle(particleCount, outer, centre, type_));
            particleCount ++;
        }
    }
    
    void updateGUI() {
        outer.length = worldSize;

        for(int i=0;i<particles.size();i++) {
            particles[i].avoidWalls = avoidWalls;
            particles[i].separationF = separationF;
            particles[i].cohesionF = cohesionF;
            particles[i].alignF = alignF;
            particles[i].pPerception = pPerception;
            particles[i].personalSpace = personalSpace;
            particles[i].pForce = pForce;
            particles[i].pSpeed = pSpeed;
            particles[i].reset = reset;
            particles[i].interactWithBodies = interactWithBodies;
            particles[i].color = color;
            particles[i].torusOuterRadius = torusOuterRadius;
            particles[i].torusInnerRadius = torusInnerRadius;
            particles[i].circleLocation.set(circleLocation);
            particles[i].outerBoundF = outerBoundF;
            particles[i].innerBoundF = innerBoundF;
            particles[i].attractF = attractF;
            particles[i].bodyChargeF = bodyChargeF;
        }
        for (int i=0;i<bodies.size();i++) {
            bodies[i].mass = bodyMass;
        }
    }
    
};