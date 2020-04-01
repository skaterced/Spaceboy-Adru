#ifndef _TRIGO_
#define _TRIGO_

#include "vec2.h"

#define NB_DIR 16

#define LINE_LENGTH 10

int trueDir(int dir){
  if (0>dir)
    dir+=NB_DIR;
  if (dir>=NB_DIR)
    dir-=NB_DIR;
  return dir;
}

int invDir(int dir){
  dir-=NB_DIR/2;
  return trueDir(dir);
}

int trigo(int dir, int length, bool x){ //x or y
  float temp;
  /*
  float cos[NB_DIR]={0,0.36,0.7,0.9,0.9,0.9,0.7,0.3,0,-0.3,-0.7,-0.9,-0.9,-0.9,-0.7,-0.3};
  temp=dir+x?0:12;
  if (temp>NB_DIR)
    temp-=NB_DIR;
*/    

  switch (dir){
    case 0:
      temp= x? 0:-1;
    break;
    case 1:
      temp= x? 0.3:-0.9;
    break;
    case 2:
      temp= x? 0.7:-0.7;
    break;    
    case 3:
      temp= x? 0.9:-0.3;
    break;
    case 4:
      temp= x? 1:0;
    break;
    case 5:
      temp= x? 0.9:0.3;
    break;
    case 6:
      temp= x? 0.7:0.7;
    break;     
    case 7:
      temp= x? 0.3:0.9;
    break;
    case 8:
      temp= x? 0:1;
    break;
    case 9:
      temp= x? -0.3:0.9;
    break;
    case 10:
      temp= x? -0.7:0.7;
    break; 
    case 11:
      temp= x? -0.9:0.3;
    break;
    case 12:
      temp= x? -1:0;
    break;
    case 13:
      temp= x? -0.9:-0.3;
    break;
    case 14:
      temp= x? -0.7:-0.7;
    break;     
    case 15:
      temp= x? -0.3:-0.9;
    break;    
  }
  return length*temp;
  //return (int)((float)length*cos[temp]);
}

vec2 trigoVec(int dir, int length, vec2 pos){ //x or y
  pos.x+=trigo(dir, length, true);
  pos.y+=trigo(dir, length, false);
  return pos;
}

#endif
