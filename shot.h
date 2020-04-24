#ifndef _SHOT_
#define _SHOT_

#include "globals.h"
//#include "background.h"
#include "vec2.h"
#include "element.h"

#define SHOTS_MAX 4
#define COOLDOWN 10
#define SHOT_DURATION 50


class Shot {
  public:
    vec2 pos;
    vec2 speed;
    byte dir;
    int active;
    Explosion boom;
    Shot() {
      boom.type=EXPLOSION_SMALL;
      pos=vec2(0,0);
      speed=vec2(0,0);
      dir=0;
      active=false;
    }  
    void Shot::draw();
    void Shot::explode();
};
void Shot::explode(){
  active=-18;
  boom.count=0;
  boom.pos=pos-mapCoord;
}
void Shot::draw(){
  if (active>0){    
    //drawVecLine(this->pos/*+mapCoord*/,trigoVec(this->dir,4,this->pos/*+mapCoord*/)); //normal piou piou
    ab.drawCircle(this->pos.x,pos.y,1); //normal piou piou
    this->pos+=this->speed;  //trigoVec(this->dir,2,vec2(0,0));
    active--;
  }
  else if (active<0){ //shot is exploding
    active++;
    boom.update();    
  }
}


class Gun {
  public :
  bool canHold;
  Shot shots[SHOTS_MAX];
  int coolDown;
  byte maxBullets;
  byte dmg;
  Gun(){
    canHold=true;
    maxBullets=SHOTS_MAX; //not sure why we need this
    coolDown=0;
    dmg=2;
  }
  void Gun::shoot(vec2 pos, vec2 speed, byte dir){
    if (0==coolDown){ 
      for (int i=0;i<maxBullets;i++){        
        if (0==shots[i].active){          
          shots[i].active=SHOT_DURATION;
          coolDown=COOLDOWN;                   
          shots[i].pos=pos+trigoVec(dir,10,speed/SPEED_DIVISOR);
          shots[i].dir=dir;
          //p1->shots[i].speed=p1->speed/SPEED_DIVISOR+trigoVec(p1->dir,6,vec2(0,0));
          shots[i].speed=trigoVec(dir,6,speed/SPEED_DIVISOR);
          i=99;
        }
      }
    }     
  }
  void Gun::draw(){
  for (int i=0;i<SHOTS_MAX;i++){
    if (shots[i].active!=0){      
      shots[i].draw();
    }
  }  
  if (coolDown>0)
    coolDown--;
  }
};

#endif
