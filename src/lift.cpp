#include "main.h"
bool liftbool = false;

Motor Lift(9, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);

/****Basic****/
void lift(int vel){
  Lift.set_brake_mode(MOTOR_BRAKE_HOLD);
  Lift.move(vel);
}

void liftFast(int distance){
  distance *= 5; // This is the gear ratio which allows you to use proper degrees
  Lift.move_absolute(distance, 200);
}

void liftSlow(int distance){
  distance *= 5; // This is the gear ratio which allows you to use proper degrees
  Lift.move_absolute(distance, 60);
}

void lift_encod(int distance, int speed){
  distance *= 5; // This is the gear ratio which allows you to use proper degrees
  Lift.move_absolute(distance, speed);
}

/********User Control*****/
void liftOp(void* parameter){
  /*Lift.set_brake_mode(MOTOR_BRAKE_BRAKE);
  Lift.tare_position();
  while(true){
  if(master.get_digital(DIGITAL_R1) == 1){
    if(Lift.get_position() < 500){
    lift(175);
    }
    else{
    lift(90);
    }
  }
  else if(master.get_digital(DIGITAL_R2) == 1){
    lift(-175);
  }
  else{
  if(Lift.get_position() > 50 && Lift.get_position() < 500){
  lift(10);
  }
  else if(Lift.get_position() > 800){
    lift(-10);
  }
  else{
    lift(0);
  }
}
}*/
}
