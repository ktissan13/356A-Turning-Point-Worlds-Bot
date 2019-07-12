#include "main.h"

Controller master(E_CONTROLLER_MASTER);
Controller partner(E_CONTROLLER_PARTNER);

void opcontrol(){
  TurnOnLED();
  auton_mode = false;
  _driveReset();
  _adjust(-1, 600);
  master.set_text(0, 0, "Hey, Yahya");
  adjustReset();
  puncherReset();
  mirror = false;
  rumble();
  Task puncher_task(puncherOp);
  Task adjuster_task(adjusterOp);
  Task driver_task(driveOp);
  Task intake_op(intakeOp);
  Task lift_task(liftOp);
}
