#pragma once

#include "ofMain.h"
#include "MagicLightCircle.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    void  saveGUIPreset();
    void loadGUIPreset(int id);
		MagicLightCircle magicCircle;
    ofxPanel  gui;
  ofParameter<int> presetId;
  void handlerOSCMessage(ofxOscMessage &m);
		ofTrueTypeFont	font;
  bool useMinimalGUI;
  
  
  vector<string> newLineString;
  void addNewLine(string newLine);
};
