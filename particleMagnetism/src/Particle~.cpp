/*
 *  Particle.cpp
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#include "Particle.h"
#include "testApp.h"
//#include "msaColor.h"


#define MOMENTUM		0.5
#define FLUID_FORCE		0.6




void Particle::init(float x, float y) {
	this->x = x;
	this->y = y;
	vx = ofRandom(-100,100);
	vy = ofRandom(-100,100);
	radius = 5;
	alpha  = ofRandom(0.3, 255);
	mass = ofRandom(0.1, 1);
}


void Particle::update() {
	// only update if particle is visible
	if(alpha == 0) return;
	
	
	
	// update position
//	x += vx;
//	y += vy;
	
	// bounce of edges
//	if(x<0) {
//		x = 0;
//		vx *= -1;
//	}
//	else if(x > myApp->window.width) {
//		x = myApp->window.width;
//		vx *= -1;
//	}	
//	if(y<0) {
//		y = 0;
//		vy *= -1;
//	}
//	else if(y > myApp->window.height) {
//		y = myApp->window.height;
//		vy *= -1;
//	}
	
	// hackish way to make particles glitter when the slow down a lot
//	if(vx * vx + vy * vy < 1) {
//		vx = ofRandom(-0.5, 0.5);
//		vy = ofRandom(-0.5, 0.5);
//	}
	
	// fade out a bit (and kill if alpha == 0);
	alpha *= 0.999;
	if(alpha < 0.01) alpha = 0;
}


void Particle::updateVertexArrays(int i, float* posBuffer, float* colBuffer) {
	int vi = i * 4;
	posBuffer[vi++] = x - vx;
	posBuffer[vi++] = y - vy;
	posBuffer[vi++] = x;
	posBuffer[vi++] = y;	
	int ci = i * 6;

}


void Particle::drawStandardGL() {
	ofSetColor(200,200,200,alpha);
	glVertex2f(x-vx, y-vy);
	glVertex2f(x, y);
}

void Particle::drawOldSchool() {
	ofSetColor(200,200,200,alpha);
    ofCircle(x,y,10);
}



