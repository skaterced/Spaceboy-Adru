#ifndef _PLAYER_
#define _PLAYER_

#define SPEED_MAX 50
#define SPEED_DIVISOR 8

#include "globals.h"
#include "trigo.h"
#include "shot.h"
#include "background.h"

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
    void Player::checkColision();
};
void Player::draw(){
  //Background ajust
  mapCoord-=(this->speed/SPEED_DIVISOR);

  if (mapCoord.x>0){  // Map limits
    mapCoord.x=0;
    this->speed.x=0;
  }
  if (mapCoord.y>0){
    mapCoord.y=0;
    this->speed.y=0;
  }
  if (mapCoord.x<-(SECTOR_COLUMNS-1)*IMAGE_WIDTH){
    mapCoord.x=-(SECTOR_COLUMNS-1)*IMAGE_WIDTH;
    this->speed.x=0;
  }
  if (mapCoord.y<-(SECTOR_LINES-1)*IMAGE_HEIGHT){
    mapCoord.y=-(SECTOR_LINES-1)*IMAGE_HEIGHT;
    this->speed.y=0;
  }
    
  ab.fillCircle(pos.x,pos.y,4);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),3);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),2,0);
    
  //draw shots
  for (int i=0;i<SHOTS_MAX;i++){
    if (this->shots[i].actif>0){      
      this->shots[i].draw();
    }
  }
  
  if (this->coolDown>0)
    this->coolDown--;
    
  //debug    
  //ab.setCursor(0,0);
  //ab.print(magn(this->speed));
    
}
void Player::checkColision(){
  vec2 temp=MetColision(this->pos);
  if (temp!=vec2(0,0)){
    ab.drawCircle(this->pos.x,this->pos.y,20);
    this->speed=temp;
  }
}

void  drawFlames(Player* p1){
  volatile bool burn;
  vec2 temp=trigoVec(invDir(p1->dir),burn? 16:14,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+1),6,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir-1),6,temp));
  burn=!burn;
}

void  drawRetroFlames(Player* p1){
  volatile bool burn;
  vec2 temp=trigoVec(trueDir(p1->dir+2),burn? 8:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+2),burn? 5:4,temp));
  
  temp=trigoVec(trueDir(p1->dir-2),burn? 8:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir-2),burn? 5:4,temp));
  
  temp=trigoVec(trueDir(p1->dir+6),burn? 8:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+6),burn? 5:4,temp));
  
  temp=trigoVec(trueDir(p1->dir-6),burn? 8:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir-6),burn? 5:4,temp));
  /*
  vec2 temp=trigoVec(trueDir(p1->dir+2),burn? 12:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(invDir(p1->dir)+3),4,temp));
  drawVecLine(temp, trigoVec(trueDir(invDir(p1->dir)+1),4,temp));
  temp=trigoVec(trueDir(p1->dir-2),burn? 12:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(invDir(p1->dir)-3),4,temp));
  drawVecLine(temp, trigoVec(trueDir(invDir(p1->dir)-1),4,temp));
  temp=trigoVec(invDir(trueDir(p1->dir+2)),burn? 12:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+3),4,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir+1),4,temp));
  temp=trigoVec(invDir(trueDir(p1->dir-2)),burn? 12:10,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir-3),4,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir-1),4,temp));
  */
  burn=!burn;
}

#endif
