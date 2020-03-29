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
    int actif;
    Shot() {
      pos=vec2(0,0);
      speed=vec2(0,0);
      dir=0;
      actif=false;
    }  
    void Shot::draw();
};
void Shot::draw(){
  /*
  ab.drawPixel(x,y);
  this->x+=trigo(dir, 2, true);
  this->y+=trigo(dir, 2, false);
  */
  //vec2 temp=trigoVec(this->dir,2,this->pos);
  drawVecLine(this->pos,trigoVec(this->dir,4,this->pos));
  this->pos+=this->speed;  //trigoVec(this->dir,2,vec2(0,0));
  if (--this->actif<=0)
    this->actif=0;
  /*
  ab.display();
  delay(130);
  */
}


#endif

