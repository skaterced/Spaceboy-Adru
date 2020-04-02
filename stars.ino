
#include "globals.h"
#include "trigo.h"
#include "controls.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "vec2.h"
#include "element.h"


Player ship(64,32,4);

vec2 pointA(10,20);
vec2 pointB(30,20);
//vec2 pointC(5,7);

void setup()
{  
  ab.begin();  
  ab.setFrameRate(60);
  ab.initRandomSeed();  
  
  //pointB+=vec2(pointC);
  mapCenter();

  putMeteor(vec2(100,300));
  putMeteor(vec2(10,500));
  putEnnemis(vec2(50,0),vec2(0,10));
  putEnnemis(vec2(70,0),vec2(0,10));
  putEnnemis(vec2(90,0),vec2(0,10));
  putEnnemis(vec2(100,0),vec2(0,10));
}

void loop() {
  if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();

  
  //drawStars(mapCoord.x,mapCoord.y, 3309);
  drawBackground(mapCoord.x,mapCoord.y, 3309);
  //drawMeteor(vec2(100,80),false);
  ship.draw();
  controls(&ship);
  ship.checkcollision();
  ship.checkShotscollision();
  
/*
  ab.drawCircle(pointA.x,pointA.y,2);
  ab.drawCircle(pointB.x,pointB.y,2);
  drawVecLine(pointA,trigoVec(trigoInv(pointA,pointB),20,pointA));
  */
  
  ab.display();
  
}
