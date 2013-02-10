#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
    saveFrame = true;
    guiDraw = false;
    tick = 0.0001;
	memset(snapString, 0, 255);

    // set the camera distance
	camDist  = 100;
	camera.setDistance(camDist);

    
//    setupCam();
    setupGUI();
}

void testApp::update(){
    time = time + tick;
    if (time > 1) {
        ps.updateGUI();
        ps.update();
        time = 0;
    }
//    cam.setPosition(camPos.x, camPos.y, camPos.z);
//    cam.lookAt(ps.centre);
}


void testApp::draw(){
//    if (camDraw) cam.begin(); cam.draw();
    
    camera.begin();
    ps.render();
    camera.end();

//    if (camDraw) cam.end();
    snapFrame("auto");
    if (guiDraw) gui.draw();
    ofSetColor(255,200);
    ofDrawBitmapString("Hit 'g' to toggle GUI", 20,ofGetHeight()-20);

}

void testApp::updateGUI() {}


void testApp::setupGUI() {
    gui.addTitle("Personality");
	gui.addSlider("Separation", ps.separationF, 0, 60);
	gui.addSlider("Cohesion", ps.cohesionF, 0, 5);
	gui.addSlider("Alignment", ps.alignF, 0, 5);
    gui.addSlider("Perception", ps.pPerception, 1, 500);
    gui.addSlider("PersonalSpace", ps.personalSpace, 1, 400);
    gui.addSlider("Force", ps.pForce, 0.1, 10);
    gui.addSlider("Speed", ps.pSpeed, 0.1, 60);
    gui.addSlider("Drag", ps.dragF, 0.1, 1);
    gui.addColorPicker("Color", ps.color);
    gui.addSlider("orbitForce",ps.orbitF,0.001,0.9);
    
    gui.addTitle("Behaviour").setNewColumn(true);
    gui.addToggle("Orbit", ps.orbit);
    gui.addToggle("Avoid Boundaries", ps.avoidBoundaries);
    gui.addToggle("Gravitate", ps.gravitate);
    gui.addToggle("Reset", ps.reset);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Gravity",ps.G,0.1,50);
    gui.addSlider("bodyMass",ps.bodyMass,1,100);

    gui.addPage("Graphics");
    gui.addTitle("Drawing");
    gui.addToggle("Draw Bounds", ps.drawBounds);
    gui.addToggle("Draw Bodies", ps.drawBodies);
    gui.addColorPicker("backgroundColor", ps.bgColor);

    gui.addTitle("Camera").setNewColumn(true);
    gui.addSlider("Camera Position X", camPos.x, -2000, 2000);
    gui.addSlider("Camera Position Y", camPos.y, -2000, 2000);
    gui.addSlider("Camera Position Z", camPos.z, -2000, 2000);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("outerBounds",ps.torusOuterRadius,7,600);
    gui.addSlider("innerBounds", ps.torusInnerRadius, 5,290);
    gui.addSlider("innerBoundForce",ps.innerBoundF,0.1,50);
    gui.addSlider("outerBoundForce",ps.outerBoundF,0.1,50);
    
    gui.addTitle("Blending").setNewColumn(true);
    gui.addToggle("Blending", ps.blending);
    gui.addToggle("Depth", ps.depth);
    string blendArray[] = {"Additive", "Screen", "Multiply", "Alpha", "Subtract"};
    gui.addComboBox("BlendMode", ps.blendMode, 5, blendArray);
    string renderArray[] = {"VBO", "Spheres", "Points", "VertexArray", "Gradients!", "Trails", "VBO Billboarding", "debug"};
    gui.addComboBox("RenderMode", ps.renderMode, 8, renderArray);

    gui.addPage("Bright Hearts Gradients");
    gui.addTitle("rings");
    string shapeArray[] = {"Sphere", "Ring", "FeatheredEdge"};
    gui.addComboBox("shapeType", ps.BHGShapeType, 3, shapeArray);
    gui.addSlider("Blur", ps.BHGBlur,-20,100);
    gui.addSlider("Number of Sides", ps.BHGNumSides,3,60);
    gui.addSlider("Thickness", ps.BHGThickness,-50,50);
    
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
    if (key == 's') {
        snapFrame("key");
    }
    
    if(key>='0' && key<='9') {
		gui.setPage(key - '0');
		gui.show();
	} else {
		switch(key) {
			case ' ': gui.toggleDraw(); break;
			case '[': gui.prevPage(); break;
			case ']': gui.nextPage(); break;
			case 'p': gui.nextPageWithBlank(); break;
		}
	}

    if(key == OF_KEY_UP) {
		camDist -= 10;
	}
	if(key == OF_KEY_DOWN) {
		camDist += 10;
	}
	camera.setDistance(camDist);
}

void testApp::snapFrame(string mode) {
    
    if (mode == "key") {
        img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
		string fileName = "../../../../../images/particles_"+ofGetTimestampString()+".png";
		img.saveImage(fileName);
    }
    else if (mode == "auto") {
        if (ofGetFrameNum() % 900 == 0 && saveFrame == true){
            img.grabScreen(0,0,ofGetWidth(),ofGetHeight());
            string fileName = "../../../../../images/particles_"+ofGetTimestampString()+".png";
            img.saveImage(fileName);
        }
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

