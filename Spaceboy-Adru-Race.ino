/* 
 *  This is a "Spin-off" from SpaceBoy Ardu
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
#include "menus.h"

Player ship(64, 32, 4);
//Station home = Station (vec2(300, 300));
//bool station_active = false; //3%Progmem...

//bool dead=false;
byte state;
//unsigned int timer = 0;
//bool race=false;
//byte selector=0;



//variables for test
/*
Blob testEnnemi=Blob();
Ennemies testEnnemies[3];
Element * testPtrEl;
vec2 pointA(60, 30);
vec2 pointB(20, 40);
vec2 pointC(25, 50);
byte count=0;
byte frame=0;
vec2 pointD;
*/

void setup()
{
  ab.begin();  
  //ab.boot(); //846 bytes (3%) saved by using boot instead of begin (but must implement an Upload method)
  //testEnnemi.reboot(pointB, vec2(0,0), 0);
  ab.setFrameRate(60);
  //state = STATE_GAME;
  state = 0; //state = STATE_MENU;
  //state=STATE_TESTING;
  ab.initRandomSeed();

  //pointB+=vec2(pointC);

  //putStation();
}

void loop() {
  /*RMtimer++;*/
  //if (!(ab.nextFrameDEV())) { //32B
  if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();


  switch (state) {
    default: 
      state = menu(state, &ship);
      //if (STATE_GAME==state) randomSeed(timer * 3000);
    break;      

    case STATE_PAUSE: case STATE_GAMEOVER:
      if (STATE_GAMEOVER==state){
        ab.println("       Game Over");
        ab.println("");
      }
      else {
        ab.println("      * Pause *");      
        //ab.print("ship(s) left: ");
        //ab.println(ship.lives);
      }
      //ab.print("score: ");
      //ab.println(ship.money);
      
      if (ab.justPressed(DOWN_BUTTON)&&(STATE_GAMEOVER!=state)){
        state = STATE_GAME;
      }      
      break;
      
    case STATE_GAME:      
      if (ab.pressed(LEFT_BUTTON)&&ab.pressed(RIGHT_BUTTON)){
        state = STATE_PAUSE;
      }
      //drawStars(mapCoord.x,mapCoord.y, 3309);
      drawStars();
      if (ship.draw()){ //out of bound
        state = STATE_MENU;
        /*
        if (--ship.lives==0){
          state=STATE_GAMEOVER;
        }
        else {      
          ship.invincible=200;
          ship.armor=ARMOR_MAX;
          ship.energy=ENERGY_MAX;
          ship.speed=vec2(0,0);
          ship.pos=vec2(64,32);
          mapCenter(true);
        }
        */
      }
      drawBackground();
/*
      if (station_active) {
        home.draw();
      }
*/      
      controls(&ship);
      if (ship.checkcollision()){
        if (--ship.lives==0){
          state=STATE_GAMEOVER;
        }
        else {          
          explode(ship.pos-mapCoord, EXPLOSION_BIG);
          ship.invincible=200;
          ship.armor=ARMOR_MAX;
          ship.energy=ENERGY_MAX;
          //mapCenter(true);       
        }
      }/*RM
      ship.checkShotscollision();*/
      break;


  }
  ab.display();
}
