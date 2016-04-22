//
//  MagicPoint.cpp
//  MagicLightCircle
//
//  Created by XXX on 20/04/16.
//
//

#include "MagicPoint.h"


MagicPoint::MagicPoint()
{
    
}

MagicPoint::~MagicPoint()
{
  
}
  
void MagicPoint::setup()
{
  intensity = 1;
  life = 0;
  active    = false;
  desiredIntensity = 0;
  reverseLogic = false;
}
  
void MagicPoint::update(ofVec2f pos, float lightFadeOutSpeed, float lightFadeInSpeed)
{
  if(getDistance(pos) < radius)
  {
    setActive(true);
  }
  else
  {
    setActive(false);
  }
  update(lightFadeOutSpeed, lightFadeInSpeed);
}

void MagicPoint::update(float lightFadeOutSpeed, float lightFadeInSpeed)
{
  // Prima la luce deve "morire", non avere più vita e poi passa
  // all'else dove piano piano si spegne
  if(life > 0)
  {
    if(intensity < desiredIntensity)
      intensity += lightFadeInSpeed;
    else if(!active)
      life--;
  }
  else
  {
    if(!reverseLogic)
    {
//      if(active)
        intensity -= lightFadeOutSpeed;
      if(intensity < 0)
      {
        reverseLogic = false;
        intensity = 0;
      }
    }
  }
}
  
void MagicPoint::setPos(ofVec2f pos)
{
  this->pos = pos;
}
  
float MagicPoint::getIntensity()
{
  return intensity;
}

void MagicPoint::setDesiredIntensity(ofVec2f blobPos)
{
  desiredIntensity = calculateIntensity(blobPos);
}

void MagicPoint::setDesiredIntensity(float _intensity)
{
  desiredIntensity = _intensity;
}

void MagicPoint::setIntensity(ofVec2f blobPos)
{
  intensity = calculateIntensity(blobPos);
}
  
void MagicPoint::setIntensity(float _intensity)
{
  intensity = _intensity;
}
  
float MagicPoint::getDistance(ofVec2f blobPos)
{
  return pos.distance(blobPos);
}
  
float MagicPoint::calculateIntensity(ofVec2f blobPos)
{
  float distance = getDistance(blobPos);
  if(distance > radius)  // Forse queste 2 righe sono superflue perchè il controllo avviene già fuori. Forse è per questo motivo che la luce si attiva rapidamente
    return 0;
  distance = ofClamp(distance, 0, radius);
  return (1 - (distance/radius));
}
  
void MagicPoint::setId(int id)
{
  this->id = id;
  setOutputPort(id);
}
  
void MagicPoint::setOutputPort(int port)
{
  outputPort = port;
}
  
int MagicPoint::getOutputPort()
{
  return outputPort;
}
  
bool MagicPoint::getActive()
{
  return active;
}
  
void MagicPoint::setActive(bool _active)
{
  active = _active;
  if(active&&reverseLogic)
    life = 0;
}

void MagicPoint::draw()
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