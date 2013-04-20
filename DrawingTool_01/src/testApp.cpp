#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    img.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    bDoFade = false;
    ofSetFrameRate(30);
    
}

//--------------------------------------------------------------
void testApp::update(){

    
    unsigned char * pixels = img.getPixels();
    
    if (bDoFade == true){
		for (int i = 0; i < 640; i++){
			for (int j = 0; j < 480; j++){
				pixels[j*640 + i] = MAX(0, pixels[j*640 + i] - 1);
			}
		}
	}

    
    
    // (note: the order of these for loops doesn't matter)
    
    for (int i = 0; i < 640; i++){
        for (int j = 0; j < 480; j++){
            
            // the formula for adressing the 1d pixel via 2d is:
            // pos = y * w + x
            // so for us that's
            // pos = j * 640 + i
            
            float dist = ofDist(mouseX, mouseY, i, j);      // calculate the distance between two 2d points (pythogrean)
            
            
            if (dist < 100){
            
                
                
              //  if (fmod (dist,10) < 5){
                
                //pixels[ j * 640 + i ] = fill;
                pixels[ j * 640 + i ] = pixels[ j * 640 + i ] + ofMap(dist, 0, 100, 100, 0);
                //pixels[ j * 640 + i ] = pixels[ j * 640 + i ]+ ofMap(sin(dist/4 ), -1, 1, 10, 0);      // no idea!
// alternatively let's draw a gradient!
            
            //}
            /*    if (fmod (dist,10) >= 5){
                    
                    pixels[ j * 640 + i ] = pixels[ j * 640 + i ] + ofMap(dist, 0, 100, 0, 30);      // alternatively let's draw a gradient!
                    
                }*/
                
                
            }
        }
    }

    
    
    
    
    img.update();
    
}

//--------------------------------------------------------------
void testApp::draw(){

    
    img.draw(0,0);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'f'){
		bDoFade = !bDoFade;
	}
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