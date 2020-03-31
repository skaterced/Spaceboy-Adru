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

#define SECTOR_COLUMNS 10
#define SECTOR_LINES  20

#define MAP_WIDTH 1280
#define MAP_HEIGHT 1280

Meteor met[NBMAX_METEOR];

void putMeteor(int nb){
  if (nb>NBMAX_METEOR)
    nb=NBMAX_METEOR;
  for (int i=0; i<nb; i++){
    met[i].actif=true;
    met[i].pos.x=80;  //ok, maybe not rand... 
    met[i].pos.y=50;
    met[i].life=100;
    //met[i].speed=vec2(1,0);
  }
}

void mapCenter(){
  mapCoord.x=-(MAP_WIDTH/2-64);
  mapCoord.y=-(MAP_HEIGHT/2-32);
}

//void drawStars(int x, int y, int RandSeed){ //camera X,Y
void drawStars(){ //int x, int y, int RandSeed){
  //randomSeed(RandSeed);

  for (int i=0; i<SECTOR_COLUMNS; i++){
    for (int j=0; j< SECTOR_LINES; j++){
      sprites.drawSelfMasked(mapCoord.x+i*IMAGE_WIDTH,mapCoord.y+j*IMAGE_HEIGHT,stars_01,0);
    }
  }
  /*
  sprites.drawSelfMasked(mapCoord.x,mapCoord.y,stars_01,0);
  sprites.drawSelfMasked(mapCoord.x+IMAGE_WIDTH,mapCoord.y,stars_02,0);
  sprites.drawSelfMasked(mapCoord.x+IMAGE_WIDTH,mapCoord.y+IMAGE_HEIGHT,stars_03,0);
  sprites.drawSelfMasked(mapCoord.x,mapCoord.y+IMAGE_HEIGHT,stars_04,0);
  
  for (int i=0; i<NB_STARS_PER_LAYER ; i++){
    int tempX=random(MAP_WIDTH)+x;
    int tempY=random(MAP_HEIGHT)+y;
    if (0<tempX && tempX<MAP_WIDTH && 0<tempY && tempY<MAP_HEIGHT)
      ab.drawPixel(tempX,tempY);
  }
  */
}

void drawBackground(int x, int y, int RandSeed){
  drawStars();//x, y, RandSeed);
    for (int i=0; i<NBMAX_METEOR; i++){
      if (met[i].actif)
        met[i].draw();
    }
}

vec2 MetColision(vec2 shipPos){
  vec2 temp;
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].actif){
      temp=met[i].pos+mapCoord+vec2(6,6);
      if (magn(shipPos-temp)<12){
      //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        //ab.drawCircle(shipPos.x,shipPos.y,20);
        return shipPos-temp;
      }
    }
  }
  temp=vec2(0,0);
  return temp;
}


/*
void drawMeteor(vec2 pos, bool dmg){  // to erase...
  sprites.drawExternalMask(pos.x, pos.y, dmg? meteor_dmg:meteor, meteor_mask, 0,0);
}
*/
void drawVecLine(vec2 A, vec2 B){
  ab.drawLine(A.x,A.y,B.x,B.y);
}

#endif
