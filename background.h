#ifndef _BACKGROUND_
#define _BACKGROUND_

#include "globals.h"
#include "sprites.h"
#include "vec2.h"
#include "trigo.h"
#include "element.h"
#include "station.h"

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

#define SECTOR_COLUMNS 10
#define SECTOR_LINES  20

#define MAP_WIDTH SECTOR_COLUMNS*IMAGE_WIDTH
#define MAP_HEIGHT SECTOR_LINES*IMAGE_HEIGHT

#define RADAR_POSX 2
#define RADAR_POSY 54


Meteor met[NBMAX_METEOR];
Ennemis enn[NBMAX_ENNEMIS];
Explosion xplo[NBMAX_EXPLOSION];
byte xploIt=0;
/*
Station home=Station (vec2(300,300));
bool station_active=false;
 */

void putMeteor(vec2 pos, vec2 speed){  
  for (int i=0; i<NBMAX_METEOR; i++){
    if (!met[i].active){
      met[i].active=true;
      met[i].pos=pos;  //ok, maybe not rand... 
      //met[i].pos.y=50;
      met[i].life=METEOR_LIFE;
      met[i].speed=speed;
      return 0;
    }
  }
}
/*
void putStation(void){
  station_active=true;
}
*/

//todo change all that -> make Ennemis subClasses and an ennemis constructor
void putEnnemis(vec2 pos, vec2 speed, byte type){

  for (int i=0; i<NBMAX_ENNEMIS; i++){
    if (!enn[i].active){   
      enn[i].reboot(pos,speed,type);
      i=NBMAX_ENNEMIS;
    }
  }
}

void explode(vec2 pos, byte type){
  xplo[xploIt].type=type;
  xplo[xploIt].pos=pos;
  xplo[xploIt].count=0;
  if (++xploIt>=NBMAX_EXPLOSION)
    xploIt=0;
}

void mapCenter(){
  mapCoord.x=-(MAP_WIDTH/2-64);
  mapCoord.y=-(MAP_HEIGHT/2-32);
}

//void drawStars(int x, int y, int RandSeed){ //camera X,Y
void drawStars(int randSeed){ //int x, int y, int RandSeed){
  //randomSeed(randSeed);
  byte temp=0;
  for (int i=0; i<SECTOR_COLUMNS; i++){
    for (int j=0; j< SECTOR_LINES; j++){
      if (++temp>3)
        temp=0;
      sprites.drawSelfMasked(mapCoord.x+i*IMAGE_WIDTH,mapCoord.y+j*IMAGE_HEIGHT,stars,temp);
    }
  }
   
/*  for (int i=0; i<SECTOR_COLUMNS; i++){ 
    for (int j=0; j< SECTOR_LINES; j++){
      byte temp=random(15)+1;
      for (int k=0;k<4;k++){
        if (temp&(8>>k)==(8>>k))
          sprites.drawSelfMasked(mapCoord.x+i*IMAGE_WIDTH,mapCoord.y+j*IMAGE_HEIGHT,stars,k); //nice idea but no...
      } 
    }
  }  */  
}

void drawRadar(){
  volatile bool blinking;
  volatile bool slowBlinking;
  volatile bool fastBlinking;
  if(ab.everyXFrames(5))
    blinking=!blinking;
  if(ab.everyXFrames(10))
    slowBlinking=!slowBlinking;
  if(ab.everyXFrames(3))
    fastBlinking=!fastBlinking;    
  ab.fillRect (RADAR_POSX,RADAR_POSY,11,9);//(2,54,21,9);
  ab.drawPixel(RADAR_POSX+5,RADAR_POSY+4,0);
  ab.drawLine(RADAR_POSX-1,RADAR_POSY-1,RADAR_POSX-1,RADAR_POSY+1); // corners
  ab.drawLine(RADAR_POSX-1,RADAR_POSY-1,RADAR_POSX+1,RADAR_POSY-1);
  ab.drawLine(RADAR_POSX+11,RADAR_POSY-1,RADAR_POSX+11,RADAR_POSY+1);
  ab.drawLine(RADAR_POSX+11,RADAR_POSY-1,RADAR_POSX+9,RADAR_POSY-1);
  ab.drawLine(RADAR_POSX-1,RADAR_POSY+9,RADAR_POSX-1,RADAR_POSY+7);
  ab.drawLine(RADAR_POSX-1,RADAR_POSY+9,RADAR_POSX+1,RADAR_POSY+9);  
  ab.drawLine(RADAR_POSX+11,RADAR_POSY+9,RADAR_POSX+11,RADAR_POSY+7);
  ab.drawLine(RADAR_POSX+11,RADAR_POSY+9,RADAR_POSX+9,RADAR_POSY+9);

  //SECTOR BORDER
  int temp=(mapCoord.x-64)/IMAGE_WIDTH;
  int temp2=(mapCoord.y-32)/IMAGE_HEIGHT;
  if (temp>-5){
    ab.fillRect(RADAR_POSX,RADAR_POSY,temp+5,9,0);
  }
  else if (temp<-(SECTOR_COLUMNS-6)){
    temp+=(SECTOR_COLUMNS-6);
    ab.fillRect(RADAR_POSX+temp+11,RADAR_POSY,-temp,9,0);
  }
  if (temp2>-4){
    ab.fillRect(RADAR_POSX,RADAR_POSY,11,temp2+4,0);
  }
  else if (temp2<-(SECTOR_LINES-5)){
    temp2+=(SECTOR_LINES-5);
    ab.fillRect(RADAR_POSX,RADAR_POSY+temp2+9,11,-temp2,0);
  }
      
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      temp=(mapCoord.x+met[i].pos.x-58)/IMAGE_WIDTH; //58: IMAGE_WIDTH/2-meteor_image_width/2
      temp2=(mapCoord.y+met[i].pos.y-26)/IMAGE_HEIGHT;
      
      if ((temp<6&&temp>-6)&&(temp2<5&&temp2>-5)){
        ab.drawPixel(RADAR_POSX+temp+5,4+RADAR_POSY+temp2,blinking? 0:1);
      }
    }
  }
  for (int i=0; i<NBMAX_ENNEMIS; i++){
    if (enn[i].active){
      temp=(mapCoord.x+enn[i].pos.x-58)/IMAGE_WIDTH; //pos adjust. from meteor but...
      temp2=(mapCoord.y+enn[i].pos.y-26)/IMAGE_HEIGHT;
      
      if ((temp<6&&temp>-6)&&(temp2<5&&temp2>-5)){
        ab.drawPixel(RADAR_POSX+temp+5,4+RADAR_POSY+temp2,fastBlinking? 0:1);
      }
    }
  }  
  /*
  if (station_active){ //not in radar anymore because it will be in a cut scene
    temp=(mapCoord.x+home.pos.x-49)/IMAGE_WIDTH; //58: IMAGE_WIDTH/2-station_image_width/2= -64 +15
    temp2=(mapCoord.y+home.pos.y+3)/IMAGE_HEIGHT; //  - 32  +35
    if ((temp<6&&temp>-6)&&(temp2<5&&temp2>-5)){
      ab.drawPixel(RADAR_POSX+temp+5,4+RADAR_POSY+temp2,slowBlinking? 0:1);
    }
  }
  */
}

void drawBackground(int x, int y, int RandSeed){
  drawStars(RandSeed);//x, y, RandSeed);
 
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      met[i].draw();
    }
  }
  for (int i=0; i<NBMAX_ENNEMIS; i++){
    if (enn[i].active){
      enn[i].update();
    }
  }
  for (int i=0;i<NBMAX_EXPLOSION;i++){
    xplo[i].update();
  }

  drawRadar();
}

//todo: add Dmg to both side depending on the speed difference
vec2 elementCollision(vec2 objPos, int radius, int force, int dmg){ //Circular collision check. objPos must be previously centered. 
  //vec2 temp;
  for (int i=0; i<NBMAX_METEOR; i++){
    if (met[i].active){
      
      if ((magn(objPos-met[i].pos-mapCoord)!=-1)&&(magn(objPos-met[i].pos-mapCoord)<(radius+6))){
      //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        met[i].life-=dmg; //todo draw lifeBar ?
        if (met[i].life<=0){
          met[i].active=false;
          explode(met[i].pos,EXPLOSION_MEDIUM);
          //todo: add gem
        }
        if (force>0){
          met[i].speed-=(objPos-met[i].pos-mapCoord)*force/10;
        }
        return objPos-met[i].pos-mapCoord;
      }
    }
  }
  for (int i=0; i<NBMAX_ENNEMIS; i++){
    if (enn[i].active){
      byte temp;
      if (ENNEMIS_BIGEYEMONSTER==enn[i].type){
        temp=8;
      }
      else
        temp=5;
      if ((magn(objPos-enn[i].pos-mapCoord)!=-1)&&(magn(objPos-enn[i].pos-mapCoord)<(radius+temp))){      
        enn[i].life-=dmg; //todo draw lifeBar ?
        if (enn[i].life<=0){
          enn[i].active=false;
          explode(enn[i].pos, EXPLOSION_MEDIUM);
          //todo: add gem
        }
        if (force>0){
          enn[i].speed-=(objPos-enn[i].pos-mapCoord)*force/10;
        }
        return objPos-enn[i].pos-mapCoord;
      }
    }
  }  
  return vec2(0,0);
}


/*
void drawMeteor(vec2 pos, bool dmg){  // to erase...
  sprites.drawExternalMask(pos.x, pos.y, dmg? meteor_dmg:meteor, meteor_mask, 0,0);
}
*/


#endif
 
