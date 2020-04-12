#ifndef _CONTROLS_ 
#define _CONTROLS_ 

#include "globals.h"
#include "trigo.h"
#include "player.h"
#include "shot.h"

void controls(Player* p1){

  if (ab.pressed(RIGHT_BUTTON)){
    if (p1->turnTimer--<=0){
      p1->turnTimer=2;
      if (++p1->dir>15)
        p1->dir=0;
    }
  }
  else if (ab.pressed(LEFT_BUTTON)){
    if (p1->turnTimer--<=0){
      p1->turnTimer=2;
      if (--p1->dir>127)
        p1->dir=15;
    }
  }
  else
    p1->turnTimer=0;
  if (ab.pressed(B_BUTTON)||ab.pressed(UP_BUTTON)){
    if (p1->fuel>0){
      p1->drawFlames();
      p1->fuel-=1;
      if (ab.everyXFrames(2)){
        p1->speed+=trigoVec(p1->dir,3,vec2(0,0));
        if (magn(p1->speed)>SPEED_MAX) {
          p1->speed-=trigoVec(p1->dir,3,vec2(0,0));
        }
      }
    }
  }
  if (ab.pressed(DOWN_BUTTON)){
    if (p1->fuel>0){          
      if (magn(p1->speed)<=1) {
        p1->speed=vec2(0,0);
      }
      else {
        p1->fuel-=1;
        p1->drawRetroFlames();      
        if (ab.everyXFrames(2)){
          p1->speed.x-=abs(p1->speed.x)/p1->speed.x;
          p1->speed.y-=abs(p1->speed.y)/p1->speed.y;
        }
      }
    }
  }
  if (ab.pressed(A_BUTTON)&&ab.pressed(B_BUTTON)&&ab.pressed(LEFT_BUTTON)&&ab.pressed(RIGHT_BUTTON)){ //secret warp (
    p1->pos=vec2(64,32);
    mapCoord=vec2(0,0);    
  }
  
  if (ab.justPressed(A_BUTTON)){    //another weapons allows to hold fire button
    if (0==p1->coolDown){ 
      for (int i=0;i<SHOTS_MAX;i++){        
        if (0==p1->shots[i].active){          
          p1->shots[i].active=SHOT_DURATION;
          p1->coolDown=COOLDOWN;
          //p1->shots[i].pos=p1->pos+trigoVec(p1->dir,10,vec2(0,0));
          p1->shots[i].pos=p1->pos/*-mapCoord*/+trigoVec(p1->dir,10,vec2(0,0))+p1->speed/SPEED_DIVISOR;
          p1->shots[i].dir=p1->dir;
          p1->shots[i].speed=p1->speed/SPEED_DIVISOR+trigoVec(p1->dir,6,vec2(0,0));
          i=99;
        }
      }
    }
  }
  
/*
  //for collision test change control type (left go left instead of rotating)
  if (ab.pressed(A_BUTTON)){
    if (ab.everyXFrames(2)){
      if (++p1->dir>15)
        p1->dir=0;
    }
  }
  if (ab.pressed(B_BUTTON)){
    if (ab.everyXFrames(2)){
      if (--p1->dir>127)
        p1->dir=15;
    }
  }
  if (ab.pressed(UP_BUTTON))
    p1->pos.y--;
  if (ab.pressed(DOWN_BUTTON))
    p1->pos.y++;
  if (ab.pressed(LEFT_BUTTON))
    p1->pos.x--;
  if (ab.pressed(RIGHT_BUTTON))
    p1->pos.x++;
*/

}
#endif
