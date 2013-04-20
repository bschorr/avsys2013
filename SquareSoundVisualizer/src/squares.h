//
//  squares.h
//  sound_visualizer
//
//  Created by Bernardo Schorr on 3/19/13.
//
//

#ifndef __sound_visualizer__squares__
#define __sound_visualizer__squares__

#include "ofMain.h"


class square {
	
public:
    void setup(float initSize, ofColor initColor, float initRotation, float initSpeed);
    void update();
    void draw();
        
    //float dist;
    
    ofColor color;
    float rotation;
    float speed;
    float size;
    float alpha;
    ofPoint pos;
        
};


#endif /* defined(__sound_visualizer__squares__) */
