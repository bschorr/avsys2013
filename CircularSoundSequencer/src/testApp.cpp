#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    sender.setup("localhost", 4567);
    
    ofToggleFullscreen();
    ofSetVerticalSync(true);
    circle.set(ofGetScreenWidth()/2, ofGetScreenHeight()/2);

}

//--------------------------------------------------------------
void testApp::update(){

    rotation += 1;
    
    if (rotation > 359) rotation = 0;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //ofSetColor(0, 125, 60);
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
    
    for (int i = 0; i < notes.size(); i++) {
        
        ofSetColor(255);
        
        //cout << rotation << endl;
        // << int(notes[i].angle) << endl;
        
        if (rotation == int(notes[i].angle)) {
         
            ofSetColor(0);
            
            ofxOscMessage message;
            message.setAddress("/playtone");
            //tone = notePlayer[y].frequency;
            message.addIntArg( notes[i].note );
            sender.sendMessage(message);
            
            cout << int(notes[i].angle) << endl;


        }
        
        notes[i].draw();
        
        
        
    }
    
    
    

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
        notes.clear();

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
    
    if (ofDist(circle.x, circle.y, x, y) < radius){
    
    dots myDot;
    myDot.setup(x, y);
    notes.push_back( myDot );
        
    }
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