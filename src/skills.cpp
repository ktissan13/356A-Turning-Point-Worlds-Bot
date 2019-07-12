#include "main.h"

/*********************************************************/
void Skills1(){
  //intake ball under the nearest cap
  intakeFlip();
  
  //back up against wall
  drive(-1.63 TL);
  adjustAsync(64);

 //toggle flag column
  drive(.2 TL);
  turn(76);
  shoot();
  adjustAsync(146);
  loadBall();
  shoot();

  //pick up CAP
  turn(62);
  drive(-1.6 TL);
  liftFast(80);
  turn(36);
  drive(1.9 TL);
  slowDrive(.27 TL);
  liftFast(183);
  delay(275);
  drive(-.32 TL);
  liftFast(0);
  turn(-90);
  drive(-.8  TL);
  loadBallAsync();
  drive(2.5 TL);
  turn(-90);
  drive(-.6 TL);
  loadbreak = true;
  drive(1.6 TL);
  intakeBallAsync();
  wait(0.2);
  adjustAsync(128);
  turn(90);
  loadBall();
  shoot();
  loadBallAsync();
  drive(2 TL);
  drive(-1 TL);
  loadbreak = true;
  turn(-96);
  intake(-600);
  drive(1.6 TL);
}

void skills2(){
  backCap();

  // cap 2
  intakeFlip();
  turn(-3);
  slowDrive(-2.5 TL, -1.3 TL);

  // first flag column =============================

  backToFront();
  wallToFlag();
  lowFlag();

  // second flag column =============================

  //backup to align with next cap
  turn(2);
  drive(-2.0 TL);
  turn(-90);
  drive(-.5 TL);

  //cap 3
  intakeBallAsync();
  slowDrive(2.1 TL, 1 TL);

  //shoot both flags
  drive(-.28 TL);
  turn(75);
  frontdoubleShot();

  //toggle the low flag
  turn(13);
  slowDrive(2.5 TL, 1.2 TL);

  // third column low flag ============================

  //cap 4
  drive(-1.2 TL);
  turn(89);
  intake(-40);
  slowDrive(1.1 TL);

  //cap 5
  drive(-.3 TL);
  turn(177);
  slowDrive(3 TL, 1 TL);

  //low flag
  drive(-.4 TL);
  turn(80);
  slowDrive(1.4 TL, .5 TL);

  // last flags ==========================================

  //align with cap 6
  turn(-6);
  drive(-2.05 TL);
  turn(92);

  //intake ball
  intakeBallAsync();
  slowDrive(.9 TL);

  //shoot flags
  drive(-.45 TL);
  turn(-115);
  frontdoubleShot();

  //flip cap
  intake(-50);
  turn(108);
  slowDrive(1.6 TL);


  // park =================================================

  turn(-9);
  drive(-2.6 TL);
  turn(88);
  drive(1 TL);
  turn(-93);
  drive(.6 TL);

  //alliance park
  alliancePark();

  //center park
  park();
}
