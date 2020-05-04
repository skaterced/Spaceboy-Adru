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
#define sectorColumns 12
#define sectorLines  20
*/
byte sectorColumns=12;   //to have several map size
byte sectorLines=20;

#define MAP_WIDTH sectorColumns*IMAGE_WIDTH
#define MAP_HEIGHT sectorLines*IMAGE_HEIGHT

#define RADAR_POSX 2
#define RADAR_POSY 54

#define STARS_PER_SCREEN 9
#define STARS_TOT 58

#define NBMAX_METEOR 9
#define NBMAX_ENNEMI 12
#define NBMAX_EXPLOSION 3
#define NBMAX_GEM 7
#define NBMAX_CP 10

// TODO: Add a "sectorInit()" 


//const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9}; //42 -> 21190
const byte stars[STARS_TOT]={59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9,39,49,63,10,25,52,41,10,52,53,23,13,2,40,57,0};//,48,26,43,41,30,3,61};//,0,17,58,28,48,18,6}; //72 -> 21220

Meteor met[NBMAX_METEOR]; //not sure if there will be meteors in Race Mode but we never know
#ifdef RACE_MODE
  CheckPoint CP[NBMAX_CP];
  //unsigned int elapsedtime=0;
#else  
  Ennemies enn[NBMAX_ENNEMI];
  Waves waves;
  Shot ennShot;
  Explosion xplo[NBMAX_EXPLOSION];
  byte xploIt = 0;
  Gem gems[NBMAX_GEM];
#endif

byte sectorType;
/* 7 6 5 4 3 2 1 0        NDY : (Not Defined Yet)
 * I I I I I I I L___ in race Mode: Race finished 
 * I I I I I I L_____ 
 * I I I I I L_______ \____ in race mode: circuit: 0 "O", 1 "inv(Z)", 2 ? 3"X"
 * I I I I L_______________ Meteor respawn between waves
 * I I I L___________ 
 * I I L_____________ \____ Meteor 0-11 a little -> a lot      //(Size: 00 9x18, 01 12x20, 10 ?x?, 11 continuous?)I think I'll forget the different sizes)
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
void putMeteors(bool randomPlace){
    byte temp=(3*((sectorType&0x30)>>4));    
    bool temp2 = random(100)>50? true:false;
    while (temp-->0){
      if (randomPlace){
        putMeteor(vec2( random(MAP_WIDTH)+30,random(MAP_HEIGHT)),vec2((random(100)-50),random(20)-10));
      }
      else 
        putMeteor(vec2( (temp2? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+2)*(temp2? 1:-1),random(20)-10));
    }    
}
/*
  void putStation(void){
  station_active=true;
  }
*/
#ifndef RACE_MODE
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
        byte temp2=random(MAP_HEIGHT);
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
#endif

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
#else
  void sectorInit(byte type, byte wavesType){ //, byte difficulty){  
    sectorType=type;

    CP[0].last=true; //so the whole array isn't tested every loop
    waves.init(wavesType); 
    nextWave();
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
  else if (temp < -(sectorColumns - 6)) {
    temp += (sectorColumns - 6);
    ab.fillRect(RADAR_POSX + temp + 11, RADAR_POSY, -temp, 9, 0);
  }
  if (temp2 > -4) {
    ab.fillRect(RADAR_POSX, RADAR_POSY, 11, temp2 + 4, 0);
  }
  else if (temp2 < -(sectorLines - 5)) {
    temp2 += (sectorLines - 5);
    ab.fillRect(RADAR_POSX, RADAR_POSY + temp2 + 9, 11, -temp2, 0);
  }

  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {
      temp = (mapCoord.x + met[i].pos.x - 32) / IMAGE_WIDTH; //29: IMAGE_WIDTH/4-meteor_image_width/4 = 32 - 12/4 
      temp2 = (mapCoord.y + met[i].pos.y - 16) / IMAGE_HEIGHT; //13: IMAGE_HEIGHT/4-meteor_image_width/4 = 16 - 12/4 

      if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
        ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, slowBlinking ? 0 : 1);
      }
    }
  }
  #ifdef RACE_MODE
    //if ((sectorType&0xC0)==0x80){  // Check points only during Race Mode
      for (int i=0; i<NBMAX_CP;i++){
        temp = (mapCoord.x + CP[i].pos.x - 32) / IMAGE_WIDTH; 
        temp2 = (mapCoord.y + CP[i].pos.y - 16) / IMAGE_HEIGHT;
    
        if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
          ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
        }
        if (CP[i].last)
          i=99;
      }
    //}
  #else 
      for (int i = 0; i < NBMAX_ENNEMI; i++) {
        if (enn[i].active) {
          temp = (mapCoord.x + enn[i].pos.x - 29) / IMAGE_WIDTH; //29: IMAGE_WIDTH/4-Ennemi_image_width/4 = 32 - 3  (I know not every Ennemi is 12x12)
          temp2 = (mapCoord.y + enn[i].pos.y - 13) / IMAGE_HEIGHT; //29: IMAGE_HEIGHT/4-Ennemi_image_height/4 = 16 - 3 
    
          if ((temp < 6 && temp > -6) && (temp2 < 5 && temp2 > -5)) {
            ab.drawPixel(RADAR_POSX + temp + 5, 4 + RADAR_POSY + temp2, fastBlinking ? 0 : 1);
          }
        }
      }
    #endif

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
  byte last = 0;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {
      if (!isOut(met[i].pos)) {
        met[i].draw();
        last++;
      }
      else {
        met[i].active = false;                    
        bool temp2 = met[i].pos.x>100? true:false;          
        putMeteor(vec2( (temp2? 0:MAP_WIDTH),random(MAP_HEIGHT)),vec2((random(50)+10)*(temp2? 1:-1),random(20)-10));
      }
    }
  }
  
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
  #else      
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
              ennShot.speed = trigoVec(temp, 6, vec2(0, 0));
            }
          }
          last++;
        }
        else {
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
    for (int i = 0; i < NBMAX_EXPLOSION; i++) {
      xplo[i].update();
    }
    for (int i = 0; i < NBMAX_GEM; i++) {
      if (gems[i].active)
        gems[i].draw();
    }
  #endif
  drawRadar();

  //ab.println(waves[0].type);
}


//todo: add Dmg to both side depending on the speed difference

vec2 elementCollision(vec2 objPos, int radius, int force, int dmg) { //Circular collision check. objPos must be previously centered. //-------- Collision ----------------------------------------------------------
  //vec2 temp;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {

      if ((magn(objPos - met[i].pos - mapCoord) != -99) && (magn(objPos - met[i].pos - mapCoord) < (radius + 6))) {
        //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        met[i].life -= dmg;
        if (met[i].life <= 0) {
          met[i].active = false;
          #ifndef RACE_MODE
            explode(met[i].pos, EXPLOSION_MEDIUM);          
            addGem(met[i].pos); //todo add random ?
          #endif
        }
        if (force > 0) {
          met[i].speed -= (objPos - met[i].pos - mapCoord) * force /5;
        }
        return objPos - met[i].pos - mapCoord;
      }
    }
  }
  #ifdef RACE_MODE
    //if ((sectorType&0xC0)==0x80){ // Race Mode
    for (int i=0; i<NBMAX_CP;i++){
      if(CP[i].active){
        if ((radius!=0)&&(magn(objPos - CP[i].pos - mapCoord) != -99) && (magn(objPos - CP[i].pos - mapCoord) < (radius + 12))) {
          CP[i].active=false;
          CP[i].blink=0; //light it up for a while
          if (CP[i].last){
            //race ends...
            sectorType|=0x01;           
          }
          else {
            CP[i+1].active=true; 
            return (CP[i+1].pos);
            i=99;
          }
        }
      }
    }
  #else
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        byte ennRadius;
        if (ENNEMI_SPACEINVADER == enn[i].type) {
          ennRadius = 5;
        }
        else
          ennRadius = 8;
        vec2 temp=objPos - enn[i].pos - mapCoord;
        if ((magn(temp) != -99) && (magn(temp) < (radius + ennRadius))) {
          //enn[i].hit()
          
          if (ENNEMI_BLOB!=enn[i].type){
            enn[i].life -= dmg;
            if (enn[i].life <= 0) {
              enn[i].active = false;
              explode(enn[i].pos, EXPLOSION_MEDIUM);
              addGem(enn[i].pos); //todo add random ?
            }
            if (force > 0) {
              enn[i].speed -= (temp) * force / 10;
            }
            return temp;
          }
          else {
            putEnnemies(trigoVec(trigoInv(enn[i].pos,objPos)-4,8,enn[i].pos),vec2(0,0),ENNEMI_BLOB);
            enn[i].pos=trigoVec(trigoInv(enn[i].pos,objPos)+4,8,enn[i].pos);
          }
        }
      }
    }
    if (ennShot.active>0) {
      if ((magn(objPos - ennShot.pos) != -99) && (magn(objPos - ennShot.pos) < (radius + 1))) {
        ennShot.explode();
        //ennShot.active = false;
        return vec2(99, 2); // x 99 means hit by an ennemi shot -> y is the dmg inflicted
      }
    }
    for (int i = 0; i < NBMAX_GEM; i++) {
      if (gems[i].active) {
        if ((radius!=0)&&(magn(objPos - gems[i].pos - mapCoord) != -99) && (magn(objPos - gems[i].pos - mapCoord) < (radius + 3))) {
          gems[i].active = false;
          return vec2(98, 2); // x 98 means coin collected
        }
      }
    }
  #endif
  return vec2(0, 0);
}


#endif 
