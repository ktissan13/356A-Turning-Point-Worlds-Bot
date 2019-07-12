#include "main.h"

// Angle Changer Motor
Motor Angle_Changer (5, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

static int adjusterTarget = 0;
static int angle =  0;
static int frontHigh = 19;
static int frontMiddle = 98;
static int backHigh = 55;
static int backMiddle = 130;

/*****************Basic*******/
// Sets adjuster speed
void adjust(int vel){
  Angle_Changer.move(vel);
}

// Sets the angle of the puncher
void _adjust(int distance, int vel){
  while(distance != Angle_Changer.get_position()){
    Angle_Changer.move_absolute(distance, 600);
    if (Angle_Changer.get_position() >= (distance-5) && Angle_Changer.get_position() <= (distance+5)){
      break;
    }
}
}

// Resets the angle changer position
void adjustReset(){
  Angle_Changer.tare_position();
}

void adjustAsync (int distance){
  angle = distance;
  adjusterTarget = 1;
}

void adjustTask(void * parameter){
  while(auton_mode){
    delay(20);

    switch(adjusterTarget){
      case 1:
       _adjust(angle, 600);
       break;
    }

    adjusterTarget = 0;
  }
}
/*************Operator Control*******/
void adjusterOp(void*parameter){
  Angle_Changer.set_brake_mode(MOTOR_BRAKE_BRAKE);
  while(true){
  // If partner click up button then it move adjuster positive direction
  if(partner.get_digital(DIGITAL_UP) == 1){
    adjust(127);
  }
  // If partner click down then it move adjuster negative direction
  else if(partner.get_digital(DIGITAL_DOWN)){
    adjust(-127);
  }
  // front high flag
  else if(partner.get_digital(DIGITAL_L1) == 1 && partner.get_digital(DIGITAL_X) == 1){
   _adjust(frontHigh,127);
  }
  // front middle flag
  else if(partner.get_digital(DIGITAL_L1) == 1 && partner.get_digital(DIGITAL_A) == 1){
   _adjust(frontMiddle,127);
  }
  // back high flag
  else if(partner.get_digital(DIGITAL_L2) == 1 && partner.get_digital(DIGITAL_X) == 1){
   _adjust(backHigh,127);
  }
  // back middle flag
  else if(partner.get_digital(DIGITAL_L2) == 1 && partner.get_digital(DIGITAL_A) == 1){
   _adjust(backMiddle,127);
  }
  else if(partner.get_digital(DIGITAL_LEFT) == 1){
    adjustReset();
  }
  else{
    adjust(0);
  }
}
}
