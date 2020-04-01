
#include "globals.h"
#include "trigo.h"
#include "controls.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "vec2.h"
#include "element.h"



//#define CHAR_WIDTH 16
//define CHAR_HEIGHT 16
//#define X_MAX (WIDTH - CHAR_WIDTH)
//#define Y_MAX (HEIGHT - CHAR_HEIGHT)
//byte frame = 0;
//char cdir = 'T'; // T, L, R, A

Player ship(64,32,4);

vec2 pointA(10,20);
vec2 pointB(30,20);
vec2 pointC(5,7);

void setup()
{  
  ab.begin();  
  ab.setFrameRate(60);
  ab.initRandomSeed();  
  
  pointB+=vec2(pointC);
  //mapCenter();

  putMeteor(1);
}

void loop() {
  if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();
/*
  ab.drawLine(pointA.x,pointA.y,pointB.x,pointB.y);
  drawVecLine(pointA+vec2(0,1),pointB+vec2(0,1));
  */
  controls(&ship);
  //drawStars(mapCoord.x,mapCoord.y, 3309);
  drawBackground(mapCoord.x,mapCoord.y, 3309);
  //drawMeteor(vec2(100,80),false);
  ship.draw();
  ship.checkcollision();
  ship.checkShotscollision();
  
  ab.display();
  
}
