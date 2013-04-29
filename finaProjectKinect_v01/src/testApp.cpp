#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sender.setup("localhost", 6534);
    
    ofToggleFullscreen();
    ofSetVerticalSync(true);
    
    ofSetLogLevel(OF_LOG_VERBOSE);
	
	// enable depth->video image calibration
	kinect.setRegistration(true);
	kinect.init();	
	kinect.open();
    
    colorImg.allocate(kinect.width, kinect.height);
	grayImage.allocate(kinect.width, kinect.height);
    prevGrayImage.allocate(kinect.width, kinect.height);
    diffImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 220;
	farThreshold = 100;
	bThreshWithOpenCV = true;
		
	// zero the tilt on startup
	angle = 0;
	kinect.setCameraTiltAngle(angle);
    
    //set position of the circle
    circle.set(ofGetScreenWidth()/2, ofGetScreenHeight()/2);
    
    prevSpeed = 0;

	
}

//--------------------------------------------------------------
void testApp::update(){
    
    kinect.update();
	
	// there is a new frame and we are connected
	if(kinect.isFrameNew()) {
		
		// load grayscale depth image from the kinect source
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
        
        // detect motion before thresholding CV image
        detectMotion();
        
        // update sequencer before thresholding CV image
        updateSequencer();
        
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
    contourFinder.findContours(grayImage, 900, (kinect.width*kinect.height)/2, 6, false);


    //sequencer update
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //draw background, circle, reader etc
    ofBackground (0, 230, 230);
    ofSetColor(0, 200, 200);
    ofFill();
    ofSetCircleResolution(100);
    
    radius = 300;
    
    ofPushMatrix();
    
    ofTranslate(circle.x, circle.y);
    ofCircle(0, 0, radius);
    
    ofSetColor(255);
    ofSetLineWidth(5);
    ofRotate(rotation);
    ofLine(0, 0, 0, radius);
    
    ofPopMatrix();
    
    
    // do the kinect thing
    ofSetColor(255, 255, 255);
    
    // draw from the live kinect
    //kinect.drawDepth(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    //kinect.draw(420, 10, 400, 300);
    
    grayImage.draw(10, ofGetScreenHeight()-160, 200, 150);
    contourFinder.draw(10, ofGetScreenHeight()-160, 200, 150);
    
    //notes.clear();
    ofSetColor(255, 0, 0);
    
    for( int i=0; i<(int)contourFinder.blobs.size(); i++ ) {
        
        float x = contourFinder.blobs[i].boundingRect.x;
        float y = contourFinder.blobs[i].boundingRect.y;
        x = (x + x + contourFinder.blobs[i].boundingRect.width) /2;
        y = (y + y + contourFinder.blobs[i].boundingRect.height) /2;
        x = ofMap(x, 0, kinect.width, 0, ofGetScreenWidth());
        y = ofMap(y, 0, kinect.height, 0, ofGetScreenHeight());
        dots myDot;
        myDot.setup(x, y);
        blobAngle = myDot.angle;
        
        //if (rotation - myDot.angle < 1 && rotation - myDot.angle > - 1 ) {
        
        if ((int)abs(rotation) == (int)myDot.angle ) {
            
            ofSetColor(0);
            
            ofxOscMessage message;
            message.setAddress("/playtone");
            message.addIntArg( myDot.note );
            sender.sendMessage(message);
            
            
            
        }
        
        prevRotation = rotation;
        //cout << prevRotation << endl;
        cout << (int)abs (rotation) << endl;
        cout << int(myDot.angle) << endl;

        myDot.draw();

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

void testApp::updateSequencer(){
    
    speed = totalMov/1000;
    speed = 0.99 * prevSpeed + 0.01 * speed;
    speed = MIN (speed, 1);
    
    unsigned char * pix = grayImage.getPixels();
    
    maxBrightness = 0;
    
    int numPixels = grayImage.getWidth() * grayImage.getHeight();
    for(int i = 0; i < numPixels; i++) {
        if(pix[i] > maxBrightness) maxBrightness = pix[i];
    }
    
    if (maxBrightness > 200) {
        rotation += 1;
        
    } else {
        
        rotation -= 1;
    }
    
    if (rotation > 360) rotation = 0;
    if (rotation < 0) rotation = 360 - rotation;
    
    prevSpeed = speed;
    //rotation = abs(rotation);

    
}

void testApp::detectMotion(){
    
    int threshold = 50;
		
		diffImage.absDiff(grayImage,prevGrayImage);
		diffImage.threshold(threshold);
		
		prevGrayImage = grayImage;
    
        totalMov = diffImage.countNonZeroInRegion(0, 0, kinect.width, kinect.height);
    
        //cout << totalMov << endl;

    
}

