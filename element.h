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

#define BH_RADIUS 30

#define METEOR_LIFE 15
#define ENNEMI_SPACEINVADER 0x20
#define SPACEINVADER_LIFE 5
#define ENNEMI_BIGEYEMONSTER 0x40
#define BIGEYEMONSTER_LIFE 20
#define ENNEMI_FLYINGSAUCER 0x60
#define FLYINGSAUCER_LIFE 20
#define ENNEMI_ENNSHIP 0x80
#define ENNSHIP_LIFE 20
#define ENNEMI_BLOB 0xA0
#define ENNEMI_EXPLOSIVE_METEOR 0x00
#define DEFAULT_ENNEMI_LIFE 20

#define CP1 vec2(400,150)
#define CP2 vec2(1200,150)
#define CP3 vec2(800,575)
#define CP4 vec2(400,1000)
#define CP5 vec2(1200,1000)

#define NBMAX_WAVE 5
// WT: Wave Type
//#define WT_HARD 0x01
#define WT_RESPAWN 0x02
#define WT_FROM_LEFT 0x04
#define WT_FORMATION 3

const byte wave1=(ENNEMI_SPACEINVADER|(3<<WT_FORMATION)|WT_FROM_LEFT|WT_RESPAWN);

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
    void update(){
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
    void draw() {
      if (ab.everyXFrames(6)){
        blink=!blink;
        if (active>0)
          active--;
      }
      if (blink){
        ab.fillCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,1);      
      }
      else {
        //ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,1);      
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
    void update() {
            
      ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,13);   
      if (ab.everyXFrames(5)){
          if (++blink>22)
            blink=10;
      }      
      if (active){           
        ab.drawCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,15+(blink-10)*5);              
      }
      if (blink<10)
        ab.fillCircle(this->pos.x+mapCoord.x,this->pos.y+mapCoord.y,13);   //Get filled when you pass the CheckPoint
    }
};

//#ifdef BILLARD_MODE //maybe also in some part of the story mode
class BlackHole {
  public:
  vec2 pos;
  byte blink;
    BlackHole(){
      blink=8;
    }
    void draw() {
      ab.fillCircle(pos.x+mapCoord.x, pos.y+mapCoord.y,BH_RADIUS);      
      /*
      ab.fillCircle(pos.x+mapCoord.x, pos.y+mapCoord.y,blink,0);
      if (--blink<3)
        blink=BH_RADIUS;
        */
    }
};
//#endif
class Element {  
  public:
    vec2 pos;
    vec2 speed;
    vec2 reste;
    byte radius;
    //byte dir; //will add it if needed
    int life;
    bool active;
    Element() {
      pos=vec2(0,0);
      speed=vec2(0,0);
      reste=vec2(0,0);
      //dir=0;
      radius=6;
      life=METEOR_LIFE; 
      active=false;
    }/*
    bool Element::update(){
      //ab.fillRect(pos.x,pos.y,5,5);
    }*/
};

class Meteor : public Element {
  public:
    void draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      ab.fillCircle(pos.x+mapCoord.x, pos.y+mapCoord.y,6,0);      
      sprites.drawSelfMasked(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6,  this->life<(METEOR_LIFE/2)? meteor_dmg:meteor,0); 
      #ifdef BILLARD_MODE
        //"frottement..."
        if (ab.everyXFrames(10)){
          speed-=trigoVec(trigoInv(vec2(0,0),speed),3,vec2(0,0));
        }
        //rebond 
        //TODO:  add rotation
        if (pos.x<6){
          pos.x=-pos.x;
          speed.x=speed.x*(-1);
          reste.x=reste.x*(-1);
        }
        if (pos.x>MAP_WIDTH-6){
          pos.x-=(pos.x-(MAP_WIDTH-6));
          speed.x=speed.x*(-1);
          reste.x=reste.x*(-1);      
        }
        if (pos.y<6){
          
          pos.y=12-pos.y;
          speed.y=speed.y*(-1);
          reste.y=reste.y*(-1);      
        }
        if (pos.y>MAP_HEIGHT-6){
          pos.y-=(pos.y-(MAP_HEIGHT-6));
          speed.y=speed.y*(-1);
          reste.y=reste.y*(-1);    
        }
      #endif
    }
};

class Ennemies : public Element {
  public:
    byte frame;
    byte type;    
    //byte randBytes[10];
    Ennemies():Element(){}
    void reboot(vec2 pos_, vec2 speed_, byte type_){
      active=true;
      pos=pos_;
      speed=speed_;
      type=type_;
      if (ENNEMI_SPACEINVADER==type){
        life=SPACEINVADER_LIFE;
        radius=5;
      }
      else if (ENNEMI_BIGEYEMONSTER==type){
        life=BIGEYEMONSTER_LIFE;
        radius=8;
      }
      else if (ENNEMI_FLYINGSAUCER==type){
        life=FLYINGSAUCER_LIFE;
        radius=8;
      }
      else {
        life=DEFAULT_ENNEMI_LIFE;
        radius=8;
      }
    }
    bool update(void){  //return true if Ennemi is shooting
      vec2 pointD;
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      switch (type){
        case ENNEMI_EXPLOSIVE_METEOR:
          ab.fillCircle(pos.x+mapCoord.x, pos.y+mapCoord.y,6,0);      
          sprites.drawSelfMasked(pos.x+mapCoord.x-6, pos.y+mapCoord.y-6,  this->life<(METEOR_LIFE/2)? meteor_dmg:meteor,0); 
          ab.drawPixel(pos.x+mapCoord.x-3, pos.y+mapCoord.y-3);
        break;
        case ENNEMI_SPACEINVADER: default:
          //this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          //this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
          sprites.drawSelfMasked(pos.x+mapCoord.x-5, pos.y+mapCoord.y-4, spaceInvader_sprite, frame);
          if (ab.everyXFrames(5))
            frame=frame==0? 1:0;      
        break;      
        case ENNEMI_FLYINGSAUCER:
          //this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          //this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
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
          //this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
          //this->reste=(this->reste+this->speed)%SPEED_DIVISOR;

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
    bool update(){
      //ab.fillCircle(pos.x,pos.y,4);  
      //ab.fillCircle(pos.x+mapCoord.x+type+2*((frame>>0)&0x0F)%4-8,pos.y+type+mapCoord.y+(((frame>>1)&0x0F)%4-4),type-1);  
      /*
       //" Loto Balls"
       if (ab.everyXFrames(10)){
        //for (int i=0;i<18;i++){
          type=random(254);        
      }
      if (ab.everyXFrames(3)){
        if(++frame>15)
           frame=0;
      }
      vec2 temp;
      temp=pos+mapCoord+trigoVec(-frame,((type>>0)&0x07)+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+4,((type>>1)&0x07)+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      //temp=pos+mapCoord+trigoVec(frame+7,(type>>2)&0x07+3,vec2(0,0));      
      //ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+11,((type>>3)&0x07)+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+15,((type>>4)&0x07)+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);*/

      if (ab.everyXFrames(3)){
        frame++;
      }
      vec2 temp;
      temp=pos+mapCoord+trigoVec(-frame,frame%5+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+4,(frame+pos.x)%4+3,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      //temp=pos+mapCoord+trigoVec(frame%16+7,(type>>2)&0x07+3,vec2(0,0));      
      //ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+11,-(frame+pos.y)%5+2,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      temp=pos+mapCoord+trigoVec(frame+15,frame%3,vec2(0,0));      
      ab.fillCircle(temp.x,temp.y,2);
      return false;
    }
    void grow(){
      type+=10;
    }
    
};
/* 
 * wave type 
 * 7 6 5 4 3 2 1 0        NDY : (Not Defined Yet)
 * I I I I I I I L___ lucky? NDY
 * I I I I I I L_______ respawn if out of screen
 * I I I I I L___________ from west
 * I I I I L_________ 
 * I I I L___________ \____ formation
 * I I L_____________ 
 * I L_______________\
 * L_________________ \____ Monsters type
 */
 
class Waves{ 
  public:
    //Ennemi boss;
    byte waveType[NBMAX_WAVE];
    byte it;
    Waves(){
      //type=type;
    }
    byte actual(){
      return waveType[it];
    }
    bool next(){
      if (0==waveType[it]||(it==(NBMAX_WAVE-1)))
        return false;
      it++;
      return true;
    }
    void init(byte toto){
    //const byte wave1=(ENNEMI_SPACEINVADER|0x3<<WT_FORMATION|WT_FROM_LEFT|WT_RESPAWN);
      it=0;
      waveType[0]=(ENNEMI_EXPLOSIVE_METEOR|(1<<WT_FORMATION));
      waveType[1]=wave1;
      waveType[2]=(ENNEMI_SPACEINVADER|(3<<WT_FORMATION)|WT_RESPAWN);
      waveType[3]=(ENNEMI_BIGEYEMONSTER|(1<<WT_FORMATION));
      waveType[4]=(ENNEMI_FLYINGSAUCER|(1<<WT_FORMATION));
    }
};

#endif
