#ifndef _PLAYER_
#define _PLAYER_

#define SPEED_MAX 100
//#define SPEED_DIVISOR -> in globals.h

#include "globals.h"
#include "trigo.h"
#include "shot.h"
#include "background.h"

#define ARMOR_MAX 60

//#define TANK_SMALL 10000
//#define TANK_EMERGENCY 300

class Player {       
  public:
    vec2 pos;
    vec2 speed;    
    vec2 reste;
    byte dir;
    byte turnTimer;
    //unsigned int fuel;
    //unsigned int fuelMax;
    byte armor;
    int coolDown;
    bool burn;
    Shot shots[SHOTS_MAX];
    //Player() : x(64),y(30),dir(0) {}
    Player(int x, int y, int dir){
      this->pos.x=x;
      this->pos.y=y;
      this->dir=dir;
      this->coolDown=0;
      this->turnTimer=0;
      this->speed=vec2(0,0);
      armor=ARMOR_MAX;
      //fuelMax=TANK_SMALL;
      //fuel=fuelMax;
      reste=vec2(0,0);     
      burn=false; 
    }
    void Player::draw();
    void Player::drawFlames();
    void Player::drawRetroFlames();
    void Player::checkcollision();
    void Player::checkShotscollision();
};
void Player::draw(){ //--------------------------------------------------------------------DRAW----------------------------------

  pos+=((this->speed+this->reste)/SPEED_DIVISOR);
  this->reste=(this->speed+this->reste)%SPEED_DIVISOR;  

  //Fuel jauge
  //drawVecLine(vec2(126,63),vec2(126,63-(fuel/300))); //todo: modify drawTrigoVec (vec2, dir, length){...
  //ab.drawPixel(126,63-(fuelMax/300));  
  
  //ARMOR
  drawVecLine(vec2(126,63),vec2(126,63-(armor))); 
  ab.drawPixel(126,63-(ARMOR_MAX));    
  
  //Background ajust
  if (pos.x<64){
    //int temp = -(SECTOR_LINES-1)*IMAGE_HEIGHT);
    if (mapCoord.x-(pos.x-64)<0){
      mapCoord.x-=(pos.x-64);
      pos.x=64;
    }
    else{            
      pos.x+=mapCoord.x;
      mapCoord.x=0;      
    }
  }  
  else if (pos.x>64){
    int temp = -(SECTOR_COLUMNS-1)*IMAGE_WIDTH+64;
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
    if (mapCoord.y-(pos.y-32)<0){
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
    int temp = -(SECTOR_LINES-1)*IMAGE_HEIGHT+32;
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
  //sprites.drawSelfMasked(pos.x-8,pos.y-8,Ship, dir); //Sprites (unmasked) instead of geometrical drawing uses +222 bytes of progmem (1%). Don't know about speed yet. 
  ab.fillCircle(pos.x,pos.y,5);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),3);
  ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),2,0);
  ab.drawPixel(pos.x+trigo((dir+1),6,true),pos.y+trigo((dir+1),6,false));
  ab.fillCircle(pos.x+trigo((dir+8),6,true),pos.y+trigo((dir+8),6,false),4,0);
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
  vec2 temp=elementCollision(this->pos,6,magn(this->speed)/10,1);
  if (temp!=vec2(0,0)){
    ab.drawCircle(this->pos.x,this->pos.y,20);
    if (temp.x!=99){
      armor-=magn(this->speed)/10; //todo make dmg proportional to speed diference between the 2 objects
      this->speed=temp;
    }
    else {
      armor-=temp.y;
    }
  }
}
void Player::checkShotscollision(){
  for (int i=0; i<SHOTS_MAX; i++){
    if (shots[i].active){
      vec2 temp=elementCollision(shots[i].pos,0,0,2);
      if (temp!=vec2(0,0)&&temp.x!=99){ //not much chance of being hit by own shot (maybe at the beggining)
        shots[i].active=false;
      }
    }
  }
}

void  Player::drawFlames(){  //if both flames at the same time, they aren't animated anymore
  vec2 temp=trigoVec(invDir(dir),burn? 14:12,pos);
  drawVecLine(temp, trigoVec((dir+1),6,temp));
  drawVecLine(temp, trigoVec((dir-1),6,temp));
  if(ab.everyXFrames(3))
    burn=!burn;
}

void  Player::drawRetroFlames(){
  if(ab.everyXFrames(3))
    burn=!burn;
  vec2 temp=trigoVec((dir+2),burn? 9:11,pos);
  //drawVecLine(temp, trigoVec((dir+2),burn? 6:4,temp));
  drawVecLine(temp, trigoVec((dir+2),4,temp));
  
  temp=trigoVec((dir-2),burn? 9:11,pos);
  drawVecLine(temp, trigoVec((dir-2),4,temp));
  
  temp=trigoVec((dir+6),burn? 9:11,pos);
  drawVecLine(temp, trigoVec((dir+6),4,temp));
  
  temp=trigoVec((dir-6),burn? 9:11,pos);
  drawVecLine(temp, trigoVec((dir-6),4,temp));
}

#endif
