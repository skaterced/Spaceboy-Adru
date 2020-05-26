#ifndef _CONTROLS_ 
#define _CONTROLS_ 

#include "globals.h"
#include "trigo.h"
#include "player.h"
#include "shot.h"

void controls(Player* p1){ //, bool raceMode){
//bool raceMode=(0x80==(p1->setup&0x80))?true:false; 
#ifdef RACE_MODE //todo: suppress bool raceMode and add #ifdef inside the control routine
  //bool raceMode=true;
#else
#endif  

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
  #ifdef RACE_MODE
  if (ab.pressed(UP_BUTTON)||(ab.pressed(B_BUTTON))){
  #else
  if (ab.pressed(UP_BUTTON)){  
  #endif
    
    #ifdef FUEL
    if (p1->fuel>0){
      p1->drawFlames();      
      p1->fuel-=1;
    #else
      p1->drawFlames();
      if (true){
    #endif
      if (ab.everyXFrames(2)){
        p1->speed+=trigoVec(p1->dir,5+((0x10==(p1->setup&0x10))?4:0),vec2(0,0));
        if (magn(p1->speed)>SPEED_MAX+((0x10==(p1->setup&0x10))?20:0)) {
          p1->speed-=trigoVec(p1->dir,5+((0x10==(p1->setup&0x10))?4:0),vec2(0,0));
        }
      }
    }
  }
  #ifdef RACE_MODE
  if (ab.pressed(DOWN_BUTTON)||(ab.pressed(A_BUTTON))){
  #else
  if (ab.pressed(DOWN_BUTTON)){  
  #endif
  //if (ab.pressed(DOWN_BUTTON)||(raceMode&&ab.pressed(A_BUTTON))){
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
    p1->mapCenter(true);//, vec2(sectorColumns, sectorLines));
    //mapCoord=vec2(0,0);    
  }

//  if(!raceMode){
    #ifndef RACE_MODE
    if (ab.pressed(B_BUTTON)&&(p1->shield>0)){
      ab.drawCircle(p1->pos.x,p1->pos.y,11);
      p1->invincible=1;
      p1->shield--;    
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
  #endif
  //}
}
#endif
