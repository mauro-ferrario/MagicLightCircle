//
//  PixelMappingCircle.cpp
//  MagicLightCircle
//
//  Created by XXX on 09/05/16.
//
//

#include "PixelMappingCircle.h"



PixelMappingCircle::PixelMappingCircle()
{
  
}

void PixelMappingCircle::setup(int totPixel)
{
  for(int a = 0; a < totPixel; a++)
    values.push_back(0);
  this->totPixel = totPixel;
  fbo.allocate(totPixel*30, 1);
  fbo.begin();
  ofClear(0,0,0,255);
  fbo.end();
}

void PixelMappingCircle::update()
{
  fbo.begin();
  drawFunction();
  ofPushStyle();
  ofSetColor(0,4);
  ofRect(0,0,totPixel*30, 1);
  ofPopStyle();
  fbo.end();
  
  
  ofPixels pixels;
  fbo.readToPixels(pixels);
  
  for(int a = 0; a < totPixel; a++)
  {
    values[a] = pixels.getColor(15+(a*30), 0).r;
  }
  
}

void  PixelMappingCircle::draw(int x, int y)
{
  ofPushMatrix();
  ofTranslate(x, y);
  draw();
  ofPopMatrix();
}

void  PixelMappingCircle::draw()
{
  int pixelSize = 30;
  fbo.draw(0, 0, totPixel*pixelSize,pixelSize);
  for(int a = 0; a <= totPixel; a++)
  {
    ofLine(a*pixelSize, 0, a*pixelSize, pixelSize);
  }
}

void PixelMappingCircle::drawFunction()
{
  ofPushMatrix();
  ofTranslate(rectPos);
  rectPos.x += 4;
  if(rectPos.x > totPixel*30)
    rectPos.x = -1;
  ofPushStyle();
  ofSetColor(255);
  ofRect(0, 0, 30, 30);
  ofPopStyle();
  ofPopMatrix();
}