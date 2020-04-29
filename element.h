/* Contains Explosion, Element -> Meteor, Ennemies ->...
 *  
 */

#ifndef _ELEMENT_
#define _ELEMENT_

#include "globals.h"
#include "vec2.h"
#include "sprites.h"

#define EXPLOSION_SMALL 1
#define EXPLOSION_MEDIUM 2
#define EXPLOSION_BIG 3

#define METEOR_LIFE 10
#define ENNEMI_SPACEINVADER 1
#define SPACEINVADER_LIFE 5
#define ENNEMI_BIGEYEMONSTER 2
#define BIGEYEMONSTER_LIFE 20
#define ENNEMI_FLYINGSAUCER 3
#define FLYINGSAUCER_LIFE 20
#define ENNEMI_ENNSHIP 4
#define ENNSHIP_LIFE 20
#define ENNEMI_BLOB 5
#define DEFAULT_ENNEMI_LIFE 20

#define CP1 vec2(400,150)
#define CP2 vec2(1200,150)
#define CP3 vec2(800,575)
#define CP4 vec2(400,1000)
#define CP5 vec2(1200,1000)


class Explosion {
  public:
    vec2 pos;
    byte type;
    byte count;
    Explosion(){
      type=0;
      pos=vec2(0,0);
      count=50; //means inactive
    }
    /*Explosion::explode(vec2 pos_, int type_){
      type=type_;
      pos=pos_;    
      count=0;
    }*/
    Explosion::update(){
      if (count<18){
        count++;
        
        switch(type){
        case EXPLOSION_BIG:
          if (count<6){ //big
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,2+count*2);
          }
          else if (count<18){
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,13);
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,count-6,0);      
          }
        break;
        case EXPLOSION_MEDIUM:    
          if (count<6){ //medium
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,count+1);
          }
          else if (count<17){
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,7);
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,count-6,0);      
          }
        break;
        case EXPLOSION_SMALL:
          if (count<4){ //small
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,count);
          }
          else if (count<13){
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,4);
            ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,count-4,0);
          }
        break;
        default:
        break;
        }  
      }
    }
};

class Gem {
  public:
    vec2 pos;
    bool blink;
    byte active;
    Gem(){
      active=0;
    }
    void Gem::draw() {
      if (ab.everyXFrames(6)){
        blink=!blink;
        if (active>0)
          active--;
      }
      if (blink){
        ab.fillCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,1);      
      }
      else {
        ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,1);      
      }
    }
};

class CheckPoint {
  public:
    vec2 pos;
    byte blink;
    //byte number; //to get them in the right order ?
    bool active;
    bool last; //if this is true, it triggers something when the ship touches it
    CheckPoint(){
      pos=vec2(0,0);
      active=false;
      blink=10;
      last=false;
    }
    /*CheckPoint(vec2 pos){
      pos=pos;
      active=false;
      blink=0;
      last=false;
    }*/
    void CheckPoint::update() {
            
      ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,13);   
      if (ab.everyXFrames(5)){
          if (++blink>22)
            blink=10;
      }      
      if (active){           
        ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,15+blink*5);              
      }
      if (blink<10)
        ab.fillCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,13);   //Get filled when you pass the CheckPoint
    }
};

class Element {  
  public:
    vec2 pos;
    vec2 speed;
    vec2 reste;
    //byte dir; //will add it if needed
    int life;
    int active;
    Element() {
      pos=vec2(0,0);
      speed=vec2(0,0);
      reste=vec2(0,0);
      //dir=0;
      int life=METEOR_LIFE; 
      active=false;
    }
};

class Meteor : public Element {
  public:
    void Meteor::draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      ab.fillCircle(pos.x+mapCoord.x, pos.y+mapCoord.y,6,0);      
      sprites.drawSelfMasked(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6,  this->life<(METEOR_LIFE/2)? meteor_dmg:meteor,0); 
      //sprites.drawExternalMask(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6, this->life<(METEOR_LIFE/2)? meteor_dmg:meteor, meteor_mask, 0,0); //mask is "drooling". Don't know why...
      //mask is "leaking" on the left side. No idea why. 
    }
};

class Ennemies : public Element {
  public:
    byte frame;
    byte type;    
    //byte randBytes[10];
    Ennemies():Element(){}
    Ennemies::reboot(vec2 pos_, vec2 speed_, byte type_){
      active=true;
      pos=pos_;
      speed=speed_;
      type=type_;
      if (ENNEMI_SPACEINVADER==type){
        life=SPACEINVADER_LIFE;
      }
      else if (ENNEMI_BIGEYEMONSTER==type){
        life=BIGEYEMONSTER_LIFE;
      }
      else if (ENNEMI_FLYINGSAUCER==type){
        life=FLYINGSAUCER_LIFE;
      }
      else life=DEFAULT_ENNEMI_LIFE;
    }
    bool Ennemies::update(void){  //return true if Ennemi is shooting
      vec2 pointD;
      switch (type){
        case ENNEMI_SPACEINVADER: default:
          this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
          sprites.drawSelfMasked(pos.x+mapCoord.x-5, pos.y+mapCoord.y-4, spaceInvader_sprite, frame);
          if (ab.everyXFrames(5))
            frame=frame==0? 1:0;        
        break;      
        case ENNEMI_FLYINGSAUCER:
          this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
          if (ab.everyXFrames(5)){
            frame++;   
            if (frame>7)
              frame=0;  
          }              
          //sprites.drawSelfMasked(pos.x+mapCoord.x-8,pos.y+mapCoord.y-7,monster,frame);
          ab.fillCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,6);          
          ab.fillCircle(pos.x+mapCoord.x,pos.y+mapCoord.y,2,0);
          ab.drawPixel(pos.x+mapCoord.x+1,pos.y+mapCoord.y-1,3);          
          pointD=trigoVec(frame,5,this->pos+mapCoord);
          ab.drawPixel(pointD.x,pointD.y,0);
          pointD=trigoVec(frame+8,5,this->pos+mapCoord);
          ab.drawPixel(pointD.x,pointD.y,0);          
          pointD=trigoVec(trigoInv(this->pos+mapCoord,vec2(64,32)),5,this->pos+mapCoord);
          if (ab.everyXFrames(80)){
            if ((magn(vec2(64,32)-pos-mapCoord)==-1)||(magn(vec2(64,32)-pos-mapCoord)>35))
              this->speed=(pointD-this->pos-mapCoord)*3;
            else {
              this->speed=vec2(0,0);
              return true;
            }
          } 
        break;
        case ENNEMI_BIGEYEMONSTER:
          this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
          if (ab.everyXFrames(10)){
            frame++;   
            if (frame>4)
              frame=0;  
          }              
          sprites.drawSelfMasked(pos.x+mapCoord.x-8,pos.y+mapCoord.y-7,monster,frame);
          //int temp=trigoInv(pos+mapCoord,vec2(64,32));
          //vec2 pointD=trigoVec(temp,4,pos)+mapCoord;
          pointD=trigoVec(trigoInv(this->pos+mapCoord,vec2(64,32)),4,this->pos+vec2(0,-4)+mapCoord);
          //if (abs(temp-8)<3)
          //pointD+=vec2(0,-1);
          ab.drawRect(pointD.x-1,pointD.y,3,2,0);
          ab.drawPixel(pointD.x,pointD.y);
          if (ab.everyXFrames(2))
            this->speed=(pointD-this->pos-mapCoord+vec2(0,5))*3;                    
        break;
        case ENNEMI_BLOB:        
          for (int i=0; i<5; i++){
            ab.fillCircle(pos.x+mapCoord.x+2*((frame>>i)&0x07)-8,pos.y+mapCoord.y+(((frame>>(i+1))&0x07)-4),2);  
          }
          if (ab.everyXFrames(10)){
            for (int i=0;i<6;i++){
              frame=random(254);
            }
          }
        break;
        case ENNEMI_ENNSHIP:
          this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          this->reste=(this->reste+this->speed)%SPEED_DIVISOR;

        break;      
      }
    return false;
    }    
};

class Blob : public Ennemies {
  private:
    //byte randBytes[10];
  public:
  Blob(){
    type=3;
  }
    bool Blob::update(){
      //ab.fillCircle(pos.x,pos.y,4);  
      /*
      for (int i=0; i<5; i++){
        ab.fillCircle(pos.x+2*(randBytes[i]-4),pos.y+(randBytes[i+1]-4),2);  
      }
      if (ab.everyXFrames(10)){
        for (int i=0;i<6;i++){
          randBytes[i]=random(8);
        }
      }
      */
      /*
      for (int i=0; i<5; i++){
        ab.fillCircle(pos.x+mapCoord.x+2*((frame>>i)&0x07)-8,pos.y+mapCoord.y+(((frame>>(i+1))&0x07)-4),2);          
      }*/
      if (ab.everyXFrames(10)){
        for (int i=0;i<6;i++){
          frame=random(254);
        }
      }
      ab.fillCircle(pos.x+mapCoord.x+type+2*((frame>>0)&0x0F)%4-8,pos.y+type+mapCoord.y+(((frame>>1)&0x0F)%4-4),type-1);  
      ab.fillCircle(pos.x+mapCoord.x+type+2*((frame>>1)&0x0F)%4-8,pos.y-type+mapCoord.y+(((frame>>3)&0x0F)%4-4),type-1);  
      ab.fillCircle(pos.x+mapCoord.x-type+2*((frame>>2)&0x0F)%4-8,pos.y+type+mapCoord.y+(((frame>>4)&0x0F)%4-4),type-1);  
      ab.fillCircle(pos.x+mapCoord.x-type+2*((frame>>3)&0x0F)%4-8,pos.y-type+mapCoord.y+(((frame>>2)&0x0F)%4-4),type-1);  
      ab.fillCircle(pos.x+mapCoord.x+2*((frame>>4)&0x0F)%4-8,pos.y+mapCoord.y+(((frame>>5)&0x0F)%4-4),type-1);  
      return false;
    }
    void Blob::grow(){
      type+=10;
    }
    
};

#endif
