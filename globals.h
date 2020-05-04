#ifndef _GLOBALS_ 
#define _GLOBALS_ 

//#include "shot.h"
#include "vec2.h"

#include <Arduboy2.h>

#define SPEED_DIVISOR 40

Arduboy2 ab;
//Arduboy2Base ab; //2136 bytes(8%) saved by using Base... But then I have to "draw" a menu or rewrite a print system
Sprites sprites;

vec2 mapCoord(0,0);
unsigned int elapsedTime=0;
int score;
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


// 24698, 2349 bytes used before splitting
//19362, 2047 in race mode or 23392, 2277 in normal mode. I can split more if needed

#ifdef RACE_MODE
  unsigned int circuitTime[6]={9999,9999,9999,9999,9999,9999}; //no EEPROM save yet
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

