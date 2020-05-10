#ifndef _TRIGO_
#define _TRIGO_

#include "vec2.h"

#define NB_DIR 16

#define LINE_LENGTH 10

int trueDir(int dir){
  while (0>dir)   // while instead of if -> 32bytes less and an even better "result" (hum... maybe the compilator is out of the plaque)
    dir+=NB_DIR;
  while (dir>=NB_DIR)
    dir-=NB_DIR;
  return dir;
}

int invDir(int dir){
  dir-=NB_DIR/2;
  return trueDir(dir);
}

int trigo(int dir, int length, bool x){ // to get the coordinate of a 2nd point with a direction
  float temp;
  dir=trueDir(dir);
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

byte trigoInv(vec2 a, vec2 b){ //to get the direction from a to b
  if (a.x==b.x){ //to avoid /0
    if (a.y>=b.y)
      return 0;
    else
      return NB_DIR/2;
  }
  float temp=((float)abs(a.y-b.y)/(float)abs(a.x-b.x));
  if (temp>5){
    if (a.y>=b.y)
      return 0;
    else
      return 8;
  }
  else if (temp>1.25){
    if (a.y>=b.y){
      if (a.x>b.x){ return 15;}
      else{ return 1; }
    }     
    else
      if (a.x>b.x){ return 9;}
      else{ return 7; }
  }
  else if (temp>0.56){
    if (a.y>=b.y){
      if (a.x>b.x){ return 14;}
      else{ return 2; }
    }     
    else
      if (a.x>b.x){ return 10;}
      else{ return 6; }
  }
  else if (temp>0.2){
    if (a.y>=b.y){
      if (a.x>b.x){ return 13;}
      else{ return 3; }
    }     
    else
      if (a.x>b.x){ return 11;}
      else{ return 5; }
  }
  else {
    if (a.x>b.x){ return 12;}
    else{ return 4; }     
  }   
  //all possibilities really?
  //return 0;
}

int trigoInv2 (vec2 A, vec2 B, vec2 C) {
  int temp = trigoInv(A,B);
  int temp2 = trigoInv(A,C);
  int temp3 =temp2-temp;
  if ((temp3<-10)||(temp3>10)) {
    temp+=16;
  }
  return (temp2-temp);  
}

void drawVecLine(vec2 A, vec2 B){
  ab.drawLine(A.x,A.y,B.x,B.y);
}

void drawCylinder (vec2 A, vec2 B, int R,bool Hz, bool white){ //Hz :must be true if the Cylinder is horizontal. If it rotates-> call the function twice.
  ab.fillCircle(A.x,A.y,R, white);
  ab.fillCircle(B.x,B.y,R, white);
  vec2 temp;  
  if (Hz){ temp=vec2(0,1); }
  else { temp=vec2(1,0);}
  for (int i=0; i<R+1;i++){
    drawVecLine(A+(temp*i),B+(temp*i));
    drawVecLine(A-(temp*i),B-(temp*i));
  }
}

void drawGrid (vec2 pos, vec2 dirA, vec2 dirB,int nbA,int nbB){

  vec2 temp=pos+(dirA*(nbA-1));

  for (int i=0; i<nbB; i++){    
    drawVecLine(pos+(dirB*i), temp+(dirB*i));
    //tempA+=dirB;
  }
  temp=pos+(dirB*(nbB-1));
  for (int i=0; i<nbA; i++){    
    drawVecLine(pos+(dirA*i), temp+(dirA*i));
  }  
}

#endif
