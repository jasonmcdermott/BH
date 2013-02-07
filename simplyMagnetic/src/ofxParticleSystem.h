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
    int boidCount;
    bool reset = false;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, drawPreds, interactWithPredators;
    float separationF, cohesionF, alignF, dragF, personalSpace, pPerception, predPerception, predSpeed, predForce, pForce, evadeForce;
    ofFloatColor	boidColor;
    float pSpeed;
    bool renderVA = true, flock, drawBounds;
    ofVec3f circleLocation;
    float torusInnerRadius, torusOuterRadius;
    
    ofxParticleSystem() {
        worldSize = 800;
        centre.set(ofGetWidth()/2,ofGetHeight()/2,0);
        circleLocation.set(centre);
        bodies.push_back(ofxBody( ofVec3f(centre), 30, ATTRACT));
        outer.setDims(centre,worldSize);
        addBoids(200, outer, centre,0);
    }
    
    void update() {
        for(int i=0;i<particles.size();i++) {
            particles[i].run(particles, outer, bodies);
        }
        if (reset == true) {
            reset = false;
        }

        if (torusInnerRadius == torusOuterRadius - 5) {
            torusOuterRadius = torusInnerRadius + 1;
        }
        if (torusOuterRadius == torusInnerRadius) {
            torusInnerRadius = torusOuterRadius - 1;
        }
        
        if (interactWithPredators) {
//            for (int i=0;i<particles.size();i++) {
//                if (particles[i].type == 1) {
//                    ofVec3f mid;
//                    ofVec3f steer;
//                    mid.set(findBoidsMidst());
//                    steer.set(particles[i].pos);
//                    steer -= mid;
//                    steer.limit(predForce);
//                    particles[i].acc += -steer;
//                }
//            }
        }
    }
    
    int countLiveBoids() {
        int liveBoidCount = 0;
        for (int i=0;i<particles.size();i++) {
            if (particles[i].isDead == false) {
                liveBoidCount ++;
            }
        }
        return liveBoidCount;
    }
    
    ofVec3f findBoidsMidst() {
        ofVec3f steer;
        steer.set(0,0,0);
        int count = 0;
        for(int i=0;i<particles.size();i++) {
            if (particles[i].type == 0 && particles[i].isDead != true) {
                steer += particles[i].pos;
            }
        }
        int c = countLiveBoids();
        steer /= c;
        return steer;
    }
    
    void draw() {

        if (drawBodies) {
            for (int i=0;i<bodies.size();i++) {
                bodies[i].draw();
            }
        }
        
        if (drawBounds == true) {
            outer.draw();
            drawBounds = true;
        } else {
            drawBounds = false;
        }


//        int n = particles.size();
//        glBegin(GL_POINTS);
//        for(int i = 0; i < n; i++)
//            particles[i].draw();
//        glEnd();

        glEnable(GL_POINT_SIZE);
        glPointSize(3);
        glBegin(GL_POINTS);
        for (int i=0;i<particles.size();i++) {
            if (drawFlock == true && particles[i].type == 0) {
                glVertex3f(particles[i].pos.x,particles[i].pos.y,particles[i].pos.z);
            }
        }
        glEnd();
        
//        for(int i=0;i<particles.size();i++) {
//            if (drawFlock == true && particles[i].type == 0) {
//                particles[i].render();
//            }
//            if (drawPreds == true && particles[i].type == 1) {
//                particles[i].render();
//            }
//        }
        
        if (drawBounds) {
            ofFill();
            ofSetColor(255);
            ofSphere(circleLocation, torusInnerRadius * 0.45);
            ofNoFill();
            ofSphere(circleLocation, torusOuterRadius * 0.55);
        }

    }
    
    void addBoids(int n, ofxBoundary outer, ofVec3f centre, int type_) {
        for(int i=0;i<n;i++) {
            particles.push_back(ofxParticle(boidCount, outer, centre, type_));
            boidCount ++;
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
            particles[i].predPerception = predPerception;
            particles[i].personalSpace = personalSpace;
//            particles[i].pForce = pForce;
            particles[i].pSpeed = pSpeed;
//            particles[i].predSpeed = predSpeed;
            particles[i].pForce = pForce;
            particles[i].evadeForce = evadeForce;
            particles[i].reset = reset;
            particles[i].interactWithBodies = interactWithBodies;
            particles[i].interactWithPredators = interactWithPredators;
            particles[i].boidColor = boidColor;
            particles[i].renderVA = renderVA;
            particles[i].torusOuterRadius = torusOuterRadius;
            particles[i].torusInnerRadius = torusInnerRadius;
            particles[i].flock = flock;
            particles[i].circleLocation.set(circleLocation);
        }
    }
    
};