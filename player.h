#ifndef _PLAYER_
#define _PLAYER_

#define SPEED_MAX 10

#include "globals.h"
#include "trigo.h"
//#include "shot.h"

class Player {
  public:
    vec2 pos;
    vec2 speed;    
    byte dir;
    //Player() : x(64),y(30),dir(0) {}
    Player(int x, int y, int dir){
      this->pos.x=x;
      this->pos.y=y;
      this->dir=dir;
      this->speed=vec2(0,0);
    }
    void Player::draw();
};
void Player::draw(){
  //Background ajust
//  mapX+=trigo(this->dir,this->speed,true);
//  mapY+=trigo(this->dir,this->speed,false);
  mapCoord-=this->speed;
  if (0<=mapCoord.x){
    mapCoord.x=0;
    this->speed.x=0;
  }
  if (0<=mapCoord.y){
    mapCoord.y=0;
    this->speed.y=0;
  }
  ab.fillCircle(pos.x,pos.y,4);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),3);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),2,0);
  if (speed.x>0)
    speed.x--;
  if (speed.y>0)
    speed.y--;  
}

#endif
