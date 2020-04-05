
#include "globals.h"
#include "trigo.h"
#include "controls.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "vec2.h"
#include "element.h"


Player ship(64,32,4);

vec2 pointA(50,10);
vec2 pointB(20,40);
vec2 pointC(25,50);

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

byte frame=0;
vec2 pointD;

void loop() {
  if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();

  /*
  //drawStars(mapCoord.x,mapCoord.y, 3309);
  drawBackground(mapCoord.x,mapCoord.y, 3309);
  //drawMeteor(vec2(100,80),false);
  ship.draw();
  controls(&ship);
  ship.checkcollision();
  ship.checkShotscollision();
  */
  
  

  vec2 moveCurs=vec2(0,0);
  if (ab.justPressed(LEFT_BUTTON))
    moveCurs+=vec2(-1,0);
  if (ab.justPressed(UP_BUTTON))
    moveCurs+=vec2(0,-1);
  if (ab.justPressed(RIGHT_BUTTON))
    moveCurs+=vec2(1,0);
  if (ab.justPressed(DOWN_BUTTON))
    moveCurs+=vec2(0,1);
  if (ab.pressed(A_BUTTON))
    moveCurs=moveCurs*10;
  pointB+=moveCurs;        

  //ab.drawCircle(pointA.x,pointA.y,2);
  ab.drawCircle(pointB.x,pointB.y,2);
  int temp=trigoInv(pointA,pointB);
  //drawVecLine(pointA,trigoVec(temp,20,pointA));
  
  
  if (ab.everyXFrames(15)){
    frame++;   
  }
  if (frame>4)
    frame=0;
  
  //ab.fillCircle(pointA.x,pointA.y,5);
  sprites.drawSelfMasked(pointA.x-8,pointA.y-5,monster,frame);
  pointD=trigoVec(temp,4,pointA);
  ab.drawRect(pointD.x-1,pointD.y,3,2,0);
  ab.drawPixel(pointD.x,pointD.y);
  //ab.drawCircle(pointD.x,pointD.y,1);

//drawGrid(pointC,pointB,vec2(-pointB.x,pointB.y),1,1);

drawCylinder(pointC,pointB,10,false);
ab.fillCircle(pointC.x,pointC.y,9,0);
  
  /*
   * ab.setCursor(0,0);
  ab.println((float)(abs(pointA.y-pointB.y)/(float)abs(pointA.x-pointB.x)));
  ab.println(temp);
  */
  
  ab.display();
  
}

