
#include "Particle.h"
#include "testApp.h"


void Particle::init(float x_, float y_, int ID_) {
	this->x = x_;
	this->y = y_;
    ID = ID_;
    pos.set(x_,y_);
    origin.set(x_,y_);
    vel.set(0,0);
    acc.set(0,0);

	radius = 5;
	alpha  = ofRandom(100, 255);
	mass = (radius * radius) * 0.9;
    decay = 0.9;
    isDead = false;
    charge = 1;
}


void Particle::updateParticle() {
    if (age > 100000) {
        isDead = true;
        return;
    }
    vel += acc;
    pos += vel;
    vel *= decay;
    acc.set(0,0);
    age++;
}


void Particle::updateVertexArrays(int i, float* posBuffer, float* colBuffer) {
	int vi = i * 4;
	posBuffer[vi++] = pos.x - vel.x;
	posBuffer[vi++] = pos.y - vel.y;
	posBuffer[vi++] = pos.x;
	posBuffer[vi++] = pos.y;
	int ci = i * 6;
}


void Particle::drawStandardGL() {
	ofSetColor(200,200,200,alpha);
	glVertex2f(pos.x-origin.x, pos.y-origin.y);
	glVertex2f(pos.x, pos.y);
}

void Particle::drawOldSchool() {
    if (isDead) return;
	ofSetColor(200,200,200,alpha);
//    ofRect(pos.x,pos.y,radius,radius);
    ofCircle(pos.x,pos.y,radius);
    
    if (ID == 10){
//        ofSetColor(0);
//        ofLine(pos.x,pos.y,pos.x+50,pos.y+50);
//        string  info  = "Vel: "+ofToString(acc,0)+"\n";
//        ofDrawBitmapString(info, pos.x+50, pos.y+30);
    }
    
}









