#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    D = 0.7;
    timeCounter = D;
    time = 1;
    x = 100;
    y = 300;
    tick = false;

    for (int i=0; i<100; i++)
	{
		positions.push_back(ofVec3f(ofRandom(-10, 10),
									ofRandom(-10, 10),
									ofRandom(-10, 10)));
		
		colours.push_back(ofColor(ofRandom(100) + 100,
								  ofRandom(100) + 100,
								  ofRandom(100) + 100));
	}
	
	ofBackground(100, 100, 100);
	ofEnableSmoothing();
    glEnable(GL_NORMALIZE);
    glEnable ( GL_LIGHTING ) ;
    glEnable(GL_DEPTH_TEST);
    // light the scene to show off why normals are important
    light.enable();
    light.setPointLight();
    light.setPosition(0,0,300);
    
    
    
//    ofLightlight.enable();
//    light.setDirectional();
//    light.setPosition(0,0,150);
//    ofFloatColorambient_color(1.0,0.0,0.0,1.0);
//    ofFloatColordiffuse_color(1.0,1.0,1.0);
//    ofFloatColorspecular_color(0.0,1.0,0.0);
//    light.setAmbientColor(ambient_color);
//    light.setDiffuseColor(diffuse_color);
//    light.setSpecularColor(specular_color);
    

}



//--------------------------------------------------------------
void testApp::update(){
    setHSB();
    timeCounter = timeCounter + D;
    if (timeCounter > 1){
        tick = true;
        timeCounter = D;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if (tick == true){
        x ++;
        tick = false;
    }
//    GLfloat lightpos[] = {.5, -1., -1., 0.};
//    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    
    //    ofRect(x,y,10,10);
    
    vector<ofVec3f>::iterator p = positions.begin();
	vector<ofColor>::iterator c = colours.begin();
	
	////
	//draw scene

    camera.begin();
    light.draw();
    
    ofPushMatrix();
    ofTranslate(0,0,-1);
    
    drawShape(0.3,0.5,-1,0.2,0.6,0.2,x,x,x,top,bottom,front,back,left,right,1);
    drawShape(0.1,0.6,-0.5,0.8,0.5,0.2,x,x,x,top,bottom,front,back,left,right,1);
    drawShape(0.1,0.6,-0.5,0.8,0.5,0.2,x,x,x,top,bottom,front,back,left,right,0);
    drawShape(0,0,0,2,2,6,0,0,0,top,bottom,front,back,left,right,1);
    
	drawGrid(5.0f, 10.0f);

    ofPopMatrix();
	camera.end();

    ofSetColor(255,100,100);
    int row = 1;
	ofDrawBitmapString("ofxGrabCam", 10, row++ * 15);
	ofDrawBitmapString("Drag with left mouse to orbit", 10, row++ * 15);
	ofDrawBitmapString("Drag with right mouse to zoom", 10, row++ * 15);
	ofDrawBitmapString("Hold 'h' and drag with left mouse to pan", 10, row++ * 15);
	ofDrawBitmapString("Press 'r' to reset", 10, row++ * 15);
    
	row++;
	
	ofDrawBitmapString("This example", 10, row++ * 15);
	ofDrawBitmapString("Press 'c' to toggleCursorDraw", 10, row++ * 15);
	ofDrawBitmapString("Press 'u' to  toggleFixUpwards", 10, row++ * 15);
	ofDrawBitmapString("Press 's' to save camera pose to savedPose", 10, row++ * 15);
	ofDrawBitmapString("Press 'l' to load camera pose from savedPose", 10, row++ * 15);
	
	//demonstrate resiliance to stray matrices
//	ofRotate(ofRandom(360), 0, 1, 0);
//	ofScale(ofRandom(30), ofRandom(30));
    
    
    string  info  = "FPS:        "+ofToString(cols[0],0)+"\n";
    info += "D: "+ofToString(D, 5)+"\n";
    ofSetColor(0);
    ofDrawBitmapString(info, 20, 20);
    
    
}

void testApp::drawShape(float xOffset_, float yOffset_, float zOffset_, float width_, float height_, float depth_, float orientationX_, float orientationZ_, float orientationY_, ofColor top_, ofColor bottom_,ofColor front_,ofColor back_, ofColor left_, ofColor right_, int shapeType){
    
    ofPushMatrix();
    ofTranslate(xOffset_,yOffset_,zOffset_);	
    ofPushMatrix();
    ofRotateX(orientationX_);
    ofRotateY(orientationY_);
    ofRotateZ(orientationZ_);
    if (shapeType == 1) {
        drawCube(width_,height_,depth_,top_,bottom_,front_,back_,left_,right_);
    } else if (shapeType == 0) {
        ofSphere(xOffset_,yOffset_,zOffset_,width_);
    }
    ofPopMatrix();
    ofPopMatrix();
    
}

void testApp::drawGrid(float scale, float ticks, bool labels, bool x, bool y, bool z) {
	
	ofColor c = ofGetStyle().color;
	
	ofPushStyle();
	
	if (x) {
		c.setHue(0.0f);
		ofSetColor(c);
		drawGridPlane(scale, ticks, labels);
	}
	if (y) {
		c.setHue(255.0f / 3.0f);
		ofSetColor(c);
		ofPushMatrix();
		ofRotate(90, 0, 0, 1);
		drawGridPlane(scale, ticks, labels);
		ofPopMatrix();
	}
	if (z) {
		c.setHue(255.0f * 2.0f / 3.0f);
		ofSetColor(c);
		ofPushMatrix();
		ofRotate(90, 0, 1, 0);
		drawGridPlane(scale, ticks, labels);
		ofPopMatrix();
	}
	
	ofPopStyle();
}


void testApp::drawCube(float x_,float y_,float z_,ofColor top_, ofColor bottom_, ofColor front_, ofColor back_, ofColor left_, ofColor right_){

    float x = x_/2;
    float y = y_/2;
    float z = z_/2;
    
    
    glBegin(GL_QUADS);

    pSetHSV(top_.getHue(),top_.getSaturation(),top_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f( x, y,-z);          // Top Right Of The Quad (Top)
    glVertex3f(-x, y,-z);          // Top Left Of The Quad (Top)
    glVertex3f(-x, y, z);          // Bottom Left Of The Quad (Top)
    glVertex3f( x, y, z);          // Bottom Right Of The Quad (Top)

    pSetHSV(bottom_.getHue(),bottom_.getSaturation(),bottom_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f( x,-y, z);          // Top Right Of The Quad (Bottom)
    glVertex3f(-x,-y, z);          // Top Left Of The Quad (Bottom)
    glVertex3f(-x,-y,-z);          // Bottom Left Of The Quad (Bottom)
    glVertex3f( x,-y,-z);          // Bottom Right Of The Quad (Bottom)

    pSetHSV(front_.getHue(),front_.getSaturation(),front_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f( x, y, z);          // Top Right Of The Quad (Front)
    glVertex3f(-x, y, z);          // Top Left Of The Quad (Front)
    pSetHSV(60,100,100);
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f(-x,-y, z);          // Bottom Left Of The Quad (Front)
    glVertex3f( x,-y, z);          // Bottom Right Of The Quad (Front)
    
    pSetHSV(back_.getHue(),back_.getSaturation(),back_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f( x,-y,-z);          // Bottom Left Of The Quad (Back)
    glVertex3f(-x,-y,-z);          // Bottom Right Of The Quad (Back)
    glVertex3f(-x, y,-z);          // Top Right Of The Quad (Back)
    glVertex3f( x, y,-z);          // Top Left Of The Quad (Back)

    pSetHSV(left_.getHue(),left_.getSaturation(),left_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f(-x, y, z);          // Top Right Of The Quad (Left)
    glVertex3f(-x, y,-z);          // Top Left Of The Quad (Left)
    glVertex3f(-x,-y,-z);          // Bottom Left Of The Quad (Left)
    glVertex3f(-x,-y, z);          // Bottom Right Of The Quad (Left)

    pSetHSV(right_.getHue(),right_.getSaturation(),right_.getBrightness());
    glColor3f(cols[0],cols[1],cols[2]);
    glVertex3f( x, y,-z);          // Top Right Of The Quad (Right)
    glVertex3f( x, y, z);          // Top Left Of The Quad (Right)
    glVertex3f( x,-y, z);          // Bottom Left Of The Quad (Right)
    glVertex3f( x,-y,-z);          // Bottom Right Of The Quad (Right)

    glEnd();                        // Done Drawing The Quad

}


//--------------------------------------------------------------
void testApp::drawGridPlane(float scale, float ticks, bool labels) {
    
	float minor = scale / ticks;
	float major =  minor * 2.0f;
	
	ofPushStyle();
	for (int iDimension=0; iDimension<2; iDimension++)
	{
		for (float yz=-scale; yz<=scale; yz+= minor)
		{
			//major major
			if (fabs(yz) == scale || yz == 0)
				ofSetLineWidth(4);
			
			//major
			else if (yz / major == floor(yz / major) )
				ofSetLineWidth(2);
			
			//minor
			else
				ofSetLineWidth(1);
			if (iDimension==0)
				ofLine(0, yz, -scale, 0, yz, scale);
			else
				ofLine(0, -scale, yz, 0, scale, yz);
		}
	}
	ofPopStyle();
	
	if (labels) {
		//draw numbers on axes
		ofPushStyle();
		ofSetColor(255, 255, 255);
		
		ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
		for (float yz = -scale; yz<=scale; yz+=minor)
		{
			ofDrawBitmapString(ofToString(yz, 0), 0, yz, 0);
			ofDrawBitmapString(ofToString(yz, 0), 0, 0, yz);
		}
		ofPopStyle();
	}
    
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


void testApp::setHSB(){
    
    top.setHue(240);
    top.setBrightness(100);
    top.setSaturation(0);
    
    bottom.setHue(240);
    bottom.setBrightness(100);
    bottom.setSaturation(0);
    
    front.setHue(360);
    front.setBrightness(100);
    front.setSaturation(100);
    
    back.setHue(60);
    back.setBrightness(100);
    back.setSaturation(100);
    
    left.setHue(60);
    left.setBrightness(100);
    left.setSaturation(100);
    
    right.setHue(60);
    right.setBrightness(100);
    right.setSaturation(100);
        
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if (key=='c')
		camera.toggleCursorDraw();
	
	if (key=='u')
		camera.toggleFixUpwards();
	
	if (key=='s')
		savedPose = camera.getGlobalTransformMatrix();
	
	if (key=='l')
		camera.setTransformMatrix(savedPose);
    
    if (key == 'v')
        useViewPort != useViewPort;
    
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