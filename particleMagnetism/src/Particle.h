/*
 *  Particle.h
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */

#pragma once
#include "ofVec2f.h"


class Particle {
public:	

	float x, y;
	float vx, vy;
	float mass, decay, alpha, radius, charge;
    ofVec2f vel, dir, pos, acc, origin;
    bool isDead;
	void init(float x, float y, int ID);
	void updateParticle();
	void updateVertexArrays(int i, float* posBuffer, float* colBuffer);
    void drawStandardGL();
	void drawOldSchool();
    int ID, age;
    
};

