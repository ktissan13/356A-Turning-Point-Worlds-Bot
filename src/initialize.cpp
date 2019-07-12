#include "main.h"

bool auton_mode = false;

bool loadbreak = false;

bool mirror = false;

int intake_speed = 0;

int auton_sel = 0;


ADIAnalogOut LED (2);

void TurnOnLED(){
	LED = ADI_LEGACY_PWM;
}


void initialize() {
	Task lcd_task(gui);
	partner.set_text(0, 0, "Hey, Tissan");
}

void disabled() {}

void competition_initialize() {}
