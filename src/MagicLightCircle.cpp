//
//  MagicLightCircle.cpp
//  MagicLightCircle
//
//  Created by Mauro Ferrario on 11/11/15.
//
//

#include "MagicLightCircle.h"


MagicLightCircle::MagicLightCircle()
{
}

MagicLightCircle::~MagicLightCircle()
{
  
}

void MagicLightCircle::setupOSC()
{
  receiver.setup(12345);
}

void MagicLightCircle::updateOSC()
{
  while(receiver.hasWaitingMessages())
  {
    ofxOscMessage m;
    receiver.getNextMessage(&m);
    string address = m.getAddress();
    if(address.find("newPoint") <= 10)
    {
      int pointPos = ofToInt(address.substr(10,1));
      ofVec3f point;
      point.x = (m.getArgAsFloat(0) * radius * 2);
      point.y = (m.getArgAsFloat(1) * radius * 2);
      point.z = m.getArgAsFloat(2);
      Blob tempBlob;
      tempBlob.point = point;
      tempBlob.life = lightLife;
      if(pointPos+1>blobs.size())
        blobs.push_back(tempBlob);
      else
        blobs[pointPos] = tempBlob;
    }
  }
}

void MagicLightCircle::setCircleResolution(int num)
{
  
}

void MagicLightCircle::setup(int resolution)
{
  radius = 200;
  totMagicPoints = resolution;
  for(int a = 0; a < resolution; a++)
  {
    addNewMagicPoint();
  }
  magicPoints[0]->setOutputPort(2);
  magicPoints[1]->setOutputPort(0);
  magicPoints[2]->setOutputPort(3);
  magicPoints[3]->setOutputPort(4);
  magicPoints[4]->setOutputPort(5);
  magicPoints[5]->setOutputPort(8);
  magicPoints[6]->setOutputPort(1);
  magicPoints[7]->setOutputPort(7);
  setupDMX();
  setupOSC();
}

void MagicLightCircle::addNewMagicPoint()
{
  int id = magicPoints.size();
  float angle = 0;
  angle = float(id*float(float(360)/totMagicPoints));
  cout << angle << endl;
  MagicPoint* p = new MagicPoint();
  ofVec2f pos;
  pos.x = (cos(ofDegToRad(angle)) * radius) + radius;
  pos.y = (sin(ofDegToRad(angle)) * radius) + radius;
  p->setPos(pos);
  p->setId(id);
  magicPoints.push_back(p);
  p = NULL;
}

void MagicLightCircle::update()
{
  updateOSC();
  update(blobs);
}

void MagicLightCircle::update(vector<Blob> _blobs)
{
  for(int i = 0; i < _blobs.size(); i++)
  {
   for(int a = 0; a < totMagicPoints; a++)
   {
    float tempIntensity = magicPoints[a]->calculateIntensity(_blobs[i].point, radius);
    if(tempIntensity > magicPoints[a]->getIntensity()&&_blobs[i].life>0)
      magicPoints[a]->setIntensity(_blobs[i].point, radius);
    magicPoints[a]->intensity -= lightFadeOutSpeed;
    if(magicPoints[a]->intensity < 0)
      magicPoints[a]->intensity = 0;
    dmxData_[magicPoints[a]->getOutputPort()+1] = magicPoints[a]->getIntensity()*255;
   }
  }
  sendDMX();
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
  //force first byte to zero (it is not a channel but DMX type info - start code)
  dmxData_[0] = 0;
  if ( ! dmxInterface_ || ! dmxInterface_->isOpen() ) {
    printf( "Not updating, enttec device is not open.\n");
  }
  else{
    //send the data to the dmx interface
    dmxInterface_->writeDmx( dmxData_, DMX_DATA_LENGTH );
  }
}

ofParameterGroup* MagicLightCircle::getParameterGroup()
{
  if(!magicLightParams)
  {
    magicLightParams = new ofParameterGroup();
  }
  if(magicLightParams->getName() == "")
  {
    magicLightParams->setName("MagicLightCircle");
//    kinectTrackingParams->add(roiPos.set("Roi pos", ofVec2f(0,0), ofVec2f(0,0), ofVec2f(kinect.width, kinect.height)));
//    kinectTrackingParams->add(roiSize.set("Roi size", ofVec2f(10,10), ofVec2f(10,10), ofVec2f(kinect.width, kinect.height)));
//    kinectTrackingParams->add(nearThreshold.set("Near Threshold", 218,0, 255));
//    kinectTrackingParams->add(farThreshold.set("Far Threshold", 110,0, 255));
//    kinectTrackingParams->add(minArea.set("Min area", 110,0, 1000));
//    kinectTrackingParams->add(maxArea.set("Max area", 500,0, kinect.width * kinect.height));
//    kinectTrackingParams->add(maxRadius.set("Max radius", 200,0, 500));
//    kinectTrackingParams->add(maxPointToSend.set("Max point to send", 2,0, 10));
    magicLightParams->add(lightLife.set("Light life", 10,0, 200));
    magicLightParams->add(lightFadeOutSpeed.set("Fade Out Speed", .050,0.000, 0.100));
  }
  return magicLightParams;
}
