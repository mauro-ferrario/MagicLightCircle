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
#include "ofxGenericDmx.h"
#include "ofxOsc.h"

#define DMX_DATA_LENGTH 513

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
  
  float getIntensity()
  {
    return intensity;
  }
  
  void  setIntensity(ofVec2f blobPos, float maxRadius)
  {
    intensity = calculateIntensity(blobPos, maxRadius);
  }
  
  float calculateIntensity(ofVec2f blobPos, float maxRadius)
  {
    float distance = pos.distance(blobPos);
    distance = ofClamp(distance, 0, maxRadius * 1.5);
    return (1 - (distance/maxRadius));
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
  
  float   intensity;
private:
  int     id;
  ofVec2f pos;
};


struct Blob
{
  ofVec3f point;
  int     life;
};

class MagicLightCircle
{
public:
                      MagicLightCircle();
                      ~MagicLightCircle();
  
  void                setup(int resolution);
  void                update();
  void                update(vector<Blob> _blobs);
  void                draw();
  float               radius;

private:
  void                setupDMX();
  void                sendDMX();
  void                addNewMagicPoint();
  void                setCircleResolution(int num);
  int                 totMagicPoints;
  vector<MagicPoint*> magicPoints;
  DmxDevice*          dmxInterface_;
  unsigned char       dmxData_[DMX_DATA_LENGTH];
  ofxOscReceiver      receiver;
  void                setupOSC();
  void                updateOSC();
  vector<Blob>        blobs;
};

#endif /* defined(__MagicLightCircle__MagicLightCircle__) */
