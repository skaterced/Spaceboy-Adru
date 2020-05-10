/*
   Yhea, I know, I name a lot of thing "temp" it's short from temporaire and not from temperature
   
  Randomly generated numbers from 0 to 64. I used this separated file to remove space (ctrl-V from Excel added two spaces between each character)
 * 
 59,12,41,5,59,33,38,28,5,2,35,27,14,29,63,14,7,57,28,30,57,5,52,31,6,32,37,22,34,33,24,48,46,27,6,10,45,35,14,4,9
39,49,63,10,25,52,41,10,52,53,23,13,2,40,57,0,48,26,43,41,30,3,61,0,17,58,28,48,18,6


//todo: add Dmg to both side depending on the speed difference
Backup
vec2 elementCollision(vec2 objPos, int radius, int force, int dmg) { //Circular collision check. objPos must be previously centered. //-------- Collision ----------------------------------------------------------
  //vec2 temp;
  for (int i = 0; i < NBMAX_METEOR; i++) {
    if (met[i].active) {

      if ((magn(objPos - met[i].pos - mapCoord) != -99) && (magn(objPos - met[i].pos - mapCoord) < (radius + 6))) {
        //if ((temp.x-7<shipPos.x&&shipPos.x<temp.x+19)&&(temp.y-7<shipPos.y&&shipPos.y<temp.y+19)){ // 22 = 12(image width/heigth)+10(ship radius)
        met[i].life -= dmg;
        if (met[i].life <= 0) {
          met[i].active = false;
          #ifndef RACE_MODE
            explode(met[i].pos, EXPLOSION_MEDIUM);          
            addGem(met[i].pos); //todo add random ?
          #endif
        }
        if (force > 0) {
          met[i].speed -= (objPos - met[i].pos - mapCoord) * force /5;
        }
        return objPos - met[i].pos - mapCoord;
      }
    }
  }
  #ifdef RACE_MODE
    //if ((sectorType&0xC0)==0x80){ // Race Mode
    for (int i=0; i<NBMAX_CP;i++){
      if(CP[i].active){
        if ((radius!=0)&&(magn(objPos - CP[i].pos - mapCoord) != -99) && (magn(objPos - CP[i].pos - mapCoord) < (radius + 12))) {
          CP[i].active=false;
          CP[i].blink=0; //light it up for a while
          if (CP[i].last){
            //race ends...
            sectorType|=0x01;
            if (circuitTime[selector]>elapsedTime)
              circuitTime[selector]=elapsedTime;
          }
          else {
            CP[i+1].active=true; 
            return (CP[i+1].pos);
            i=99;
          }
        }
      }
    }
  #else
    for (int i = 0; i < NBMAX_ENNEMI; i++) {
      if (enn[i].active) {
        byte ennRadius;
        if (ENNEMI_SPACEINVADER == enn[i].type) {
          ennRadius = 5;
        }
        else
          ennRadius = 8;
        vec2 temp=objPos - enn[i].pos - mapCoord;
        if ((magn(temp) != -99) && (magn(temp) < (radius + ennRadius))) {
          //enn[i].hit()
          
          if (ENNEMI_BLOB!=enn[i].type){
            //int temp=magn(enn[i].speed...
            enn[i].life -= dmg;
            if (enn[i].life <= 0) {
              enn[i].active = false;
              explode(enn[i].pos, EXPLOSION_MEDIUM);
              addGem(enn[i].pos); //todo add random ?
            }
            if (force > 0) {
              enn[i].speed -= (temp) * force / 10;
            }
            return temp;
          }
          else {
            putEnnemies(trigoVec(trigoInv(enn[i].pos,objPos)-4,8,enn[i].pos),vec2(0,0),ENNEMI_BLOB);
            enn[i].pos=trigoVec(trigoInv(enn[i].pos,objPos)+4,8,enn[i].pos);
          }
        }
      }
    }
    if (ennShot.active>0) {
      if ((magn(objPos - ennShot.pos) != -99) && (magn(objPos - ennShot.pos) < (radius + 1))) {
        ennShot.explode();
        //ennShot.active = false;
        return vec2(99, 2); // x 99 means hit by an ennemi shot -> y is the dmg inflicted
      }
    }
    for (int i = 0; i < NBMAX_GEM; i++) {
      if (gems[i].active) {
        if ((radius!=0)&&(magn(objPos - gems[i].pos - mapCoord) != -99) && (magn(objPos - gems[i].pos - mapCoord) < (radius + 3))) {
          gems[i].active = false;
          return vec2(98, 2); // x 98 means coin collected
        }
      }
    }
  #endif
  return vec2(0, 0);
}



*/
