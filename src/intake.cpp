#include "main.h"

static int intakeTarget = 0;
static int sonar_value;
bool intake_bool = true;

//motors
Motor intake1(20, MOTOR_GEARSET_6, true, MOTOR_ENCODER_DEGREES);
ADIUltrasonic Ball_Detector_2 (5,6);


/**************************************************/
//basic control
void intake(int vel){
  intake1.move_velocity(vel);
}

void _intake(int distance, int speed){
  intake1.move_relative(distance, speed);
}

void intakeReset(){
  intake1.tare_position();
}

void stopintakeAsync(){
  intakeTarget = 0;
}

void yeetthecap(){
  while(intakeTarget == 3){
  intake(-600);
}
}

void loadBallAsync(){
  intakeTarget = 1;
}

void intakeBallAsync(){
  intakeTarget = 2;
}

void flipAsync(){
  intakeTarget = 3;
}

void intake2ndBall(){
  intake_bool = true;
while(intake_bool){
  intake(600);
}
intake(0);
}


/**************************************************/
//task control

void ultrasonic(void * parameter){
  while(true){
    std::cout << Ball_Detector_2.get_value() << "\n";
    if(Ball_Detector_2.get_value() > 10 && Ball_Detector_2.get_value() < 80 ){
    std::cout << "True" << "\n";
      intake_bool = false;
    }
    else{
      intake_bool = true;
      std::cout << "false" << "\n";
    }
  }
}

void intakeTask(void* parameter){
  intake1.set_brake_mode(MOTOR_BRAKE_BRAKE);
  while(auton_mode){
    delay(20);

  switch(intakeTarget){
      case 1:
       loadBall();
        break;
        case 2:
        intake2ndBall();
        break;
        case 3:
        yeetthecap();
        break;
    }

    intakeTarget = 0;
  }
}

/**************************************************/
//operator control
void intakeOp(void* parameter){
  static int vel = 0;
  intake1.set_brake_mode(MOTOR_BRAKE_COAST);
  while(true){
  if(master.get_digital(DIGITAL_L1) == 1)
    intake(intake_speed);
  else if(master.get_digital(DIGITAL_L2) == 1)
    intake(-intake_speed);
  else
    intake(0);
  }
}
