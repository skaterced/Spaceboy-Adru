#ifndef _PLAYER_
#define _PLAYER_

#include "globals.h"
#include "trigo.h"
#include "shot.h"
#include "background.h"

#define SPEED_MAX 160
//#define SPEED_DIVISOR -> in globals.h

#define ARMOR_MAX 50
#define ENERGY_MAX 250

//#define TANK_SMALL 10000
//#define TANK_EMERGENCY 300

#define sectorBorderMargin 300

// Player.setup
/* 7 6 5 4 3 2 1 0        
 * I I I I I I I L___ big Bullets
 * I I I I I I L_____ Auto fire
 * I I I I I L_______ Multi shots
 * I I I I L_________ Shield Generator?
 * I I I L___________ EngineV2
 * I I L_____________ Radar
 * I L_______________ Auto Repair 
 * L_________________ Race Mode
 * */

class Player {       
  public:
    vec2 pos;
    vec2 speed;    
    vec2 reste;
    vec2 target;
    int money;
    byte dir;
    byte turnTimer;
    //unsigned int fuel;
    //unsigned int fuelMax;
    byte armor;
    byte energy;
    byte invincible;
    byte lives;
    bool burn;
    //bool engineV2;
    byte setup;
    /*
     * //TODO: create "State" byte including 
     *    display jauge? lives, burn,...
      */
    //int coolDown;
    //Shot shots[SHOTS_MAX];
    Gun gun;
    //Player() : x(64),y(30),dir(0) {}
    Player(int x, int y, int dir){
      this->pos.x=x;
      this->pos.y=y;
      this->dir=dir;
      money=0;      
      lives=3;
      //this->coolDown=0;
      this->turnTimer=0;
      this->speed=vec2(0,0);
      armor=ARMOR_MAX;
      energy=ENERGY_MAX;
      //fuelMax=TANK_SMALL;
      //fuel=fuelMax;
      reste=vec2(0,0);     
      burn=false; 
      invincible=0;
      //engineV2=false;
    }
    bool Player::draw();
    void Player::drawFlames();
    void Player::drawRetroFlames();
    bool Player::checkcollision(); //return true if armor drops below 0 (but it's unsigned so >200)
    void Player::checkShotscollision();
    void Player::shoot();  
    void Player::mapCenter(bool center);
};

void Player::mapCenter(bool center) {
  pos=vec2(64,32);
  speed=vec2(0,0);
  //elapsedTime=0;
  if (center){
    mapCoord.x = -(MAP_WIDTH / 2 - 64);
    mapCoord.y = -(MAP_HEIGHT / 2 - 32);
  }
  else {
    mapCoord=vec2(50,50);
  }
}

void Player::shoot(){
  gun.shoot(pos,speed,dir);
}
bool Player::draw(){ //(return true if ship dies) --------------------------------------------------------------------DRAW----------------------------------

  if(ab.everyXFrames(3))
    burn=!burn;
  if (invincible>0)
    invincible--;

  //compas
  if (target!=vec2(0,0)){
    //ab.println(target.x);
    //byte dirTemp=trigoInv(pos,target+mapCoord);
    //drawVecLine(trigoVec(dirTemp,19,pos),trigoVec(dirTemp,25,pos));
    //drawVecLine(trigoVec(dirTemp,19,pos),target+mapCoord);
    drawVecLine((pos+(target+mapCoord-pos)/28),(pos+(target+mapCoord-pos)/20));
  }
    
  pos+=((this->speed+this->reste)/SPEED_DIVISOR);
  this->reste=(this->speed+this->reste)%SPEED_DIVISOR;  

  //Background ajust
  if (pos.x<64){
    //int temp = -(sectorLines-1)*IMAGE_HEIGHT);
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
    int temp = -(sectorColumns-1)*IMAGE_WIDTH+64;
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
    //int temp = -(sectorLines-1)*IMAGE_HEIGHT);
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
    int temp = -(sectorLines-1)*IMAGE_HEIGHT+32;
    if (mapCoord.y-(pos.y-32)>temp){
      mapCoord.y-=(pos.y-32);
      pos.y=32;
    }
    else{      
      pos.y+=mapCoord.y-temp;
      mapCoord.y=temp;          
    }      
  }
  //out of bound
  if (pos.x<-sectorBorderMargin || pos.x>168+sectorBorderMargin || pos.y<-sectorBorderMargin || pos.y>64+sectorBorderMargin )
    return true;
      
 //Ship V2 "Half Moon"
  if ((invincible<2)||(burn)){
    //sprites.drawSelfMasked(pos.x-8,pos.y-8,Ship, dir); //Sprites (unmasked) instead of geometrical drawing uses +222 bytes of progmem (1%). Don't know about speed yet. 
    ab.fillCircle(pos.x,pos.y,5);
    ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),3);
    ab.fillCircle(pos.x+trigo(dir,5,true),pos.y+trigo(dir,5,false),2,0);
    ab.drawPixel(pos.x+trigo((dir+1),6,true),pos.y+trigo((dir+1),6,false));
    ab.fillCircle(pos.x+trigo((dir+8),6,true),pos.y+trigo((dir+8),6,false),4,0);
    drawVecLine(pos,trigoVec(invDir(dir),4,pos));
  }
   
  //Fuel jauge
  //drawVecLine(vec2(126,63),vec2(126,63-(fuel/300))); //todo: modify drawTrigoVec (vec2, dir, length){...
  //ab.drawPixel(126,63-(fuelMax/300));  
  
  if (0x80!=(setup&0x80)){ //not in Race mode
    //ARMOR
    drawVecLine(vec2(126,63),vec2(126,63-(armor))); 
    ab.drawPixel(126,63-(ARMOR_MAX));   
  
    //Energy
    drawVecLine(vec2(124,63),vec2(124,63-(energy/5))); 
    ab.drawPixel(124,63-(ENERGY_MAX/5));      
     
    //draw shots
    gun.draw();
  }

  return false;
}

bool Player::checkcollision(){  //return true if armor drops below 0 (but it's unsigned so >200)
  vec2 temp=elementCollision(this->pos,invincible==1? 10:6,magn(this->speed)/10,1);
  if (temp!=vec2(0,0)){
    if (0x80!=(setup&0x80)){ //not in Race mode
      if (98==temp.x){
        money+=10;
      }
      else {
        //ab.drawCircle(this->pos.x,this->pos.y,20);
        if (temp.x!=99){
          if (0==invincible)
            armor-=magn(this->speed)/10; //todo make dmg proportional to speed diference between the 2 objects
          this->speed=temp*2;
        }    
        else { //got hit by an ennemi shot
          if (0==invincible)
            armor-=temp.y;
        }
        if (armor>ARMOR_MAX){
          return true;
        }
      }
    }
    else {
      target=temp;
    }
  }
  return false;
}
void Player::checkShotscollision(){ //not in shot.h because "background.h" needs "shots.h"
  for (int i=0; i<SHOTS_MAX; i++){
    if (gun.shots[i].active>0){
      vec2 temp=elementCollision(gun.shots[i].pos,0,0,gun.dmg);
      if (temp!=vec2(0,0)){ 
        gun.shots[i].explode();
        //gun.shots[i].active=false;
      }
    }
  }
}

void  Player::drawFlames(){  //if both flames at the same time, they aren't animated anymore
  vec2 temp=trigoVec(invDir(dir),burn? 14:12,pos);
  drawVecLine(temp, trigoVec((dir+1),6,temp));
  drawVecLine(temp, trigoVec((dir-1),6,temp));
}

void  Player::drawRetroFlames(){

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
