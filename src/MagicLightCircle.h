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
#include "MagicPoint.h"
#include<tr1/unordered_map>
#include "PixelMappingCircle.h"

#define DMX_DATA_LENGTH 513
#define MAX_DURATION_FRAMES_BLOB_WITH_NO_INTERACTION 5


struct Blob
{
  ofVec3f point;
  int     life;
};

class MagicLightCircle: public ofBaseApp
{
public:
                      MagicLightCircle();
                      ~MagicLightCircle();
  
  void                setup(int resolution);
  void                update();
  void                update(vector<Blob> _blobs);
  void                updateMagicPoints(ofVec3f point);
  void                draw();
  float               radius;
  ofParameterGroup*   getParameterGroup();
  
  
  ofParameter<float>  lightLife;
  ofParameter<float>  lightFadeOutSpeed;
  ofParameter<float>  lightFadeInSpeed;
  ofParameter<float>  percMaxDistanceCircle;
  ofParameter<bool>   reverseLogic;
  
  void                turnOnRandomLight();

private:
  void                setupAudio();
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
  ofParameter<bool>   useDepthForIntensity;
  ofParameter<bool>   useOSC;
  ofParameter<bool>   usePixelMapping;
  ofParameter<bool>   useSound;
  ofParameter<float>  audioMultiplier;
  ofParameter<int>    pixelMappingPerno;
  ofParameter<bool>   activePixelMappingFunction;
  ofParameterGroup*   magicLightParams;
  bool                prevUseDepthForIntensity;
  bool                prevUseOSC;
  bool                prevUseSound;
  bool                prevUsePixelMapping;
  void                audioIn(float * input, int bufferSize, int nChannels);
  void                checkLightInputControllerChanged();
  void                updateSound();
  vector<float>       left;
	vector<float>       right;
  vector<float>       volHistory;
  int                 bufferCounter;
  int                 drawCounter;
	float               smoothedVol;
  float               scaledVol;
  ofSoundStream       soundStream;
  void                turnOnLight(int lightId, float newIntensityValue = 1);
  std::tr1::unordered_map<string, ofParameter<float>* > mapToOfParameterFloatValue;
  std::tr1::unordered_map<string, float >  multipliers;
  int timerNoPoints;
  PixelMappingCircle  pixelMapping;
  void                setupPixelMapping();
};

#endif /* defined(__MagicLightCircle__MagicLightCircle__) */
