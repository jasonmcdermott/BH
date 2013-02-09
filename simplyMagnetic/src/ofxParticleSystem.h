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
    bool reset = false, renderVertexArray = false, renderPoints = false, renderSphere = false, renderNormal = false, renderVBO = true;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, orbit, interactWithPredators;
    float separationF, cohesionF, alignF, dragF, personalSpace, pPerception, predPerception, predSpeed, predForce, pForce, evadeForce, attractF;
    ofFloatColor	color;
    float pSpeed;
    bool renderVA = true, flock, drawBounds;
    ofVec3f circleLocation;
    float torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G;
    float bodyMass, orbitF;
    
    ofVbo vbo;
    ofShader shader;
    ofTexture texture;
    
    // upload the data to the vbo
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    
    ofxParticleSystem() {
        worldSize = 800;
        centre.set(ofGetWidth()/2,ofGetHeight()/2,0);
        circleLocation.set(centre);
        bodies.push_back(ofxBody( ofVec3f(centre.x,centre.y,centre.z), 10, 0));
        outer.setDims(centre,worldSize);
        addParticles(100, outer, centre, 0);

        // load the texure

        ofDisableArbTex();
        ofLoadImage(texture, "dot.png");

        for (int i=0;i<particles.size();i++) {
            points.push_back(particles[i].pos);
            sizes.push_back(ofVec3f(particles[i].sc * 50));
        }

        
        // load the shader
        if(shader.load("shader")) {
            printf("Shader is loaded\n");
        }
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
        
        if (renderVBO) {
            
            glDepthMask(GL_FALSE);

            // upload the data to the vbo
            ofSetColor(color);
            for (int i=0;i<particles.size();i++) {
                points[i].set(particles[i].pos);
                sizes[i].set(particles[i].sc * 50);
            }
            
            int total = (int)points.size();
            vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
            vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
            
            // this makes everything look glowy :)
            ofEnableBlendMode(OF_BLENDMODE_ADD);
            ofEnablePointSprites();
            
            shader.begin();
            
            texture.bind();
            vbo.draw(GL_POINTS, 0, (int)points.size());
            texture.unbind();
            shader.end();
            
            ofDisablePointSprites();
            ofDisableBlendMode();
            
            
            ofEnableAlphaBlending();
            
            glDepthMask(GL_TRUE);
        }
        
        
        if (renderNormal) {
            for (int i=0;i<particles.size();i++) {
                particles[i].render();
            }
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
                        bodies[i].render();
                }
            }
        }
        
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
            particles[i].orbit = orbit;
            particles[i].interactWithBodies = interactWithBodies;
            particles[i].color = color;
            particles[i].torusOuterRadius = torusOuterRadius;
            particles[i].torusInnerRadius = torusInnerRadius;
            particles[i].circleLocation.set(circleLocation);
            particles[i].outerBoundF = outerBoundF;
            particles[i].innerBoundF = innerBoundF;
            particles[i].attractF = attractF;
            particles[i].G = G;
            particles[i].orbitF = orbitF;
        }
        for (int i=0;i<bodies.size();i++) {
            bodies[i].mass = bodyMass;
        }
    }
    
};