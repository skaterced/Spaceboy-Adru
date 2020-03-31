#ifndef _ELEMENT_
#define _ELEMENT_

#include "globals.h"
#include "vec2.h"

#define NBMAX_METEOR 3

class Element {
  public:
    vec2 pos;
    vec2 speed;
    byte dir;
    int life;
    int actif;
    Element() {
      pos=vec2(0,0);
      speed=vec2(0,0);
      dir=0;
      int life=100;
      actif=false;
    }  
    void Element::draw();
};
void Element::draw(){
  ab.setCursor(pos.x+mapCoord.x,pos.y+mapCoord.y);
  ab.print(F("Est-ce que ca marche?"));
}

class Meteor : public Element {
  public:
    void Meteor::draw() {
      if (ab.everyXFrames(2))
        this->pos+=this->speed;
      sprites.drawExternalMask(pos.x+mapCoord.x, pos.y+mapCoord.y, this->life<50? meteor_dmg:meteor, meteor_mask, 0,0);
    }
};


#endif
