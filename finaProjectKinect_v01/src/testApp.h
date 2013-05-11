#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "dots.h"
#include "ofxOsc.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void updateSequencer();
        void detectMotion();
    
        ofxKinect kinect;
    
        ofxCvColorImage colorImg;
	
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage prevGrayImage;
        ofxCvGrayscaleImage diffImage;

    
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	
        ofxCvContourFinder contourFinder;
    
        bool bThreshWithOpenCV;
    
        int nearThreshold;
        int farThreshold;
	
        int angle;
    
        float rotation;
        float prevRotation;
    
        vector <dots> notes;
        ofPoint circle;
        float radius;
    
        ofxOscSender sender;

        int maxBrightness;
        int totalMov;
        float prevSpeed;
    
        //vector <ofPoint> notes;

	



		
};
