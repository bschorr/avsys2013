#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
    
    ofEnableAlphaBlending();
    soundStream.setup(this, 0, 1, 44100, 256, 4);
    
    //ofSetBackgroundAuto(false);
    ofBackground(0);
    ofSetFullscreen(true);
    
    sampleSmooth = 0;
    bSignOflastValue = false;
    
    volume = 0;
    pitch = 0;
    
    volumeSmoothSlow = 0;
    pitchSmoothSlow = 0;
    
    ofSetVerticalSync(true);
    
    rotation = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    
    rotation += 0.5;
    
    sat = 180;
    bri = ofMap(volume, 0, 0.2, 0, 500, true);
    hue = ofMap(pitch, 0, 3000, 0, 360, true);
    
    color.setHsb(hue, sat, 255);
    
    float speed = volume * 100;
    float size = ofMap(volume, 0, 0.2, 0, 500, true);
    
    
    if (ofGetFrameNum()% 15 == 0) {
    
    square mySquare;
    mySquare.setup(size, color, rotation, speed);
    squares.push_back( mySquare );
        
    }
    
    for (int i = 0; i < squares.size(); i++){
		squares[i].update();
        if (squares[i].alpha <= 0) squares.erase(squares.begin() + i);

	}
    
    
    

    
    
}

//--------------------------------------------------------------
void testApp::draw(){

    //ofDrawBitmapStringHighlight(ofToString(volume), ofPoint(50,50));
    //ofDrawBitmapStringHighlight(ofToString(pitch), ofPoint(50,100));
    
    for (int i = 0; i < squares.size(); i++){
		squares[i].draw();
	}
    
    ofTranslate(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
    ofRotate(rotation, 0, 0, 1);
    
    ofSetColor(color);
    ofFill();
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(0, 0,bri,bri);
    
    
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

void testApp::audioIn(float * input, int bufferSize, int nChannels){
    
    // compute RMS
    // see: http://en.wikipedia.org/wiki/Root_mean_square
    
    float rms = 0;
    for (int i = 0; i < bufferSize; i++){
        rms += input[i] * input[i];
    }
    rms /= (float)bufferSize;
    rms = sqrt(rms);
    
    volume = 0.9f * volume + 0.1 * rms;
    volumeSmoothSlow = 0.99f * volumeSmoothSlow + 0.01 * rms;
    
    
    
    // compute pitch
    
    
    
    int zeroCrossingCount = 0;
    
    for (int i = 0; i < bufferSize; i++){
        
        // this is how to do "low pass filtering"
        
        //sampleSmooth = 0.9f * sampleSmooth + 0.1 * input[i];
        //bool curSign = sampleSmooth > 0 ? true : false;   // if this line looks confusing, see "ternary operator"
                                                      // http://www.cplusplus.com/forum/articles/14631/
        
        // w/ out low pass filtering
        
        bool curSign = input[i] > 0 ? true : false;
        
        if (curSign != bSignOflastValue){
            zeroCrossingCount++;
        }
        bSignOflastValue = curSign;
    }
    
    float pitchVal = zeroCrossingCount * (44100.0 / (float)bufferSize) * (0.5);
    pitch = 0.9f * pitch + 0.1 * pitchVal;
    pitchSmoothSlow = 0.99f * pitchSmoothSlow + 0.01f * pitchVal;
    
    
}

