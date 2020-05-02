/* Welcome to my third Arduboy game
    This game was meant to be an exploration game with a galaxy looking general map, a space station where you dock between each mission and plenty of other things...
    I was thinking too big for the Arduboy RAM and now I have to cut in my ideas. I might actually program them, check if they work and then comment it.
    That way, if you edit my code, you could see what the game could have been. We never know, maybe there will be an Arduboy V2 with more RAM...

   Capacity Countdown:
   15% progmem left but I have to program the following:
   ship can die (maybe replace fuel jauge with shield)    Check
   Something happen when ship is off the map (game over?) Check
   FlyingSaucer can shoot (and move less predictibly)     Check
   add score                                              Check (but is actually money not the number of things destroyed)
   ...
   
   24% Progmem, I changed the way the stars was displayed. But now Glob var uses 75% and uploading problems may occur...
   I still want to add the following depending on mode: Arcade, Story or Both
   a nice Title B (but name will maybe differ) "Space Digger", "Space Minner", "SpaceBoy Adru", ,... ?
   Menus
   EEPROM S
    why not old school "save" code
   Border B (but differently)         Check (for A)
   Waves  B (but differently)
   Force Field B                      Check
      "     "  jauge ? B              Check
   more Monsters  B (espacially A)
    "multiplying evil cloud"
   more Weapons B (espacially S)
   score (other than just money) A
   more Meteor shape and size S
   Fuel ? S
   Increasing thrust B
   Compas S
   Galaxy Map S
   Home S
   Races                              Check
   Rescue Mission

   debug: 
   "drooling" meteor mask             Check
   Collisions don't deal enough dmg

   ...
   
   22% Progmem 21% globVar
   Race mode is a success, I'll keep it, either as a bonus stage for A or a sector type for S
   still a lot in my head and less space but here are some ideas:
    Story  Map is always generated the same way but its size depends on you antenna or whatever. you can buy new stuff depending on money or what you already have. Basically 3 sort:
            weapon: +dmg; +speed; bombs
            devices: Radar; Better Engine? warp?; compas?
            defense: shield; shieldGenerator; autoShield;
   Ennemies: An evil multiplying cloud
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
#define STATE_PAUSE 4
#define STATE_GAMEOVER 5
#define STATE_TESTING 9

Player ship(64, 32, 4);
//Station home = Station (vec2(300, 300));
//bool station_active = false; //3%Progmem...

//bool dead=false;
byte state;
unsigned int timer = 0;
bool race=false;

//variables for test
Blob testEnnemi=Blob();
Ennemies testEnnemies[3];
Element * testPtrEl;
vec2 pointA(60, 30);
vec2 pointB(20, 40);
vec2 pointC(25, 50);
byte count=0;
byte frame=0;
vec2 pointD;

void setup()
{
  ab.begin();  
  //ab.boot(); //846 bytes (3%) saved by using boot instead of begin (but must implement an Upload method)
  //testEnnemi.reboot(pointB, vec2(0,0), 0);
  ab.setFrameRate(60);
  //state = STATE_GAME;
  state = STATE_MENU;
  //state=STATE_TESTING;
  ab.initRandomSeed();

  //pointB+=vec2(pointC);
/*
  if (race)
    sectorInit(0x80);
  else
    sectorInit(0);
 
    putMeteor(vec2(10,500), vec2(3,0));
    putMeteor(vec2(600,800), vec2(1,-2));
    putMeteor(vec2(10,900), vec2(2,-1));
    putMeteor(vec2(10,300), vec2(2,2));
    putMeteor(vec2(550,550), vec2(1,-1));

    putEnnemies(vec2(0,600),vec2(5,0),0);
    putEnnemies(vec2(-20,600),vec2(5,0),0);
    putEnnemies(vec2(-40,600),vec2(5,0),0);
    putEnnemies(vec2(1000,80),vec2(5,0),ENNEMI_BIGEYEMONSTER);
  
  //putEnnemies(vec2(600, 600), vec2(5, 0), ENNEMI_FLYINGSAUCER);
*/
  //putStation();
}

void loop() {
  timer++;
  //if (!(ab.nextFrameDEV())) { //32B
  if (!(ab.nextFrame())){
    return;
  }
  ab.pollButtons();
  ab.clear();


  switch (state) {    
    case STATE_MENU:
    
      //sprites.drawSelfMasked(0,0,menus,0);
/*    
      ab.println(F("Welcome SpaceBoy"));
      ab.println("");
      ab.println("up: Credit");
      ab.println("left: Quick Race");
      ab.println("right: Quick Game");
      ab.println("down: Test");
      ab.println("A: New Game");
      ab.println("B: Continue");
*/
      ab.println(F("Welcome SpaceBoy"));
      ab.println("");
      ab.print((char)24);
      ab.println(": Credit");
      ab.print((char)27);
      ab.println(": Race 'O'");
      ab.print((char)26);
      ab.println(": fast Race 'O'");
      ab.print((char)25);
      ab.println(": Test");
      ab.println("A: New Game");
      ab.println("B: Continue");


      if (ab.justPressed(LEFT_BUTTON)) {
        mapCenter(false);
        sectorInit(0x80,0);
        race=true;
        state = STATE_GAME;
      }
      if (ab.justPressed(RIGHT_BUTTON)) { //race with EngineV2 for now
        ship.engineV2=true;
        mapCenter(false);
        sectorInit(0x80,0);
        race=true;
        state = STATE_GAME;
      }      
      if (ab.justPressed(A_BUTTON)) {
        randomSeed(timer * 3000);
        mapCenter(true);
        sectorInit(0x00,0);
        ship.gun.canHold=false;
        state = STATE_GAME;
      }
      if (ab.justPressed(B_BUTTON)) {
        randomSeed(timer * 3000);
        mapCenter(true);
        sectorInit(0x30,0);
        ship.engineV2=true;
        ship.gun.multi=true;
        state = STATE_GAME;
      }
      if (ab.justPressed(UP_BUTTON))
        state = STATE_CREDIT;
      if (ab.justPressed(DOWN_BUTTON))
        state = STATE_TESTING;        
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
    case STATE_PAUSE: case STATE_GAMEOVER:
      if (STATE_GAMEOVER==state){
        ab.println("       Game Over");
        ab.println("");
      }
      else {
        ab.println("      * Pause *");      
        ab.print("ship left: ");
        ab.println(ship.lives);
      }
      ab.print("score: ");
      ab.println(ship.money);
      
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
      controls(&ship, race);
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
      }
      ship.checkShotscollision();
      break;


    case STATE_TESTING:

        mapCoord=vec2(0,0);
    
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
        
        if (ab.justPressed(B_BUTTON)){
//          testEnnemi.grow();
          testEnnemies[0].reboot(pointB,vec2(0,0),1);
          testPtrEl=&testEnnemi;
        }
        ab.drawCircle(pointA.x,pointA.y,2);
        //ab.drawCircle(pointB.x,pointB.y,2);
        int temp=trigoInv(pointA,pointB);
        drawVecLine(pointA,trigoVec(temp,20,pointA));
        ab.println(pointB.x);
        ab.println(pointB.y);

        if (ab.everyXFrames(15)){
          frame++;
        }
        if (frame>4)
          frame=0;
        //ab.fillCircle(pointA.x,pointA.y,4);
        //ab.fillCircle(pointA.x+2,pointA.y+1,2);
        //ab.fillCircle(pointA.x-1,pointA.y-2,2);
        //ab.fillCircle(pointA.x-2,pointA.y+3,2);
        //ab.fillCircle(pointA.x,pointA.y,2);
        //ab.fillCircle(pointA.x,pointA.y,2);
        //ab.fillCircle(pointA.x,pointA.y,2);
       
       testEnnemi.pos=pointA;
       testPtrEl->update();
       //testEnnemies[0].update();
/*
      for (int i=0; i<5; i++){
        ab.fillCircle(pointB.x+2*((frame>>i)&0x07)-8,pointB.y+(((frame>>(i+1))&0x07)-4),2);  
      }
      if (ab.everyXFrames(10)){
        for (int i=0;i<6;i++){
          frame=random(254);
        }
      }
*/

        //drawGrid(pointC,pointB,vec2(-pointB.x,pointB.y),1,1);

        //drawCylinder(pointC,pointB,10,false, true);
        //ab.fillCircle(pointC.x,pointC.y,9,0);


      break;

  }
  ab.display();
}
