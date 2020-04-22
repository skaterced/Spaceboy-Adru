/* Welcome to my third Arduboy game
    This game was meant to be an exploration game with a galaxy looking general map, a space station where you dock between each mission and plenty of other things...
    I was thinking too big for the Arduboy RAM and now I have to cut in my ideas. I might actually program them, check if they work and then comment it.
    That way, if you edit my code, you could see what the game could have been. We never know, maybe there will be an Arduboy V2 with more RAM...

   Capacity Countdown:
   15% progmem left but I have to program the following:
   ship can die (maybe replace fuel jauge with shield)
   Something happen when ship is off the map (game over?)
   FlyingSaucer can shoot (and move less predictibly)
   add score

*/

#include "globals.h"
#include "trigo.h"
#include "controls.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "vec2.h"
#include "element.h"
#include "station.h"

#define STATE_MENU 1
#define STATE_CREDIT 2
#define STATE_GAME 3
#define STATE_TESTING 9

Player ship(64, 32, 4);
Station home = Station (vec2(300, 300));
bool station_active = false; //3%Progmem...

byte state;
unsigned int timer = 0;

vec2 pointA(60, 30);
vec2 pointB(20, 40);
vec2 pointC(25, 50);

void setup()
{
  ab.begin();
  ab.setFrameRate(60);
  state = STATE_MENU;
  //state=STATE_TESTING;
  ab.initRandomSeed();

  //pointB+=vec2(pointC);
  mapCenter();

  /*
    putMeteor(vec2(10,500), vec2(1,0));
    putMeteor(vec2(550,550), vec2(0,0));
    putEnnemis(vec2(1000,0),vec2(0,5),0);
    putEnnemis(vec2(1020,0),vec2(0,5),0);
    putEnnemis(vec2(1040,0),vec2(0,5),0);
    putEnnemis(vec2(1060,0),vec2(0,5),0);

    putEnnemis(vec2(0,600),vec2(5,0),0);
    putEnnemis(vec2(-20,600),vec2(5,0),0);
    putEnnemis(vec2(-40,600),vec2(5,0),0);
    putEnnemis(vec2(-60,600),vec2(5,0),ENNEMIS_BIGEYEMONSTER);
  */
  putEnnemis(vec2(600, 600), vec2(5, 0), ENNEMIS_FLYINGSAUCER);

  //putStation();
}

//byte count=0;
//byte frame=0;
//vec2 pointD;

void loop() {
  timer++;
  if (!(ab.nextFrameDEV())) {
    //if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();


  switch (state) {
    case STATE_MENU:
      ab.println("Welcome Spaceman");
      ab.println("");
      ab.println("Ready to blast");
      ab.println("some Aliens?");
      ab.println("");
      ab.println("");
      ab.println("A: Start");
      ab.println("B: Credit");

      if (ab.justPressed(A_BUTTON)) {
        randomSeed(timer * 3000);
        state = STATE_GAME;
      }
      if (ab.justPressed(B_BUTTON))
        state = STATE_CREDIT;
      break;
    case STATE_CREDIT:
      ab.println("");
      ab.println("Written by");
      ab.println("   C" "\x82" "dric Martin");
      ab.println("");
      ab.println("  April 2020");
      ab.println("");
      ab.println("");
      ab.println("A or B: back");

      if (ab.justPressed(A_BUTTON) || ab.justPressed(B_BUTTON))
        state = STATE_MENU;
      break;
    case STATE_GAME:

      //drawStars(mapCoord.x,mapCoord.y, 3309);
      drawStars();
      ship.draw();
      drawBackground();

      if (station_active) {
        home.draw();
      }
      controls(&ship);
      ship.checkcollision();
      ship.checkShotscollision();
      break;


    case STATE_TESTING:
      /*
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

          ab.drawCircle(pointA.x,pointA.y,2);
          ab.drawCircle(pointB.x,pointB.y,2);
          int temp=trigoInv(pointA,pointB);
          drawVecLine(pointA,trigoVec(temp,20,pointA));
          ab.println(pointB.x);
          ab.println(pointB.y);


          if (ab.everyXFrames(15)){
            frame++;
          }
          if (frame>4)
            frame=0;
          //ab.fillCircle(pointA.x,pointA.y,5);
          sprites.drawSelfMasked(pointA.x-8,pointA.y-5,monster,frame);
        //  pointD=trigoVec(temp,4,pointA);
          ab.drawRect(pointD.x-1,pointD.y,3,2,0);
          ab.drawPixel(pointD.x,pointD.y);
          //ab.drawCircle(pointD.x,pointD.y,1);

        //drawGrid(pointC,pointB,vec2(-pointB.x,pointB.y),1,1);

        //drawCylinder(pointC,pointB,10,false, true);
        //ab.fillCircle(pointC.x,pointC.y,9,0);

        int temp;
          count++;
          if (count<11){
            ab.fillCircle(pointB.x,pointB.y,count);
          }
          else if (count<21){
            ab.fillCircle(pointB.x,pointB.y,11);
            ab.fillCircle(pointB.x,pointB.y,count-11,0);
          }
          if (count>50)
            count=0;
      */
      break;

  }
  ab.display();
}
