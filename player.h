#ifndef _PLAYER_
#define _PLAYER_

#define SPEED_MAX 50

#include "globals.h"
#include "trigo.h"
#include "shot.h"

class Player {
  public:
    vec2 pos;
    vec2 speed;    
    byte dir;
    int coolDown;
    Shot shots[SHOTS_MAX];
    //Player() : x(64),y(30),dir(0) {}
    Player(int x, int y, int dir){
      this->pos.x=x;
      this->pos.y=y;
      this->dir=dir;
      this->coolDown=0;
      this->speed=vec2(0,0);
    }
    void Player::draw();
};
void Player::draw(){
  //Background ajust
  mapCoord-=(this->speed/5);
  if (0<mapCoord.x){
    mapCoord.x=0;
    this->speed.x=0;
  }
  if (0<mapCoord.y){
    mapCoord.y=0;
    this->speed.y=0;
  }
  ab.fillCircle(pos.x,pos.y,4);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),3);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),2,0);
  /*
  if (speed.x>0)
    speed.x--;
  if (speed.y>0)
    speed.y--; 
*/    
    
  //draw shots
  for (int i=0;i<SHOTS_MAX;i++){
    if (this->shots[i].actif>0){
      //this->shots[i].pos-=this->speed/5;
      this->shots[i].draw();
    }
  }
  if (this->coolDown>0)
    this->coolDown--;
    
  //debug    
  ab.setCursor(0,0);
  ab.print(magn(this->speed));
    
}

void  drawFlames(Player* p1){
  volatile bool burn;
  vec2 temp=trigoVec(invDir(p1->dir),burn? 16:14,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+1),6,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir-1),6,temp));
  burn=!burn;
}

#endif
