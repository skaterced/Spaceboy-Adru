#ifndef _GLOBALS_ 
#define _GLOBALS_ 

//#include "shot.h"
#include "vec2.h"

#include <Arduboy2.h>

#define SPEED_DIVISOR 20

Arduboy2 ab;
//Arduboy2Base ab; //2136 bytes(8%) saved by using Base
Sprites sprites;

vec2 mapCoord(0,0);
int score;

#endif

/*  
 *   //for debugging purpose.
 *   
      ab.setCursor(0,0);
      ab.println(temp);
      ab.println(temp2);
  */
