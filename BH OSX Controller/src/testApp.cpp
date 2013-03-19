#include "testApp.h"


void testApp::setup(){
	sender.setup(HOST, PORT);
    setupGUI();
    orbitInt = 0;
    gravityInt = 0;
    flockInt = 0;
    boundaryInt = 0;
    transmit();
}

void testApp::update(){
    if (orbit) {
        orbitMe = "yes";
    } else {
        orbitMe = "no";
    }
    if (gravitate) {
        gravityMe = "yes";
    } else {
        gravityMe = "no";
    }
    if (avoidBoundaries) {
        avoidMe = "yes";
    } else {
        avoidMe = "no";
    }
    if (reset) {
        resetMe = "yes";
    }
    if (flock) {
        flockMe = "yes";
    } else {
        flockMe = "no";
    }
    if (ofGetFrameNum() % 100 == 0) {
        transmit();
    }
}

void testApp::draw(){
    ofBackground(bgColor);
    gui.draw();
}

void testApp::setupGUI() {
    gui.addTitle("Personality");
	gui.addSlider("Separation", separationF, 0, 60);
	gui.addSlider("Cohesion", cohesionF, 0, 5);
	gui.addSlider("Alignment", alignF, 0, 5);
    gui.addSlider("Perception", perception, 1, 500);
    gui.addSlider("PersonalSpace", personalSpace, 1, 400);
    gui.addSlider("Force", force, 0.1, 10);
    gui.addSlider("Speed", speed, 0.1, 60);
    gui.addSlider("DotSize", scale, 1,100);
    gui.addSlider("maxOrbitForce",maxOrbitForce,0.01,1);
    gui.addSlider("orbitForce",orbitF,0.001,0.9);
    
//    gui.addColorPicker("Color", col);
    gui.addSlider("Red",Red,0,255);
    gui.addSlider("Green",Green,0,255);
    gui.addSlider("Blue",Blue,0,255);
    gui.addSlider("Alpha",Alpha,0,255);
    gui.addSlider("Ribbon Opacity", ribbonOpacity, 0,1);
    gui.addSlider("RibbonWidth", ribbonWidth, 0.1,4).setSmoothing(0.4);
    
    gui.addTitle("Behaviour").setNewColumn(true);
    gui.addToggle("Orbit", orbit);
    gui.addToggle("Avoid Boundaries", avoidBoundaries);
    gui.addToggle("Gravitate", gravitate);
    gui.addToggle("Flock", flock);
    gui.addToggle("Reset", reset);
    gui.addSlider("Flock",flockInt,0,1);
    
    gui.addTitle("World").setNewColumn(true);
//    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Gravity",G,0.01,5);
    gui.addSlider("Drag", dragF, 0.1, 0.99);
    gui.addSlider("bodyMass",bodyMass,1,100);
    gui.addSlider("Rendering Mode",mode,0,3);
    
    gui.addPage("Graphics");
    gui.addTitle("Drawing");
    gui.addToggle("Draw Bounds", drawBounds);
    gui.addToggle("Draw Bodies", drawBodies);
    gui.addColorPicker("backgroundColor", bgColor);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("outerBounds",torusOuterRadius,7,600);
    gui.addSlider("innerBounds", torusInnerRadius, 5,290);
    gui.addSlider("innerBoundForce",innerBoundF,0.1,50);
    gui.addSlider("outerBoundForce",outerBoundF,0.1,50);
    
    gui.addTitle("Blending").setNewColumn(true);
    gui.addToggle("Blending", blending);
    gui.addToggle("Depth", depth);
    string renderArray[] = {"VBO", "Spheres", "Points", "VertexArray", "Gradients!", "Dots and Ribbons", "VBO Billboarding", "debug", "trails", "ribbons"};
    gui.addComboBox("RenderMode", renderMode, 10, renderArray);
    
    gui.addPage("Bright Hearts Gradients");
    gui.addTitle("rings");
    string shapeArray[] = {"Sphere", "Ring", "FeatheredEdge"};
    gui.addComboBox("shapeType", BHGShapeType, 3, shapeArray);
    gui.addSlider("Blur", BHGBlur,-20,100);
    gui.addSlider("Number of Sides", BHGNumSides,3,60);
    gui.addSlider("Thickness", BHGThickness,-50,50);
    
    gui.addTitle("Central Body");
    string bodyShapeArray[] = {"Sphere", "Ring", "FeatheredEdge"};
    gui.addComboBox("shapeType", bodyBHGShapeType, 3, bodyShapeArray);
    gui.addSlider("Blur", bodyBHGBlur,-20,100);
    gui.addSlider("Number of Sides", bodyBHGNumSides,3,60);
    gui.addSlider("Thickness", bodyBHGThickness,-50,50);
    
    gui.loadFromXML();
	gui.show();
}



void testApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m);
	}
    if (key == '[') {
        gui.prevPage();
    }
    if (key == ']') {
        gui.nextPage();
    }

}


void testApp::transmit() {
    ofxOscMessage m;
    
	m.setAddress("/BH/bgColor");
    m.addFloatArg(bgColor.r);
    m.addFloatArg(bgColor.g);
    m.addFloatArg(bgColor.b);
    m.addFloatArg(bgColor.a);
	sender.sendMessage(m);
    
    m.setAddress("/BH/flock");
    m.addFloatArg(separationF);
    m.addFloatArg(alignF);
    m.addFloatArg(cohesionF);
    m.addFloatArg(personalSpace);
    m.addFloatArg(perception);
    m.addFloatArg(force);
    m.addFloatArg(speed);
    m.addFloatArg(orbitF);
    sender.sendMessage(m);
    
    m.setAddress("/BH/visuals");
    m.addFloatArg(scale);
    m.addFloatArg(Red);
    m.addFloatArg(Green);
    m.addFloatArg(Blue);
    m.addFloatArg(Alpha);
    sender.sendMessage(m);
    
    m.setAddress("/BH/world");
    m.addStringArg(orbitMe);
    m.addStringArg(avoidMe);
    m.addStringArg(gravityMe);
    m.addStringArg(flockMe);
    m.addStringArg(resetMe);
    m.addFloatArg(G);
    m.addFloatArg(dragF);
    m.addIntArg(mode);
    sender.sendMessage(m);
    
    reset = false;
    resetMe = "no";
}



void testApp::keyReleased(int key){
    transmit();
}


void testApp::mouseMoved(int x, int y){
	ofxOscMessage m;
	m.setAddress("/mouse/position");
	m.addIntArg(x);
	m.addIntArg(y);
	sender.sendMessage(m);
}

void testApp::mouseDragged(int x, int y, int button){}

void testApp::mousePressed(int x, int y, int button){}

void testApp::mouseReleased(int x, int y, int button){
    
    transmit();
    
}

void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

