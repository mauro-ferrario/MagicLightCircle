//
//  MagicPoint.h
//  MagicLightCircle
//
//  Created by XXX on 20/04/16.
//
//

#ifndef __MagicLightCircle__MagicPoint__
#define __MagicLightCircle__MagicPoint__

#include "ofMain.h"

class MagicPoint
{
public:
              MagicPoint();
              ~MagicPoint();
  void        setup();
  void        update(ofVec2f pos, float lightFadeOutSpeed, float lightFadeInSpeed);
  void        update(float lightFadeOutSpeed, float lightFadeInSpeed);
  void        setPos(ofVec2f pos);
  float       getIntensity();
  void        setIntensity(ofVec2f blobPos);
  void        setIntensity(float _intensity);
  void        setDesiredIntensity(ofVec2f blobPos);
  void        setDesiredIntensity(float _intensity);
  float       getDistance(ofVec2f blobPos);
  float       calculateIntensity(ofVec2f blobPos);
  void        setId(int id);
  void        setOutputPort(int port);
  int         getOutputPort();
  bool        getActive();
  void        setActive(bool _active);
  void        draw();
  float       radius;
  float       intensity;
  float       life;
  bool        reverseLogic;
  bool        fadeInActived; // Da implementare
  float       desiredIntensity;
private:
  int         id;
  int         outputPort;
  ofVec2f     pos;
  bool        active;
};


#endif /* defined(__MagicLightCircle__MagicPoint__) */
