#include "main.h"

#define MAX 200;

Motor Chasis_L1 (19, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor Chasis_L2 (17, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
Motor Chasis_R1 (18, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
Motor Chasis_R2 (16, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);

 static int driveMode = 1;
 static int driveTarget = 0;
 static int turnTarget = 0;
 static int maxSpeed = MAX;
 static int slant = 0;

 /*********************************/
 //Basic Controls
 // Controls left side of chassis
 void Chasis_left(int value){
   Chasis_L1.move(value);
   Chasis_L2.move(value);
 }

 // Controls right side of chassis
 void Chasis_right(int value){
   Chasis_R1.move(value);
   Chasis_R2.move(value);
 }

 // Clears the Motors encoders
 void _driveClr(){
   Chasis_L1.tare_position();
   Chasis_L2.tare_position();
   Chasis_R1.tare_position();
   Chasis_R2.tare_position();
 }

 // Resets the whole drive system
 void _driveReset(){
   maxSpeed = MAX;
   slant = 0;
   driveTarget = 0;
   turnTarget = 0;
   _driveClr();
   Chasis_left(0);
   Chasis_right(0);
 }

// if called returns integer value
 int drivePos(){
   return (Chasis_L1.get_position() + Chasis_R1.get_position())/2;
 }

// set the max speed for slew control
 void setSpeed(int speed){
   maxSpeed = speed;
 }

 /*********************************/
 //slew control
 // 9 works fine if any other number does not work
 const int accel_step = 9;
 const int deccel_step = 256; // no decel slew
 static int leftSpeed = 0;
 static int rightSpeed = 0;

 void leftSlew(int leftTarget){
   int step;

   if(abs(leftSpeed) < abs(leftTarget))
     step = accel_step;
   else
     step = deccel_step;

   if(leftTarget > leftSpeed + step)
     leftSpeed += step;
   else if(leftTarget < leftSpeed - step)
     leftSpeed -= step;
   else
     leftSpeed = leftTarget;

   Chasis_left(leftSpeed);
 }

 //slew control
 void rightSlew(int rightTarget){
   int step;

   if(abs(rightSpeed) < abs(rightTarget))
     step = accel_step;
   else
     step = deccel_step;

   if(rightTarget > rightSpeed + step)
     rightSpeed += step;
   else if(rightTarget < rightSpeed - step)
     rightSpeed -= step;
   else
     rightSpeed = rightTarget;

   Chasis_right(rightSpeed);
 }

 /**************************************************/
 //slop correction
 void slop(int sp){
   driveMode = 2;
   if(sp < 0){
     Chasis_right(-30);
     pros::delay(100);
   }
   driveMode = 1;

 }

 /**************************************************/
 //feedback
 bool isDriving(){
   static int count = 0;
   static int last = 0;
   static int lastTarget = 0;

   int leftPos = Chasis_L1.get_position();
   int rightPos = Chasis_R1.get_position();

   int curr = (abs(leftPos) + abs(rightPos))/2;
   int thresh = 3;
   int target = turnTarget;

   if(driveMode == 1)
     target = driveTarget;


   if(abs(last-curr) < thresh)
     count++;
   else
     count = 0;

   if(target != lastTarget)
     count = 0;

   lastTarget = target;
   last = curr;

   //not driving if we haven't moved
   if(count > 4)
     return false;
   else
     return true;

 }

 /**************************************************/
 //autonomous functions
 void driveAsync(int sp){
   _driveReset();
   driveTarget = sp;
   driveMode = 1;
 }

 void turnAsync(int sp){
   if(mirror)
     sp = -sp; // inverted turn for blue auton
   _driveReset();
   turnTarget = sp;
   driveMode = 0;
 }

 void drive(int sp){
   driveAsync(sp);
   pros::delay(450);
   while(isDriving()) pros::delay(20);
 }

 void turn(int sp){
   turnAsync(sp);
   pros::delay(450);
   while(isDriving()) pros::delay(20);
 }

 void slowDrive(int sp, int dp){
   driveAsync(sp);

   if(sp > 0)
     while(drivePos() < dp) delay(20);
   else
     while(drivePos() > dp) delay(20);

   setSpeed(60);
   while(isDriving()) pros::delay(20);
 }

 /**************************************************/
 //drive modifiers
 void setSlant(int s){
   if(mirror)
     s = -s;

   slant = s;
 }

 void setCurrent(int mA){
   Chasis_L1.set_current_limit(mA);
   Chasis_L2.set_current_limit(mA);
   Chasis_R1.set_current_limit(mA);
   Chasis_R2.set_current_limit(mA);
 }

 void setBrakeMode(int mode){
   pros::motor_brake_mode_e_t brakeMode;
   switch(mode){
     case 0:
       brakeMode = MOTOR_BRAKE_COAST;
       break;
     case 1:
       brakeMode = MOTOR_BRAKE_BRAKE;
       break;
     case 2:
       brakeMode = MOTOR_BRAKE_HOLD;
       break;
   }

   Chasis_L1.set_brake_mode(brakeMode);
   Chasis_L2.set_brake_mode(brakeMode);
   Chasis_R1.set_brake_mode(brakeMode);
   Chasis_R2.set_brake_mode(brakeMode);
 }
 /**************************************************/
 // PID task
 void driveTask(void* parameter){
   int prevError = 0;
   setBrakeMode(1);

   while(auton_mode){
     pros::delay(20);

     if(driveMode != 1)
       continue;

     int sp = driveTarget;

     double kp = .3;
     double kd = .5;

     //read sensors
     int ls = Chasis_L1.get_position();
     int rs = Chasis_R1.get_position();
     int sv = ls;

     //speed
     int error = sp-sv;
     int derivative = error - prevError;
     prevError = error;
     int speed = error*kp + derivative*kd;

     if(speed > maxSpeed)
       speed = maxSpeed;
     if(speed < -maxSpeed)
       speed = -maxSpeed;

     //set motors
     leftSlew(speed - slant);
     rightSlew(speed + slant);
   }
 }

 void turnTask(void* parameter){
   int prevError;

   while(auton_mode){
   pros::delay(20);

     if(driveMode != 0)
       continue;

     int sp = turnTarget;

     if(sp > 0)
       sp *= 2.35;
     else
       sp *= 2.3;

     double kp = .9;
     double kd = 3.5;

     int sv = (Chasis_R1.get_position() - Chasis_L1.get_position())/2;
     int error = sp-sv;
     int derivative = error - prevError;
     prevError = error;
     int speed = error*kp + derivative*kd;

     if(speed > maxSpeed)
       speed = maxSpeed;
     if(speed < -maxSpeed)
       speed = -maxSpeed;

     leftSlew(-speed);
     rightSlew(speed);
     }
 }

 void driveOp(void* parameter){
   while(true){
   setCurrent(2500);
   setBrakeMode(0);
     // Chassis Control
     if(master.get_digital(DIGITAL_RIGHT) == 1){
       Task turn_task(turnTask);
       turn(-30);
       turn_task.remove();
     }
     else if(master.get_digital(DIGITAL_LEFT) == 1){
       Task turn_task(turnTask);
       turn(32);
       turn_task.remove();
     }
     else if(master.get_digital(DIGITAL_L2) == 1){
       Chasis_L1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_L2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_R1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_R2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_L1.move(0);
       Chasis_L2.move(0);
       Chasis_R1.move(0);
       Chasis_R2.move(0);
     }
     else{
       Chasis_L1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_L2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_R1.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
       Chasis_R2.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
      Chasis_L1.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
      Chasis_L2.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
      Chasis_R1.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
      Chasis_R2.move(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y));
    }
}
 }
