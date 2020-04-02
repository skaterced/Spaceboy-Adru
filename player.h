#ifndef _PLAYER_
#define _PLAYER_

#define SPEED_MAX 50
//#define SPEED_DIVISOR -> in globals.h

#include "globals.h"
#include "trigo.h"
#include "shot.h"
#include "background.h"

class Player {       
  public:
    vec2 pos;
    vec2 speed;    
    vec2 reste;
    byte dir;
    int coolDown;
    bool burn;
    Shot shots[SHOTS_MAX];
    //Player() : x(64),y(30),dir(0) {}
    Player(int x, int y, int dir){
      this->pos.x=x;
      this->pos.y=y;
      this->dir=dir;
      this->coolDown=0;
      this->speed=vec2(0,0);
      reste=vec2(0,0);     
      burn=false; 
    }
    void Player::draw();
    void Player::checkcollision();
    void Player::checkShotscollision();
};
void Player::draw(){

  pos+=((this->speed+this->reste)/SPEED_DIVISOR);
  this->reste=(this->speed+this->reste)%SPEED_DIVISOR;  
        
  //Background ajust
  if (pos.x<64){
    //int temp = -(SECTOR_LINES-1)*IMAGE_HEIGHT);
    if (mapCoord.x-(pos.x-64)<0){
      mapCoord.x-=(pos.x-64);
      pos.x=64;
    }
    else{      
      //int temp=mapcoord.x-(pos.x-64);
      pos.x+=mapCoord.x;
      mapCoord.x=0;      
    }
  }  
  else if (pos.x>64){
    int temp = -(SECTOR_LINES-1)*IMAGE_HEIGHT;
    if (mapCoord.x-(pos.x-64)>temp){
      mapCoord.x-=(pos.x-64);
      pos.x=64;
    }
    else{      
      pos.x+=mapCoord.x-temp;
      mapCoord.x=temp;          
    }      
  }
  
  if (pos.y<32){
    //int temp = -(SECTOR_LINES-1)*IMAGE_HEIGHT);
    if (mapCoord.x-(pos.y-32)<0){
      mapCoord.y-=(pos.y-32);
      pos.y=32;
    }
    else{      
      //int temp=mapcoord.x-(pos.y-32);
      pos.y+=mapCoord.y;
      mapCoord.y=0;      
    }
  }  
  else if (pos.y>32){
    int temp = -(SECTOR_COLUMNS-1)*IMAGE_WIDTH;
    if (mapCoord.y-(pos.y-32)>temp){
      mapCoord.y-=(pos.y-32);
      pos.y=32;
    }
    else{      
      pos.y+=mapCoord.y-temp;
      mapCoord.y=temp;          
    }      
  }  

  
/* 
    mapCoord-=((this->speed+this->reste)/SPEED_DIVISOR);
    this->reste=(this->speed+this->reste)%SPEED_DIVISOR;  
  
    if (mapCoord.x>0){  // Map limits
      pos.x-=mapCoord.x;
      mapCoord.x=0;
      //this->speed.x=0;
    }
    if (mapCoord.y>0){
      pos.y-=mapCoord.y;
      mapCoord.y=0;
      //this->speed.y=0;
    }
    if (mapCoord.x<-(SECTOR_COLUMNS-1)*IMAGE_WIDTH){
      pos.x+=mapCoord.x-(SECTOR_COLUMNS-1)*IMAGE_WIDTH;
      mapCoord.x=-(SECTOR_COLUMNS-1)*IMAGE_WIDTH;
      //this->speed.x=0;
    }
    if (mapCoord.y<-(SECTOR_LINES-1)*IMAGE_HEIGHT){
      pos.y+=mapCoord.y-(SECTOR_LINES-1)*IMAGE_HEIGHT;
      mapCoord.y=-(SECTOR_LINES-1)*IMAGE_HEIGHT;
      //this->speed.y=0;
    }
  }
  else{
    
  }
*/
  
/*    
  //Ship V1 "Bubble"
  ab.fillCircle(pos.x,pos.y,4);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),3);
  ab.fillCircle(pos.x+trigo(dir,4,true),pos.y+trigo(dir,4,false),2,0);
  ab.drawPixel(pos.x+trigo(trueDir(dir+1),5,true),pos.y+trigo(trueDir(dir+1),5,false)); //litle reflexion ^^
 */
  /*
  //Ship V1.5 "Lander"
  ab.fillCircle(pos.x,pos.y,4);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,4,false),3);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,4,false),2,0);
  ab.drawPixel(pos.x+trigo(trueDir(dir+1),6,true),pos.y+trigo(trueDir(dir+1),6,false));
  vec2  temp=trigoVec(trueDir(dir+6),6,pos);
  drawVecLine(temp, trigoVec(trueDir(dir+7),3,temp));
  temp=trigoVec(trueDir(dir-6),6,pos);
  drawVecLine(temp, trigoVec(trueDir(dir-7),3,temp));
*/

 //Ship V2 "Half Moon"  
  ab.fillCircle(pos.x,pos.y,5);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),3);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),2,0);
  ab.drawPixel(pos.x+trigo(trueDir(dir+1),6,true),pos.y+trigo(trueDir(dir+1),6,false));
  ab.fillCircle(pos.x+trigo(trueDir(dir+8),6,true),pos.y+trigo(trueDir(dir+8),6,false),4,0);
  drawVecLine(pos,trigoVec(invDir(dir),4,pos));
  
  
  //draw shots
  for (int i=0;i<SHOTS_MAX;i++){
    if (this->shots[i].active>0){      
      this->shots[i].draw();
    }
  }  
  if (this->coolDown>0)
    this->coolDown--;
    
  //debug    
  //ab.setCursor(0,0);
  //ab.print(magn(this->speed));    
}
void Player::checkcollision(){
  vec2 temp=Metcollision(this->pos,6,magn(this->speed)/10,1);
  if (temp!=vec2(0,0)){
    ab.drawCircle(this->pos.x,this->pos.y,20);
    this->speed=temp;
  }
}
void Player::checkShotscollision(){
  for (int i=0; i<SHOTS_MAX; i++){
    if (shots[i].active){
      vec2 temp=Metcollision(shots[i].pos,0,0,2);
      if (temp!=vec2(0,0)){
        shots[i].active=false;
      }
    }
  }
}

void  drawFlames(Player* p1){
  vec2 temp=trigoVec(invDir(p1->dir),p1->burn? 14:12,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+1),6,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir-1),6,temp));
  if(ab.everyXFrames(3))
    p1->burn=!p1->burn;
}

void  drawRetroFlames(Player* p1){
  if(ab.everyXFrames(3))
    p1->burn=!p1->burn;
  vec2 temp=trigoVec(trueDir(p1->dir+2),p1->burn? 9:11,p1->pos);
  //drawVecLine(temp, trigoVec(trueDir(p1->dir+2),p1->burn? 6:4,temp));
  drawVecLine(temp, trigoVec(trueDir(p1->dir+2),4,temp));
  
  temp=trigoVec(trueDir(p1->dir-2),p1->burn? 9:11,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir-2),4,temp));
  
  temp=trigoVec(trueDir(p1->dir+6),p1->burn? 9:11,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir+6),4,temp));
  
  temp=trigoVec(trueDir(p1->dir-6),p1->burn? 9:11,p1->pos);
  drawVecLine(temp, trigoVec(trueDir(p1->dir-6),4,temp));
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
  //burn=!burn;
}

#endif
