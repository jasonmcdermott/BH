#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
//    saveFrame = false;
//    guiDraw = true;
//    tick = 0.0001;

//	camera.setDistance(100);
//    setupGUI();
}

void testApp::update(){
//    time = time + tick;
//    if (time > 1) {
//        ps.update();
//        time = 0;
//    }
}

void testApp::draw(){
//    camera.begin();
//    ps.render();
//    camera.end();
//    if (guiDraw) gui.draw();
}

//void testApp::setupGUI() {
//    gui.addTitle("Personality");
//	gui.addSlider("Separation", ps.separationF, 0, 60);
//	gui.addSlider("Cohesion", ps.cohesionF, 0, 5);
//	gui.addSlider("Alignment", ps.alignF, 0, 5);
//    gui.addSlider("Perception", ps.pPerception, 1, 500);
//    gui.addSlider("PersonalSpace", ps.personalSpace, 1, 400);
//    gui.addSlider("Force", ps.pForce, 0.1, 10);
//    gui.addSlider("Speed", ps.pSpeed, 0.1, 60);
//    gui.addSlider("Mass", ps.particleMass,1,100);
//    gui.addSlider("maxOrbitForce",ps.maxOrbitForce,0.01,1);
//    gui.addSlider("orbitForce",ps.orbitF,0.001,0.9);
//
//    gui.addColorPicker("Color", ps.color);
//    gui.addSlider("Ribbon Opacity", ps.ribbonOpacity, 0,1);
//    gui.addSlider("RibbonWidth", ps.ribbonWidth, 0.1,4).setSmoothing(0.4);
//
//    gui.addTitle("Behaviour").setNewColumn(true);
//    gui.addToggle("Orbit", ps.orbit);
//    gui.addToggle("Avoid Boundaries", ps.avoidBoundaries);
//    gui.addToggle("Gravitate", ps.gravitate);
//    gui.addToggle("Reset", ps.reset);
//    gui.addToggle("Draw Bounds", ps.drawBounds);
//    gui.addToggle("Draw Bodies", ps.drawBodies);
//    gui.addColorPicker("backgroundColor", ps.bgColor);
//    
//    gui.addTitle("World").setNewColumn(true);
//    gui.addSlider("TimeSpeed",tick,0,1);
//    gui.addSlider("Gravity",ps.G,0.01,5);
//    gui.addSlider("Drag", ps.dragF, 0.1, 0.99);
//    gui.addSlider("bodyMass",ps.bodyMass,1,100);
//    
//    gui.loadFromXML();
//	gui.show();
//}

void testApp::keyPressed(int key){
//    if (key == 'g') {
//        guiDraw = !guiDraw;
//    }
//    if (key == 's') {
//        snappy = true;
//    }
//    if (key == '[') {
//        gui.prevPage();
//    }
//    if (key == ']') {
//        gui.nextPage();
//    }
}
