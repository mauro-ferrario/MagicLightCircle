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
  this->totPixel = totPixel;
  values.assign(totPixel, 0);
  for(int a = 0; a < totPixel; a++)
    order.push_back(a);
  reorder(1, 1);
  fbo.allocate(totPixel*30, 1);
  fbo.begin();
  ofClear(0,0,0,255);
  fbo.end();
  setupGUI();
  active = true;
}

//void PixelMappingCircle::idFunctionChanged(int& newIdFunction)
//{
//  reorder(newIdFunction, 1);
//}

void PixelMappingCircle::update()
{
  fbo.begin();
  if(active)
    drawFunction();
  ofPushStyle();
  ofSetColor(0,fadeOutSpeed);
  ofRect(0,0,totPixel*30, 1);
  ofPopStyle();
  fbo.end();
  
  
  ofPixels pixels;
  fbo.readToPixels(pixels);
  
  for(int a = 0; a < totPixel; a++)
  {
    values[order[a]] = pixels.getColor(15+(a*30), 0).r;
  }
  
}

void PixelMappingCircle::reorder(int orderType, int perno)
{
  switch (orderType) {
    case 0:   // Movimento circolare continuo a partire da un perno
    {
      int position = perno;
      for(int a = 0; a < totPixel; a++)
      {
        position = perno + a;
        if(position > totPixel - 1)
          position = position - totPixel;
        
        order[a] = position;
      }
      break;
    }
    case 1:
    {
      int position = perno;
      int center = totPixel/2;
      for(int a = 0; a < totPixel; a++)
      {
        int distanceFromCenter = (center - a);
        position = perno - distanceFromCenter;
       // if(distanceFromCenter > center)
        //{
          if(position < 0)
          {
            position = totPixel + position;
          }
          else if(position > totPixel - 1)
          {
            position = position - totPixel;
          }
        //}
        order[a] = position;
      }
      break;
    }
      default:
      break;
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
  ofPushStyle();
  ofSetColor(255,0,0);
  for(int a = 0; a <= totPixel; a++)
  {
    if(a < totPixel)
    {
     if(a > 9)
       ofDrawBitmapString(ofToString(order[a]), ofPoint(a*pixelSize+pixelSize/2 - 7, 15));
      else
        ofDrawBitmapString(ofToString(order[a]), ofPoint(a*pixelSize+pixelSize/2 - 4, 15));
    }
    
    ofLine(a*pixelSize, 0, a*pixelSize, pixelSize);
  }
  ofPopStyle();
}

void PixelMappingCircle::drawGUI()
{
  gui.draw();
}


void PixelMappingCircle::startNewFunction(int perno)
{
  startNewFunction(idFunction, perno);
}

void PixelMappingCircle::startNewFunction(int newIdFunction, int perno)
{
  reorder(newIdFunction, perno);
  idFunction = newIdFunction;
  active = true;
  rectPos.x = -1;
}


void PixelMappingCircle::circularAnimation()
{
  ofPushMatrix();
  ofTranslate(rectPos);
  rectPos.x += colorSpeed;
  if(rectPos.x > totPixel*30)
  {
    rectPos.x = 1;
    if(!loop)
    {
      rectPos.x = -666;
      active = false;
    }
  }
  ofPushStyle();
  ofSetColor(255);
  ofRect(0, 0, 30, 30);
  ofPopStyle();
  ofPopMatrix();
}

void PixelMappingCircle::doubleSemiCircularAnimation()
{
  ofPushMatrix();
  ofTranslate(totPixel*30/2 + rectPos.x, rectPos.y);
  rectPos.x += colorSpeed;
  if(rectPos.x > totPixel*30)
  {
    rectPos.x = -1;
    if(!loop)
    {
      rectPos.x = -666;
      active = false;
    }
  }
  ofPushStyle();
  ofSetColor(255);
  ofRect(0, 0, 30, 30);
  ofPopStyle();
  ofPopMatrix();
  
  ofPushMatrix();
  ofTranslate(totPixel*30/2 - rectPos.x, rectPos.y);
  ofPushStyle();
  ofSetColor(255);
  ofRect(0, 0, 30, 30);
  ofPopStyle();
  ofPopMatrix();

}

void PixelMappingCircle::drawFunction()
{
  int id = idFunction;
  switch (id) {
    case 0:
      circularAnimation();
      break;
    case 1:
      doubleSemiCircularAnimation();
    default:
      break;
  }
}

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