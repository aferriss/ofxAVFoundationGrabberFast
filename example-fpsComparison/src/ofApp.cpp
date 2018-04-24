#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(1280, 720);
    slowGrab.setup(1280, 720);
    
    ofSetWindowShape(1280, 360);
    
    avgFast = 0.0;
    avgSlow = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
    slowGrab.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    grabber.getTexture()->draw(0,0, 640, 360);
    img.setFromPixels(slowGrab.getPixels());
    img.draw(640, 0, 640, 360);
    
    if(ofGetFrameNum() > 60){
        // discard the first second
        // note that getFps was added custom to AVFoundationGrabber and doesn't exist by default
        // it adds an ofFpsCounter object to the grabber and inside the captureOutput function calls counter.newFrame()
        // check the fast grabber src for a similar thing
        avgFast += grabber.getFps();
        avgSlow += slowGrab.getFps();
    }
    
    
    ofDrawBitmapString(ofToString(grabber.getFps()), 320, 180);
    ofDrawBitmapString(ofToString(avgFast / ofGetFrameNum() ), 320, 240);
    
    ofDrawBitmapString(ofToString(slowGrab.getFps()), 960, 180);
    ofDrawBitmapString(ofToString(avgSlow / ofGetFrameNum()), 960, 240);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
