#ifndef _MENU_TUT_
#define _MENU_TUT_

#include "globals.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "element.h"

#define STATE_MENU 1
//#define STATE_RACE_MENU 6
#define STATE_SHOP 7
#define STATE_SHOP_REPAIR 8
#define STATE_SHOP_GUN 9
#define STATE_SHOP_DEVICES 10
#define STATE_CREDIT 2
#define STATE_GAME 3
#define STATE_PAUSE 4
#define STATE_GAMEOVER 5
#define STATE_TESTING 99

#define REPAIR_COST 1
#define GUN_BIGB  0X01
#define GUN_MULTI 0X02
#define GUN_AUTO  0X04
#define DVICE_ENGINE 0x10
#define DVICE_RADAR 0xA0
#define DVICE_SHIELD 0x20
#define DVICE_ANTENNA 0x40

//byte selector;

void shopMsg(int money){
    ab.println(F("   Hi Adru"));
    ab.print("you have ");
    ab.print(money);      
    ab.println(" cristals");
    ab.println("");          
}

byte menu(byte state, Player* ship){

  switch (state){

    case 0:
      selector=0;
      state=STATE_MENU;
    break;
    case STATE_MENU:
      ab.println(F("  Welcome to tutorial"));
      ab.println(F("   SpaceBoy"));
      ab.println("");      
      ab.println("  Start");
      ab.println("  Shop");
      /*ab.println("  Start");
      ab.println("  Cheat");*/
      ab.println("  Credit");      
      //ab.println("  Test");

      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=2;
      }
      if (ab.justPressed(DOWN_BUTTON)) { //race with EngineV2 for now
        if(++selector>2)
          selector=0;
      }      
      ab.fillRect(2,26+8*selector,3,2);
      
      if (ab.justPressed(A_BUTTON)||ab.justPressed(B_BUTTON)) {
        ship->speed=vec2(0,0);
        //race=false;
        switch(selector){
          case 0:       // ********************** New Game *****************************
            //randomSeed(timer * 3000);            
            if (DVICE_SHIELD==(ship->setup&DVICE_SHIELD))
              ship->shield=SHIELD_MAX;              
            //sectorInit(SCT_METEOR_LOT|((ship->setup&DVICE_ANTENNA)?1:0),0);  //only two size for now
            sectorInit(SCT_METEOR_LOT|SCT_METEOR_RESPAWN|SECTOR_SIZE_MED,0); 
            
            ship->mapCenter(true);//, vec2(sectorColumns, sectorLines));
            return( STATE_GAME );
          break;
          case 3: //cheat
            ship->money+=300;
            //randomSeed(timer * 3000);            
            //sectorInit(0x30|DVICE_ANTENNA,0);
            //ship->mapCenter(true);//, vec2(sectorColumns, sectorLines));
            
            //ship->engineV2=true;
            //ship->setup|=0x0F;
            //ship->gun.canHold=true;
            //ship->gun.multi=true;
            //return( STATE_GAME);
          break;
          case 2:
            return( STATE_CREDIT);
          break;
          case 1:
            return( STATE_SHOP);
            selector=0;
          break;
          case 5:
            //return( STATE_TESTING);        
          break;
          case 9:

          break;
        }
        return( STATE_MENU);
      }
    break;

    case STATE_CREDIT:
      ab.println("");
      ab.println("Written by");
      ab.println("   C" "\x82" "dric Martin");
      ab.println("");
      ab.println("  Mai 2020");
      ab.println("");
      ab.println("");
      ab.println("A or B: back");

      if (ab.justPressed(A_BUTTON) || ab.justPressed(B_BUTTON))
        return( STATE_MENU);
    break;    

#ifndef RACE_MODE // NOT R_M
    
    case STATE_SHOP:  //sounds like skate shop... makes me wanna pop some kickflips...

      shopMsg(ship->money);
      ab.println("  Repair");
      ab.println("  Gun upgrade");
      ab.println("  Devices");      
      //ab.println("  New Ship");

      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=2;
      }
      if (ab.justPressed(DOWN_BUTTON)) { //race with EngineV2 for now
        if(++selector>2)
          selector=0;
      }      
      ab.fillRect(2,26+8*selector,3,2);

      if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
      }
      if (ab.justPressed(A_BUTTON)){
        switch(selector){
          
          case 0:
            //return( STATE_SHOP_REPAIR);
            while ((ship->armor<ARMOR_MAX)&&(ship->money>REPAIR_COST)){
              ship->money-=REPAIR_COST;
              ship->armor+=2;
            }                   
          break;
          case 1:
            return( STATE_SHOP_GUN);        
          break;
          case 2:
            return( STATE_SHOP_DEVICES);
          break;
        }
      }
    break;
    /*case STATE_SHOP_REPAIR :

      shopMsg(ship->money);
      ab.print("  Repair");
      if (ship->setup&DVICE_SHIELD)
        ab.print(" and Recharge");   
      //ab.println("  New Ship");

      ab.fillRect(2,26+8*selector,3,2);
      
      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=2;
      }
      else if (ab.justPressed(DOWN_BUTTON)) { 
        if(++selector>2)
          selector=0;
      }            
      else if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
      }
      else if (ab.justPressed(A_BUTTON)){
        while ((ship->armor<ARMOR_MAX)&&(ship->money>REPAIR_COST)){
          ship->money-=REPAIR_COST;
          ship->armor+=1;
        }
      }
    break;*/
    case STATE_SHOP_GUN :  //sounds like "click clack... BOOOOOOM"

      shopMsg(ship->money);
      ab.println("  Big Bullets  40");
      ab.println("  Auto Fire    60");
      ab.println("  Multiple     80");      
      //ab.println("  New Ship");

      ab.fillRect(2,26+8*selector,3,2);
      
      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=2;
      }
      else if (ab.justPressed(DOWN_BUTTON)) { 
        if(++selector>2)
          selector=0;
      }            
      else if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
      }
      else if (ab.justPressed(A_BUTTON)){
        switch(selector){

          case 0:
            if (ship->money>40&&(0==(ship->setup&GUN_BIGB))){
              ship->money-=40;
              ship->setup|=GUN_BIGB;
              ship->gun.bigB=true;
              ship->gun.dmg+=2;
            }
          break;
          case 1:
            if (ship->money>60&&(0==(ship->setup&GUN_AUTO))){
              ship->money-=60;
              ship->setup|=GUN_AUTO;
              ship->gun.canHold=true;
            }      
          break;
          case 2:
            if (ship->money>80&&(0==(ship->setup&GUN_MULTI))){
              ship->money-=80;
              ship->setup|=GUN_MULTI;              
              ship->gun.multi=true;
            }
          break;
        }
      }
    break;
    case STATE_SHOP_DEVICES :
    /*
 * I I I L___________ Radar
 * I I L_____________ shield
 * I L_______________ Antenna 
 * L_________________ EngineV2
     */
          shopMsg(ship->money);
      ab.println("  Radar     20");
      ab.println("  Shield    60");
      ab.println("  Antenna   80");      
      //ab.println("  New Ship");

      ab.fillRect(2,26+8*selector,3,2);
      
      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=2;
      }
      else if (ab.justPressed(DOWN_BUTTON)) { 
        if(++selector>2)
          selector=0;
      }            
      else if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
      }
      else if (ab.justPressed(A_BUTTON)){
        switch(selector){
          
          case 0:
            if (ship->money>20&&(false==radar)){
              ship->money-=20;
              //ship->setup|=DVICE_RADAR;
              radar=true;
            }
          break;
          case 1:
            if (ship->money>60&&(0==(ship->setup&DVICE_SHIELD))){
              ship->money-=60;
              ship->setup|=DVICE_SHIELD;
            }      
          break;
          case 2:
            if (ship->money>80&&(0==(ship->setup&DVICE_ANTENNA))){
              ship->money-=80;
              ship->setup|=DVICE_ANTENNA;
              //ship->gun.canHold=true;
            }
          break;
        }
      }
    break;
    default:
      
      ab.println("Sorry, only available");
      ab.println("in Race mode");
      ab.println("");
      ab.println("Recompile whith");
      ab.println("#define RACE_MODE ");
      ab.println("in globals.h");            
      /*ab.println("");
      ab.println("A or B: back");*/
            
      if (ab.justPressed(A_BUTTON) || ab.justPressed(B_BUTTON)){
        return( STATE_MENU);
        selector=0;
      }
    break;
/*
#else
    default:

      ab.println("Sorry, not available");
      ab.println("in Race mode");
      ab.println("");
      ab.println("Recompile whithout");
      ab.println("#define RACE_MODE ");
      ab.println("in globals.h");           
      
      if (ab.justPressed(A_BUTTON) || ab.justPressed(B_BUTTON)){
        return( STATE_MENU);
        selector=0;
      }
    break;
    
    case STATE_RACE_MENU:
    
      ab.print((char)27);
      ab.print(F(" Select Race "));
      ab.println((char)26);
      ab.println("");
      ab.print("Circuit : '");
      switch (selector&0x06){
        case 0x00:
          ab.print("O");
        break;
        case 0x02: default:
          ab.print("Z");
        break;
        case 0x04:
          ab.print("X");
        break;        
      }
      ab.println("'");
      //ab.println("");
      ab.println(0x01==(selector&1)? "Fast":"Normal");
      ab.print("Best Time : "); //we'll see if there is still memory left to keep Best time
      if (circuitTime[selector]!=9999)
        ab.println(circuitTime[selector]);
      else
        ab.println("NA");
      ab.println("");
      ab.println("A: Start");
      ab.println("B: Back");

      if (ab.justPressed(LEFT_BUTTON)) {
        if(0==selector--)
          selector=5;
      }
      else if (ab.justPressed(RIGHT_BUTTON)) {
        if(++selector>5)
          selector=0;
      }      
      else if (ab.justPressed(A_BUTTON)) {
        ship->setup|=(selector&1)<<4; //normal fast
        ship->setup|=0x80;
        sectorInit((0x80|(selector&0x06)),0);
        ship->mapCenter(false);//, vec2(sectorColumns, sectorLines));
        //elapsedTime=0; //-> in SectorInit 
        ship->target=CP1;        
        return( STATE_GAME);
      }
      else if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
        selector=0;
      }

    break;

#endif
*/
    
    }
    return (state);
}

#endif
#endif
