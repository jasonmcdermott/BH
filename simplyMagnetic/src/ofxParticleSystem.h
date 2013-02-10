#pragma once
#include "ofxParticle.h"
#include "ofxBody.h"
#include "ofxBoundary.h"
#include "ofVbo.h"

#define ATTRACT 0
#define REPEL 1
#define NUM_BILLBOARDS 5000


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
    ofFloatColor	color, bgColor;
    float pSpeed;
    bool renderVA = false, flock, drawBounds, avoidBoundaries, gravitate;
    ofVec3f circleLocation;
    float torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G;
    float bodyMass, orbitF;

    int blendMode = -1, renderMode = 0;
    bool blending, depth;

    // Bright Hearts Gradients
    int BHGShapeType, BHGNumSides;
    float BHGBlur, BHGThickness, BHGDiameter;
    
    ofVbo vbo;
    ofShader shader;
    ofTexture texture;
    
    // upload the data to the vbo
    vector <ofVec3f> points;
    vector <ofVec3f> sizes;
    
    // VBO BILLBOARDING
    ofVec3f cameraRotation;
    float zoom, zoomTarget;
    // billboard particles
    float billboardSizeTarget[NUM_BILLBOARDS];
    ofShader billboardShader;
    ofImage billboardTexture;
    ofVboMesh billboards;
    ofVec3f billboardVels[NUM_BILLBOARDS];
    
    ofxParticleSystem() {
        worldSize = 800;
//        centre.set(ofGetWidth()/2,ofGetHeight()/2,0);
        centre.set(0,0,0);
        circleLocation.set(centre);
        bodies.push_back(ofxBody( ofVec3f(centre.x,centre.y,centre.z), 10, 0));
//        outer.setDims(centre,worldSize);
        addParticles(100, centre, 0);

        // load the texure

        ofDisableArbTex();
        ofLoadImage(texture, "dot.png");

        for (int i=0;i<particles.size();i++) {
            points.push_back(particles[i].pos);
            sizes.push_back(ofVec3f(particles[i].sc * 50));
        }

        setupVBOBillboard();
        
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
        ofBackground(bgColor);
        if (blending) {
            ofEnableAlphaBlending();
            if (blendMode == 0) ofEnableBlendMode(OF_BLENDMODE_ADD);
            if (blendMode == 1) ofEnableBlendMode(OF_BLENDMODE_SCREEN);
            if (blendMode == 2) ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
            if (blendMode == 3) ofEnableBlendMode(OF_BLENDMODE_ALPHA);
            if (blendMode == 4) ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);

        } else {
            ofDisableAlphaBlending();
        }
        if (depth) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
        
        
        // "VBO", "Spheres", "Points", "VertexArray", "Trails", "Boxes"};
        if (renderMode == 0) {
            
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
                    bodies[i].render();
                }
            }
            
            glDepthMask(GL_FALSE);

            // upload the data to the vbo
            ofSetColor(color);
            for (int i=0;i<particles.size();i++) {
                points[i].set(particles[i].pos);
                sizes[i].set(particles[i].sc*2);
            }
            
            int total = (int)points.size();
            vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
            vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
            
            ofEnablePointSprites();
            
            shader.begin();
            
            texture.bind();
            vbo.draw(GL_POINTS, 0, (int)points.size());
            texture.unbind();
            shader.end();
            
            ofDisablePointSprites();            
            glDepthMask(GL_TRUE);
        }  // VBO

        if (renderMode == 1) {
            for (int i=0;i<particles.size();i++) {
                particles[i].renderSphere();
            }
        }  // OF default Spheres
        
        if (renderMode == 2) {
            static GLfloat attenuate[3] = { 0.0, 0.0, 0.01 };  //Const, linear, quadratic
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
        } // as Points
        
        if (renderMode == 3) {
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
                    bodies[i].renderVertexArray();
                }
            }
            glEnableClientState(GL_VERTEX_ARRAY);
            for(int i=0;i<particles.size();i++) {
                particles[i].renderVertexArray();
            }
            glDisableClientState(GL_VERTEX_ARRAY);
        } // as a Vertex Array
        
        if (renderMode == 4) {
            if (drawBodies) {
                for (int i=0;i<bodies.size();i++) {
                    bodies[i].renderVertexArray();
                }
            }
            glEnableClientState(GL_COLOR_ARRAY);
            glEnableClientState(GL_VERTEX_ARRAY);
            for(int i=0;i<particles.size();i++) {
                particles[i].renderBHGradients();
            }
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
            
        } // old BRIGHT HEARTS RENDER VISUALS!
        
        if (renderMode == 5) {
            
        } // the soon-to-be-added trail rendering mode..!
        
        if (renderMode == 6) {
            float t = (ofGetElapsedTimef()) * 0.9f;
            float div = 250.0;
            
            for (int i=0; i<NUM_BILLBOARDS; i++) {
                
                // noise
                ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
                            ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
                            ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
                
                vec *= 10 * ofGetLastFrameTime();
                billboardVels[i] += vec;
                billboards.getVertices()[i] += billboardVels[i];
                billboardVels[i] *= 0.94f; 
                billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
            }
            
            ofPushMatrix();
            ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
            ofRotate(cameraRotation.x, 1, 0, 0);
            ofRotate(cameraRotation.y, 0, 1, 0);
            ofRotate(cameraRotation.y, 0, 0, 1);
            
            // bind the shader so that we can change the
            // size of the points via the vert shader
            billboardShader.begin();
            
            ofEnablePointSprites();
            billboardTexture.getTextureReference().bind();
            billboards.draw();
            billboardTexture.getTextureReference().unbind();
            ofDisablePointSprites();
            
            billboardShader.end();
            
            ofPopMatrix();

            
        } // VBO Billboarding
        
        if (renderMode == 7) {
            for(int i=0;i<particles.size();i++) {
                particles[i].renderDebug();
            }
        } // Debug Rendering
        
        if (drawBodies) {
            for (int i=0;i<bodies.size();i++) {
                bodies[i].render();
            }
        }

        
        if (blending) ofEnableAlphaBlending();
        if (blendMode == 0 || blendMode == 1 || blendMode == 2 || blendMode == 3) ofDisableBlendMode();
        
        if (drawBounds) {
            ofFill();
            ofSetColor(125);
            ofSphere(circleLocation, torusInnerRadius * 0.45);
            ofNoFill();
            ofSetColor(125);
            ofSphere(circleLocation, torusOuterRadius * 0.55);
        }
    }
    
    
    void setupVBOBillboard() {
        billboards.getVertices().resize(NUM_BILLBOARDS);
        billboards.getColors().resize(NUM_BILLBOARDS);
        billboards.getNormals().resize(NUM_BILLBOARDS,ofVec3f(0));
        
        // ------------------------- billboard particles
        for (int i=0; i<NUM_BILLBOARDS; i++) {
            billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
            billboards.getVertices()[i].set(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500));
            billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(96, 160), 255, 255));
            billboardSizeTarget[i] = ofRandom(4, 64);
        }
        billboards.setUsage( GL_DYNAMIC_DRAW );
        billboards.setMode(OF_PRIMITIVE_POINTS);
        //billboardVbo.setVertexData(billboardVerts, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
        //billboardVbo.setColorData(billboardColor, NUM_BILLBOARDS, GL_DYNAMIC_DRAW);
        
        // load the bilboard shader
        // this is used to change the
        // size of the particle
        billboardShader.load("Billboard");
        
        // we need to disable ARB textures in order to use normalized texcoords
        ofDisableArbTex();
        billboardTexture.loadImage("dot.png");
    }
    
    void addParticles(int n, ofVec3f centre, int type_) {
        for(int i=0;i<n;i++) {
            particles.push_back(ofxParticle(particleCount, centre, type_));
            particleCount ++;
        }
    }
    
    void updateGUI() {
//        outer.length = worldSize;

        for(int i=0;i<particles.size();i++) {
            particles[i].avoidBoundaries = avoidBoundaries;
            particles[i].separationF = separationF;
            particles[i].cohesionF = cohesionF;
            particles[i].alignF = alignF;
            particles[i].pPerception = pPerception;
            particles[i].personalSpace = personalSpace;
            particles[i].pForce = pForce;
            particles[i].pSpeed = pSpeed;
            particles[i].reset = reset;
            particles[i].orbit = orbit;
            particles[i].gravitate = gravitate;
            particles[i].color = color;
            particles[i].torusOuterRadius = torusOuterRadius;
            particles[i].torusInnerRadius = torusInnerRadius;
            particles[i].circleLocation.set(circleLocation);
            particles[i].outerBoundF = outerBoundF;
            particles[i].innerBoundF = innerBoundF;
            particles[i].attractF = attractF;
            particles[i].G = G;
            particles[i].orbitF = orbitF;
            particles[i].BHGShapeType = BHGShapeType;
            particles[i].BHGBlur = BHGBlur;
            particles[i].BHGNumSides = BHGNumSides;
            particles[i].BHGThickness = BHGThickness;
            particles[i].BHGDiameter = BHGDiameter;
        }
        for (int i=0;i<bodies.size();i++) {
            bodies[i].mass = bodyMass;
        }
    }
    
};