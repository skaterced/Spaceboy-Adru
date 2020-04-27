#ifndef _BACKGROUND_
#define _BACKGROUND_

#include "globals.h"
#include "sprites.h"
#include "vec2.h"
#include "trigo.h"
#include "element.h"
#include "station.h"
#include "shot.h"

#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

/*
#define SECTOR_COLUMNS 12
#define SECTOR_LINES  20
*/
byte SECTOR_COLUMNS=12;   //to have several map size
byte SECTOR_LINES=20;

#define MAP_WIDTH SECTOR_COLUMNS*IMAGE_WIDTH
#define MAP_HEIGHT SECTOR_LINES*IMAGE_HEIGHT

#define RADAR_POSX 2
#define RADAR_POSY 54

#define STARS_PER_SCREEN 9
#define STARS_TOT 58

#define NBMAX_METEOR 10
#define NBMAX_ENNEMI 10
#define NBMAX_EXPLOSION 3
#define NBMAX_GEM 5
#define NBMAX_CP 10

// TODO: Add a "sectorInit()"


//const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9}; //42 -> 21190
const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9,39,49,63,10,25,52,41,10,52,53,23,13,2,40,57,0};//,48,26,43,41,30,3,61};//,0,17,58,28,48,18,6}; //72 -> 21220

Meteor met[NBMAX_METEOR];
Ennemies enn[NBMAX_ENNEMI];
Shot ennShot;
Explosion xplo[NBMAX_EXPLOSION];
byte xploIt = 0;
Gem gems[NBMAX_GEM];
//CheckPoint CP[3]={vec2(100,100), vec2(700,700), vec2(900,900)};
CheckPoint CP[NBMAX_CP];
unsigned int elapsedtime=0;

byte sectorType;
/* 7 6 5 4 3 2 1 0        NDY : (Not Defined Yet)
 * I I I I I I I L___ in race Mode: Race finished
 * I I I I I I L_____ NDY
 * I I I I I L_______ NDY
 * I I I I L_________ NDY
 * I I I L___________ 
 * I I L_____________ \____ Size: 00 9x18, 01 12x20, 10 ?x?, 11 continuous?
 * I L_______________ 
 * L_________________ \____ Mode: 00 normal, 01 hard? 10 Race, 11 Rescue, 
 * 
 * size 
 * Race
 * Rescue mission 
 * 
 * Meteor activated ?
 * Ennemi X activated ?
 * ammount of waves ?
 */

//CP[0].active=true;
/*
  Station home=Station (vec2(300,300));
  bool station_active=false;
*/
bool isOut(vec2 pos) {
  if ((-128 > pos.x) || pos.x > MAP_WIDTH || (-64 > pos.y) || pos.y > MAP_HEIGHT)
    return true;
  else
    return false;
}
void putMeteor(vec2 pos, vec2 speed) {
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (!met[i].active) {
      met[i].active = true;
      met[i].pos = pos;
      met[i].life = METEOR_LIFE;
      met[i].speed = speed;
      i = 99;
    }
  }
}
/*
  void putStation(void){
  station_active=true;
  }
*/

void putEnnemies(vec2 pos, vec2 speed, byte type) {

  for (int i = 0; i < NBMAX_ENNEMI; i++) {
    if (!enn[i].active) {
      enn[i].reboot(pos, speed, type);
      i = NBMAX_ENNEMI;
    }
  }
}

void sectorInit(byte type){ //, byte difficulty){
  sectorType=type;
  if (0x80==(type&0x80)){
    CP[0].active=true;      
    //   1 4
    //   3 2
    CP[0].pos=vec2(400,150);  
    CP[1].pos=vec2(1200,1000);
    CP[2].pos=vec2(400,1000);
    CP[3].pos=vec2(1200,150);
    CP[4].pos=vec2(400,150);    //2nd lap
    CP[5].pos=vec2(1200,1000);
    CP[6].pos=vec2(400,1000);
    CP[7].pos=vec2(1200,150);    
    CP[8].pos=vec2(400,150);    //finish
    /*
    // 'Z' shape
    CP[0].pos=vec2(300,150);  
    CP[3].pos=vec2(1200,1000);
    CP[2].pos=vec2(300,1000);
    CP[1].pos=vec2(1200,150);
    CP[4].pos=vec2(300,150);    //2nd lap
    CP[7].pos=vec2(1200,1000);
    CP[6].pos=vec2(300,1000);
    CP[5].pos=vec2(1200,150);    
    CP[8].pos=vec2(300,150);    //finish
    // 'O' shape
    CP[0].pos=vec2(300,150);  
    CP[2].pos=vec2(1200,1000);
    CP[3].pos=vec2(300,1000);
    CP[1].pos=vec2(1200,150);
    CP[4].pos=vec2(300,150);    //2nd lap
    CP[6].pos=vec2(1200,1000);
    CP[7].pos=vec2(300,1000);
    CP[5].pos=vec2(1200,150);    
    CP[8].pos=vec2(300,150);    //finish
    */
    CP[8].last=true;    
  }
  else {
    CP[0].last=true; //so the whole array isn't tested every loop
    
    putMeteor(vec2(10,500), vec2(3,0));
    putMeteor(vec2(600,800), vec2(1,-2));
    putMeteor(vec2(10,900), vec2(2,-1));
    putMeteor(vec2(10,300), vec2(2,2));
    putMeteor(vec2(550,550), vec2(1,-1));

    putEnnemies(vec2(0,600),vec2(5,0),0);
    putEnnemies(vec2(-20,600),vec2(5,0),0);
    putEnnemies(vec2(-40,600),vec2(5,0),0);
    putEnnemies(vec2(1000,80),vec2(5,0),ENNEMI_BIGEYEMONSTER);
  }
  //putEnnemies(vec2(600, 600), vec2(5, 0), ENNEMI_FLYINGSAUCER);
}

void explode(vec2 pos, byte type) {
  xplo[xploIt].type = type;
  xplo[xploIt].pos = pos;
  xplo[xploIt].count = 0;
  if (++xploIt >= NBMAX_EXPLOSION)
    xploIt = 0;
}

void addGem(vec2 pos) {
  for (int i = 0; i < NBMAX_GEM; i++) {
    if (0==gems[i].active) {
      gems[i].active = 254;
      gems[i].pos = pos;
      i = 99;
    }
  }
}
void mapCenter() {
  mapCoord.x = -(MAP_WIDTH / 2 - 64);
  mapCoord.y = -(MAP_HEIGHT / 2 - 32);
}

void drawStars() {
  /*
     byte temp=0;
    for (int i=0; i<SECTOR_COLUMNS; i++){
    for (int j=0; j< SECTOR_LINES; j++){
      if (++temp>3)
        temp=0;
      sprites.drawSelfMasked(mapCoord.x+i*IMAGE_WIDTH,mapCoord.y+j*IMAGE_HEIGHT,stars,temp); //4952 bytes... far too much
    }
    }
  */

  //randomSeed(1000);
  byte temp = 0;
  for (int i = 0; i < SECTOR_COLUMNS; i++) {
    for (int j = 0; j < SECTOR_LINES; j++) {
      if (++temp>6)//3
        temp=0;    
      for (int k = 0; k < STARS_PER_SCREEN ; k++) {
        //ab.drawPixel(mapCoord.x + i * IMAGE_WIDTH + random(128), mapCoord.y + j * IMAGE_HEIGHT + random(64)); //far too slow
        ab.drawPixel(mapCoord.x + i * IMAGE_WIDTH + 2*stars[(temp*STARS_PER_SCREEN+k)], mapCoord.y + j * IMAGE_HEIGHT + stars[temp*STARS_PER_SCREEN+k+1]);
      }
    }
  }

}

void drawRadar() {
  volatile bool blinking;
  volatile bool slowBlinking;
  volatile bool fastBlinking;
  if (ab.everyXFrames(5))
    blinking = !blinking;
  if (ab.everyXFrames(10))
    slowBlinking = !slowBlinking;
  if (ab.everyXFrames(3))
    fastBlinking = !fastBlinking;
  ab.fillRect (RADAR_POSX, RADAR_POSY, 11, 9); //(2,54,21,9);
  ab.drawPixel(RADAR_POSX + 5, RADAR_POSY + 4, 0);
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY - 1, RADAR_POSX - 1, RADAR_POSY + 1); // corners
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY - 1, RADAR_POSX + 1, RADAR_POSY - 1);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY - 1, RADAR_POSX + 11, RADAR_POSY + 1);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY - 1, RADAR_POSX + 9, RADAR_POSY - 1);
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY + 9, RADAR_POSX - 1, RADAR_POSY + 7);
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY + 9, RADAR_POSX + 1, RADAR_POSY + 9);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY + 9, RADAR_POSX + 11, RADAR_POSY + 7);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY + 9, RADAR_POSX + 9, RADAR_POSY + 9);

  //SECTOR BORDER
  int temp = (mapCoord.x - 64) / IMAGE_WIDTH;
  int temp2 = (mapCoord.y - 32) / IMAGE_HEIGHT;
  if (temp > -5) {
    ab.fillRect(RADAR_POSX, RADAR_POSY, temp + 5, 9, 0);
  }
  else if (temp < -(SECTOR_COLUMNS - 6)) {
    temp += (SECTOR_COLUMNS - 6);
    ab.fillRect(RADAR_POSX + temp + 11, RADAR_POSY, -temp, 9, 0);
  }
  if (temp2 > -4) {
    ab.fillRect(RADAR_POSX, RADAR_POSY, 11, temp2 + 4, 0);
  }
  else if (temp2 < -(SECTOR_LINES - 5)) {
    temp2 += (SECTOR_LINES - 5);
    ab.fillRect(RADAR_POSX, RADAR_POSY + temp2 + 9, 11, -temp2, 0);
  }
  
  if ((sectorType&0x80)==0x80){  // Race Mode
    for (int i=0; i<NBMAX_CP;i++){
      temp = (mapCoord.x + CP[i].pos.x - 29) / IMAGE_WIDTH; //pos adjust. from meteor but...
      temp2 = (mapCoord.y + CP[i].pos.y - 13) / IMAGE_HEIGHT;
  
      if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
        ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
      }
      if (CP[i].last)
        i=99;
    }
  }
  else {
    for (int i = 0; i < NBMAX_METEOR; i++) {
      if (met[i].active) {
        temp = (mapCoord.x + met[i].pos.x - 29) / IMAGE_WIDTH; //29: IMAGE_WIDTH/4-meteor_image_width/4
        temp2 = (mapCoord.y + met[i].pos.y - 13) / IMAGE_HEIGHT;
  
        if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
          ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, slowBlinking ? 0 : 1);
        }
      }
    }
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        temp = (mapCoord.x + enn[i].pos.x - 29) / IMAGE_WIDTH; //pos adjust. from meteor but...
        temp2 = (mapCoord.y + enn[i].pos.y - 13) / IMAGE_HEIGHT;
  
        if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
          ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
        }
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

void drawBackground() { //, int RandSeed){  //-------------------------------------- Draw Background --------------------------
  
  if ((sectorType&0x80)==0x80){  // Race Mode
    ab.print(elapsedtime);
    if (!CP[0].active&&(sectorType&0x81)!=0x81)
      elapsedtime++;
    
    for (int i=0; i<NBMAX_CP;i++){
      CP[i].update();
      if (CP[i].last)
        i=99;
    }
  }
  else {
    byte temp = 0;
    for (int i = 0; i < NBMAX_METEOR; i++) {
      if (met[i].active) {
        if (!isOut(met[i].pos)) {
          met[i].draw();
          temp++;
        }
        else {
          met[i].active = false;
        }
      }
    }
    if (0 == temp) {
      //putMeteor(vec2(0, random(1000)), vec2(random(10) + 1, random(2) - 1));
    }
    temp = 0;
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        if (!isOut(enn[i].pos)) {
          if (enn[i].update()) {
            if (0 == ennShot.active) {
              ennShot.active = SHOT_DURATION;
              int temp = trigoInv(enn[i].pos + mapCoord, vec2(64, 32)); // <-aiming the ship (if it's not in the border...)
              ennShot.pos = trigoVec(temp, 10, enn[i].pos + mapCoord);
              ennShot.dir = temp;
              ennShot.speed = trigoVec(temp, 6, vec2(0, 0));
            }
          }
          temp++;
        }
        else {
          enn[i].active = false;
        }
      }
    }
    if (ennShot.active!=0) {
      ennShot.draw();
    }
    if (0 == temp) {
      //putEnnemies(vec2(1280, 1280), vec2(0, 0), ENNEMI_FLYINGSAUCER);
    }
    for (int i = 0; i < NBMAX_EXPLOSION; i++) {
      xplo[i].update();
    }
    for (int i = 0; i < NBMAX_GEM; i++) {
      if (gems[i].active)
        gems[i].draw();
    }
  }
  
  drawRadar();
}


//todo: add Dmg to both side depending on the speed difference
vec2 elementCollision(vec2 objPos, int radius, int force, int dmg) { //Circular collision check. objPos must be previously centered. //-------- Collision ----------------------------------------------------------
  //vec2 temp;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {

      if ((magn(objPos - met[i].pos - mapCoord) != -1) && (magn(objPos - met[i].pos - mapCoord) < (radius + 6))) {
        //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        met[i].life -= dmg;
        if (met[i].life <= 0) {
          met[i].active = false;
          explode(met[i].pos, EXPLOSION_MEDIUM);
          addGem(met[i].pos); //todo add random ?
        }
        if (force > 0) {
          met[i].speed -= (objPos - met[i].pos - mapCoord) * force / 10;
        }
        return objPos - met[i].pos - mapCoord;
      }
    }
  }
  for (int i = 0; i < NBMAX_ENNEMI; i++) {
    if (enn[i].active) {
      byte ennRadius;
      if (ENNEMI_SPACEINVADER == enn[i].type) {
        ennRadius = 5;
      }
      else
        ennRadius = 8;
      if ((magn(objPos - enn[i].pos - mapCoord) != -1) && (magn(objPos - enn[i].pos - mapCoord) < (radius + ennRadius))) {
        enn[i].life -= dmg;
        if (enn[i].life <= 0) {
          enn[i].active = false;
          explode(enn[i].pos, EXPLOSION_MEDIUM);
          addGem(enn[i].pos); //todo add random ?
        }
        if (force > 0) {
          enn[i].speed -= (objPos - enn[i].pos - mapCoord) * force / 10;
        }
        return objPos - enn[i].pos - mapCoord;
      }
    }
  }
  if (ennShot.active>0) {
    if ((magn(objPos - ennShot.pos) != -1) && (magn(objPos - ennShot.pos) < (radius + 1))) {
      ennShot.explode();
      //ennShot.active = false;
      return vec2(99, 2); // x 99 means hit by an ennemi shot -> y is the dmg inflicted
    }
  }
  for (int i = 0; i < NBMAX_GEM; i++) {
    if (gems[i].active) {
      if ((radius!=0)&&(magn(objPos - gems[i].pos - mapCoord) != -1) && (magn(objPos - gems[i].pos - mapCoord) < (radius + 3))) {
        gems[i].active = false;
        return vec2(98, 2); // x 98 means coin collected
      }
    }
  }
  if ((sectorType&0x80)==0x80){  // Race Mode
    for (int i=0; i<NBMAX_CP;i++){
      if(CP[i].active){
        if ((radius!=0)&&(magn(objPos - CP[i].pos - mapCoord) != -1) && (magn(objPos - CP[i].pos - mapCoord) < (radius + 12))) {
          CP[i].active=false;
          if (CP[i].last){
            //race ends...
            sectorType|=0x01;
          }
          else {
            CP[i+1].active=true;        
            i=99;
          }
        }
      }
    }
  }
  return vec2(0, 0);
}


#endif
