#ifndef _ELEMENT_
#define _ELEMENT_

#include "globals.h"
#include "vec2.h"

#define NBMAX_METEOR 3
#define NBMAX_ENNEMIS 10

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
      int life=100;
      active=false;
    }  
    void Element::draw();
};
void Element::draw(){
  //ab.setCursor(pos.x+mapCoord.x,pos.y+mapCoord.y);
  //ab.print(F("Est-ce que ca marche?"));
}

class Meteor : public Element {
  public:
    void Meteor::draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      sprites.drawExternalMask(pos.x+mapCoord.x, pos.y+mapCoord.y, this->life<50? meteor_dmg:meteor, meteor_mask, 0,0);
    }
};

class Ennemis : public Element {
};

class SpaceInvader : public Ennemis {  
  public:
    boolean blink ;  //because he's got only 2 frames
    void SpaceInvader::draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      sprites.drawSelfMasked(pos.x+mapCoord.x, pos.y+mapCoord.y, spaceInvader_sprite, blink? 0:1);
      if (ab.everyXFrames(5))
        blink=!blink;
    }
};
/*
class SpaceInvader : public Ennemis {  
  public:
    boolean blink ;  //because he's got only 2 frames
    void SpaceInvader::draw() {
      this->pos+=(this->reste+this->speed)/SPEED_DIVISOR;
      this->reste=(this->reste+this->speed)%SPEED_DIVISOR;
      sprites.drawSelfMasked(pos.x+mapCoord.x, pos.y+mapCoord.y, spaceInvader_sprite, blink? 0:1);
      if (ab.everyXFrames(5))
        blink=!blink;
    }
};
*/
#endif
