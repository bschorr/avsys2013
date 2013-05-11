//
//  petal.cpp
//  finalProjectv1OF
//
//  Created by Bernardo Schorr on 4/22/13.
//
//

#include "petal.h"

void Petal::setup(float x, float y) {
    cx = x;
    cy = y;
    
   // cx = ofGetWidth()/2;
   // cy = ofGetHeight()/2;
    
    counterCurve = ofRandom(2*PI);
    counterDiam = ofRandom(0.2);
    
    while (counterCurveInc < 0.05 && counterCurveInc > -0.05) {
     
        counterCurveInc = ofRandom(-0.2, 0.2);
    }
    
    
    
    counterDiamInc = ofRandom(0.035, 0.04);
    
    vel = 1;
    accel = 0.08;
    petal = true;
    
    initDiam = ofRandom(10, 30);
    curveMult = ofRandom(2, 3);
    diamMult = ofRandom(10, 30);
    
    ofRotate(30);
    
    
};

void Petal::draw () {
 
    
    diam = ((sin (counterDiam)) * diamMult);
    
    cx += sin(counterCurve)*curveMult;
    ofCircle (cx, cy, diam);
    
    counterCurve += counterCurveInc;
    counterDiam += counterDiamInc;
    
    vel += accel;
    cy -= vel;
    
    if (diam < 0) petal = false;
    
    
    
    
};