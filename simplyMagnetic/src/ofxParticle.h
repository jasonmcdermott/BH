#pragma once
#include "ofxBoundary.h"
#include "ofxBody.h"
#include <math.h>

class ofxParticle {
public:
    
    ofVec3f pos, vel, acc, ali, coh, sep, att, origin, bias, outerTemp, other, dist, circleLocation;
    float pSpeed = 3, pForce = .5, h, sc = 3, t = 0, c, attractF = 1, separationF = 1, alignF = 1, cohesionF = 1, dragF = 0.95, mass = 1, personalSpace = 15, pPerception = 50;
    string string;
    bool reset = false, isDead = false, interactWithBodies = true, renderVA = true, avoidWalls = true, outside, inside, orbit;
    int age = 0, type, prey, trailCount = 0, ID;
    ofFloatColor	color;
    float torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G;
    ofVec3f cross, a, b, distToCent, crossVec;
    float distToCentre, orbitF, randomX, randomY;
    
    // BAKER SPHERICAL COMPONENTS
    float degreeIncrement         = 20;      // 10 degrees between
    int   sphereVertexCount      = (180 / degreeIncrement) * (360 / degreeIncrement) * 4;
    float M_PI_Divided_By_180;
    
    
    ofTexture texture;
    
    
    ofxParticle() {}
    
    ofxParticle(int ID_, ofxBoundary outer, ofVec3f centre_, int type_) {
        origin.set(centre_);
        mass = ofRandom(0.4,2);
        ID = ID_;
        type = type_;
        initParticle(outer);
        sc = mass;
        randomX = ofRandom(-1,1);
        randomY = ofRandom(-1,1);
    }

    void initParticle(ofxBoundary outer) {
        origin.set(origin.x + ofRandom(-100,100),origin.y + ofRandom(-100,100) ,origin.z + ofRandom(-100,100));
        pos.set(origin);
        vel.set(0,0,0);
        acc.set(0,0,0);
        bias.set(0,0,0);
        string = "";
        degreeIncrement         = 15;
        sphereVertexCount      = (180 / degreeIncrement) * (360 / degreeIncrement) * 4;
        M_PI_Divided_By_180 = M_PI/180;
        circleLocation.set(0,0,0);
        a.set(pos);
        b.set(pos);
        age = 0;
//        ofVec3f aPlus(ofRandom(-10,10),ofRandom(-10,10),ofRandom(-10,10));
//        a += aPlus;

    }
    
    void run(vector <ofxParticle> particles, ofxBoundary outer, vector <ofxBody> bodies) {
        if (reset == true) {
            initParticle(outer);
        }
        
        
        if (isDead != true) {
            age ++;
            if (orbit) {
                crossProd(bodies);
            }

            if (interactWithBodies == true) {
                interactingBodies(bodies);
            }

            if (separationF > 0) {
                separate(particles);
            }
            
            if (alignF > 0 || cohesionF > 0) {
                flocking(particles);
            }
            
            moveInward();
//            moveOutward();
            move();
        }
    }
    
    float calcDistToCentre() {
        distToCent.set(pos);
        distToCent -= circleLocation;
        distToCentre = distToCent.length();
        return distToCentre;
    }
    
    void crossProd(vector <ofxBody> bodies) {

        a.set(pos);
        a.x += 5;
//        a.y += randomY;
        cross.set(pos);
        
//        b.set(pos);
//        
//        ofPushMatrix();
//        ofRotateX(circleLocation.x);
//        ofRotateY(circleLocation.y);
//        ofRotateZ(circleLocation.z);
//        ofPopMatrix();
//        
//        b.normalize();
//        b /= 5;
        
        
//        ofVec3f b(a);
//        b -= pos;
        
        // Vector1 (x1, y1, z1) and Vector2 (x2, y2, z2), and one output vector, OutVect(ox, oy, oz)
        
        // pos = 1
        // a = 2
        
        // cross.x = (y1 * z2) - (y2 * z1)
        // cross.y = (z1 * x2) - (z2 * x1)
        // cross.z = (x1 * y2) - (x2 * y1)

        //  cross.x = (circleLocation.y * a.z) - (a.y * circleLocation.z);
        //  cross.y = (circleLocation.z * a.x) - (a.z * circleLocation.x);
        //  cross.z = (circleLocation.x * a.y) - (a.x * circleLocation.y);
        
        cross = circleLocation.crossed(a);
//        cross.normalize();
//        cross *= 2;
//        cross.normalize();
//        cross *= (orbitF * 0.1);
        
//        crossVec.set(pos);
//        crossVec += cross;
//        acc += cross / (age/10);
        
        acc -= cross * (orbitF * 0.1);
        
    }
    
    void interactingBodies(vector <ofxBody> bodies) {
        for (int i=0;i<bodies.size();i++) {
            if (bodies[i].charge == 0) {
//                ofVec3f bodyAtt(pos);
                ofVec3f bodyForce(bodies[i].pos);
//                bodyAtt.set(bodies[i].pos);
//                bodyForce = bodyAtt - pos;
                bodyForce -= pos;
                
                float dist = bodyForce.length();
                float inverseSquare = G * ((mass * bodies[i].mass) / (dist * dist));
                
                bodyForce *= inverseSquare;
                acc += bodyForce;
                
            }
            if (bodies[i].charge > 0) {
                ofVec3f rep;
                ofVec3f bodyForce;
                rep.set(bodies[i].pos);
                bodyForce = rep - pos;
                float dist = bodyForce.length();
                float inverseSquare = (G * mass * bodies[i].mass) / (dist * dist);
                if (dist < mass * 300) {
                    bodyForce *= inverseSquare;
                    acc += -bodyForce;
                }
            }
        }
    }

    void flocking(vector <ofxParticle> particles) {
        ali = align(particles);
        coh = cohere(particles);
        
        ali *= alignF;
        coh *= cohesionF;
        
        acc += ali;
        acc += coh;
    }
    
    void move() {
        vel += acc;
        vel.limit(pSpeed);
        vel *= dragF;
        pos += vel;
        acc *= 0;
    }
    
    void render() {
        if (isDead != true) {

//            ofSetColor(255,0,255); // purple line between particle and centre
//            ofLine(pos, circleLocation);
            
            ofSetColor(color);       // box
            ofBox(pos.x,pos.y,pos.z,sc);
            
            ofSetColor(0,0,255); // blue line indicating 'up' (may be indicating 'left', it makes no difference)
            ofLine(pos,a);
            ofTriangle(circleLocation,pos,a);
            ofSetColor(255);   // white line pointing perpendicularly away from the centre
            ofLine(pos,cross);

            
        }
    }
    
    void renderPoints() {
        if (isDead != true) {
            ofSetColor(color);
            glVertex3f(pos.x,pos.y,pos.z);
        }
    }
    
    void renderVALaMarche() {
//        // enable vertex and normal data
//        glEnableClientState(GL_VERTEX_ARRAY);
//        glEnableClientState(GL_NORMAL_ARRAY);
//        // draw fan parts of sphere
//        glVertexPointer(3, GL_FLOAT, 0, sphereTriangleFanVertices);
//        glNormalPointer(GL_FLOAT, 0, sphereTriangleFanNormals);
//        glDrawArrays(GL_TRIANGLE_FAN, 0, sphereTriangleFanVertexCount);
//        // draw strip parts of sphere
//        glVertexPointer(3, GL_FLOAT, 0, sphereTriangleStripVertices);
//        glNormalPointer(GL_FLOAT, 0, sphereTriangleStripNormals);
//        glDrawArrays(GL_TRIANGLE_STRIP, 0, sphereTriangleStripVertexCount);
//        // disable vertex and normal data
//        glDisableClientState(GL_VERTEX_ARRAY);
//        glDisableClientState(GL_NORMAL_ARRAY);
    }
    
    
    void renderVertexArray() {
        ofPushMatrix();
        ofTranslate(pos.x,pos.y,pos.z);
        ofSetColor(color);
        GLfloat sphereVertex3f [sphereVertexCount][3];
        int vertNum = 0;
        
        for (float z = 0; z <= 180 - degreeIncrement; z += degreeIncrement)  // Iterate through height of sphere of Z
            for (float c = 0; c <= 360 - degreeIncrement; c += degreeIncrement) { // Each point of the circle X, Y of "C"
                
                sphereVertex3f   [vertNum][0] = sinf( (c) * M_PI_Divided_By_180 ) * sinf( (z) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f   [vertNum][1] = cosf( (c) * M_PI_Divided_By_180 ) * sinf( (z) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f   [vertNum][2] = cosf( (z) * M_PI_Divided_By_180 )*sc;
                //                sphereTexCoord2f [vertNum][0] = (c)     / 360;
                //                sphereTexCoord2f [vertNum][1] = (2 * z) / 360;
                vertNum ++; // ^ Top Left
                
                sphereVertex3f    [vertNum][0] = sinf( (c) * M_PI_Divided_By_180 ) * sinf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][1] = cosf( (c) * M_PI_Divided_By_180 ) * sinf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][2] = cosf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                //                sphereTexCoord2f [vertNum][0] = (c)               / 360;
                //                sphereTexCoord2f [vertNum][1] = (2 * (z + degreeIncrement)) / 360;
                vertNum ++; // ^ Top Right
                
                sphereVertex3f    [vertNum][0] = sinf( (c + degreeIncrement) * M_PI_Divided_By_180 ) * sinf( (z) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][1] = cosf( (c + degreeIncrement) * M_PI_Divided_By_180 ) * sinf( (z) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][2] = cosf( (z) * M_PI_Divided_By_180 )*sc;
                //                sphereTexCoord2f [vertNum][0] = (c + degreeIncrement) / 360;
                //                sphereTexCoord2f [vertNum][1] = (2 * z)     / 360;
                vertNum ++; // ^ Bottom Left
                
                sphereVertex3f    [vertNum][0] = sinf( (c + degreeIncrement) * M_PI_Divided_By_180 ) * sinf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][1] = cosf( (c + degreeIncrement) * M_PI_Divided_By_180 ) * sinf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                sphereVertex3f    [vertNum][2] = cosf( (z + degreeIncrement) * M_PI_Divided_By_180 )*sc;
                //                sphereTexCoord2f [vertNum][0] = (c + degreeIncrement)       / 360;
                //                sphereTexCoord2f [vertNum][1] = (2 * (z + degreeIncrement)) / 360;
                vertNum ++; // ^ Bottom Right
                
            }

        glVertexPointer         (3, GL_FLOAT, 0, sphereVertex3f);
        glDrawArrays         (GL_TRIANGLE_STRIP, 0, sphereVertexCount);
        ofPopMatrix();
    }
    
    void checkBounds(ofxBoundary outer) {
        if(pos.x > outer.right.x) pos.x = outer.left.x;
        if(pos.x < outer.left.x) pos.x = outer.right.x;
        if(pos.y < outer.top.y) pos.y = outer.bottom.y;
        if(pos.y > outer.bottom.y) pos.y = outer.top.y;
        if(pos.z > outer.front.z) pos.z = outer.back.z;
        if(pos.z < outer.back.z) pos.z = outer.front.z;
    }
    
    void avoidBounds(ofxBoundary outer) {
        ofVec3f left(outer.left.x,pos.y,pos.z);
        ofVec3f right(outer.right.x,pos.y,pos.z);
        ofVec3f top(pos.x,outer.top.y,pos.z);
        ofVec3f bottom(pos.x,outer.bottom.y,pos.z);
        ofVec3f front(pos.x,pos.y,outer.front.z);
        ofVec3f back(pos.x,pos.y,outer.back.z);
        
        ofVec3f avLeft(avoid(left,true));
        ofVec3f avRight(avoid(right,true));
        ofVec3f avTop(avoid(top,true));
        ofVec3f avBottom(avoid(bottom,true));
        ofVec3f avFront(avoid(front,true));
        ofVec3f avBack(avoid(back,true));
        
        
        
        
        acc += avLeft;
        acc += avRight;
        acc += avTop;
        acc += avBottom;
        acc += avFront;
        acc += avBack;
    }
    
    bool checkIfWithinTorus() {

        // Predict location 5 (arbitrary choice) frames ahead
        ofVec3f predict(vel);
        predict *= 25;
        ofVec3f futureLocation(pos);
        
        futureLocation += predict;
        
        ofVec3f distFromCircleCentre(circleLocation);
        
        distFromCircleCentre -= futureLocation;
        
        float distance = distFromCircleCentre.length();

        if (distance > torusOuterRadius * 0.6) {
            outside = true;
            return false;
        } else if (distance < torusInnerRadius * 0.6) {
            inside = true;
            return false;
        } else {
            outside = false;
            inside = false;
            return true;
        }
    }
    
    void moveInward() {
        
        ofVec3f desired;        
        ofVec3f predict;
        predict.set(vel);
        predict *= pPerception / 5;
        ofVec3f futureLocation(pos);
        futureLocation += predict;
        ofVec3f distFromCircleCentre(circleLocation);
        distFromCircleCentre -= futureLocation;
        float distance = distFromCircleCentre.length();

        if (distance > torusOuterRadius * 0.6) {
            ofVec3f toCenter(circleLocation);
            toCenter -= pos;
            toCenter.normalize();
            toCenter *= vel.length();
            toCenter += vel;
            
            desired.set(toCenter);
            desired.normalize();
//            if (alignF > 0 || separationF > 0 || cohesionF > 0) {
//                desired *= (alignF + separationF + cohesionF)*2;
//            }
            desired *= outerBoundF;
        }
        
        if (desired.length() != 0) {
            ofVec3f moveVec(desired);
            moveVec -= vel;
            moveVec.limit(pForce);
            acc += moveVec;
        }
        
    }
    
    void moveOutward() {
        
        ofVec3f desired;
        ofVec3f predict;
        predict.set(vel);
        predict *= pPerception / 5;
        ofVec3f futureLocation(pos);
        futureLocation += predict;
        ofVec3f distFromCircleCentre(circleLocation);
        distFromCircleCentre -= futureLocation;
        float distance = distFromCircleCentre.length();
        if (distance < torusInnerRadius * 0.5) {
            ofVec3f toCenter(circleLocation);
            toCenter += pos;
            toCenter.normalize();
            toCenter *= vel.length();
            toCenter += vel;
            desired.set(-toCenter);
            desired.normalize();
            if (alignF > 0 || separationF > 0 || cohesionF > 0) {
                desired *= (alignF + separationF + cohesionF)*5;
            }
            desired *= innerBoundF;
        }
        if (desired.length() != 0) {
            ofVec3f steer(desired);
            steer -= vel;
            steer.limit(pForce);
            acc += steer;
        }        
    }

    
    ofVec3f steer(ofVec3f target,bool arrival) {
        ofVec3f steer;
        if(!arrival){
            steer.set(target);
            steer -= pos;
            // steer.set(PVector.sub(target,pos));
            // steering vector points towards target (switch target and pos for avoiding)
            steer.limit(pForce); //limits the steering force to maxSteerForce
        } else {
            ofVec3f targetOffset(pos);
            targetOffset -= target;
            float distance = targetOffset.length();
            float rampedSpeed = pSpeed * (distance/100);

//   want to finish this off, although it's more important for the boids code...
//            float clippedSpeed = min(rampedSpeed,pSpeed);
//            PVector desiredVelocity = PVector.mult(targetOffset,(clippedSpeed/distance));
//            steer.set(PVector.sub(desiredVelocity,vel));
        }
        return steer;
    }
    ofVec3f avoid(ofVec3f target, bool weight) {
        ofVec3f steer;
        steer.set(pos);
        steer -= target;
        float distance = steer.length();
        if (distance < pPerception) {
            if (weight) {
                steer *= (1 / (distance * distance));
            }
            steer *= 2;
            return steer;
        } else {
            steer.set(0,0);
            return steer;
        }
    }
    void separate(vector <ofxParticle> particles) {
        ofVec3f posSum;
        ofVec3f repulse;
        for(int i=0;i<particles.size();i++) {
            if (particles[i].ID != ID && particles[i].isDead != true) {
                other.set(particles[i].pos);
                dist.set(pos);
                dist -= other;
                float d = dist.length();
                if(type == particles[i].type && d > 0 && d <= personalSpace) {
                    repulse.set(dist);
                    repulse.normalize();
                    repulse /= ((mass * particles[i].mass) * (d * d));
                    posSum += repulse;
                }
            }
        }
        sep.set(posSum);
        sep *= separationF;
        acc += sep;
    }
    
    ofVec3f attract(vector <ofxParticle> particles) {
        ofVec3f posSum;
        ofVec3f attract;
        for(int i=0;i<particles.size();i++) {
            if (particles[i].ID != ID && particles[i].isDead != true) {
                other.set(particles[i].pos);
                dist.set(pos);
                dist -= other;
                float d = dist.length();
                if(type == particles[i].type && d > 0 && d <= pPerception) {
                    attract.set(dist);
                    attract.normalize();
                    attract /= d;
                    posSum -= attract;
                }
            }
        }
        return posSum;
    }
    ofVec3f align(vector <ofxParticle> particles) {
        ofVec3f velSum;
        int count = 0;
        for(int i=0;i<particles.size();i++){
            if (particles[i].ID != ID && particles[i].isDead != true) {
                other.set(particles[i].pos);
                dist.set(pos);
                dist -= other;
                float d = dist.length();
                
                if (d > 0 && d <= pPerception) {
                    velSum += particles[i].vel;
                    count++;
                }
            }
        }
        if(count > 0) {
            velSum /= (float)count;
            velSum.limit(pForce);
        }
        return velSum;
    }
    ofVec3f cohere(vector <ofxParticle> particles) {
        ofVec3f posSum;
        ofVec3f steer;
        posSum.set(origin);
        steer.set(origin);
        int count = 0;
        for(int i=0;i<particles.size();i++) {
            if (particles[i].ID != ID && particles[i].isDead != true) {
                other.set(particles[i].pos);
                dist.set(pos);
                dist -= other;
                float d = dist.length();
                
                if(d > 0 && d <= pPerception) {
                    posSum += particles[i].pos;
                    count++;
                }
            }
        }
        if(count>0) {
            posSum /= (float)count;
        }
        steer.set(pos);
        steer -= posSum;
        steer.limit(pForce);
        return steer;
    }
    void killStrays(ofxBoundary outer) {
        if (pos.x > outer.right.x || pos.x < outer.left.x) {
            isDead = true;
        }
        if (pos.y > outer.bottom.y || pos.y < outer.top.y) {
            isDead = true;
        }
        if (pos.z > outer.front.z || pos.z < outer.back.z) {
            isDead = true;
        }
    }

    
};


