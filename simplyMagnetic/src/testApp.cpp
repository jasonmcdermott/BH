#include "testApp.h"



void testApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
//    glEnable(GL_DEPTH_TEST);
    ofSetCircleResolution(100);

    
    saveFrame = false;
    guiDraw = false;

    tick = 0.0001;
	memset(snapString, 0, 255);
    
//    personalSpace = 1;

    cam.resetTransform();
    cam.setFov(60);
    cam.clearParent();
    camDraw = true;
    
    setupGUI();
    camPos.set(ofGetWidth()/2, ofGetHeight()/2, WORLDSIZE*2);
    
    gui.loadFromXML();
	gui.show();
}


void testApp::update(){
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_BLEND);

    ofEnableAlphaBlending();
    time = time + tick;
    if (time > 1) {
        updateGUI();
        ps.update();
        time = 0;
    }
    cam.setPosition(camPos.x, camPos.y, camPos.z);
    cam.lookAt(ps.centre);
}


void testApp::draw(){
    if (camDraw) cam.begin(); cam.draw();

//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnableClientState      (GL_VERTEX_ARRAY);
    ps.draw();
    glDisableClientState   (GL_VERTEX_ARRAY);
    
    if (camDraw) cam.end();
    if (guiDraw) gui.draw();
    ofSetColor(255,200);
    ofDrawBitmapString("Hit 'g' to toggle GUI", 20,ofGetHeight()-20);
    snapFrame();
}

void testApp::updateGUI() {
    ps.updateGUI();

}


void testApp::setupGUI() {
    gui.addTitle("Boids");

	gui.addSlider("Separation", ps.separationF, 0, 15);
	gui.addSlider("Cohesion", ps.cohesionF, 0, 5);
	gui.addSlider("Alignment", ps.alignF, 0, 5);
    gui.addSlider("Boid Perception", ps.pPerception, 1, 500);
    gui.addSlider("PersonalSpace", ps.personalSpace, 1, 100);
    gui.addSlider("Boid Force", ps.pForce, 0.1, 10);
    gui.addSlider("Boid Speed", ps.pSpeed, 0.1, 10);
    gui.addSlider("Drag", ps.dragF, 0.1, 1);
    gui.addColorPicker("Boid Color", ps.boidColor);
    gui.addSlider("Evade Force", ps.evadeForce, 0.1, 35);
    gui.addToggle("Interact with Bodies", ps.interactWithBodies);
    gui.addToggle("Interact with Predators", ps.interactWithPredators);
    gui.addToggle("Avoid Walls", ps.avoidWalls);
//    gui.addToggle("ps", ps.flock);
    
    gui.addTitle("Predators").setNewColumn(true);
    gui.addSlider("Predator Speed",ps.predSpeed,0.1,10);
    gui.addSlider("Predator Force",ps.predForce,0.1,10);
    gui.addSlider("Predator Perception", ps.predPerception, 1, 500);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Size",ps.worldSize,100,2000);
    gui.addToggle("Draw Bounds", ps.drawBounds);
    gui.addToggle("Draw Bodies", ps.drawBodies);
    gui.addToggle("Draw ps", ps.drawFlock);
    gui.addToggle("Draw Predators", ps.drawPreds);
    gui.addToggle("Reset Boids", ps.reset);
    gui.addSlider("outerBounds",ps.torusOuterRadius,50,1000);
    gui.addSlider("innerBounds", ps.torusInnerRadius, 50,1000);
    
    gui.addTitle("Camera").setNewColumn(true);
    gui.addSlider("Camera Position X", camPos.x, -2000, 2000);
    gui.addSlider("Camera Position Y", camPos.y, -2000, 2000);
    gui.addSlider("Camera Position Z", camPos.z, -2000, 2000);

}

void testApp::keyPressed(int key){
    if (key == 'g') {
        guiDraw = !guiDraw;
    }
}

void testApp::snapFrame() {
    
    if (ofGetFrameNum() % 900 == 0 && saveFrame == true){
		img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		string fileName = "../../../../../images/psing3D_"+ofGetTimestampString()+".png";
		img.saveImage(fileName);
	}
}

void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

