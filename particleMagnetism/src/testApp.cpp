#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    D = 0.7;
    timeCounter = D;
    time = 1;
    x = 100;
    y = 300;
    tick = false;
    particleSystem.renderMode = 2;
    

    for( int i=0; i<8; i++ ){
        for( int j=0; j<6; j++ ){
            float x = ( i + 50 ) * 5.0f;
            float y = ( j + 50 ) * 5.0f;
            particleSystem.addParticle(x,y);
        }
    }
//    for (int i=0;i<NUM_PARTICLES;i++) {
//        particleSystem.addParticle(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()));
//    }
    
	ofBackground(100, 100, 100);
	
    glEnable(GL_NORMALIZE);
    
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
}



//--------------------------------------------------------------
void testApp::update(){
//    ofBackground(100, 100, 100);
    particleSystem.updateParticles();
//    timeCounter = timeCounter + D;
//    if (timeCounter > 1){
//        tick = true;
//        timeCounter = D;
//    }
}

//--------------------------------------------------------------
void testApp::draw(){

    particleSystem.drawParticles();
    drawInfoStrings();
//    increaseTime();
}


void testApp::pSetHSV( float h, float s, float v) {
    // H [0, 360] S, V and A [0.0, 1.0].
    int i = (int)floor(h/60.0f) % 6;
    float f = h/60.0f - floor(h/60.0f);
    float p = v * (float)(1 - s);
    float q = v * (float)(1 - s * f);
    float t = v * (float)(1 - (1 - f) * s);
    
    switch (i) {
        case 0:
            cols[0] = v;
            cols[1] = t;
            cols[2] = p;
            break;
        case 1:
            cols[0] = q;
            cols[1] = v;
            cols[2] = p;
            break;
        case 2:
            cols[0] = p;
            cols[1] = v;
            cols[2] = t;
            break;
        case 3:
            cols[0] = p;
            cols[1] = q;
            cols[2] = v;
            break;
        case 4:
            cols[0] = t;
            cols[1] = p;
            cols[2] = v;
            break;
        case 5:
            cols[0] = v;
            cols[1] = p;
            cols[2] = q;
    }
}

void testApp::increaseTime(){
    if (tick == true){
        x ++;
        tick = false;
    }

}

void testApp::drawInfoStrings() {
    ofSetColor(255,100,100);
    int row = 1;
    row++;
    
    string  info  = "FPS: "+ofToString(ofGetFrameRate(),0)+"\n";
    info += "Particles: "+ofToString(particleSystem.curIndex, 5)+"\n";
    ofDrawBitmapString(info, 10, row++ * 15);

}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    D = ofMap(x,0,1024,0,1);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}