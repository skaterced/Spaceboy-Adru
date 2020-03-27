#ifndef _TRIGO_
#define _TRIGO_

#include "vec2.h"


#define LINE_LENGTH 10

int trigo(int dir, int length, bool x){ //x or y
  float temp;
  switch (dir){
    case 0:
      temp= x? 0:-0.9;
    break;
    case 1:
      temp= x? 0.2:-0.8;
    break;
    case 2:
      temp= x? 0.5:-0.5;
    break;    
    case 3:
      temp= x? 0.8:-0.2;
    break;
    case 4:
      temp= x? 0.9:0;
    break;
    case 5:
      temp= x? 0.8:0.2;
    break;
    case 6:
      temp= x? 0.5:0.5;
    break;     
    case 7:
      temp= x? 0.2:0.8;
    break;
    case 8:
      temp= x? 0:0.9;
    break;
    case 9:
      temp= x? -0.2:0.8;
    break;
    case 10:
      temp= x? -0.5:0.5;
    break; 
    case 11:
      temp= x? -0.8:0.2;
    break;
    case 12:
      temp= x? -0.9:0;
    break;
    case 13:
      temp= x? -0.8:-0.2;
    break;
    case 14:
      temp= x? -0.5:-0.5;
    break;     
    case 15:
      temp= x? -0.2:-0.8;
    break;    
  }
  return length*temp;
}

void trigoVec(int dir, int length, vec2* pos){ //x or y
  pos->x+=trigo(dir, length, true);
  pos->y+=trigo(dir, length, false);
}


#endif
