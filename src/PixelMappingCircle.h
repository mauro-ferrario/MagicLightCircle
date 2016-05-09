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

class PixelMappingCircle
{
public:
        PixelMappingCircle();
  void  setup(int totPixel);
  void  update();
  void  draw();
  void  draw(int x, int y);
  vector<int> values;
  
private:
  
  int   totPixel;
  int   idFunction;
  ofFbo fbo;
  void  drawFunction();
  ofVec2f  rectPos;
  
};

#endif /* defined(__MagicLightCircle__PixelMappingCircle__) */
