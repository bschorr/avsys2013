#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofNoFill();
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(false);
    ofBackground(0, 0, 0);
    
    for (int i = 0; i < NUM; i++) {
        
        vert[i].x = ofRandom(640);
        vert[i].y = ofRandom(480);
        vel[i].x = ofRandom(-2, 2);
        vel[i].y = ofRandom(-2, 2);
        
    }
    
    ofSetVerticalSync (true);
    img.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    
}

//--------------------------------------------------------------
void testApp::update(){

    for (int i = 0; i < NUM; i++) {
        
        vert[i] += vel[i];
        
        if (vert[i].x < 0 || vert[i].x > 640) {
            
            vel[i].x *= -1;
        }
        
        if (vert[i].y < 0 || vert[i].y > 480) {
            
            vel[i].y *= -1;
        }
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(0, 0, 0, 10);
    ofFill();
    ofRect(0, 0, 640, 480);
    ofSetColor(255, 255, 255);
    
    ofNoFill();
    
    ofBeginShape();
    
    for (int i = 0; i < NUM; i++) {
        ofVertex(vert[i].x, vert[i].y);
    }
    
    ofVertex(vert[0].x, vert[0].y);
    
    ofEndShape();

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