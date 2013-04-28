#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofToggleFullscreen();
    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
	
	// enable depth->video image calibration
	kinect.setRegistration(true);
	kinect.init();	
	kinect.open();
    
    colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 230;
	farThreshold = 70;
	bThreshWithOpenCV = true;
		
	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
	
}

//--------------------------------------------------------------
void testApp::update(){
    
    kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		
		// we do two thresholds - one for the far plane and one for the near plane
		// we then do a cvAnd to get the pixels which are a union of the two thresholds
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		}
    
    // update the cv images
    grayImage.flagImageChanged();
    
    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
    contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 100, false);

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 255, 255);
    
    // draw from the live kinect
    kinect.drawDepth(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    kinect.draw(420, 10, 400, 300);
    
    grayImage.draw(10, 320, 400, 300);
    contourFinder.draw(10, 320, 400, 300);
    
    notes.clear();
    ofSetColor(255, 0, 0);
    
    for( int i=0; i<(int)contourFinder.blobs.size(); i++ ) {
        
        float x = contourFinder.blobs[i].boundingRect.x;
        float y = contourFinder.blobs[i].boundingRect.y;
        x = (x + x + contourFinder.blobs[i].boundingRect.width) /2;
        y = (y + y + contourFinder.blobs[i].boundingRect.height) /2;
        x = ofMap(x, 0, kinect.width, 0, ofGetScreenWidth());
        y = ofMap(y, 0, kinect.height, 0, ofGetScreenHeight());
        ofPoint myNote;
        myNote.set(x, y);
        notes.push_back( myNote );
        
        ofCircle(myNote, 20);
        
		/*ofRect( contourFinder.blobs[i].boundingRect.x, contourFinder.blobs[i].boundingRect.y,
               contourFinder.blobs[i].boundingRect.width, contourFinder.blobs[i].boundingRect.height );
         */
	}
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

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

void testApp::exit() {
	kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}
