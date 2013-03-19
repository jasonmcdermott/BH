#pragma once
#include "ofxBoundary.h"
#include "ofxBody.h"
#include <math.h>

class ofxParticle {
public:
    
    ofVec3f pos, vel, acc, ali, coh, sep, att, origin, bias, outerTemp, other, dist, circleLocation;
    float pSpeed = 3, pForce = .5, h, sc = 100, t = 0, c, attractF = 1, separationF = 1, alignF = 1, cohesionF = 1, dragF = 0.95, mass = 1, personalSpace = 15, pPerception = 50;
    string string;
    bool reset = false, isDead = false, interactWithBodies = true, renderVA = true, avoidBoundaries = true, outside, inside, orbit, gravitate;
    int age = 0, type, prey, trailCount = 0, ID;
    ofFloatColor	color;
    float torusInnerRadius, torusOuterRadius, innerBoundF, outerBoundF, G;
    ofVec3f cross, a, b, distToCent, crossVec;
    float distToCentre, orbitF, randomX, randomY;
    float blur, diameter, thickness, Alpha, numSides, middleRadius, maxOrbitForce, ribbonWidth;
    int shapeType;
    GLfloat cols[3];
    ofVec3f scale;

    // BAKER SPHERICAL COMPONENTS
    float degreeIncrement         = 20;      // 10 degrees between
    int   sphereVertexCount      = (180 / degreeIncrement) * (360 / degreeIncrement) * 4;
    float M_PI_Divided_By_180;
    ofTexture texture;
    
    // BRIGHT HEARTS GRADIENTS
    int BHGShapeType, BHGNumSides;
    float BHGBlur, BHGThickness, BHGDiameter;
    
    // CAMERA MESH
    vector<ofVec3f> meshPoints;
    
    ofxParticle() {}
    
    ofxParticle(int ID_, ofVec3f centre_, int type_) {
        origin.set(centre_);
        mass = ofRandom(5,10);
        ID = ID_;
        type = type_;
        initParticle();
        Alpha = 255;
        numSides = 100;
        shapeType = 0;
        randomX = ofRandom(-1,1);
        randomY = ofRandom(-1,1);
        cols[0] = 200;
        cols[1] = 255;
        cols[2] = 255;
        scale.set(mass,mass,mass);
    }

    void initParticle() {
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
        diameter = sc * 2;
        blur = 3;
        meshPoints.clear();
        reset = false;
    }
        
    void run(vector <ofxParticle> particles, vector <ofxBody> bodies) {
        if (reset == true) {
            initParticle();
        }
        if (isDead != true) {
            age ++;
            if (orbit) crossProd(bodies);
            if (gravitate) interactingBodies(bodies);
            if (separationF > 0) separate(particles);            
            if (alignF > 0) align(particles);
            if (cohesionF > 0) cohere(particles);
            if (avoidBoundaries) moveInward(); moveOutward();
            move();
        } else {
//            reset = true;
        }
    }

    // MOVEMENT
    void interactingBodies(vector <ofxBody> bodies) {
        for (int i=0;i<bodies.size();i++) {
            if (bodies[i].charge == 0) {
                ofVec3f bodyForce(bodies[i].pos);
                bodyForce -= pos;
                float dist = bodyForce.length();
                
                float inverseSquare = G * ((mass * bodies[i].mass) / (dist * dist));
                
//                float inverseSquare = ((mass * bodies[i].mass) / (dist * dist));

                if (dist < bodies[i].mass) {
                    isDead == true;
//                    dragF = 0.95;
//                    acc -= bodyForce / 50;
                } else {
                    bodyForce *= inverseSquare;
                    acc += bodyForce;
                }
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
    
    void crossProd(vector <ofxBody> bodies) {
        
        a.set(pos);
        a.y += 50;
        cross.set(circleLocation);
    
//        cross = circleLocation.crossed(pos);
        
        cross.x = (pos.y * a.z) - (a.y * pos.z);
        cross.y = (pos.z * a.x) - (a.z * pos.x);
        cross.z = (pos.x * a.y) - (a.x * pos.y);
        
//        cross *=;
        
//        cross /= 1000;
        cross.limit(maxOrbitForce);
        acc -= cross * orbitF;

        
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
        
//        cross.x = (y1 * z2) - (y2 * z1)
//        cross.y = (z1 * x2) - (z2 * x1)
//        cross.z = (x1 * y2) - (x2 * y1)
        

        


        
        //        cross.normalize();
        //        cross *= 2;
        //        cross.normalize();
        //        cross *= (orbitF * 0.1);
        
        //        crossVec.set(pos);
        //        crossVec += cross;
        //        acc += cross / (age/10);

        
        
    }
    
    void move() {
        vel += acc;
        vel.limit(pSpeed);
        vel *= dragF;
        pos += vel;
        acc *= 0;
    }
    
    // RENDER
    void render() {}
            
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
        if (isDead != true) {
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
    }
    
    void renderDebug() {
        if (isDead != true) {
            
            ofSetColor(255,0,255); // purple line between particle and centre
            ofLine(pos, circleLocation);
            
//            ofSetColor(color);       // sphere
//            ofSphere(pos.x,pos.y,pos.z,sc);

//            ofSetColor(0,0,255); // blue line indicating 'up'
//            ofTriangle(circleLocation,pos,a);

            ofSetColor(0,0,255);
            ofLine(pos,a);
            
            ofSetColor(255);   // white line pointing perpendicularly away from the centre
            ofSphere(cross,1);
            ofLine(pos,cross);
//            ofDrawBitmapString(ofToString(cross,2),cross.x,cross.y,cross.z);
        }
    }
    
    void renderSphere() {
        if (isDead != true) {
            ofSetColor(color);
            ofSphere(pos.x,pos.y,pos.z,mass);
        }
    }
    
    void renderBHGradients() {
        if (isDead != true) {
            if (BHGShapeType == 0) {
                drawGradient(mass-BHGBlur,0,color.a,0,BHGNumSides);
                drawGradient(mass,mass-BHGBlur,0,0,BHGNumSides);
            } else if (BHGShapeType == 1) {
                drawGradient(mass+BHGThickness-BHGBlur,mass-BHGThickness+BHGBlur,color.a,0,BHGNumSides);
                drawGradient(mass+BHGThickness,mass+BHGThickness-BHGBlur,0,0,BHGNumSides);
                drawGradient(mass-BHGThickness,mass-BHGThickness+BHGBlur,0,0,BHGNumSides);
            } else if (BHGShapeType == 2) {
                drawGradient(mass-BHGThickness,mass+BHGThickness,0,0,BHGNumSides);
                drawGradient(mass+BHGThickness+BHGThickness*0.05, mass+BHGThickness, 0, 0, BHGNumSides);
            }
        }
    }
    
    void drawGradient(float opaque_, float transp_, float opac_, float blur_, int ns_) {
        
        ofPushMatrix();
        ofTranslate(pos.x,pos.y,pos.z);
        
        GLfloat* ver_coords = new GLfloat[ (ns_+1) * 4];
        GLfloat* ver_cols = new GLfloat[ (ns_+1) * 8];

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
            ver_coords[i*4+0] = (opaque_*cos(angle));
            ver_coords[i*4+1] = (opaque_*sin(angle));
            ver_cols[i*8+0] = color.r;
            ver_cols[i*8+1] = color.g;
            ver_cols[i*8+2] = color.b;
            ver_cols[i*8+3] = opac_;
            ver_coords[i*4+2] = (transp_*cos(angle));
            ver_coords[i*4+3] = (transp_*sin(angle));
            ver_cols[i*8+4] = color.r;
            ver_cols[i*8+5] = color.g;
            ver_cols[i*8+6] = color.b;
            ver_cols[i*8+7] = color.a;
        }
        
        
        glVertexPointer( 2, GL_FLOAT, 0, ver_coords);
        glColorPointer(4, GL_FLOAT, 0, ver_cols);
        glDrawArrays( GL_TRIANGLE_STRIP, 0, ( ns_ + 1 ) * 2 );
        
        delete[] ver_coords;
        delete[] ver_cols;
        ofPopMatrix();
    }
    
    void renderTrails() {
        ofSetColor(color);
        ofVec3f newPos(pos.x,pos.y,pos.z);
        meshPoints.push_back(newPos);
        
//        ofMesh mesh;
//        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//        mesh.setMode(GL_QUADS);
        
        glBegin(GL_QUADS);
        
        for(int i = 1; i < meshPoints.size(); i++){
            
            //find this point and the next point
            ofVec3f thisPoint = meshPoints[i-1];
            ofVec3f nextPoint = meshPoints[i];
            
            //get the direction from one to the next.
            //the ribbon should fan out from this direction
            ofVec3f direction = (nextPoint - thisPoint);
            
            //get the distance from one point to the next
            float distance = direction.length();
            
            //get the normalized direction. normalized vectors always have a length of one
            //and are really useful for representing directions as opposed to something with length
            ofVec3f unitDirection = direction.normalized();
            
            //find both directions to the left and to the right
            ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
            ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));
            
            //use the map function to determine the distance.
            //the longer the distance, the narrower the line.
            //this makes it look a bit like brush strokes
//            float thickness = ofMap(distance, 0, 60, 20, 2, true);
            thickness = 1;
            
            //calculate the points to the left and to the right
            //by extending the current point in the direction of left/right by the length
            ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
            ofVec3f rightPoint = thisPoint+toTheRight*thickness;
            
            
            //add these points to the triangle strip
//            mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
//            mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
            glVertex3f(leftPoint.x, leftPoint.y, leftPoint.z);
            glVertex3f(rightPoint.x, rightPoint.y, rightPoint.z);
            glVertex3f(nextPoint.x,nextPoint.y,nextPoint.z);
        }
        
        glEnd();
//        meshPoints[i-1].
        
//        for (int i=1;i<meshPoints.size();i++) {
//            
//        }
        
        //end the shape
//        mesh.draw();

    }
    
    // CONSTRAIN
    
    float calcDistToCentre() {
        distToCent.set(pos);
        distToCent -= circleLocation;
        distToCentre = distToCent.length();
        return distToCentre;
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
    
    // FLOCKING
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
    void align(vector <ofxParticle> particles) {
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
        ali.set(velSum);
        ali *= alignF;
        acc += ali;
    }
    void cohere(vector <ofxParticle> particles) {
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
        coh.set(steer);
        coh *= cohesionF;
        acc += coh;
    }


    
};


