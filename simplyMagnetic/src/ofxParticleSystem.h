#pragma once
#include "ofxParticle.h"
#include "ofxBody.h"
#include "ofxBoundary.h"
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

    float col, worldSize, torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G, bodyMass, orbitF, maxOrbitForce, ribbonWidth, mass, ribbonOpacity, separationF, cohesionF, alignF, dragF, personalSpace, pPerception, pForce, attractF, pSpeed, particleMass;
    bool reset = false, blending, depth, drawBounds, avoidBoundaries, gravitate;
    int renderMode = 0, particleCount;
    ofFloatColor	color, bgColor;
    bool avoidWalls, interactWithBodies, drawBodies, drawFlock, orbit;

    // BRIGHT HEARTS GRADIENTS
    int BHGShapeType, BHGNumSides;
    float BHGBlur, BHGThickness, BHGDiameter;
    
    // BRIGHT HEARTS GRADIENTS, BODY ONLY
    int bodyBHGShapeType, bodyBHGNumSides;
    float bodyBHGBlur, bodyBHGThickness, bodyBHGDiameter;
    
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
    
    // RIBBONS
    int pTotal		= MAX_PARTICLES;
    int		posSpread, velSpread, trailIndex = 0;
    GLuint	vboRibbon[ MAX_PARTICLES * 2 ];
    float	posRibbon[ MAX_PARTICLES ][ 3 ];
    float	velRibbon[ MAX_PARTICLES ][ 3 ];
    float	colRibbon[ MAX_PARTICLES ][ 4 ];
    float	trlRibbon[ MAX_PARTICLES ][ 3 * MAX_TRAIL_LENGTH ];		// trail position.
    float	tvrRibbon[ MAX_PARTICLES ][ 3 * MAX_TRAIL_LENGTH * 2 ];	// trail vertexes.
    float	tclRibbon[ MAX_PARTICLES ][ 4 * MAX_TRAIL_LENGTH * 2 ];	// trail colour.
    ofVec3f	upAxis;
    float		rotateY, upAxisRot;
    
    ofxParticleSystem() {
        worldSize = 800;
        centre.set(0,0,0);
        circleLocation.set(centre);
        bodies.push_back(ofxBody( ofVec3f(centre.x,centre.y,centre.z), 10, 0));
        addParticles(100, centre, 0);
//        addParticles(1, centre, 1);

        ofDisableArbTex();
        ofLoadImage(texture, "dot.png");

        for (int i=0;i<particles.size();i++) {
            points.push_back(particles[i].pos);
            sizes.push_back(ofVec3f(particles[i].sc*50));
        }

//        setupVBOBillboard();

//        initRibbons();
    }

    
    void update() {
        for(int i=0;i<particles.size();i++) {
            particles[i].run(particles, bodies);
        }
        if (reset == true) {
            reset = false;
        }
//        if (torusInnerRadius > torusOuterRadius) {
//            torusOuterRadius = torusInnerRadius + 5;
//        }
//        if (torusOuterRadius < torusInnerRadius) {
//            torusInnerRadius = torusOuterRadius - 5;
//        }
        
//        if (renderMode == 9 || renderMode == 5) {
//            for( int i=0; i<particles.size(); i++ ) {
//                
//                int j = 0;
//                if( trailIndex < MAX_TRAIL_LENGTH ) {
//                    j = trailIndex;
//                } else {
//                    j = MAX_TRAIL_LENGTH - 1;
//                }
//                
//                //      Iterator
//                // TRAIL POSITIONS.
//                if( trailIndex > 0 ) memmove( trlRibbon[ i ] + 3, trlRibbon[ i ], 3 * j * sizeof(float) );
//                
//                trlRibbon[ i ][ 0 ] = particles[i].pos.x;
//                trlRibbon[ i ][ 1 ] = particles[i].pos.y;
//                trlRibbon[ i ][ 2 ] = particles[i].pos.z;
//                
//                // TRAIL VERTEX.
//                if( trailIndex > 0 ) memmove( tvrRibbon[ i ] + 6, tvrRibbon[ i ], 6 * j * sizeof(float) );
//                
//                if( trailIndex == 0 ) {
//                    tvrRibbon[ i ][ 0 ] = particles[i].pos.x;
//                    tvrRibbon[ i ][ 1 ] = particles[i].pos.y;
//                    tvrRibbon[ i ][ 2 ] = particles[i].pos.z;
//                    tvrRibbon[ i ][ 3 ] = particles[i].pos.x;
//                    tvrRibbon[ i ][ 4 ] = particles[i].pos.y;
//                    tvrRibbon[ i ][ 5 ] = particles[i].pos.z;
//                    
//                } else {
//                    int m = 0;
//                    int n = 1;
//                    
//                    float t0x = trlRibbon[ i ][ m * 3 + 0 ];	// xyz position of 1st trail point.
//                    float t0y = trlRibbon[ i ][ m * 3 + 1 ];
//                    float t0z = trlRibbon[ i ][ m * 3 + 2 ];
//                    
//                    float t1x = trlRibbon[ i ][ n * 3 + 0 ];	// xyz position of 2nd trail point.
//                    float t1y = trlRibbon[ i ][ n * 3 + 1 ];
//                    float t1z = trlRibbon[ i ][ n * 3 + 2 ];
//                    
//                    ofVec3f t0 = ofVec3f( t0x, t0y, t0z );	// position vector of 1st trail point.
//                    ofVec3f t1 = ofVec3f( t1x, t1y, t1z );	// position vector of 2nd trail point.
//                    
//                    ofVec3f v1 = t0 - t1;
//                    v1.normalize();
//                    ofVec3f ya = ofVec3f( upAxis );
//                    ofVec3f v2 = ya.cross( v1 );
//                    ofVec3f v3 = v1.cross( v2 ).normalize();
//                    
//                    float w		= particles[i].ribbonWidth;
//                    float xOff	= v3.x * w;
//                    float yOff	= v3.y * w;
//                    float zOff	= v3.z * w;
//                    
//                    tvrRibbon[ i ][ 0 ] = t0x - xOff;
//                    tvrRibbon[ i ][ 1 ] = t0y - yOff;
//                    tvrRibbon[ i ][ 2 ] = t0z - zOff;
//                    tvrRibbon[ i ][ 3 ] = t0x + xOff;
//                    tvrRibbon[ i ][ 4 ] = t0y + yOff;
//                    tvrRibbon[ i ][ 5 ] = t0z + zOff;
//                }
//                
//                // TRAIL COLOUR.
//                float r, g, b, a;
//                
//                r = color.r;
//                g = color.g;
//                b = color.b;
//                a = ribbonOpacity;
//                
//                //      Iterator
//                if( trailIndex > 0 ) {
//                    memmove( tclRibbon[ i ] + 4 * 2, tclRibbon[ i ], 4 * 2 * j * sizeof(float) );
//                }
//                
//                tclRibbon[ i ][ 0 ] = tclRibbon[ i ][ 4 ] = r;
//                tclRibbon[ i ][ 1 ] = tclRibbon[ i ][ 5 ] = g;
//                tclRibbon[ i ][ 2 ] = tclRibbon[ i ][ 6 ] = b;
//                tclRibbon[ i ][ 3 ] = tclRibbon[ i ][ 7 ] = a;
//            }
//            
//            if( trailIndex < MAX_TRAIL_LENGTH ) {
//                ++trailIndex;
//            }
//        }  // updating ribbons :)
    }
        
    void render() {
        ofBackground(bgColor);
        
        if (blending) {
            ofEnableAlphaBlending();
            ofEnableBlendMode(OF_BLENDMODE_ADD);
        } else {
            ofDisableAlphaBlending();
        }
        if (depth) {
            glEnable(GL_DEPTH_TEST);
        } else {
            glDisable(GL_DEPTH_TEST);
        }
        
        // "VBO", "Spheres", "Points", "VertexArray", "Trails", "Boxes"};
        
        if (renderMode == 0 || renderMode == 5) {
            glDepthMask(GL_FALSE);

            // upload the data to the vbo
            ofSetColor(color);
            for (int i=0;i<particles.size();i++) {
                points[i].set(particles[i].pos);
                sizes[i].set(particles[i].mass * 50);
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

        
//        if (renderMode == 1) {
//            for (int i=0;i<particles.size();i++) {
//                particles[i].renderSphere();
//            }
//        }  // OF default Spheres
        
        
//        if (renderMode == 2) {
//            static GLfloat attenuate[3] = { 0.0, 0.0, 0.01 };  //Const, linear, quadratic
//            glEnable(GL_POINT_SIZE);
//            glPointSize(10);
//
//            glBegin(GL_POINTS);
//
//            for (int i=0;i<particles.size();i++) {
//                if (particles[i].isDead != true) {
//                    ofPushMatrix();
//                    ofTranslate(particles[i].pos);
//                    ofSetColor(particles[i].color);
//                    glVertex3f(0,0,0);
//                    ofPopMatrix();
//                }
//            }
//            glEnd();
//        } // as Points
        
        
        
//        if (renderMode == 3) {
////            glEnableClientState(GL_VERTEX_ARRAY);
////            for(int i=0;i<particles.size();i++) {
////                particles[i].renderVertexArray();
////            }
////            glDisableClientState(GL_VERTEX_ARRAY);
//        } // as a Vertex Array
        
        
        
//        if (renderMode == 4) {
////            glEnableClientState(GL_COLOR_ARRAY);
////            glEnableClientState(GL_VERTEX_ARRAY);
////            for(int i=0;i<particles.size();i++) {
////                particles[i].renderBHGradients();
////            }
////            glDisableClientState(GL_VERTEX_ARRAY);
////            glDisableClientState(GL_COLOR_ARRAY);
//        } // old BRIGHT HEARTS RENDER VISUALS!
        
        
        
//        if (renderMode == 6) {
//            float t = (ofGetElapsedTimef()) * 0.9f;
//            float div = 250.0;
//            
//            for (int i=0; i<NUM_BILLBOARDS; i++) {
//                
//                // noise
//                ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y/div, billboards.getVertex(i).z/div),
//                            ofSignedNoise(billboards.getVertex(i).x/div, t, billboards.getVertex(i).z/div),
//                            ofSignedNoise(billboards.getVertex(i).x/div, billboards.getVertex(i).y/div, t));
//                
//                vec *= 10 * ofGetLastFrameTime();
//                billboardVels[i] += vec;
//                billboards.getVertices()[i] += billboardVels[i];
//                billboardVels[i] *= 0.94f; 
//                billboards.setNormal(i,ofVec3f(12 + billboardSizeTarget[i] * ofNoise(t+i),0,0));
//            }
//            
//            ofPushMatrix();
//            ofTranslate(ofGetWidth()/2, ofGetHeight()/2, zoom);
//            ofRotate(cameraRotation.x, 1, 0, 0);
//            ofRotate(cameraRotation.y, 0, 1, 0);
//            ofRotate(cameraRotation.y, 0, 0, 1);
//            
//            // bind the shader so that we can change the
//            // size of the points via the vert shader
//            billboardShader.begin();
//            
//            ofEnablePointSprites();
//            billboardTexture.getTextureReference().bind();
//            billboards.draw();
//            billboardTexture.getTextureReference().unbind();
//            ofDisablePointSprites();
//            
//            billboardShader.end();
//            
//            ofPopMatrix();
//            
//        } // VBO Billboarding
        
        
//        if (renderMode == 7) {
//            for(int i=0;i<particles.size();i++) {
//                particles[i].renderDebug();
//            }
//        } // Debug Rendering
        
        
        
//        if (renderMode == 8) {
//            for(int i=0;i<particles.size();i++) {
//                particles[i].renderTrails();
//            }
//        } // Render Trails :)
        
        
        
//        if (renderMode == 9 || renderMode == 5) {
//            
//            for( int i=0; i<MAX_PARTICLES; i++ ) {
//                glEnableClientState( GL_VERTEX_ARRAY );
//                glEnableClientState( GL_COLOR_ARRAY );
//                
//                glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboRibbon[ i * 2 + 0 ] );
//                glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, sizeof( tvrRibbon[ i ] ), tvrRibbon[ i ] );
//                glVertexPointer( 3, GL_FLOAT, 0, 0 );
//                
//                glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboRibbon[ i * 2 + 1 ] );
//                glBufferSubDataARB( GL_ARRAY_BUFFER_ARB, 0, sizeof( tclRibbon[ i ] ), tclRibbon[ i ] );
//                glColorPointer( 4, GL_FLOAT, 0, 0 );
//                
//                glDrawArrays( GL_QUAD_STRIP, 0, MAX_TRAIL_LENGTH );
//                
//                glDisableClientState( GL_VERTEX_ARRAY );
//                glDisableClientState( GL_COLOR_ARRAY );
//                
//                glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );
//            }
//        } // Render Ribbons :)
        
        
        
        if (drawBodies) {
//            glEnableClientState(GL_COLOR_ARRAY);
//            glEnableClientState(GL_VERTEX_ARRAY);
//            for(int i=0;i<particles.size();i++) {
//                bodies[i].renderBHGradients();
//            }
//            glDisableClientState(GL_VERTEX_ARRAY);
//            glDisableClientState(GL_COLOR_ARRAY);
        }
        
        if (blending) ofDisableAlphaBlending();
        
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
            particles[i].maxOrbitForce = maxOrbitForce;
            particles[i].ribbonWidth = ribbonWidth;
            particles[i].mass = particleMass;
            particles[i].dragF = dragF;
        }
        for (int i=0;i<bodies.size();i++) {
            bodies[i].mass = bodyMass;
            bodies[i].BHGShapeType = bodyBHGShapeType;
            bodies[i].BHGBlur = bodyBHGBlur;
            bodies[i].BHGNumSides = bodyBHGNumSides;
            bodies[i].BHGThickness = bodyBHGThickness;
            bodies[i].BHGDiameter = bodyBHGDiameter;
        }
    }
    
    void initRibbons() {
        upAxis.set(0, 1, 0);
        upAxisRot = 5;
        
        glGenBuffersARB( MAX_PARTICLES * 2, &vboRibbon[ 0 ] );
        for( int i=0; i<MAX_PARTICLES; i++ ) {
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboRibbon[ i * 2 + 0 ] );
            glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof( tvrRibbon[ i ] ), tvrRibbon[ i ], GL_STREAM_DRAW_ARB );
            
            glBindBufferARB( GL_ARRAY_BUFFER_ARB, vboRibbon[ i * 2 + 1 ] );
            glBufferDataARB( GL_ARRAY_BUFFER_ARB, sizeof( tclRibbon[ i ] ), tclRibbon[ i ], GL_STREAM_DRAW_ARB );
        }
    }
    
};

