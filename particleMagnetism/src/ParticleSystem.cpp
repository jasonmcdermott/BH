
#include "testApp.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
	curIndex = 0;
}


void ParticleSystem::updateParticles() {
    
    for (int i=0; i<curIndex; ++i) {
        if (particles[i].isDead == false) {
            for (int j=0;j<curIndex;j++) {
                if (particles[j].isDead == false) {
                    if (particles[i].ID != particles[j].ID) {
                        ofVec2f a;
                        ofVec2f b;
                        a.set(particles[i].x,particles[i].y);
                        b.set(particles[j].x,particles[i].y);
                        
                        float dist = a.distance(b);
                    
                        ofVec2f dir = particles[i].pos - particles[j].pos;
//                        cout << " a " << particles[i].x << " b " <<  particles[j].x << " _ " << dist << ". ";
                        
                        
                        
                        float distSquared = dir.lengthSquared();
//                        cout << " " << distSquared << ". ";
                        if (distSquared > 0.0) {
                            dir.normalize();
                            float F = 1.0f/distSquared;
                            if (particles[i].charge > 0 && particles[j].charge > 0){
                                particles[i].acc += (dir * F) / particles[i].mass;
                                particles[j].acc -= (dir *  F) / particles[j].mass;
                            } else if (particles[i].charge < 0 && particles[j].charge < 0){
                                particles[i].acc -= (dir * F) / particles[i].mass;
                                particles[j].acc += (dir *  F) / particles[j].mass;
                            } else if (particles[i].charge > 0 && particles[j].charge < 0) {
                                particles[i].acc -= (dir * F) / particles[i].mass;
                                particles[j].acc += (dir *  F) / particles[j].mass;
                            } else if (particles[i].charge < 0 && particles[j].charge > 0) {
                                particles[i].acc -= (dir * F) / particles[i].mass;
                                particles[j].acc += (dir *  F) / particles[j].mass;
                            }
                        }
                    }
                }
            }
        }
    }
    
    for (int i=0;i<curIndex;i++) {
        if (particles[i].isDead == false) {
            particles[i].updateParticle();
        }
    }
}

void ParticleSystem::drawParticles(){
    
    if (renderMode == 0) {     // use vanilla OF renderng
		for(int i=0; i<curIndex; i++) {
            particles[i].drawOldSchool();
		}
    } else if (renderMode > 0) {
    	glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_LINE_SMOOTH);
        if(renderMode == 2) {
            for(int i=0; i<curIndex; i++) {
                particles[i].updateVertexArrays(i, posArray, colArray);
            }
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(2, GL_FLOAT, 0, posArray);
            
            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer(3, GL_FLOAT, 0, colArray);
            
            glDrawArrays(GL_LINES, 0, MAX_PARTICLES * 2);

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
        } else if (renderMode == 1){
            glBegin(GL_LINES);               // start drawing points
            for(int i=0; i<curIndex; i++) {
                particles[i].drawStandardGL();    // use standard vertex renderng
            }
            glEnd();
        }
        glDisable(GL_BLEND);
    }
}

void ParticleSystem::addParticles(float x, float y, int count ){
	for(int i=0; i<count; i++) addParticle(x + ofRandom(-15, 15), y + ofRandom(-15, 15));
}


void ParticleSystem::addParticle(float x, float y) {
	particles[curIndex].init(x, y, curIndex);
	curIndex++;
	if(curIndex >= MAX_PARTICLES) curIndex = 0;
}

