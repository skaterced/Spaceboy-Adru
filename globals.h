#ifndef _GLOBALS_ 
#define _GLOBALS_ 

#include "vec2.h"
#include <Arduboy2.h>
#include "temp.h"

//#define CAN_LEAVE_MAP

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


/*************************  RACE MODE *************************************
 * in this mode you can't shoot anymore. A and B do the same as up and down.
 * you have to pass the 9 checkpoints in the right order (a compas will show 
 * you the direction of the next one).
 * 
 * Try to beat my personal best :
 * 
 *  *  on an Emulator :
 * 'O' normal  :
 * 'O' fast    :
 * 'Z' normal  :
 * 'Z' fast    :
 * 'X' normal  :
 * 'X' fast    :
 * 
 *  *  on the Arduboy :
 * 'O' normal  :
 * 'O' fast    :
 * 'Z' normal  :
 * 'Z' fast    :
 * 'X' normal  :
 * 'X' fast    :
 * 
 * Don't forget: opposing accelerating is faster than the brake. Both are even faster
 * 
 */
 
//#define RACE_MODE 
//#define BILLARD_MODE
#define STORY_MODE  // for Story Mode this one must be defined along with one of the following
//#define STORY_MODE_TUTO
//#define STORY_MODE_lvl1

// 24698, 2349 bytes used before splitting
//19362, 2047 in race mode or 23392, 2277 in normal mode. I can split more if needed

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
