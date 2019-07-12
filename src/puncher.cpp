#include "main.h"

pros::Motor Puncher (6, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
ADILightSensor Ball_Detector(1);

static int launcherTarget = 0;
const int rd = -180;
static const int final = 200;
static bool launcherBool = false;
static int launchSwitch = 0;
static bool ready;

/*****************Basic*****************/
void launcher(int vel){
  Puncher.move(vel);
}

void puncherReset(){
  Puncher.tare_position();
}

void loadBall(){
  loadbreak = false;
  while(Ball_Detector.get_value() > 1000){
    intake(600);
    if(loadbreak == true){
      break;
    }
  }
  intake(0);
}

/**********Auton Control*****/
void shootAsync(){
  launcherTarget = 1;
}

void shoot(){
  launcherBool = true;
  launchSwitch = 0;
  while(launcherBool){
    if(launchSwitch == 0){
      launcher(127);
      if(Puncher.get_torque() > 1){
        launchSwitch = 1;
      }
    }
    else if(launchSwitch == 1){
      if(Puncher.get_torque() < 0.5){
        Puncher.tare_position();
        while(abs(Puncher.get_position()) <= final){
          launcher(600);
        }
        launcherBool = false;
      }
      else{
        launcher(600);
      }
    }
  }

  launcher(0);
}
/******Task*****/
void launcherTask(void* parameter){
  while(true){
    pros::delay(20);

    switch(launcherTarget){
      case 1:
      shoot();
      break;
    }
    launcherTarget = 0;
  }
}

/********Operator*********/
void puncherOp(void* parameter){
  while(true){

   if(Ball_Detector.get_value() < 1000){
     intake_speed = 600*0.5;
     Partner_Control_rumble();
     ready = true;
   }
   else{
     intake_speed = 600;
     ready = false;
   }

   if(ready == true){
    if(partner.get_digital(DIGITAL_R1) == 1){
      shoot();
    }
   }
   else if(partner.get_digital(DIGITAL_R2) == 1){
     shoot();
   }
   else if(partner.get_digital(DIGITAL_RIGHT) == 1){
     launcher(600);
   }
   else{
     launcher(0);
   }
 }
  }
