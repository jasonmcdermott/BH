#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
    saveFrame = true;
    guiDraw = true;
    tick = 0.0001;
	memset(snapString, 0, 255);

	camera.setDistance(100);
    setupGUI();
}

void testApp::update(){
    time = time + tick;
    if (time > 1) {
        ps.updateGUI();
        ps.update();
        time = 0;
    }
}


void testApp::draw(){
    
    camera.begin();
        ps.render();
    camera.end();

    snapFrame(snappy);
    if (guiDraw) gui.draw();
    ofSetColor(255,200);
    ofDrawBitmapString("Hit 'g' to toggle GUI", 20,ofGetHeight()-20);

}

void testApp::setupGUI() {
    gui.addTitle("Personality");
	gui.addSlider("Separation", ps.separationF, 0, 60);
	gui.addSlider("Cohesion", ps.cohesionF, 0, 5);
	gui.addSlider("Alignment", ps.alignF, 0, 5);
    gui.addSlider("Perception", ps.pPerception, 1, 500);
    gui.addSlider("PersonalSpace", ps.personalSpace, 1, 400);
    gui.addSlider("Force", ps.pForce, 0.1, 10);
    gui.addSlider("Speed", ps.pSpeed, 0.1, 60);
    gui.addSlider("Mass", ps.particleMass,1,100);
    gui.addSlider("maxOrbitForce",ps.maxOrbitForce,0.01,1);
    gui.addSlider("orbitForce",ps.orbitF,0.001,0.9);

    gui.addColorPicker("Color", ps.color);
    gui.addSlider("Ribbon Opacity", ps.ribbonOpacity, 0,1);
    gui.addSlider("RibbonWidth", ps.ribbonWidth, 0.1,4).setSmoothing(0.4);

    gui.addTitle("Behaviour").setNewColumn(true);
    gui.addToggle("Orbit", ps.orbit);
    gui.addToggle("Avoid Boundaries", ps.avoidBoundaries);
    gui.addToggle("Gravitate", ps.gravitate);
    gui.addToggle("Reset", ps.reset);
    gui.addToggle("Draw Bounds", ps.drawBounds);
    gui.addToggle("Draw Bodies", ps.drawBodies);
    gui.addColorPicker("backgroundColor", ps.bgColor);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Gravity",ps.G,0.01,5);
    gui.addSlider("Drag", ps.dragF, 0.1, 0.99);
    gui.addSlider("bodyMass",ps.bodyMass,1,100);

    gui.addTitle("Blending").setNewColumn(true);
    gui.addToggle("Blending", ps.blending);
    gui.addToggle("Depth", ps.depth);
    string renderArray[] = {"VBO", "Spheres", "Points", "VertexArray", "Gradients!", "Dots and Ribbons", "VBO Billboarding", "debug", "trails", "ribbons"};
    gui.addComboBox("RenderMode", ps.renderMode, 10, renderArray);
    
    gui.addPage("Graphics");
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("outerBounds",ps.torusOuterRadius,7,600);
    gui.addSlider("outerBoundForce",ps.outerBoundF,0.1,50);
    gui.addSlider("innerBounds", ps.torusInnerRadius, 5,290);
    gui.addSlider("innerBoundForce",ps.innerBoundF,0.1,50);

    gui.addPage("Bright Hearts Gradients");
    gui.addTitle("rings");
    string shapeArray[] = {"Sphere", "Ring", "FeatheredEdge"};
    gui.addComboBox("shapeType", ps.BHGShapeType, 3, shapeArray);
    gui.addSlider("Blur", ps.BHGBlur,-20,100);
    gui.addSlider("Number of Sides", ps.BHGNumSides,3,60);
    gui.addSlider("Thickness", ps.BHGThickness,-50,50);
    
    gui.addTitle("Central Body");
    string bodyShapeArray[] = {"Sphere", "Ring", "FeatheredEdge"};
    gui.addComboBox("shapeType", ps.bodyBHGShapeType, 3, bodyShapeArray);
    gui.addSlider("Blur", ps.bodyBHGBlur,-20,100);
    gui.addSlider("Number of Sides", ps.bodyBHGNumSides,3,60);
    gui.addSlider("Thickness", ps.bodyBHGThickness,-50,50);
    
    gui.loadFromXML();
	gui.show();
}

void testApp::keyPressed(int key){
    if (key == 'g') {
        guiDraw = !guiDraw;
    }
    if (key == 's') {
        snappy = true;
    }
    if (key == '[') {
        gui.prevPage();
    }
    if (key == ']') {
        gui.nextPage();
    }
    
//    if(key == OF_KEY_UP) {
//		camDist -= 10;
//	}
//	if(key == OF_KEY_DOWN) {
//		camDist += 10;
//	}
}

void testApp::snapFrame(bool snap) {
    
    if (snap == true) {
        img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		string fileName = "../../../../../images/particles_"+ofGetTimestampString()+".png";
		img.saveImage(fileName);
    }
    else if (snap == false) {
        if (ofGetFrameNum() % 900 == 0 && saveFrame == true){
            img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
            string fileName = "../../../../../images/particles_"+ofGetTimestampString()+".png";
            img.saveImage(fileName);
        }
    }
    snappy = false;
}

void testApp::keyReleased(int key){}
void testApp::mouseMoved(int x, int y){}
void testApp::mouseDragged(int x, int y, int button){}
void testApp::mousePressed(int x, int y, int button){}
void testApp::mouseReleased(int x, int y, int button){}
void testApp::windowResized(int w, int h){}
void testApp::gotMessage(ofMessage msg){}
void testApp::dragEvent(ofDragInfo dragInfo){}

