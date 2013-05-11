#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
    
    kick.loadSound("kick4.wav");
    kick.setVolume(0.5);
    hat.loadSound("hat4.wav");
    hat.setVolume(0.5);

    
    ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
    ofToggleFullscreen();
    
    //sequencer setup
    sender.setup("localhost", 6534);
    circle.set(ofGetWidth()/2, ofGetHeight()/2);
    rotation = 180;

    
    //Set the background to black
    ofBackground( 0 , 0 , 0 ) ; 
    //if the app performs slowly raise this number
  
    //Loop through all the rows
    for ( float i = 0 ; i < 360 ; i += 0.1 )
    {
            ofColor color;
            color = ofColor (255);       //red pixel
            //color.g = pixels[index+1] ;     //blue pixel
            //color.b = pixels[index+2] ;     //green pixel
            int x = ofGetWidth()/2 + cos(i)*150;
            int y = ofGetHeight()/2 + sin(i)*150;
        
            particles.push_back( Particle ( ofPoint ( x, y ) , color ) ) ;
    }
    
    ofSetFrameRate( 30 ) ; 
    //numParticles = ( image.width * image.height ) / sampling ;
    numParticles = particles.size() ;

    
    //Set spring and sink values
    cursorMode = 0 ; 
    forceRadius = 45 ; 
    friction = 0.85 ; 
    springFactor = 0.12 ; 
    springEnabled = true ; 
}

//--------------------------------------------------------------
void testApp::update(){
    
    if (kickPlay == true && ofGetFrameNum()%15 == 0) kick.play();
    if (hatPlay == true && ofGetFrameNum()%15 == 7) hat.play();

    
    //sequencer update
    prevRotation = rotation;
    rotation += 1;
    
    if (rotation > 360) rotation = 0;
    if (rotation < 0) rotation = 360-rotation;
    
    
    ofPoint diff ;          //Difference between particle and mouse
    float dist ;            //distance from particle to mouse ( as the crow flies ) 
    float ratio ;           //Ratio of how strong the effect is = 1 + (-dist/maxDistance) ;
    const ofPoint mousePosition = ofPoint( mouseX , mouseY ) ; //Allocate and retrieve mouse values once.

    
    //Create an iterator to cycle through the vector
    std::vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ ) 
    {
        ratio = 1.0f ; 
        p->velocity *= friction ; 
        //reset acceleration every frame
        p->acceleration = ofPoint() ; 
        diff = mousePosition - p->position ;  
        dist = ofDist( 0 , 0 , diff.x , diff.y ) ;
        //If within the zone of interaction
        if ( dist < forceRadius )  
        {
            ratio = -1 + dist / forceRadius ; 
            //Repulsion
            if ( cursorMode == 0 ) 
                p->acceleration -= ( diff * ratio) ;
            //Attraction
            else
                p->acceleration += ( diff * ratio ) ; 
        }
        if ( springEnabled ) 
        {
            //Move back to the original position
            p->acceleration.x += springFactor * (p->spawnPoint.x - p->position.x);
            p->acceleration.y += springFactor * (p->spawnPoint.y - p->position.y) ;
        }
        
        p->velocity += p->acceleration * ratio ; 
        p->position += p->velocity ;
    
        p->defineAngleNote();
        
        //float tempNote  = ofDist(mouseX, mouseY, ofGetWidth()/2, ofGetHeight()/2);
        
        //cout << tempNote << endl;

    }
}

//--------------------------------------------------------------
void testApp::draw() {
    
    //draw sequencer
    radius = 300;
    
    ofPushMatrix();
    
    ofTranslate(circle.x, circle.y);
    //ofCircle(0, 0, radius);
    
    ofSetColor(255);
    //ofSetLineWidth(5);
    ofRotate(rotation);
    ofLine(0, 0, 0, radius);
    
    ofPopMatrix();
    
   
    //Begin the openGL Drawing Mode
    glBegin(GL_POINTS);
    
    //Triangles look Cool too 
    //glBegin(GL_TRIANGLES);

    //Create an iterator to cycle through the vector
    vector<Particle>::iterator p ; 
    for ( p = particles.begin() ; p != particles.end() ; p++ )
    //for ( int i = 0 ; i < particles.size() ; i++ )
    {
        glColor3ub((unsigned char)p->color.r,(unsigned char)p->color.g,(unsigned char)p->color.b);
        glVertex3f(p->position.x, p->position.y , 0 );
        //ofSetColor(255);
        //ofFill();
        //ofCircle(p->position.x, p->position.y, 3);
        
        //playing the notes
        
        Boolean play = false;
        
        if (prevRotation <= int(p->angle) && rotation >= int(p->angle)) play = true;
        
        if (prevRotation >= int(p->angle) && rotation <= int(p->angle)) play =true;
        
        if (play == true) {
            
            ofSetColor(0);
            
            ofxOscMessage message;
            message.setAddress("/playtone");
            //tone = notePlayer[y].frequency;
            message.addIntArg( p->note );
            sender.sendMessage(message);
            averageNote += p->note;
            particleCounter++;
            play = false;
            
            //cout << p->note << endl;
            
            
        }
        
        
        
    }
    if (particleCounter == 0) particleCounter = 1;
    averageNote /= particleCounter;
    //cout << averageNote << endl;
    
    averageNote = 0;
    particleCounter=0;
    
    
    glEnd();
    
    ofSetColor ( 255 , 255 , 255 ) ;
    
    string output = "S :: Springs on/off : " + ofToString(springEnabled) +
    
    "\n C :: CursorMode repel/attract " + ofToString( cursorMode ) +
    
    "\n # of particles : " + ofToString( numParticles ) +
    
    " \n fps:" +ofToString( ofGetFrameRate() ) ;
    
    ofDrawBitmapString(output ,20,666);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    switch ( key ) 
    {
        case 'c':
        case 'C':
            cursorMode = ( cursorMode + 1 > 1 ) ? 0 : 1 ; 
            break ; 
            
        case 's':
        case 'S':
            springEnabled = !springEnabled ; 
            break ;
            
        case 'k':
        case 'K':
            kickPlay = !kickPlay ;
            break ;
            
        case 'h':
        case 'H':
            hatPlay = !hatPlay ;
            break ;
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

