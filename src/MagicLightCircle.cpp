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
  for(int a = 0; a < resolution; a++)
  {
    addNewMagicPoint();
  }
}

void MagicLightCircle::addNewMagicPoint()
{
  MagicPoint* p = new MagicPoint();
  magicPoints.push_back(p);
  totMagicPoints++;
  p = NULL;
}

void MagicLightCircle::update()
{
  
}

void MagicLightCircle::draw()
{
  float radius = 100;
  float angle = 0;
  ofPushStyle();
  ofNoFill();
  ofRect(0,0,radius*2, radius*2);
  ofSetColor(255);
  ofPushMatrix();
  ofTranslate(radius, radius);
  ofCircle(0, 0, 100);
  for(int a = 0; a < totMagicPoints; a++)
  {
    ofVec2f pos;
    pos.x = (cos(ofDegToRad(angle)) * radius);// + radius*.5;
    pos.y = (sin(ofDegToRad(angle)) * radius);// + radius*.5;
    magicPoints[a]->draw(pos);
    angle += float(360/totMagicPoints);
    cout << angle << endl;
  }
  ofPopStyle();
  ofPopMatrix();
}
