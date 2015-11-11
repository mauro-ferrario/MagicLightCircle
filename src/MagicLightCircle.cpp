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
  setupDMX();
}

void MagicLightCircle::addNewMagicPoint()
{
  int id = magicPoints.size();
  float angle = 0;
  angle = float(id*float(float(360)/totMagicPoints));
  cout << angle << endl;
  MagicPoint* p = new MagicPoint();
  ofVec2f pos;
  pos.x = (cos(ofDegToRad(angle)) * radius);
  pos.y = (sin(ofDegToRad(angle)) * radius);
  p->setPos(pos);
  p->setId(id);
  magicPoints.push_back(p);
  p = NULL;
}

void MagicLightCircle::update(vector<ofVec2f> posBlobs)
{
  for(int a = 0; a < totMagicPoints; a++)
  {
    for(int i = 0; i < posBlobs.size(); i++)
    {
      magicPoints[a]->setIntensity(posBlobs[i], radius);
    }
    dmxData_[a] = magicPoints[a]->getIntensity()*255;
  }
  sendDMX();
}

void MagicLightCircle::draw()
{
  ofPushStyle();
  ofNoFill();
  ofRect(-radius,-radius,radius*2, radius*2);
  ofSetColor(255);
  ofPushMatrix();
  ofCircle(0, 0, 100);
  for(int a = 0; a < totMagicPoints; a++)
  {
    magicPoints[a]->draw();
  }
  ofPopStyle();
  ofPopMatrix();
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
