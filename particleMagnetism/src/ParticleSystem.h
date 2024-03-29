/*
 *  ParticleSystem.h
 *  ofxMSAFluid Demo
 *
 *  Created by Mehmet Akten on 02/05/2009.
 *  Copyright 2009 MSA Visuals Ltd.. All rights reserved.
 *
 */
#pragma once

#include "Particle.h"

#define MAX_PARTICLES		50000


class ParticleSystem {
public:	
	float posArray[MAX_PARTICLES * 2 * 2];
	float colArray[MAX_PARTICLES * 3 * 2];
	int curIndex, renderMode;
	Particle particles[MAX_PARTICLES];
	ParticleSystem();
	void updateParticles();
    void drawParticles();
	void addParticles(float x, float y, int count );
	void addParticle(float x, float y);
    int particleID;
};