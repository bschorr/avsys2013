//
//  squares.cpp
//  sound_visualizer
//
//  Created by Bernardo Schorr on 3/19/13.
//
//

#include "squares.h"

void square::setup (float initSize, ofColor initColor, float initRotation, float initSpeed) {
    
    //this->myPoints = myPoints;
    size =  initSize;
    color = initColor;
    rotation = initRotation;
    speed = initSpeed;
    
    pos.x = 0;
    pos.y = 0;
    
    alpha = 255;
    
}



//------------------------------------------------------------------
void square::update() {
    
    //dist = ofDist(x, y, myPoints.x, myPoints.y);
    size += speed;
    alpha -= speed/2;
    
    if (alpha < 0){
        alpha = 0;
    }
    
    //or we could have each color pick it's own color
    //myRed = ofMap(dist, 0, 100, 255, 0, true);
    
}



//------------------------------------------------------------------
void square::draw() {
    
    ofPushMatrix();
    //    for example of when you keep track of each position and change color based on that
    //    ofSetColor(myRed, 0, 0, 30);
    
    ofTranslate(ofGetWindowWidth()/2,ofGetWindowHeight()/2);
    ofRotate(rotation, 0, 0, 1);
    
    ofSetColor(color, alpha);
    ofFill();
    ofRect(0, 0, size, size);
    
    ofPopMatrix();
    
}
