#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  magicCircle.setup(24);
  gui.setup("Gui");
  gui.setPosition(ofPoint(400,0));
  gui.add(*magicCircle.getParameterGroup());;
  ofSetWindowPosition(0, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
//  vector<ofVec2f> blobPos;
//  blobPos.push_back(ofVec2f(ofGetMouseX() - magicCircle.radius,ofGetMouseY() - magicCircle.radius));
  magicCircle.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  magicCircle.draw();
  gui.draw();
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
