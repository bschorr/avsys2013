//
//  petal.h
//  finalProjectv1OF
//
//  Created by Bernardo Schorr on 4/22/13.
//
//

#ifndef __finalProjectv1OF__petal__
#define __finalProjectv1OF__petal__

#include "ofMain.h"

class Petal {
public:
    
    void setup(float x, float y);
	void draw();
    
    float cx;
    float cy;
    float diam;
    float counterCurve, counterDiam;
    float vel;
    float accel;
    bool petal;
    float initDiam, diamMult;
    float curveMult;
    float counterCurveInc, counterDiamInc;
    
    
};



#endif /* defined(__finalProjectv1OF__petal__) */
