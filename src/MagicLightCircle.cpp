//
//  MagicLightCircle.cpp
//  MagicLightCircle
//
//  Created by Mauro Ferrario on 11/11/15.
//
//

#include "MagicLightCircle.h"
#include "ofApp.h"

MagicLightCircle::MagicLightCircle()
{
}

MagicLightCircle::~MagicLightCircle()
{
  
}

void MagicLightCircle::setupOSC()
{
  receiver.setup(12345);
  mapToOfParameterFloatValue["lightLife"] = &lightLife;
  mapToOfParameterFloatValue["lightFadeInSpeed"] = &lightFadeInSpeed;
  mapToOfParameterFloatValue["lightFadeOutSpeed"] = &lightFadeOutSpeed;
  mapToOfParameterFloatValue["percMaxDistanceCircle"] = &percMaxDistanceCircle;
  

  multipliers["lightLife"] = 500;
  multipliers["lightFadeOutSpeed"] = 0.100;
  multipliers["lightFadeInSpeed"] = 0.100;
  multipliers["percMaxDistanceCircle"] = 1;
}


void MagicLightCircle::setupAudio()
{
  int bufferSize = 256;
  left.assign(bufferSize, 0.0);
  right.assign(bufferSize, 0.0);
  volHistory.assign(400, 0.0);
  bufferCounter	= 0;
  drawCounter		= 0;
  smoothedVol     = 0.0;
  scaledVol		= 0.0;
  soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
}

void MagicLightCircle::audioIn(float * input, int bufferSize, int nChannels)
{
  float curVol = 0.0;
  // samples are "interleaved"
  int numCounted = 0;
  //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
  for (int i = 0; i < bufferSize; i++){
    left[i]		= input[i*2]*0.5;
    right[i]	= input[i*2+1]*0.5;
    curVol += left[i] * left[i];
    curVol += right[i] * right[i];
    numCounted+=2;
  }
  //this is how we get the mean of rms :)
  curVol /= (float)numCounted;
  // this is how we get the root of rms :)
  curVol = sqrt( curVol );
  smoothedVol *= 0.93;
  smoothedVol += 0.07 * curVol;
  bufferCounter++;
}

void MagicLightCircle::updateOSC()
{
  while(receiver.hasWaitingMessages())
  {
    ofxOscMessage m;
    receiver.getNextMessage(&m);
    string address = m.getAddress();
    if(mapToOfParameterFloatValue[address] != NULL)
    {
      mapToOfParameterFloatValue[address]->set(m.getArgAsFloat(0) * multipliers[address]);
    }
    if(address == "/savePreset")
    {
      ((ofApp*)ofGetAppPtr())->saveGUIPreset();
    }
    if(address == "/changePreset")
    {
      ((ofApp*)ofGetAppPtr())->presetId = m.getArgAsInt32(0);
    }
    if(address == "/loadPreset")
    {
      ((ofApp*)ofGetAppPtr())->presetId = m.getArgAsInt32(0);
      ((ofApp*)ofGetAppPtr())->loadGUIPreset(m.getArgAsInt32(0));
    }
    if(address == "/turnOnRandomLight")
    {
      turnOnRandomLight();
    }
    if(address == "/turnOnLight")
    {
      turnOnLight(m.getArgAsInt32(0));
    }
    if(address.find("newPoint") <= 10)
    {
      int pointPos = ofToInt(address.substr(10,1));
      ofVec3f point;
      point.x = (m.getArgAsFloat(0) * radius * 2);
      point.y = (m.getArgAsFloat(1) * radius * 2);
      point.z = m.getArgAsFloat(2);
//      cout << point.z << endl;
      Blob tempBlob;
      tempBlob.point = point;
      tempBlob.life = MAX_DURATION_FRAMES_BLOB_WITH_NO_INTERACTION;
      if(pointPos+1>blobs.size())
        blobs.push_back(tempBlob);
      else
        blobs[pointPos] = tempBlob;
      timerNoPoints = 0;
    }
    if(address == "ControlLight" && useOSC)
    {
      for(int a = 0; a < totMagicPoints; a++)
      {
        magicPoints[a]->intensity = float(m.getArgAsInt32(a))/255.0;
      }
    }
  }
}


void MagicLightCircle::turnOnRandomLight()
{
  int count = 0;
  int selectedMagicPoint = -666;;
  do
  {
    selectedMagicPoint = ofRandom(0, totMagicPoints);
    count++;
  }while(magicPoints[selectedMagicPoint]->getIntensity() > .1&&count < 100);
  if(selectedMagicPoint != -666)
    turnOnLight(selectedMagicPoint);
}

void MagicLightCircle::turnOnLight(int lightId, float newIntensityValue)
{
  if(lightId >= 0)
  {
    if(!reverseLogic)
      magicPoints[lightId]->life = lightLife;
    else
      magicPoints[lightId]->life = 0;
    if(!reverseLogic)
      magicPoints[lightId]->setActive(true);
    else
      magicPoints[lightId]->setActive(false);
    magicPoints[lightId]->setIntensity(0);
    magicPoints[lightId]->setDesiredIntensity(1);
    magicPoints[lightId]->reverseLogic = reverseLogic;
  }
  else
    ofLog(OF_LOG_WARNING, "lightId must not negative value!");
}

void MagicLightCircle::setCircleResolution(int num)
{
  
}

void MagicLightCircle::setup(int resolution)
{
  radius = 200;
  totMagicPoints = resolution;
  reverseLogic = true;
  for(int a = 0; a < resolution; a++)
  {
    addNewMagicPoint();
  }

  int cont = 0;
  int startPosOffset = 20;
  for(int a = 0;  a < totMagicPoints; a++)
  {
    int pos = a;
    int index = pos;
    int outputPort = pos;
    if(outputPort >= resolution)
      outputPort = resolution - resolution;
    if(a == 23)
      outputPort = 27;
    if(outputPort > 11)
      outputPort += 3;
    if(a == 16)
      outputPort = 14;
    magicPoints[a]->setOutputPort(outputPort);
  }
  setupPixelMapping();
  setupDMX();
  setupOSC();
  setupAudio();
  timerNoPoints = 0;
}

void MagicLightCircle::setupPixelMapping()
{
  pixelMapping.setup(totMagicPoints);
}

void MagicLightCircle::addNewMagicPoint()
{
  int id = magicPoints.size();
  float angle = 0;
  angle = float(id*float(float(360)/totMagicPoints));
  MagicPoint* p = new MagicPoint();
  ofVec2f pos;
  pos.x = (cos(ofDegToRad(angle)) * radius) + radius;
  pos.y = (sin(ofDegToRad(angle)) * radius) + radius;
  p->setPos(pos);
  p->setId(id);
  magicPoints.push_back(p);
  p->setup();
  p = NULL;
}

void MagicLightCircle::update()
{
  if(lightLife < 1)
    lightLife = 1;
  timerNoPoints++;
  if(timerNoPoints > 100 && blobs.size() > 0)
    blobs.clear();
  updateOSC();
  if(!useOSC)
    update(blobs);
  if(useSound)
    updateSound();
  if(usePixelMapping)
  {
    pixelMapping.update();
    for(int a = 0; a < totMagicPoints; a++)
    {
      magicPoints[a]->intensity = float(pixelMapping.values[a]/255.0);
    }
  }
  sendDMX();
  checkLightInputControllerChanged();
}

void MagicLightCircle::updateSound()
{
  int step = right.size()/totMagicPoints;
  for (unsigned int i = 0; i < left.size(); i+=step)
  {
    int pos = ofMap(i,0,left.size(), 0, (totMagicPoints*.5) + 1, true);
    magicPoints[pos]->intensity = left[i] * audioMultiplier;
    dmxData_[magicPoints[pos]->getOutputPort()+1] = magicPoints[pos]->intensity * 255;
  }
  for (unsigned int i = 0; i < right.size(); i+=step)
  {
    int pos = ofMap(i,0,right.size(), (totMagicPoints*.5) + 1, totMagicPoints, true);
    magicPoints[pos]->intensity = right[i] * audioMultiplier;
    dmxData_[magicPoints[pos]->getOutputPort()+1] = magicPoints[pos]->intensity * 255;
  }
}


void MagicLightCircle::updateMagicPoints(ofVec3f point)
{
  ofVec2f pointWithNoZ = ofVec2f(point.x, point.y);
  for(int a = 0; a < totMagicPoints; a++)
  {
    /// Se non ci sono i blob non faccio l'update... non so se è giusto...
    magicPoints[a]->update(point, lightFadeOutSpeed, lightFadeInSpeed);
    magicPoints[a]->radius = radius * percMaxDistanceCircle;
    float tempIntensity = magicPoints[a]->calculateIntensity(pointWithNoZ);
    if(!reverseLogic)
    {
      if((tempIntensity > magicPoints[a]->getIntensity())||useDepthForIntensity)
      {
        if(magicPoints[a]->getActive())
        {
          magicPoints[a]->life = lightLife;
          if(useDepthForIntensity)
            magicPoints[a]->setDesiredIntensity(float(point.z/255));
          else
            magicPoints[a]->setDesiredIntensity(pointWithNoZ);
        }
      }
      else
      {
        if(reverseLogic)
        {
          if(useDepthForIntensity)
            magicPoints[a]->setDesiredIntensity(float(point.z/255));
          else
            magicPoints[a]->setDesiredIntensity(pointWithNoZ);
        }
      }
    }
    else
    {
      if(magicPoints[a]->reverseLogic&&magicPoints[a]->getActive())
      {
        magicPoints[a]->life = 0;
        magicPoints[a]->setDesiredIntensity(0);
        magicPoints[a]->reverseLogic = false; // Attivare questo solo se la logica del reverseLogic è attiva
      }
    }
    dmxData_[magicPoints[a]->getOutputPort()+1] = magicPoints[a]->getIntensity()*255;
  }
}

void MagicLightCircle::update(vector<Blob> _blobs)
{
  ofPoint center = ofPoint(radius, radius);
  for(int i = 0; i < _blobs.size(); i++)
  {
    updateMagicPoints(_blobs[i].point);
  }
  if(_blobs.size() == 0)
    updateMagicPoints(ofVec3f(-10000));
}

void MagicLightCircle::draw()
{
  ofPushStyle();
  ofNoFill();
  ofRect(0,0,radius*2, radius*2);
  ofSetColor(255);
  ofCircle(radius, radius, radius);
  
  for(int a = 0; a < totMagicPoints; a++)
  {
    magicPoints[a]->draw();
  }
  for(int a = 0; a < blobs.size(); a++)
  {
    if(blobs[a].life > 0)
    {
      ofCircle(blobs[a].point.x, blobs[a].point.y, 10);
      blobs[a].life--;
    }
  }
  pixelMapping.draw(10, 550);
  ofPopStyle();
}

void MagicLightCircle::setupDMX()
{
  memset( dmxData_, 0, DMX_DATA_LENGTH );
  dmxInterface_ = ofxGenericDmx::openFirstDevice();
  if ( dmxInterface_ == 0 )
    printf( "No Enttec Device Found\n" );
  else
    printf( "isOpen: %i\n", dmxInterface_->isOpen() );
}

void MagicLightCircle::sendDMX()
{
  for(int a = 0; a < totMagicPoints; a++)
    dmxData_[magicPoints[a]->getOutputPort()+1] =  magicPoints[a]->intensity * 255;
  
  //force first byte to zero (it is not a channel but DMX type info - start code)
  dmxData_[0] = 0;
  if ( ! dmxInterface_ || ! dmxInterface_->isOpen() ) {
    printf( "Not updating, enttec device is not open.\n");
//    setupDMX();
  }
  else{
    //send the data to the dmx interface
    dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
  }
}

void MagicLightCircle::checkLightInputControllerChanged()
{
  if(prevUseSound != useSound)
  {
    useOSC = false;
    useDepthForIntensity = false;
    usePixelMapping = false;
  }
  else if(prevUseDepthForIntensity != useDepthForIntensity)
  {
    useOSC = false;
    useSound = false;
    usePixelMapping = false;
  }
  else if(prevUseOSC != useOSC)
  {
    useDepthForIntensity = false;
    useSound = false;
    usePixelMapping = false;
  }
  else if(prevUsePixelMapping != usePixelMapping)
  {
    useDepthForIntensity = false;
    useSound = false;
    prevUseOSC = false;
  }
  prevUseDepthForIntensity = useDepthForIntensity;
  prevUseOSC = useOSC;
  prevUseSound = useSound;
  prevUsePixelMapping = usePixelMapping;
}

ofParameterGroup* MagicLightCircle::getParameterGroup()
{
  if(!magicLightParams)
  {
    magicLightParams = new ofParameterGroup();
  }
  if(magicLightParams->getName() == "")
  {
    ofParameterGroup depthGroup;
    ofParameterGroup oscGroup;
    ofParameterGroup soundGroup;
    depthGroup.setName("Depth group");
    oscGroup.setName("OSC group");
    soundGroup.setName("Sound group");
    magicLightParams->setName("Magic Light Circle");
    magicLightParams->add(lightLife.set("Light life", 10,1, 500));
    magicLightParams->add(lightFadeInSpeed.set("Fade In Speed", .050,0.000, 0.080));
    magicLightParams->add(lightFadeOutSpeed.set("Fade Out Speed", .050,0.000, 0.100));
    magicLightParams->add(percMaxDistanceCircle.set("Max Distance Circle", .15,0, 1));
    magicLightParams->add(useDepthForIntensity.set("Use Dept For Intensity", false));
    magicLightParams->add(usePixelMapping.set("Use Pixel mapping", false));
    magicLightParams->add(useOSC.set("Use OSC For Intensity", false));
    magicLightParams->add(useSound.set("Use sound For Intensity", false));
    magicLightParams->add(reverseLogic.set("Reverse logic", false));
    magicLightParams->add(audioMultiplier.set("Audio Multiplier", 1.00,0.00, 5.00));
//    magicLightParams->add(depthGroup);
//    magicLightParams->add(oscGroup);
//    magicLightParams->add(soundGroup);
  }
  return magicLightParams;
}