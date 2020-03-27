#ifndef _SHOT_
#define _SHOT_

#include "globals.h"

class Shot {
  int x,y;
  byte dir;
  Shot() : x(0),y(0),dir(0) {}
  void Shot::upDate();
};
void Shot::upDate(){
  ab.drawPixel(x,y);
  this->x+=trigo(dir, 2, true);
  this->y+=trigo(dir, 2, false);
}


#endif
