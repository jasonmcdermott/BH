#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofSetVerticalSync(true);
    ofEnableSmoothing();

    ofSetCircleResolution(100);
    
    saveFrame = true;
    guiDraw = false;
    tick = 0.0001;
	memset(snapString, 0, 255);

    setupCam();
    setupGUI();
}

void testApp::update(){

//    ofEnableAlphaBlending();
    glEnable(GL_DEPTH_TEST);
    time = time + tick;
    if (time > 1) {
        ps.updateGUI();
        ps.update();
        time = 0;
    }
    
    cam.setPosition(camPos.x, camPos.y, camPos.z);
    cam.lookAt(ps.centre);
}


void testApp::draw(){
    if (camDraw) cam.begin(); cam.draw();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    ps.render();
    
    if (camDraw) cam.end();
    if (guiDraw) gui.draw();
    
    ofSetColor(255,200);
    ofDrawBitmapString("Hit 'g' to toggle GUI", 20,ofGetHeight()-20);
    snapFrame();
}

void testApp::updateGUI() {

}


void testApp::setupGUI() {
    gui.addTitle("Particles");

	gui.addSlider("Separation", ps.separationF, 0, 35);
	gui.addSlider("Cohesion", ps.cohesionF, 0, 5);
	gui.addSlider("Alignment", ps.alignF, 0, 5);
    gui.addSlider("Attraction", ps.attractF, 0, 1.00);
    gui.addSlider("Perception", ps.pPerception, 1, 500);
    gui.addSlider("PersonalSpace", ps.personalSpace, 1, 100);
    gui.addSlider("Force", ps.pForce, 0.1, 10);
    gui.addSlider("Speed", ps.pSpeed, 0.1, 10);
    gui.addSlider("Drag", ps.dragF, 0.1, 1);
    gui.addColorPicker("Color", ps.color);
    gui.addToggle("Interact with Bodies", ps.interactWithBodies);
    gui.addToggle("Avoid Walls", ps.avoidWalls);
//    gui.addToggle("ps", ps.flock);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Size",ps.worldSize,100,2000);
    gui.addToggle("Draw Bounds", ps.drawBounds);
    gui.addToggle("Draw Bodies", ps.drawBodies);
    gui.addToggle("Draw ps", ps.drawFlock);
    gui.addToggle("Draw Predators", ps.drawPreds);
    gui.addToggle("Reset", ps.reset);
    gui.addSlider("outerBounds",ps.torusOuterRadius,50,300);
    gui.addSlider("innerBounds", ps.torusInnerRadius, 5,290);
    gui.addSlider("innerBoundForce",ps.innerBoundF,0.1,50);
    gui.addSlider("outerBoundForce",ps.outerBoundF,0.1,5);
    gui.addSlider("bodyChargeForce",ps.bodyChargeF,0.1,15);
    gui.addSlider("bodyMass",ps.bodyMass,1,100);
    
    gui.addTitle("Camera").setNewColumn(true);
    gui.addSlider("Camera Position X", camPos.x, -2000, 2000);
    gui.addSlider("Camera Position Y", camPos.y, -2000, 2000);
    gui.addSlider("Camera Position Z", camPos.z, -2000, 2000);
    gui.loadFromXML();
	gui.show();
}

void testApp::setupCam() {
    cam.resetTransform();
    cam.setFov(60);
    cam.clearParent();
    camDraw = true;
    camPos.set(ofGetWidth()/2, ofGetHeight()/2, WORLDSIZE*2);
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

