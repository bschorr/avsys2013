//
//  dots.h
//  OSCtoChuck2
//
//  Created by Bernardo Schorr on 4/16/13.
//
//

#ifndef __OSCtoChuck2__dots__
#define __OSCtoChuck2__dots__

#include "ofMain.h"

class dots {
	
public:
    void setup(float x, float y);
    void update();
    void draw();
    
    //float dist;
    
    ofColor color;
    float rotation;
    float speed;
    float size;
    float alpha;
    ofPoint pos;
    float angle;
    float note;
    
};

#endif /* defined(__OSCtoChuck2__dots__) */
