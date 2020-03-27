#ifndef _CONTROLS_ 
#define _CONTROLS_ 

#include "globals.h"
#include "trigo.h"
#include "player.h"
#include "shot.h"

void controls(Player* p1){
  if (ab.pressed(RIGHT_BUTTON)){
    if (++p1->dir>15)
      p1->dir=0;
  }
  if (ab.pressed(LEFT_BUTTON)){
    if (--p1->dir>127)
      p1->dir=15;
  }
  if (ab.pressed(UP_BUTTON)){
//    if (p1->speed<SPEED_MAX)
    if(true)
      trigoVec(p1->dir,3,&p1->speed);
  }
  if (ab.pressed(A_BUTTON)){    
  }
}

#endif
