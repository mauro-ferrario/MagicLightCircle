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
    intensity = 1;
  }
  
  void  update()
  {
    
  }
  
  void  setPos(ofVec2f pos)
  {
    this->pos = pos;
  }
  
  void  setIntensity(ofVec2f blobPos, float maxRadius)
  {
    float distance = pos.distance(blobPos);
    intensity = 1 - (distance/maxRadius);
  }
  
  void  setId(int id)
  {
    this->id = id;
  }
  
  void  draw()
  {
    ofPushMatrix();
    ofTranslate(pos);
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofCircle(5,5,10,10);
    ofFill();
    ofSetColor(255,0,0, intensity * 255);
    ofCircle(5,5,10,10);
    ofPopStyle();
    ofPopMatrix();
  }
  
private:
  int     id;
  float   intensity;
  ofVec2f pos;
};


class MagicLightCircle
{
public:
                      MagicLightCircle();
                      ~MagicLightCircle();
  
  void                setup(int resolution);
  void                update(vector<ofVec2f> posBlobs);
  void                draw();

private:
  void                addNewMagicPoint();
  void                setCircleResolution(int num);
  int                 totMagicPoints;
  vector<MagicPoint*> magicPoints;
  float               radius;
};

#endif /* defined(__MagicLightCircle__MagicLightCircle__) */
