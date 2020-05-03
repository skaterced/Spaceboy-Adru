#ifndef _CONTROLS_ 
#define _CONTROLS_ 

#include "globals.h"
#include "trigo.h"
#include "player.h"
#include "shot.h"

void controls(Player* p1){ //, bool raceMode){
bool raceMode=(0x80==(p1->setup&0x80))?true:false;
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
  else {
    p1->turnTimer=0;
  }
  if (ab.pressed(UP_BUTTON)||(raceMode&&ab.pressed(B_BUTTON))){
    if (true){//if (p1->fuel>0){
      p1->drawFlames();
      //p1->fuel-=1;
      if (ab.everyXFrames(2)){
        p1->speed+=trigoVec(p1->dir,5+((0x10==(p1->setup&0x10))?4:0),vec2(0,0));
        if (magn(p1->speed)>SPEED_MAX+((0x10==(p1->setup&0x10))?20:0)) {
          p1->speed-=trigoVec(p1->dir,5+((0x10==(p1->setup&0x10))?4:0),vec2(0,0));
        }
      }
    }
  }
  if (ab.pressed(DOWN_BUTTON)||(raceMode&&ab.pressed(A_BUTTON))){
    if (true){//(p1->fuel>0){          
      if (magn(p1->speed)<=5&&magn(p1->speed)!=-99) {
        p1->speed=vec2(0,0);
      }
      else {
        //p1->fuel-=1;
        p1->drawRetroFlames();      
        if (ab.everyXFrames(2)){
          p1->speed-=trigoVec(trigoInv(vec2(0,0),p1->speed),5+((0x10==(p1->setup&0x10))?4:0),vec2(0,0));
          /*
           * // ?? How can that have been working?! a divide by 0 may occur
          p1->speed.x-=abs(p1->speed.x)/p1->speed.x;
          p1->speed.y-=abs(p1->speed.y)/p1->speed.y;
          */
        }
      }
    }
  }
  
  if (ab.pressed(A_BUTTON)&&ab.pressed(B_BUTTON)&&ab.pressed(DOWN_BUTTON)&&ab.pressed(RIGHT_BUTTON)){ //secret warp (
    p1->pos=vec2(64,32);
    mapCenter(true);
    //mapCoord=vec2(0,0);    
  }

  if(!raceMode){
    if (ab.pressed(B_BUTTON)&&(p1->energy>0)){
      ab.drawCircle(p1->pos.x,p1->pos.y,11);
      p1->invincible=1;
      p1->energy--;    
    }
    else { //(can shoot with the force field activated)
      if (p1->gun.canHold){
        if (ab.pressed(A_BUTTON)){    
          p1->shoot();
        }
      }
      else {
        if (ab.justPressed(A_BUTTON)){  
          p1->shoot();
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
