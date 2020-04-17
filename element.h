/* Contains Explosion, Element -> Meteor, Ennemis ->...
 *  
 */

#ifndef _ELEMENT_
#define _ELEMENT_

#include "globals.h"
#include "vec2.h"

#define NBMAX_METEOR 10
#define METEOR_LIFE 10
#define NBMAX_ENNEMIS 10
#define NBMAX_EXPLOSION 5

#define EXPLOSION_SMALL 1
#define EXPLOSION_MEDIUM 2
#define EXPLOSION_BIG 3

#define ENNEMIS_SPACEINVADER 1
#define SPACEINVADER_LIFE 5
#define ENNEMIS_BIGEYEMONSTER 2
#define BIGEYEMONSTER_LIFE 20
#define ENNEMIS_FLYINGSAUCER 3
#define FLYINGSAUCER_LIFE 20

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
    Explosion::explode(vec2 pos_, int type_){
      type=type_;
      pos=pos_;    
      count=0;
    }
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
    }/*
    Element (vec2 pos, vec2 speed){
      pos=pos;
      speed=speed;
      reste=vec2(0,0);
      //dir=0;
      int life=METEOR_LIFE; 
      active=false;      
    }*/
    //void Element::draw();
};

class Meteor : public Element {
  public:
    void Meteor::draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      //ab.fillCircle(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6,6,0);      
      //sprites.drawSelfMasked(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6, this->life<50? meteor_dmg:meteor,0); //uses more memory!?
      sprites.drawExternalMask(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6, this->life<(METEOR_LIFE/2)? meteor_dmg:meteor, meteor_mask, 0,0); //doesn't work properly but ok...
      //mask is "leaking" on the left side. No idea why. 
    }
};

class Ennemis : public Element {
  public:
    byte frame;
    byte type;
    Ennemis():Element(){}
    Ennemis::reboot(vec2 pos_, vec2 speed_, byte type_){
      active=true;
      pos=pos_;
      speed=speed_;
      type=type_;
      if (ENNEMIS_SPACEINVADER==type){
        life=SPACEINVADER_LIFE;
      }
      else if (ENNEMIS_BIGEYEMONSTER==type){
        life=BIGEYEMONSTER_LIFE;
      }
      else if (ENNEMIS_FLYINGSAUCER==type){
        life=FLYINGSAUCER_LIFE;
      }      
    }
    bool Ennemis::update(void){
      vec2 pointD;
      switch (type){
        case ENNEMIS_SPACEINVADER: default:
          this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
          sprites.drawSelfMasked(pos.x+mapCoord.x-5, pos.y+mapCoord.y-4, spaceInvader_sprite, frame);
          if (ab.everyXFrames(5))
            frame=frame==0? 1:0;        
        break;      
        case ENNEMIS_FLYINGSAUCER:
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
        case ENNEMIS_BIGEYEMONSTER:
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
      }
    return false;
    }    
};


#endif
