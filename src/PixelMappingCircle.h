//
//  PixelMappingCircle.h
//  MagicLightCircle
//
//  Created by XXX on 09/05/16.
//
//

#ifndef __MagicLightCircle__PixelMappingCircle__
#define __MagicLightCircle__PixelMappingCircle__

#include "ofMain.h"
#include "ofxGui.h"

class PixelMappingCircle
{
public:
        PixelMappingCircle();
  void  setup(int totPixel);
  void  setupGUI();
  void  update();
  void  draw();
  void  draw(int x, int y);
  void  drawGUI();
  vector<int> values;
  
private:
  
  int   totPixel;
  int   idFunction;
  ofFbo fbo;
  void  drawFunction();
  ofVec2f  rectPos;
  
  ofParameterGroup*   pixelMappingParams;
  ofParameterGroup*   getParameterGroup();
  ofParameter<float>  fadeOutSpeed;
  ofParameter<float>  colorSpeed;
  ofParameter<int>    idFunction;
  ofParameter<bool>   loadFunction;
  ofParameter<bool>   loop;
  ofParameter<bool>   active;
  ofxPanel  gui;
};

#endif /* defined(__MagicLightCircle__PixelMappingCircle__) */
