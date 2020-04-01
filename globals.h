#ifndef _GLOBALS_ 
#define _GLOBALS_ 

//#include "shot.h"
#include "vec2.h"

#include <Arduboy2.h>

#define SPEED_DIVISOR 15

vec2 mapCoord(0,0);

Arduboy2 ab;
Sprites sprites;

#endif

/*  
 *   //for debugging purpose.
 *   
      ab.setCursor(0,0);
      ab.println(temp);
      ab.println(temp2);
  */
