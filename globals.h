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
int score;

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
