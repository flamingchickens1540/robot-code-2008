/****************************************************************
Functions for changing the states of pneumatics
****************************************************************/

#ifndef _pneumatics_h
#define _pneumatics_h


#define ANALOGSWITCHERROR			9

//variables used for calling state setting functions
#define OPEN 		1
#define RAISED		1
#define CLOSED		0
#define DROPPED		0
#define LOWERED		0

#define WRISTUP			1
#define WRISTDOWN		0

//Variables for LEDs
#define FRONT_RIGHT_LED			Pwm1_green
#define FRONT_LEFT_LED			Pwm2_green
#define REAR_RIGHT_LED			Pwm1_red
#define REAR_LEFT_LED			Pwm2_red

//constants for checking state of wrist
#define WRISTRAISED			1
#define WRISTLOWERED		0
#define WRISTERROR			42

//variables used for the switchboard code
//add values in place of "unknown"
#define TRIGGERED				0
#define NOT_TRIGGERED			1

#define GRIP_STATE				p1_aux
#define GRIP_STATE_UP			15
#define GRIP_STATE_DOWN			246

#define FRONT_RIGHT_SWITCH		p2_x
#define FRONT_RIGHT_STATE_UP	246
#define FRONT_RIGHT_STATE_DOWN	15
#define FRONT_LEFT_SWITCH		p2_y
#define FRONT_LEFT_STATE_UP		246
#define FRONT_LEFT_STATE_DOWN	15
#define BACK_RIGHT_SWITCH		p2_wheel
#define BACK_RIGHT_STATE_UP		246
#define BACK_RIGHT_STATE_DOWN	15
#define BACK_LEFT_SWITCH		p2_aux
#define BACK_LEFT_STATE_UP		246
#define BACK_LEFT_STATE_DOWN	15

#define LIFT_STATE_UP			p2_sw_top
#define LIFT_STATE_DOWN			p2_sw_trig

#define WRIST_STATE				p1_wheel
#define WRIST_STATE_UP			246
#define WRIST_STATE_DOWN		15

#define STOW_STATE				p1_sw_trig
#define STOW_STATE_ON			TRIGGERED
#define STOW_STATE_OFF			NOT_TRIGGERED

#define MISC_SWITCH_VALUE		p1_y
#define MISC_HURDLE_DOWN		225
#define MISC_PREP_HOPPER		180
#define MISC_DROP_BALL			160
#define MISC_HURDLE_UP			246


//Functions for changing the states of variables

/*This function reads the (currently non-existant) switchboard and adjusts the states of the pneumatics accordingly
No inputs
No ouputs - adjusts values of pneumatic cylinders*/
void switchboardTriggers (void);

/*These functions set the state of the gripper
No inputs, use correct function to achieve desired state
No outputs - adjusts state of grip cylinders*/
void gripOpen(void);
void gripClose(void);

/*These functions set the states of the cylinder that holds the ball in place. Each adjusts the cylinder in the name of the function
No inputs - use correct function to achieve desired results
No outputs - adjusts state of cylinder in title of function*/
void holderFrontRightRaise (void);
void holderFrontRightDrop (void);
void holderFrontLeftRaise (void);
void holderFrontLeftDrop (void);
void holderRearRightRaise (void);
void holderRearRightDrop (void);
void holderRearLeftRaise (void);
void holderRearLeftDrop (void);

/*These functions adjust the state of the platform that the ball will rest on
No inputs - use correct function to achieve desired results
No ouputs - changes position of platform*/
void liftRaise (void);
void liftLower (void);

/*These functions adjust the state of the wrist
No inputs - use correct function to achieve desired results
No outputs - raises or lowers wrist*/
void wristRaise (void);
void wristLower (void);

/*This function determines the state of the wrist - raised or lowered
No inputs
Outputs - int state of wrist (WRISTRAISED, WRISTLOWERED)*/
int getWristState (void);

/*This function manages the cylinder - keeps it from overloading and keeps it from running out
No inputs
No outputs - adjusts state of cylinder to keep it full*/
void compressor (void);

/*This function sets the holder LEDs according to the state of the holders - up is on, down is off
No inputs
No ouputs - adjusts light*/
void LEDs (void);
// Quit getting rid of this declaration.  It causes bad shit to happen when other people use it.
int inRange (int testValue, int midPoint, int range);
#endif