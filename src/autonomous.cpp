#include "main.h"
 bool highFlag;
 bool middleFlag;
 int distance_temp;
 int distance_temp2;
 static int frontHigh = 19;
 static int frontMiddle = 98;
 static int backHigh = 55;
 static int backMiddle = 130;

 // Program on red side and then use mirror function when testing on blue
 // If need to program on blue side just make sure mirror function is true

 /*********************************************************/
 // Finish fixing for blue
 void frontAuton_10P(){

   //intake ball under the nearest cap
   intakeBallAsync();
   drive(1.56 TL);

   //back up against wall
   drive(-1.61 TL);
   adjustAsync(47);


  //toggle flag column
   wallToFlag();
   loadBallAsync();
   lowFlag();

   //backup to align with next cap
   drive(-1 TL);

   //line up with the walls
   adjustAsync(frontMiddle);
   turn(-92);
   loadbreak = true;
   drive(-.65 TL);


   //flip next cap
   intake(-600);
   drive(1.6 TL);

   //shoot flags in the center
   intake(0);
   turn(64);
   shoot();
 }


 /*********************************************************/
 void backAuton_9P(){
   // Come Foward
   drive(-.25 TL);
   if(mirror == false){
   turn(-30);
 }
 else{
   turn(-24);
 }
  // Go to back cap
   drive(-1.184 TL);
   liftFast(40);
   delay(350);
   liftFast(0);
   // Go Forward a bit
   drive(0.1 TL);
   // Face Platform
   turn(-56);
   drive(0.6 TL);
   // Face Cap
   turn(-85);
   // Intake Ball under cap
   intakeBallAsync();
   if (mirror == false){
     drive(0.624 TL);
   }
   else{
   drive(0.599 TL);
 }
   drive(-0.2 TL);
   turn (90);
   if(mirror == false){
   drive(0.45 TL);
 }
 else{
   drive(0.75 TL);
 }
   drive(-0.2 TL);
   turn(-20);
   backdoubleShot();
   turn(180);
   liftFast(25);
   drive(-1.2 TL);

 }


 /*********************************************************/
 void Backalt(){
   /*
   //intake ball under the nearest cap
   intakeBallAsync();
   drive(1.9 TL);

   //back up against wall
   drive(-1.9 TL);

   delay(1000);

   //align and shoot flags
   backToFront();
   wallToFlag();

   //park
   drive(-1 TL);
   turn(-90);
   alliancePark();
   */
 }

 void frontAuton_attack(){
   //intake ball under the nearest cap
   intakeBallAsync();
   adjustAsync(68);
   drive(1.58 TL);
   turn(49);
   wait(5);
   shoot();
   adjustAsync(146);
   loadBall();
   shoot();
   liftFast(20);
   turn(-41);
   drive(-.2 TL);
   turn(84);
   drive(-1.08 TL);
   liftFast(0);

 }

 void frontAuton_park(){
   //intake ball under the nearest cap
   intakeBallAsync();
   drive(1.58 TL);

   //back up against wall
   drive(-1.61 TL);
   adjustAsync(47);


  //toggle flag column
   wallToFlag();
   loadBallAsync();
   turn(-12);
   lowFlag();

   //backup to align with next cap
   drive(-2.58 TL);
   turn(92);
   loadbreak = true;
   drive(.65 TL);
   liftFast(20);
   slowDrive(-4 TL);


 }

 void autonomous() {
   // This will run the tasks for auton and turns it off after auton is done
   auton_mode = true;
   // if true it will hit high flag
   highFlag = false;
   // if true it will hit the middle flag
   middleFlag = false;
   // if true then auton will work for blue
   mirror = false;
   _driveReset(); // reset the drive encoders
   intakeReset(); // reset the intake encoders
   Task Ultra_Task(ultrasonic);
   Task drive_task(driveTask);
   //Task drive_task(auton_drive_task);
   Task turn_task(turnTask);
   Task adjust_task(adjustTask);
   Task intake_task(intakeTask);
   // Task launcher_task(launcherTask);



  /*if(auton_sel == 1){
    frontAuton_10P();
  }
    else if(auton_sel == 2){**/
   //backAuton_9P();
    /*}
    else if(auton_sel == 3){
    frontAuton_attack();
    }
    else if(auton_sel == 4){*/
    intake2ndBall();
  /*  }
    else if (auton_sel == 7){
    //newSkills();
  }*/

   drive_task.remove();
   turn_task.remove();
   adjust_task.remove();
   intake_task.remove();
   // launcher_task.remove();

   _driveReset(); // make sure no motors are moving
   rumble(); // Tell drivers that auton is done
   _adjust(0, 200); // reset adjuster
 }
