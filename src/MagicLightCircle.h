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
  
  void  setIntensity(ofVec2f blobPos, float maxRadius, float percMaxDistanceCircle)
  {
    intensity = calculateIntensity(blobPos, maxRadius, percMaxDistanceCircle);
  }
  
  float getDistance(ofVec2f blobPos)
  {
    return pos.distance(blobPos);
  }
  
  float calculateIntensity(ofVec2f blobPos, float maxRadius, float percMaxDistanceCircle)
  {
    float distance = getDistance(blobPos);
    if(distance > maxRadius*percMaxDistanceCircle)
      return 0;
    distance = ofClamp(distance, 0, maxRadius);
    return (1 - (distance/maxRadius));
  }
  
  void  setId(int id)
  {
    this->id = id;
    setOutputPort(id);
  }
  
  void setOutputPort(int port)
  {
    outputPort = port;
  }
  
  int getOutputPort()
  {
    return outputPort;
  }
  
  void  draw(float radius)
  {
    ofPushMatrix();
    ofTranslate(pos);
    ofPushStyle();
    ofNoFill();
    ofSetColor(255);
    ofCircle(5,5,10,radius);
    ofFill();
    ofDrawBitmapString(ofToString(id), 14, 14);
    ofFill();
    ofSetColor(255,0,0, intensity * 255);
    ofCircle(5,5,10,radius);
    ofPopStyle();
    ofPopMatrix();
  }
  
  float   intensity;
private:
  int     id;
  int     outputPort;
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
  ofParameterGroup*   getParameterGroup();

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
  ofParameter<int>    lightLife;
  ofParameter<float>  lightFadeOutSpeed;
  ofParameter<float>  percInnerRadius;
  ofParameter<float>  percMaxDistanceCircle;
  ofParameterGroup*   magicLightParams;
};

#endif /* defined(__MagicLightCircle__MagicLightCircle__) */
