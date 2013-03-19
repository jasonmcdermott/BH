#pragma once
#include "ofxParticle.h"
#include "ofxBody.h"
//#include "ofxBoundary.h"
#include "ofVbo.h"

#define ATTRACT 0
#define REPEL 1
#define NUM_BILLBOARDS 5000
#define MAX_PARTICLES		500
#define MAX_TRAIL_LENGTH	200

class ofxParticleSystem {
public:
    ofVec3f centre, circleLocation;
    vector <ofxParticle> particles;
    vector <ofxBody> bodies;
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    
    float col, worldSize, torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G, bodyMass, orbitF, maxOrbitForce, ribbonWidth, mass, ribbonOpacity, separationF, cohesionF, alignF, dragF, personalSpace, pPerception, pForce, attractF, pSpeed, particleMass;
    bool reset = false, blending, depth, drawBounds, avoidBoundaries, gravitate;
    int renderMode = 0, particleCount;
    ofFloatColor	color, bgColor;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, orbit;

    
    ofVbo vbo;
    ofShader shader;
    ofTexture texture;
    
    ofxParticleSystem() {
        worldSize = 800;
//        centre.set(0,0,0);
//        circleLocation.set(centre);
//        bodies.push_back(ofxBody( ofVec3f(centre.x,centre.y,centre.z), 10, 0));
//        addParticles(100, centre, 0);

//        ofDisableArbTex();
//        ofLoadImage(texture, "dot.png");

//        for (int i=0;i<particles.size();i++) {
//            points.push_back(particles[i].pos);
//            sizes.push_back(ofVec3f(particles[i].sc));
//        }
        
//        // upload the data to the vbo
//        int total = (int)points.size();
//        vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
//        vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
//        
//        // load the shader
//        if(shader.load("shader")) {
//            printf("Shader is loaded\n");
//        }

    }

    
    void update() {
//        updateGUI();
//        for(int i=0;i<particles.size();i++) {
//            particles[i].run(particles, bodies);
//        }
//        if (reset == true) {
//            reset = false;
//        }
//        // upload the data to the vbo
//        ofSetColor(color);
//        for (int i=0;i<particles.size();i++) {
//            points[i].set(particles[i].pos);
//            sizes[i].set(particles[i].scale);
//        }
//        
//        int total = (int)points.size();
//        vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
//        vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
    }
    
    void render() {
        
//        glDepthMask(GL_FALSE);
//        
//        ofBackground(bgColor);
//        
//        ofEnableAlphaBlending();
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
////        glEnable(GL_DEPTH_TEST);
//        
//        ofEnablePointSprites();
//        shader.begin();
//        
//        texture.bind();
//        vbo.draw(GL_POINTS, 0, (int)points.size());
//        texture.unbind();
//
//        shader.end();
//        
//        ofDisablePointSprites();            
//        glDepthMask(GL_TRUE);
//
//        ofDisableAlphaBlending();
        
    }
    
//    void addParticles(int n, ofVec3f centre, int type_) {
//        for(int i=0;i<n;i++) {
//            particles.push_back(ofxParticle(particleCount, centre, type_));
//            particleCount ++;
//        }
//    }
    
//    void updateGUI() {
//
//        for(int i=0;i<particles.size();i++) {
//            particles[i].avoidBoundaries = avoidBoundaries;
//            particles[i].separationF = separationF;
//            particles[i].cohesionF = cohesionF;
//            particles[i].alignF = alignF;
//            particles[i].pPerception = pPerception;
//            particles[i].personalSpace = personalSpace;
//            particles[i].pForce = pForce;
//            particles[i].pSpeed = pSpeed;
//            particles[i].reset = reset;
//            particles[i].orbit = orbit;
//            particles[i].gravitate = gravitate;
//            particles[i].color = color;
//            particles[i].torusOuterRadius = torusOuterRadius;
//            particles[i].torusInnerRadius = torusInnerRadius;
//            particles[i].circleLocation.set(circleLocation);
//            particles[i].outerBoundF = outerBoundF;
//            particles[i].innerBoundF = innerBoundF;
//            particles[i].attractF = attractF;
//            particles[i].G = G;
//            particles[i].orbitF = orbitF;
//            particles[i].maxOrbitForce = maxOrbitForce;
//            particles[i].ribbonWidth = ribbonWidth;
//            particles[i].mass = particleMass;
//            particles[i].dragF = dragF;
//        }
//    }
    
};

