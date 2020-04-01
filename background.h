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

#define RADAR_POSX 2
#define RADAR_POSY 54


Meteor met[NBMAX_METEOR];

void putMeteor(int nb){
  if (nb>NBMAX_METEOR)
    nb=NBMAX_METEOR;
  for (int i=0; i<nb; i++){
    met[i].active=true;
    met[i].pos.x=120;  //ok, maybe not rand... 
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

void drawRadar(){
  volatile bool blinking;
  if(ab.everyXFrames(5))
    blinking=!blinking;
  ab.fillRect (RADAR_POSX,RADAR_POSY,11,9);//(2,54,21,9);
  ab.drawPixel(RADAR_POSX+5,RADAR_POSY+4,0);
  //ab.drawPixel(RADAR_POSX,RADAR_POSY+8,blinking? 1:0);
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      int temp=(mapCoord.x+met[i].pos.x-58)/IMAGE_WIDTH; //58: IMAGE_WIDTH/2-meteor_image_width/2
      int temp2=(mapCoord.y+met[i].pos.y-26)/IMAGE_HEIGHT;
      
      if ((temp<6&&temp>-6)&&(temp2<5&&temp2>-5)){
        ab.drawPixel(RADAR_POSX+temp+5,4+RADAR_POSY+temp2,blinking? 0:1);
      }
    }
  }
}

void drawBackground(int x, int y, int RandSeed){
  drawStars();//x, y, RandSeed);
  vec2 UperLeftCorner=vec2(1,1);
  //ab.everyXFrames(2)
  ab.drawRect(UperLeftCorner.x,UperLeftCorner.y,MAP_WIDTH,MAP_HEIGHT);
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      met[i].draw();
    }
  }
  drawRadar();
}

vec2 Metcollision(vec2 objPos, int radius, int force, int dmg){ //Circular collision check. objPos must be previously centered. 
  vec2 temp;
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      temp=met[i].pos+mapCoord+vec2(6,6);
      if ((magn(objPos-temp)!=-1)&&(magn(objPos-temp)<(radius+6))){
      //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        //ab.drawCircle(shipPos.x,shipPos.y,20);
        met[i].life-=dmg; //todo check if alive and draw lifeBar
        if (force>0){
          met[i].speed-=(objPos-temp)*force/10;
        }
        return objPos-temp;
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
