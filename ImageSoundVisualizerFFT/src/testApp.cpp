#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	cam.rotate(180, 1.0, 0, 0);
    
	squirrel.loadImage("insight.png");
    graySquirrel.loadImage("insight.png");
	graySquirrel.setImageType(OF_IMAGE_GRAYSCALE);
	
	ofBackground(0,0,0);
    
    

    ofSoundStreamSetup(0,2,this, 44100, BUFFER_SIZE, 4);
	
	//left = new float[BUFFER_SIZE];
	//right = new float[BUFFER_SIZE];
    
	ofSetHexColor(0x666666);
	
	
	FFTanalyzer.setup(44100, BUFFER_SIZE/2, 2);
	
	FFTanalyzer.peakHoldTime = 15; // hold longer
	FFTanalyzer.peakDecayRate = 0.95f; // decay slower
	FFTanalyzer.linearEQIntercept = 0.9f; // reduced gain at lowest frequency
	FFTanalyzer.linearEQSlope = 0.01f; // increasing gain at higher frequencies
	
	//ofSetVerticalSync(true);
    ofSetFrameRate(15);

    
}

//--------------------------------------------------------------
void testApp::update(){

    float avg_power = 0.0f;
    
	/* do the FFT	*/
	myfft.powerSpectrum(0,(int)BUFFER_SIZE/2, left,BUFFER_SIZE,&magnitude[0],&phase[0],&power[0],&avg_power);
    
	for (int i = 0; i < (int)(BUFFER_SIZE/2); i++){
		freq[i] = magnitude[i];
        //if (freq[i] > highFreq) highFreq = freq [i];
	}
	
	FFTanalyzer.calculate(freq);
	
    for (int i= 0; i < 128; i++){
        
        freqs.push_back( freq[i] );
        
    }
    
    
    while (freqs.size() > 16384 ) {
        
        freqs.erase(freqs.begin());
        
    }

    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
	
    ofTranslate(-squirrel.width*1.5,-squirrel.height*1.5);
    
	//squirrel.draw(0,0);
	
	
	unsigned char * grayPixels = graySquirrel.getPixels();
    unsigned char * pixels = squirrel.getPixels();
	
	for (int i = 0; i < squirrel.width; i+=2){
		for (int j = 0; j < squirrel.height; j+=2){
            
			int value = grayPixels[j * squirrel.width + i];
			//ofSetColor(value, value, value);
            
			int pct = int (ofMap(value, 0,255, 0, 127));
            
            
            int red = pixels[ (j * squirrel.width + i) * 3];
			int green = pixels[ (j * squirrel.width + i) * 3 + 1];
			int blue = pixels[ (j * squirrel.width + i) * 3 + 2];
            
            
            ofSetColor(red,green,blue);
			
            ofCircle(i*3, j*3, freq[pct]*5, 2);
		}
	}
    
   cam.end();
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

void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		left[i] = input[i*2];
		right[i] = input[i*2+1];
	}
}

