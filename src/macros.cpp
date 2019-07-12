#include "main.h"
static int frontHigh = 19;
static int frontMiddle = 98;
static int backHigh = 55;
static int backMiddle = 130;

void frontdoubleShot(){
  frontHighFlag();
  _adjust(frontMiddle,127);
  loadBall();
  shoot();
}

void backdoubleShot(){
  backHighFlag();
  _adjust(backMiddle,127);
  loadBall();
  shoot();
}

void frontHighFlag(){
  _adjust(frontHigh,127);
  shoot();
}

void frontMidFlag(){
  _adjust(frontMiddle,127);
  shoot();
}

void backHighFlag(){
  _adjust(backHigh,127);//42,127
  shoot();
}

void backMidFlag(){
  _adjust(backMiddle,127);
  shoot();
}

void backLowFlag(){
  _adjust(275,127);
  shoot();
}

void PlatformReddoubleShot(){
  slowDrive(-0.2 TL);
  turn(25);
  backHighFlag();
}

void PlatformBluedoubleShot(){
  turn(-28);
}

void wallToFlag(){
  if(mirror == false){
    drive(.18 TL);
  }
  else{
    drive(.2 TL);
  }
  turn(76);
  frontdoubleShot();
}

void lowFlag(){
  if(mirror == false){
  turn(22);
}else{
  turn(16);
}
  drive(1.95 TL);
}

void backToFront(){
  drive(.2 TL);
  turn(86);
  drive(1.91 TL);
  turn(-93);
  drive(-.5 TL);
}

void intakeFlip(){
  drive(1.6 TL);
  intakeBallAsync();
  wait(0.2);
}

void backCap(){
  //back cap
  intake(-600);
  slowDrive(2.2 TL, .6 TL);

  //align with wall
  drive(-1.8 TL);
  turn(32);
  drive(-.6 TL);
}

void park(){
  driveAsync(1.6 TL);
  while(drivePos() < 1.15 TL) delay(20);
  drive(-1);
  _driveReset();
}

void alliancePark(){
  intake(127);
  driveAsync(2 TL);
  while(drivePos() < 1.4 TL) delay(20);
  setSpeed(20);
  while(isDriving()) delay(20);
}

void wait(int secs){
  static int seconds = secs*1000;
  static int temp = 0;
  while(temp != seconds){
    delay(1);
    temp += 1;
  }
}
