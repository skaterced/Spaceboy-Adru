#ifndef _BACKGROUND_
#define _BACKGROUND_

#include "globals.h"
#include "sprites.h"
#include "vec2.h"
#include "element.h"

#define NB_STARS_PER_LAYER 100 //per layer...
#define NB_LAYERS 3

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

#define MAP_WIDTH 2000
#define MAP_HEIGHT 1000

Meteor met[NBMAX_METEOR];

void putMeteor(int nb){
  if (nb>NBMAX_METEOR)
    nb=NBMAX_METEOR;
  for (int i=0; i<nb; i++){
    met[i].actif=true;
    met[i].pos.x=10;  //ok, maybe not rand... 
    met[i].pos.y=100;
    met[i].life=100;
    met[i].speed=vec2(1,0);
  }
}

void mapCenter(){
  mapCoord.x=MAP_WIDTH/2-64;
  mapCoord.y=MAP_HEIGHT/2-32;
}

void drawStars(int x, int y, int RandSeed){ //camera X,Y
  //ab.drawBitmap(mapCoord.x,mapCoord.y,stars_01,IMAGE_WIDTH,IMAGE_HEIGHT,WHITE);
  sprites.drawSelfMasked(mapCoord.x,mapCoord.y,stars_01,0);
  sprites.drawSelfMasked(mapCoord.x+IMAGE_WIDTH,mapCoord.y,stars_02,0);
  sprites.drawSelfMasked(mapCoord.x+IMAGE_WIDTH,mapCoord.y+IMAGE_HEIGHT,stars_03,0);
  sprites.drawSelfMasked(mapCoord.x,mapCoord.y+IMAGE_HEIGHT,stars_04,0);
  randomSeed(RandSeed);
  for (int i=0; i<NB_STARS_PER_LAYER ; i++){
    int tempX=random(MAP_WIDTH)+x;
    int tempY=random(MAP_HEIGHT)+y;
    if (0<tempX && tempX<MAP_WIDTH && 0<tempY && tempY<MAP_HEIGHT)
      ab.drawPixel(tempX,tempY);
  }
}

void drawBackground(int x, int y, int RandSeed){
  drawStars(x, y, RandSeed);
    for (int i=0; i<NBMAX_METEOR; i++){
      if (met[i].actif)
        met[i].draw();
    }
}
void drawMeteor(vec2 pos, bool dmg){  // to erase...
  sprites.drawExternalMask(pos.x, pos.y, dmg? meteor_dmg:meteor, meteor_mask, 0,0);
}

void drawVecLine(vec2 A, vec2 B){
  ab.drawLine(A.x,A.y,B.x,B.y);
}

#endif
