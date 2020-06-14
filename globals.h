#ifndef _GLOBALS_ 
#define _GLOBALS_ 

#include "vec2.h"
#include <Arduboy2.h>
#include "temp.h"

#define SPEED_DIVISOR 40
#define IMAGE_WIDTH 128
#define IMAGE_HEIGHT 64

#define MAP_WIDTH sectorColumns*IMAGE_WIDTH
#define MAP_HEIGHT sectorLines*IMAGE_HEIGHT

Arduboy2 ab;
//Arduboy2Base ab; //2136 bytes(8%) saved by using Base... But then I have to "draw" a menu or rewrite a print system
Sprites sprites;

vec2 mapCoord(0,0);
vec2 globVec(0,0);
byte sectorColumns=12;   //to have several map size
byte sectorLines=20;

int score;
bool radar=0;
byte selector=0;
 
//#define RACE_MODE 
//#define BILLARD_MODE
#define STORY_MODE  // for Story Mode this one must be defined along with one of the following
#define STORY_MODE_TUTO
//#define STORY_MODE_lvl1

// 24698, 2349 bytes used before splitting
//19362, 2047 in race mode or 23392, 2277 in normal mode. I can split more if needed

#ifdef STORY_MODE
  #define CAN_LEAVE_MAP
#endif

#ifdef STORY_MODE_TUTO
  const char tutext01[] PROGMEM = "Press A to shoot";
  const char tutext02[] PROGMEM = "<- or -> to rotate";
  const char tutext03[] PROGMEM = "Up for thrust";
  const char tutext04[] PROGMEM = "Down to slow down";
  const char tutext05[] PROGMEM = "B for shield";
  const char tutext06[] PROGMEM = "Oups not yet...";
  const char tutext07[] PROGMEM = "<- and -> to pause";
  const char tutext08[] PROGMEM = "Destroy asteroids";
  const char tutext09[] PROGMEM = "to get cristals";
  const char tutext10[] PROGMEM = "Bumping in asteroids";
  const char tutext11[] PROGMEM = "is harmful";   
  const char tutext12[] PROGMEM = "Watch for your shield";
  const char tutext13[] PROGMEM = "gauge on the right";
  const char tutext20[] PROGMEM = "Leaving sector will";
  const char tutext21[] PROGMEM = "send you back to base";
  const char tutext22[] PROGMEM = "Stop on the circle";
  const char tutext23[] PROGMEM = "to dock";

  
  char tBuffer[22];
  byte tutIt=1;
  int tuTimer=0;
  byte progression=0;

  //what was the use again? #define TUTPROG_BASIC //prog for progression not program or something
  const char * const tutext[] PROGMEM =
  {
    tutext01,
    tutext02,
    tutext03,
    tutext04,
    tutext05,
    tutext06,
    tutext07,
    tutext08,
    tutext09,
    tutext10,
    tutext11,
    tutext12,
    tutext13,
    tutext20,
    tutext21,
    tutext22,
    tutext23,
    //tutext29,    
  };
  //arduboy.println(strcpy_P(tBuffer, (char*)pgm_read_word(&(tutext[idx]))));
#endif

#ifdef RACE_MODE //bounce or not?
  unsigned int circuitTime[6]={9999,9999,9999,9999,9999,9999}; //no EEPROM save yet
  unsigned int elapsedTime=0;
#endif

#endif

/*  
 *   //for debugging purpose.
 *   
      ab.clear();
      ab.setCursor(0,0);
      ab.println(temp);
      ab.println(temp2);
      ab.display();
      delay(2000);
  */
