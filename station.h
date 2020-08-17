#ifndef _STATION_
#define _STATION_

#include "globals.h"
//#include "background.h"
#include "vec2.h"
#include "trigo.h"

#define BLINK_SPEED 1


class Station {
  public:
    vec2 pos;
    int blinking;
    Station(vec2 _pos){
      pos=_pos;
      blinking=0;
    }
    void draw();
};

void drawPorthole(vec2 pos){
  ab.fillCircle(pos.x,pos.y,4,0);
  ab.drawPixel(pos.x-1,pos.y-1);
}

void Station::draw(){

  vec2 temp=pos+mapCoord;
  vec2 temp2;
  
  drawCylinder(temp,temp+vec2(0,40),15,false,true);
  drawPorthole(temp+vec2(-9,8));
  drawPorthole(temp+vec2(9,8));
  drawPorthole(temp+vec2(-9,32));
  drawPorthole(temp+vec2(9,32));  
  temp2=trigoVec(12,30,temp);
  drawVecLine(temp,temp2);
  if (blinking++>100){
    drawVecLine(temp2-vec2(1,1)*(blinking-100)/BLINK_SPEED,temp2+vec2(1,1)*(blinking-100)/BLINK_SPEED);
    drawVecLine(temp2-vec2(1,-1)*(blinking-100)/BLINK_SPEED,temp2+vec2(1,-1)*(blinking-100)/BLINK_SPEED);
  }
  drawGrid(temp+vec2(-10,-10),vec2(3,0),vec2(0,-3),3,10);
  temp=temp+vec2(0,15);
  temp2=trigoVec(12,30,temp);
  drawVecLine(temp,temp2);
  if (blinking>100){
    drawVecLine(temp2-vec2(1,1)*(blinking-100)/BLINK_SPEED,temp2+vec2(1,1)*(blinking-100)/BLINK_SPEED);
    drawVecLine(temp2-vec2(1,-1)*(blinking-100)/BLINK_SPEED,temp2+vec2(1,-1)*(blinking-100)/BLINK_SPEED);
  }  
  if (blinking>100+3*BLINK_SPEED)
    blinking=0;
  
  //drawVecLine(temp+vec2(0,32),trigoVec(12,30,temp));
}


#endif 
