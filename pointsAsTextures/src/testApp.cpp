
#include "testApp.h"

void testApp::setup() {
	ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
    saveFrame = false;
    guiDraw = true;
    tick = 0.0001;
    
	camera.setDistance(300);
    createGUI();

    centre.set(0,0,0);
    circleLocation.set(centre);
    addParticles(150, centre, 0);

    ofDisableArbTex();
    ofLoadImage(texture, "dot.png");

    for (int i=0;i<particles.size();i++) {
        points.push_back(particles[i].pos);
        sizes.push_back(ofVec3f(1));
    }
    
    // upload the data to the vbo
    int total = (int)points.size();
    vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
    vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
    
    // load the shader
    if(shader.load("shader")) {
        printf("Shader is loaded\n");
    }

}

void testApp::update() {
    time = time + tick;
    if (time > 1) {
        updateGUI();
        for(int i=0;i<particles.size();i++) {
            particles[i].run(particles);
        }


        ofSetColor(color);
        for (int i=0;i<particles.size();i++) {
            points[i].set(particles[i].pos);
            sizes[i].set(particles[i].mass);
        }
        
        int total = (int)points.size();
        vbo.setVertexData(&points[0], total, GL_DYNAMIC_DRAW);
        vbo.setNormalData(&sizes[0], total, GL_DYNAMIC_DRAW);
        
        if (reset == true) {
            reset = false;
        }
        time = 0;
    }
    
}

void testApp::draw() {
    
    camera.begin();
    
    glDepthMask(GL_FALSE);
    
    ofBackground(bgColor);
    
    ofEnableAlphaBlending();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    //        glEnable(GL_DEPTH_TEST);
    
    ofEnablePointSprites();
    shader.begin();
    
    texture.bind();
    vbo.draw(GL_POINTS, 0, (int)points.size());
    texture.unbind();
    
    shader.end();
    
    ofDisablePointSprites();
    glDepthMask(GL_TRUE);
    
    ofDisableAlphaBlending();

    camera.end();
//    if (snappy) snapFrame();
    if (guiDraw) gui.draw();

	
}

void testApp::addParticles(int n, ofVec3f centre, int type_) {
    for(int i=0;i<n;i++) {
        particles.push_back(ofxParticle(particleCount, centre, type_));
        particleCount ++;
    }
}

void testApp::keyPressed(int key) {
	
    if (key == 'g') {
        guiDraw = !guiDraw;
    }
    
	if(key == OF_KEY_UP) {
		camDist -= 10;
	}
	if(key == OF_KEY_DOWN) {
		camDist += 10;
	}
    
    if (key == 'r') {
        for (int i=0;i<particles.size();i++) {
            particles[i].reset = true;
        }
    }
    
    if (key == 'f') {
        for (int i=0;i<particles.size();i++) {
            !particles[i].flocking;
        }
    }
    
    if (key == 's') {
        for (int i=0;i<particles.size();i++) {
            particles[i].mass ++;
        }
    }
    
    if (key == 'a') {
        for (int i=0;i<particles.size();i++) {
            particles[i].mass --;
        }
    }
    
	camera.setDistance(camDist);
    if (key == '[') {
        gui.prevPage();
    }
    if (key == ']') {
        gui.nextPage();
    }
}

void testApp::createGUI() {
    gui.addTitle("Personality");
	gui.addSlider("Separation", separationF, 0, 200);
	gui.addSlider("Cohesion", cohesionF, 0, 5);
	gui.addSlider("Alignment", alignF, 0, 5);
    gui.addSlider("Perception", pPerception, 1, 1000);
    gui.addSlider("PersonalSpace", personalSpace, 1, 900);
    gui.addSlider("Force", pForce, 0.1, 10);
    gui.addSlider("Speed", pSpeed, 0.1, 60);
    gui.addSlider("Mass", particleMass,1,100);
    gui.addSlider("maxOrbitForce",maxOrbitForce,0.01,1);
    gui.addSlider("orbitForce",orbitF,0.001,0.9);
    
    gui.addColorPicker("Color", color);
    gui.addSlider("Ribbon Opacity", ribbonOpacity, 0,1);
    gui.addSlider("RibbonWidth", ribbonWidth, 0.1,4).setSmoothing(0.4);
    
    gui.addTitle("Behaviour").setNewColumn(true);
    gui.addToggle("Orbit", orbit);
    gui.addToggle("Avoid Boundaries", avoidBoundaries);
//    gui.addToggle("Gravitate", gravitate);
//    gui.addToggle("Draw Bounds", drawBounds);
//    gui.addToggle("Draw Bodies", drawBodies);
    gui.addToggle("Flock", flocking);
    gui.addToggle("Reset", reset);
    
    gui.addTitle("Color").setNewColumn(true);
    gui.addColorPicker("backgroundColor", bgColor);
    
    gui.addTitle("World").setNewColumn(true);
    gui.addSlider("TimeSpeed",tick,0,1);
    gui.addSlider("Gravity",G,0.01,5);
    gui.addSlider("Drag", dragF, 0.1, 0.99);
    gui.addSlider("bodyMass",bodyMass,1,100);
    
    gui.loadFromXML();
	gui.show();
}

void testApp::updateGUI() {
    
    for(int i=0;i<particles.size();i++) {
        particles[i].avoidBoundaries = avoidBoundaries;
        particles[i].separationF = separationF;
        particles[i].cohesionF = cohesionF;
        particles[i].alignF = alignF;
        particles[i].pPerception = pPerception;
        particles[i].personalSpace = personalSpace;
        particles[i].pForce = pForce;
        particles[i].pSpeed = pSpeed;
        particles[i].reset = reset;
        particles[i].orbit = orbit;
        particles[i].gravitate = gravitate;
        particles[i].color = color;
        particles[i].torusOuterRadius = torusOuterRadius;
        particles[i].torusInnerRadius = torusInnerRadius;
        particles[i].circleLocation.set(circleLocation);
        particles[i].outerBoundF = outerBoundF;
        particles[i].innerBoundF = innerBoundF;
        particles[i].attractF = attractF;
        particles[i].G = G;
        particles[i].orbitF = orbitF;
        particles[i].maxOrbitForce = maxOrbitForce;
        particles[i].ribbonWidth = ribbonWidth;
        particles[i].mass = particleMass;
        particles[i].dragF = dragF;
        particles[i].flocking = flocking;
    }
}
