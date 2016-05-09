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

void PixelMappingCircle::drawGUI()
{
  gui.draw();
}


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
void PixelMappingCircle::setupGUI()
{
  gui.setup("Pixel Mapping GUI");
  gui.setPosition(ofPoint(650,0));
  gui.add(*getParameterGroup());
}

ofParameterGroup* PixelMappingCircle::getParameterGroup()
{
  if(!pixelMappingParams)
  {
    pixelMappingParams = new ofParameterGroup();
  }
  if(pixelMappingParams->getName() == "")
  {
    pixelMappingParams->setName("Pixel mapping");
    pixelMappingParams->add(fadeOutSpeed.set("Fade out speed", 4,0, 255));
    pixelMappingParams->add(colorSpeed.set("Color Speed", 4,0, 50));
    pixelMappingParams->add(idFunction.set("id Function To Load", 0,0, 10));
    pixelMappingParams->add(loadFunction.set("Load function",false));
    pixelMappingParams->add(loop.set("Loop",false));
    pixelMappingParams->add(active.set("Active", active));
//    idFunction.addListener(this, &PixelMappingCircle::idFunctionChanged);

  }
  return pixelMappingParams;
}