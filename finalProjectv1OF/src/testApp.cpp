#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofEnableSmoothing();
    ofSetCircleResolution(100);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 255, 255, 10);
    ofFill();
    ofRect(0, 0, ofGetWidth(), ofGetHeight());
    ofNoFill();
    ofSetColor(alpha, 255, 0);
    ofSetLineWidth(0.25);
    
    
    for (int i = 0; i< petals.size(); i++) {
        
        petals[i].draw();
        
        if (!petals[i].petal){
            petals.erase(petals.begin() + i);
        }
        
    }
    
    alpha += 1.5;
    
    if (alpha > 255) alpha = 255;
    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//-------------------------------------------------------------
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

    for (int i =0; i < 10; i++) {
        
    Petal myPetal;
    myPetal.setup(mouseX, mouseY);
    petals.push_back( myPetal );
    }
    
    alpha = 0;
     
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