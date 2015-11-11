//
//  MagicLightCircle.h
//  MagicLightCircle
//
//  Created by Mauro Ferrario on 11/11/15.
//
//

#ifndef __MagicLightCircle__MagicLightCircle__
#define __MagicLightCircle__MagicLightCircle__

#include "ofMain.h"


class MagicPoint
{
public:
        MagicPoint()
  {
    
  }
        ~MagicPoint()
  {
    
  }
  
  void  setup()
  {
    
  }
  
  void  update()
  {
    
  }
  
  void  draw(ofVec2f pos)
  {
    ofPushMatrix();
    ofTranslate(pos);
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofCircle(5,5,10,10);
    ofFill();
    ofSetColor(255,0,0);
    ofCircle(5,5,10,10);
    ofPopStyle();
    ofPopMatrix();
  }
  
private:
  int   id;
  float intensity;
};


class MagicLightCircle
{
public:
                      MagicLightCircle();
                      ~MagicLightCircle();
  
  void                setup(int resolution);
  void                update();
  void                draw();

private:
  void                addNewMagicPoint();
  void                setCircleResolution(int num);
  int                 resolution;
  int                 totMagicPoints;
  vector<MagicPoint*> magicPoints;
};

#endif /* defined(__MagicLightCircle__MagicLightCircle__) */
