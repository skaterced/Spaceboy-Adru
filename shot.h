#ifndef _SHOT_
#define _SHOT_

#include "globals.h"
#include "background.h"
#include "vec2.h"

#define SHOTS_MAX 3
#define COOLDOWN 10
#define SHOT_DURATION 50

class Shot {
  public:
    vec2 pos;
    vec2 speed;
    byte dir;
    int active;
    Shot() {
      pos=vec2(0,0);
      speed=vec2(0,0);
      dir=0;
      active=false;
    }  
    void Shot::draw();
};
void Shot::draw(){

  //vec2 temp=trigoVec(this->dir,2,this->pos);
  drawVecLine(this->pos/*+mapCoord*/,trigoVec(this->dir,4,this->pos/*+mapCoord*/));
  this->pos+=this->speed;  //trigoVec(this->dir,2,vec2(0,0));
  if (--this->active<=0)
    this->active=0;
  /*
  ab.display();
  delay(130);
  */
}


#endif
