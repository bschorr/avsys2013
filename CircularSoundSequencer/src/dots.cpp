//
//  dots.cpp
//  OSCtoChuck2
//
//  Created by Bernardo Schorr on 4/16/13.
//
//

#include "dots.h"

void dots::setup (float x, float y) {
    
    pos.set(x, y);
    angle = atan2(pos.x - ofGetScreenWidth()/2, pos.y - ofGetScreenHeight()/2);
    
    if (pos.x > ofGetScreenWidth()/2){
    angle = 360 - (angle * 180 / PI);
    
    } else {
    angle = (angle * 180 / PI) * -1;
    }
    
    float tempNote  = ofDist(pos.x, pos.y, ofGetScreenWidth()/2,ofGetScreenHeight()/2);
    note = int (ofMap (tempNote, 0, 300, 0, 17));
    
}



//------------------------------------------------------------------
void dots::update() {
    
    
}



//------------------------------------------------------------------
void dots::draw() {
    
    ofCircle (pos.x, pos.y, 5);
    
}
