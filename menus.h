#ifndef _MENUS_
#define _MENUS_

#include "globals.h"
#include "background.h"
#include "player.h"
#include "shot.h"
#include "element.h"

#define STATE_MENU 1
#define STATE_RACE_MENU 6
#define STATE_SHOP 7
#define STATE_SHOP_REPAIR 8
#define STATE_SHOP_GUN 9
#define STATE_SHOP_DEVICES 10
#define STATE_CREDIT 2
#define STATE_GAME 3
#define STATE_PAUSE 4
#define STATE_GAMEOVER 5
#define STATE_TESTING 69

byte selector;

void shopMsg(int money){
    ab.println(F("   Hi Adru"));
    ab.print("you have ");
    ab.print(money);      
    ab.println(" cristals");
    ab.println("");          
}

byte menu(byte state, Player* ship){

  switch (state){

    case 0: default://init
      selector=0;
      state=STATE_MENU;
    case STATE_MENU:
      ab.println(F("   Welcome SpaceBoy"));
      ab.println("");      
      ab.println("  Race");
      ab.println("  Shop");
      ab.println("  New Game");
      ab.println("  Cheat");
      ab.println("  Credit");      
      ab.println("  Test");

      if (ab.justPressed(UP_BUTTON)) {
        if(0==selector--)
          selector=5;
      }
      if (ab.justPressed(DOWN_BUTTON)) { //race with EngineV2 for now
        if(++selector>5)
          selector=0;
      }      
      ab.fillRect(2,18+8*selector,3,2);
      
      if (ab.justPressed(A_BUTTON)||ab.justPressed(B_BUTTON)) {
        ship->speed=vec2(0,0);
        //race=false;
        switch(selector){
          case 2:       // ********************** New Game ******
            //randomSeed(timer * 3000);
            ship->mapCenter(true);
            sectorInit(0x30,0);            
            return( STATE_GAME );
          break;
          case 3:
            //randomSeed(timer * 3000);
            ship->mapCenter(true);
            sectorInit(0x30,0);
            //ship->engineV2=true;
            ship->setup|=0x0F;
            ship->gun.canHold=true;
            ship->gun.multi=true;
            return( STATE_GAME);
          case 4:
            return( STATE_CREDIT);
          break;
          case 1:
            return( STATE_SHOP);
            selector=0;
          break;
          case 5:
            return( STATE_TESTING);        
          break;
          case 0:
            return( STATE_RACE_MENU);
            selector=0;
          break;
        }
      }
    break;
    
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
            return( STATE_SHOP_REPAIR);
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
    
    case STATE_SHOP_GUN :

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
        return( STATE_SHOP);
      }
      else if (ab.justPressed(A_BUTTON)){
        switch(selector){
          
          case 0:
            if (ship->money>40&&(0==(ship->setup&0x01))){
              ship->money-=40;
              ship->setup|=1;
              ship->gun.bigB=true;
              ship->gun.dmg+=2;
            }
          break;
          case 1:
            if (ship->money>60&&(0==(ship->setup&0x02))){
              ship->money-=60;
              ship->setup|=0x02;
              ship->gun.multi=true;
            }      
          break;
          case 2:
            if (ship->money>80&&(0==(ship->setup&0x04))){
              ship->money-=80;
              ship->setup|=0x04;
              ship->gun.canHold=true;
            }
          break;
        }
      }
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
        return( STATE_MENU);
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
      ab.println("");
      ab.println(0x01==(selector&1)? "Fast":"Normal");
      //ab.println("Best Time : NA"); //we'll see if there is still memory left to keep Best time
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
        ship->mapCenter(false);
        //elapsedTime=0; //-> in SectorInit 
        ship->target=CP1;        
        return( STATE_GAME);
      }
      else if (ab.justPressed(B_BUTTON)) {
        return( STATE_MENU);
        selector=0;
      }

    break;
    }
    return (state);
}

#endif
