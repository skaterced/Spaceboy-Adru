#ifndef _BACKGROUND_
#define _BACKGROUND_

#include "globals.h"
#include "sprites.h"
#include "vec2.h"
#include "trigo.h"
#include "element.h"
#include "station.h"
#include "shot.h"
#include "player.h"

#define RADAR_POSX 2
#define RADAR_POSY 54
#define RADAR_COL 6
#define RADAR_LIN 5
#define RADAR_XMIN 64
#define RADAR_YMIN 32
#define RADAR_DIVISOR 2 //why cst?

#define STARS_PER_SCREEN 9
#define STARS_TOT 58

#define NBMAX_METEOR 3
#define NBMAX_ENNEMI 12
#define NBMAX_EXPLOSION 3
#define NBMAX_GEM 7
#define NBMAX_CP 10
#define NBMAX_BH 7

#define SECTOR_SIZE_SMALL 0
#define SECTOR_SIZE_MED 1
#define SECTOR_SIZE_BIG 2

#define BIL_POS_INIT_X MAP_WIDTH * 1.5
#define BIL_POS_INIT_Y MAP_HEIGHT/2

#define SCT_METEOR_NONE 0
#define SCT_METEOR_FEW 0x10
#define SCT_METEOR_MORE 0x20
#define SCT_METEOR_LOT 0x30
#define SCT_METEOR_RESPAWN 0x08



//const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9}; //42 -> 21190
const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9,39,49,63,10,25,52,41,10,52,53,23,13,2,40,57,0};//,48,26,43,41,30,3,61};//,0,17,58,28,48,18,6}; //72 -> 21220

Meteor met[NBMAX_METEOR]; //not sure if there will be meteors in Race Mode but we never know
#ifdef RACE_MODE
  CheckPoint CP[NBMAX_CP];
  //unsigned int elapsedtime=0;
#endif
//#elifdef BILLARD_MODE
#ifdef BILLARD_MODE
  BlackHole BH[NBMAX_BH];
#else  
#ifndef STORY_MODE_TUTO
  Ennemies enn[NBMAX_ENNEMI];  
  Shot ennShot;
#endif  
  Waves waves;
  Explosion xplo[NBMAX_EXPLOSION];
  byte xploIt = 0;
  Gem gems[NBMAX_GEM];
  //bool station_active=false;
#endif
//bool station_active=false;
#ifdef STORY_MODE_TUTO
  Station home=Station (vec2(100,100));
  bool  station_active=false;
#endif  


byte sectorType;

/* in race mode
 * 7 6 5 4 3 2 1 0        NDY : (Not Defined Yet)
 * I I I I I I I L___ in race Mode: Race finished 
 * I I I I I I L_____ 
 * I I I I I L_______ \____ in race mode: circuit: 0 "O", 1 "inv(Z)", 2 ? 3"X"
 * I I I I L_______________ Meteor respawn between waves
 * I I I L___________ 
 * I I L_____________ \____ Meteor 0-11 none -> a lot      //(Size: 00 9x18, 01 12x20, 10 ?x?, 11 continuous?)I think I'll forget the different sizes)
 * I L_______________ 
 * L_________________ \____ Mode: 00 normal, 01 hard? 10 Race, 11 Rescue, 
 *
 * normal
 * 7 6 5 4 3 2 1 0        
 * I I I I I I I L____ 
 * I I I I I I L______\_____ size (or just one bit?)   //(Size: 00 9x18, 01 12x20, 10 ?x?, 11 continuous?)I think I'll forget the different sizes)
 * I I I I I L___________ 
 * I I I I L_______________ Meteor respawn between waves
 * I I I L___________ 
 * I I L_____________ \____ Meteor 0-11 a little -> a lot    
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
void putMeteors(bool randomPlace){
    byte temp=(3*((sectorType&0x30)>>4));    
    //bool temp2 = random(100)>50? true:false;
    while (temp-->0){
      if (randomPlace){
        putMeteor(vec2( random(MAP_WIDTH)+30,random(MAP_HEIGHT)),vec2((random(100)-50),random(20)-10));
      }
      else 
        putMeteor(vec2( (random(100)>50? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+2)*(random(100)>50? 1:-1),random(20)-10));
    }    
}

#ifdef BILLARD_MODE
void arrangeMeteors(byte nb){ //bool num 1-9 or 
//    byte temp=(3*((sectorType&0x30)>>4));    
  //vec2 temp=vec2(BIL_POS_INIT_X, BIL_POS_INIT_Y); 
  vec2 temp=vec2(100, 100); 
  
  putMeteor(temp, vec2(0,0));
  putMeteor(temp+vec2(12,12), vec2(0,0));
  putMeteor(temp+vec2(12,-12), vec2(0,0));        
}
#endif
/*
  void putStation(void){
  station_active=true;
  }
*/
#ifdef STORY_MODE
#ifndef STORY_MODE_TUTO
  void clearEnnemies (){
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      enn[i].active=false;
    }
  }
  void putEnnemies(vec2 pos, vec2 speed, byte type) {
  
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (!enn[i].active) {
        enn[i].reboot(pos, speed, type);
        i = NBMAX_ENNEMI;
      }
    }
  }
  
  bool nextWave(){
    //putMeteor(vec2( (temp2? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+2)*(temp2? 1:-1),random(20)-10));    
      if (waves.next()){
        byte temp=((waves.actual()&0x18)>>3)+1; //formation (number for now)
        byte temp2=random(MAP_HEIGHT-30)+30;
        switch (waves.actual()&0xE0){      
          case ENNEMI_SPACEINVADER:  default:      
            while (temp-->0){
              putEnnemies(vec2(-temp*20,temp2),vec2(20,0),ENNEMI_SPACEINVADER);
            }
          break;
          
          case ENNEMI_BIGEYEMONSTER: 
    
            putEnnemies(vec2(0,0),vec2(10,10),ENNEMI_BIGEYEMONSTER);
            if (--temp>0)
              putEnnemies(vec2(MAP_WIDTH,MAP_HEIGHT),vec2(-10,-10),ENNEMI_BIGEYEMONSTER);
            if (--temp>0)
              putEnnemies(vec2(MAP_WIDTH,0),vec2(-10,10),ENNEMI_BIGEYEMONSTER);
            if (--temp>0)
              putEnnemies(vec2(0,MAP_HEIGHT),vec2(10,-10),ENNEMI_BIGEYEMONSTER);                
          break;
          
          case ENNEMI_FLYINGSAUCER: 
            putEnnemies(vec2(0,0),vec2(10,10),ENNEMI_FLYINGSAUCER);
            if (--temp>0)
              putEnnemies(vec2(MAP_WIDTH,MAP_HEIGHT),vec2(-10,-10),ENNEMI_FLYINGSAUCER);
            if (--temp>0)
              putEnnemies(vec2(MAP_WIDTH,0),vec2(-10,10),ENNEMI_FLYINGSAUCER);
            if (--temp>0)
              putEnnemies(vec2(0,MAP_HEIGHT),vec2(10,-10),ENNEMI_FLYINGSAUCER);                
          break;      
        }
        return true;
      }
      else
        return false;
  }
#endif //not tuto
#endif //Story mode

#ifdef RACE_MODE
  void sectorInit(byte type, byte wavesType){ //, byte difficulty){  
    sectorType=type;
    
    //if (0x80==(type&0xC0)){ //useless now
      elapsedTime=0;
      CP[0].active=true;
      for (int i=1; i<NBMAX_CP; i++){
        CP[i].active=false;
      }           
      //   1 2
      //    3
      //   4 5
      switch(sectorType&0x06){
        case 0x02: default:
          // 'Z' shape
          CP[0].pos=CP1;  
          CP[1].pos=CP2;
          CP[2].pos=CP4;
          CP[3].pos=CP5;
          CP[4].pos=CP1;    //2nd lap
          CP[5].pos=CP2;
          CP[6].pos=CP4;
          CP[7].pos=CP5;
          CP[8].pos=CP1;    //finish
        break;
        case 0x04:
          // 'X' shape, one lap only
          CP[0].pos=CP1;  
          CP[1].pos=CP3;
          CP[2].pos=CP2;
          CP[3].pos=CP3;
          CP[4].pos=CP5;
          CP[5].pos=CP3;
          CP[6].pos=CP4;
          CP[7].pos=CP3;
          CP[8].pos=CP1;    //finish
        break;
        //case 0x04:
        //break;
        case 0:
          // 'O' shape
          CP[0].pos=CP1;  
          CP[1].pos=CP2;
          CP[2].pos=CP5;
          CP[3].pos=CP4;
          CP[4].pos=CP1;
          CP[5].pos=CP2;
          CP[6].pos=CP5;
          CP[7].pos=CP4;
          CP[8].pos=CP1;    //finish
        break;
      }
      CP[8].last=true;    
    }
#endif
//#elifdef BILLARD_MODE
#ifdef BILLARD_MODE
   void sectorInit(byte type, byte wavesType){
    
      sectorColumns=6;
      sectorLines=5;
      //todo type will define how many balls are in
      arrangeMeteors(8);
      BH[0].pos=vec2(0,0);
      BH[1].pos=vec2(MAP_WIDTH/2,0);
      BH[2].pos=vec2(MAP_WIDTH,0);
      BH[3].pos=vec2(0,MAP_HEIGHT);
      BH[4].pos=vec2(MAP_WIDTH/2,MAP_HEIGHT);
      BH[5].pos=vec2(MAP_WIDTH,MAP_HEIGHT);      
  }
#endif
#ifdef STORY_MODE
  void sectorInit(byte type, byte wavesType){ //, byte difficulty){
    sectorType=type;
    switch (sectorType&0x03){
      case SECTOR_SIZE_MED: default:
        sectorColumns=8;
        sectorLines=10;
      break;
      case SECTOR_SIZE_SMALL:
        sectorColumns=4;
        sectorLines=4;
      break;
      case SECTOR_SIZE_BIG:
        sectorColumns=12;
        sectorLines=20;
      break;
    }
    //CP[0].last=true; //so the whole array isn't tested every loop
    //clearEnnemies();
    #ifndef STORY_MODE_TUTO
    waves.init(wavesType);     
    nextWave();
    #endif
    putMeteors(true);  
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
#endif

void drawStars() {
  //randomSeed(1000);
  byte temp = 0;
  for (int i = 0; i < sectorColumns; i++) {
    for (int j = 0; j < sectorLines; j++) {
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
  
const byte RadarOffsetX1 [8] PROGMEM = {0,0,12,12,0,0,12,12};
const byte RadarOffsetX2 [8] PROGMEM = {0,2,12,10,0,2,12,10};
const byte RadarOffsetY1 [8] PROGMEM = {0,0,0,0,10,10,10,10};
const byte RadarOffsetY2 [8] PROGMEM = {2,0,2,0,8,10,8,10};
  
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
  //ab.drawPixel(RADAR_POSX + 5, RADAR_POSY + 4, 0);

  for(int i=0; i<8; i++){
     ab.drawLine(RADAR_POSX + RadarOffsetX1[i] - 1, RADAR_POSY +RadarOffsetY1[i] - 1, RADAR_POSX + RadarOffsetX2[i] - 1, RADAR_POSY + RadarOffsetY2[i] - 1); // corners
  }
  /*
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY - 1, RADAR_POSX - 1, RADAR_POSY + 1); // corners
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY - 1, RADAR_POSX + 1, RADAR_POSY - 1);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY - 1, RADAR_POSX + 11, RADAR_POSY + 1);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY - 1, RADAR_POSX + 9, RADAR_POSY - 1);
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY + 9, RADAR_POSX - 1, RADAR_POSY + 7);
  ab.drawLine(RADAR_POSX - 1, RADAR_POSY + 9, RADAR_POSX + 1, RADAR_POSY + 9);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY + 9, RADAR_POSX + 11, RADAR_POSY + 7);
  ab.drawLine(RADAR_POSX + 11, RADAR_POSY + 9, RADAR_POSX + 9, RADAR_POSY + 9);
 */
  //SECTOR BORDER
  int temp = (mapCoord.x - 64/RADAR_DIVISOR) / (IMAGE_WIDTH / RADAR_DIVISOR);
  int temp2 = (mapCoord.y - 32/RADAR_DIVISOR) / (IMAGE_HEIGHT / RADAR_DIVISOR);
  if (temp > -RADAR_COL) {
    ab.fillRect(RADAR_POSX, RADAR_POSY, temp + 5, 9, 0);
  }
  if (temp < -((sectorColumns-1)*RADAR_DIVISOR +1 - RADAR_COL)) {
    temp += ((sectorColumns-1)*RADAR_DIVISOR +1 - RADAR_COL );
    ab.fillRect(RADAR_POSX + temp + 11 , RADAR_POSY, -temp, 9, 0);
  }
  if (temp2 > -4) {
    ab.fillRect(RADAR_POSX, RADAR_POSY, 11, temp2 + 4, 0);
  }
  if (temp2 < -((sectorLines-1)*RADAR_DIVISOR +1 - RADAR_LIN)) {
    temp2 += ((sectorLines-1)*RADAR_DIVISOR +1 - RADAR_LIN);
    ab.fillRect(RADAR_POSX, RADAR_POSY + temp2 + 9, 11, -temp2, 0);
  }

  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {
      int temp = (mapCoord.x + met[i].pos.x - 64/RADAR_DIVISOR) / (IMAGE_WIDTH / RADAR_DIVISOR);
      int temp2 = (mapCoord.y + met[i].pos.y - 32/RADAR_DIVISOR) / (IMAGE_HEIGHT / RADAR_DIVISOR);

      if ((temp < RADAR_COL && temp > -RADAR_COL) && (temp2 < RADAR_LIN && temp2 > -RADAR_LIN)) {
        ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, slowBlinking ? 0 : 1);
      }
    }
  }
  ab.drawPixel(RADAR_POSX + 5, RADAR_POSY + 4, 0);
  #ifdef RACE_MODE
    //if ((sectorType&0xC0)==0x80){  // Check points only during Race Mode
      for (int i=0; i<NBMAX_CP;i++){
        temp = (mapCoord.x + CP[i].pos.x - 64/RADAR_DIVISOR) / (IMAGE_WIDTH / RADAR_DIVISOR);
        temp2 = (mapCoord.y + CP[i].pos.y - 32/RADAR_DIVISOR) / (IMAGE_HEIGHT / RADAR_DIVISOR);
    
        if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
          ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
        }
        if (CP[i].last)
          i=99;
      }
    //}
  #endif
  #ifdef STORY_MODE 
    #ifndef STORY_MODE_TUTO
        for (int i = 0; i < NBMAX_ENNEMI; i++) {
          if (enn[i].active) {
            temp = (mapCoord.x + enn[i].pos.x - 64/RADAR_DIVISOR) / (IMAGE_WIDTH / RADAR_DIVISOR);
            temp2 = (mapCoord.y + enn[i].pos.y - 32/RADAR_DIVISOR) / (IMAGE_HEIGHT / RADAR_DIVISOR);
      
            if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
              ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
            }
          }
        }
    #endif
  #endif

  #ifdef STORY_MODE_TUTO
    if (station_active){ 
      
      temp = (mapCoord.x + home.pos.x - 64/RADAR_DIVISOR) / (IMAGE_WIDTH / RADAR_DIVISOR);
      temp2 = (mapCoord.y + home.pos.y - 32/RADAR_DIVISOR) / (IMAGE_HEIGHT / RADAR_DIVISOR);
      if ((temp<6&&temp>-6)&&(temp2<5&&temp2>-5)){
        ab.drawPixel(RADAR_POSX+temp+5,4+RADAR_POSY+temp2,slowBlinking? 0:1);
      }
    }
  #endif
}

void drawBackground() { //, int RandSeed){  //-------------------------------------- Draw Background --------------------------
  byte last = 0;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {
      if (!isOut(met[i].pos)) {
        met[i].draw();
        last++; //useful?
      }
      else {
        met[i].active = false;                    
        bool temp2 = met[i].pos.x>100? true:false;          
        putMeteor(vec2( (temp2? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+10)*(temp2? 1:-1),random(20)-10));
      }
    }
  }
  #ifdef BILLARD_MODE

    for (int i=0; i<NBMAX_BH;i++){
      BH[i].draw();
    }
    drawRadar();
  #endif
  #ifdef RACE_MODE
  //if ((sectorType&0xC0)==0x80){  // Race Mode
    ab.print(elapsedTime);
    if (!CP[0].active&&(sectorType&0x81)!=0x81)
      elapsedTime++;
    
    for (int i=0; i<NBMAX_CP;i++){
      CP[i].update();
      if (CP[i].last)
        i=99;
    }
    drawRadar();
  //#elifdef STORY_MODE 
  #endif
  #ifdef STORY_MODE 
  #ifndef STORY_MODE_TUTO
    last = 0;
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        if (!isOut(enn[i].pos)) {
          if (enn[i].update()) {
            if (0 == ennShot.active) {
              ennShot.active = SHOT_DURATION;
              int temp = trigoInv(enn[i].pos + mapCoord, vec2(64, 32)); // <-aiming the ship (if it's not in the border...)
              ennShot.pos = trigoVec(temp, 10, enn[i].pos + mapCoord);
              ennShot.dir = temp;
              ennShot.speed = trigoVec(temp, 6, vec2(0, 0)); //Speed divisor dependant
            }
          }
          last++;
        }
        else {
          //check respawn bit
          enn[i].active = false;
        }
      }
    }
    if (ennShot.active!=0) {
      ennShot.draw(false);
    }
    if (0 == last) {
      //putEnnemies(vec2(1280, 1280), vec2(0, 0), ENNEMI_FLYINGSAUCER);
      //if ((waveIt<=NBMAX_WAVE)||waves[waveIt]==0){
      if(nextWave()){
        if (0x08==(sectorType&0x08)){
          putMeteors(false);
        }
      }
      else {
        ab.print("Sector Cleared");
      }
    }
    #else  //tuto mode
    if ((140==progression)/*||(13==progression)*/){
      tuTimer++;
      if (tuTimer>100){
        tutIt=0;    
        tuTimer=0;
        progression=13;
        /*
        if (10==tutIt){
          tutIt=0;
          progression++;
        }*/
      }
    }
    if (tutIt!=0){      
      ab.println(strcpy_P(tBuffer, (char*)pgm_read_word(&(tutext[tutIt-1]))));
      if (0x80==(progression&0x80)){
        ab.println(strcpy_P(tBuffer, (char*)pgm_read_word(&(tutext[tutIt]))));
        //ab.println(tuTimer);
        //ab.println(progression);
      }
    }
    if (station_active)
      home.draw();
    #endif //back to story no tuto
    
    for (int i = 0; i < NBMAX_EXPLOSION; i++) {
      xplo[i].update();
    }
    for (int i = 0; i < NBMAX_GEM; i++) {
      if (gems[i].active)
        gems[i].draw();
    }
    if(radar)
      drawRadar();
  #endif //story
  //drawRadar();

  //ab.println(waves[0].type);
}

bool checkRadiusCollision(vec2 posDiff, byte radius1, byte radius2){
  if ((magn(posDiff) != -99) && (magn(posDiff) < (radius1 + radius2)))
    return true;
  return false;
}
bool elementCollideShip(Player* ship, Element* El){ //must add element.radius
  vec2 temp=ship->pos-El->pos-mapCoord;
  vec2 temp2 = ship->speed - El->speed;  
  int temp3 = trigoInv2(vec2(0,0),temp,temp2);
    if (checkRadiusCollision(temp, (ship->invincible==1? 10:6), 6)){
      temp=temp/6;
      ship->pos+=temp;
      El->pos-=temp;

      temp=trigoVec(trigoInv(vec2(0,0),El->speed)+temp3,magn(ship->speed)/2,ship->speed);
      ship->speed=trigoVec(trigoInv(vec2(0,0),ship->speed)-temp3,magn(ship->speed)/2,El->speed);
      El->speed=temp;
      //temp=ship->reste;
      //ship->reste=El->reste;
      //El->reste=ship->reste;
      /*
      switch (temp3){
        case 0:
        break;
        case 1:
          
        break;      
      }*/
      return true;
    }
  return false;
}
bool shotCollideElement(Shot* shot, Element* El){
  
      vec2 temp=shot->pos-El->pos-mapCoord;
      if (checkRadiusCollision(temp, 1, 6)){
        shot->explode();
        return true;
      }       
  return false;
}
void checkElementCollisions(){  //Elements colide Element
  #ifdef BILLARD_MODE  // only check meteors
    //todo: build a quadtree
    for (int i = 0; i < NBMAX_METEOR-1; i++) {
      for (int j = i; j < NBMAX_METEOR; j++) {
    
        if ((met[i].active)&&(met[j].active)) {
          vec2 temp=met[i].pos-met[j].pos;
          
          if (checkRadiusCollision(temp, 6, 6)){
            //ship->justCollided=3;
            temp=temp/6;
            met[i].pos+=temp;
            met[j].pos-=temp;
            temp=met[i].speed;
            met[i].speed=met[j].speed;
            met[j].speed=temp;
            temp=met[i].reste;
            met[i].reste=met[j].reste;
            met[j].reste=met[i].reste;
          }
        }
     }
  }
  #endif
}

//vec2 checkPlayerCollisions(Player* ship, bool shot) {  //-------- Collision ----------------------------------------------------------
bool checkPlayerCollisions(Player* ship, byte shot) {  //-------- Collision ----------------------------------------------------------
  bool temp2=false;
  vec2 temp;
  int dmg;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {

     #ifdef STORY_MODE
        if (0!=shot) {
          if (shotCollideElement(&ship->gun.shots[shot-1], &met[i])){ 
            dmg=2;
            temp2=true;
          }
        }
        else {
          if (elementCollideShip(ship, &met[i])){
            dmg=magn(met[i].speed-ship->speed)/10;
            ship->armor -= (ship->invincible==1? 0:dmg);  
            temp2=true;
          }
        }
        if (temp2){       // something hit the meteor      
          met[i].life -= dmg;
            if (met[i].life <= 0) {
              met[i].active = false;
              explode(met[i].pos, EXPLOSION_MEDIUM);
              addGem(met[i].pos); //todo add random ?
              if (0x08==(sectorType&0x08)){
                putMeteor(vec2( (random(100)>50? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+2)*(random(100)>50? 1:-1),random(20)-10));
              }
            }
            i=99;
          }
      #else
        }
        elementCollideShip(ship, &met[i]);
      #endif
//        return objPos - met[i].pos - mapCoord;
  } // end of meteor collision
  

#ifdef STORY_MODE
  #ifndef STORY_MODE_TUTO
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        if (0!=shot) {
          if (shotCollideElement(&ship->gun.shots[shot-1], &enn[i])){ 
            dmg=2;
            temp2=true;
          }
        }
        else { //if (checkRadiusCollision(temp, (ship->invincible==1? 10:6), enn[i].radius)){
          if (elementCollideShip(ship, &enn[i])){
            dmg=magn(met[i].speed-ship->speed)/10;
            ship->armor -= (ship->invincible==1? 0:dmg);  
            temp2=true;
          }
        }
        if (temp2){       // something hit the ennemi      
          enn[i].life -= dmg;
            if (enn[i].life <= 0) {
              enn[i].active = false;
              explode(enn[i].pos, EXPLOSION_MEDIUM);          
              addGem(enn[i].pos); //todo add random ?
            }
            i=99;
          }
      }
    } // end of ennemi collision      
  #endif
}
          //enn[i].hit()
          /*
          if (ENNEMI_BLOB!=enn[i].type){
            enn[i].life -= dmg;
            if (enn[i].life <= 0) {
              enn[i].active = false;
              explode(enn[i].pos, EXPLOSION_MEDIUM);
              addGem(enn[i].pos); //todo add random ?
            }
            return temp;
          }
          else {
//            putEnnemies(trigoVec(trigoInv(enn[i].pos,objPos)-4,8,enn[i].pos),vec2(0,0),ENNEMI_BLOB);
  //          enn[i].pos=trigoVec(trigoInv(enn[i].pos,objPos)+4,8,enn[i].pos);
          }*/        


    if (0==shot){  //means we are testing collision with ship, not his shot
      #ifndef STORY_MODE_TUTO
      if (ennShot.active>0) {               
        temp=ship->pos-ennShot.pos;
        if (checkRadiusCollision(temp, (ship->invincible==1? 10:6), 1)){
          ennShot.explode();
          //ennShot.active = false;
          if (0==ship->invincible){
            ship->armor-=2;
            temp2=true;
          }
        }
      }
      #endif
      if (temp2){
        if (ship->armor>ARMOR_MAX)
          return true;
      }
      for (int i = 0; i < NBMAX_GEM; i++) {
        if (gems[i].active) {
          //if ((radius!=0)&&(magn(objPos - gems[i].pos - mapCoord) != -99) && (magn(objPos - gems[i].pos - mapCoord) < (radius + 3))) {
          temp=ship->pos-gems[i].pos-mapCoord;
          if (checkRadiusCollision(temp, (ship->invincible==1? 10:6), 3)){
            gems[i].active = false;
            ship->money+=10;
//            return vec2(98, 2); // x 98 means coin collected
          }
        }
      }
    }
  //return vec2(0, 0);
  #endif //story collisions

#ifdef RACE_MODE
    //if ((sectorType&0xC0)==0x80){ // Race Mode
    for (int i=0; i<NBMAX_CP;i++){
      if(CP[i].active){        
        if (checkRadiusCollision(ship->pos-CP[i].pos-mapCoord,6,12)){
          CP[i].active=false;
          CP[i].blink=0; //light it up for a while
          if (CP[i].last){
            //race ends...
            sectorType|=0x01;
            if (circuitTime[selector]>elapsedTime)
              circuitTime[selector]=elapsedTime;
          }
          else {
            CP[i+1].active=true; 
            ship->target=CP[i+1].pos;
            //return (CP[i+1].pos);
            i=99;
          }
        }
      }
    }
#endif // Race Mode checkPoints collision

#ifdef BILLARD_MODE
    
    for (int i=0; i<NBMAX_BH;i++){
      if (checkRadiusCollision(ship->pos- BH[i].pos,6,BH_RADIUS)){
      //if ((magn(ship->pos - BH[i].pos - mapCoord) != -99) && (magn(ship->pos - BH[i].pos - mapCoord) < (6 + 12))) {
        //todo: ship falls in BH next player turn        
      }
    }
#endif // Billard Mode Black Hole collision

return false;
}//end of checkPlayerCollisions()



#endif //background.h
