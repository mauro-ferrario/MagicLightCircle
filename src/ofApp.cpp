#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  magicCircle.setup(24);
  gui.setup("Gui");
  gui.setPosition(ofPoint(450,0));
  gui.add(presetId.set("Preset id", 0, 0, 20));
  gui.add(*magicCircle.getParameterGroup());
  gui.loadFromFile("settings.xml");
  ofSetWindowShape(960,630);
  ofSetWindowPosition(960, 0);
  loadGUIPreset(0);
  useMinimalGUI = true;
  font.loadFont("AndaleMono.ttf", 8);
}

//--------------------------------------------------------------
void ofApp::update(){
//  vector<ofVec2f> blobPos;
//  blobPos.push_back(ofVec2f(ofGetMouseX() - magicCircle.radius,ofGetMouseY() - magicCircle.radius));
  magicCircle.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  if(useMinimalGUI)
  {
    newLineString.clear();
    addNewLine("Light Life = " + ofToString(magicCircle.lightLife) + " frame");
    addNewLine("Light Fade Out Speed = " + ofToString(magicCircle.lightFadeOutSpeed));
    addNewLine("Perc Max Distance Circle = " + ofToString(magicCircle.percMaxDistanceCircle));
    ofPushStyle();
    ofSetColor(17,139,145);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofSetColor(120,14,81);
    for(int a = 0; a < newLineString.size(); a++)
    {
      font.drawString(newLineString[a], 20, 20*(a+1));
    }
    ofPopStyle();
  }
  else
  {
    magicCircle.draw();
    gui.draw();
  }
}


void ofApp::addNewLine(string newLine)
{
  newLineString.push_back(newLine);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

void ofApp::saveGUIPreset()
{
  gui.saveToFile("preset/preset_"+ofToString(presetId)+".xml");
}

void ofApp::loadGUIPreset(int id)
{
  // Doppio load perch ogni tanto non setta giusto subito i bottoni
  gui.loadFromFile("preset/preset_"+ofToString(id)+".xml");
  gui.loadFromFile("preset/preset_"+ofToString(id)+".xml");
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if(key == 's')
    saveGUIPreset();
  if(key == 'l')
    loadGUIPreset(presetId);
  if(key == 'm')
    useMinimalGUI = !useMinimalGUI;
  if(key == 'r')
    magicCircle.turnOnRandomLight();
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
