 /****************************************************************
These are functions designed to manipulate the pneumatics
****************************************************************/

#include "catlin.h"
#include "pneumatics.h"
#include <stdio.h>

//This wasn't prototyped.
int inRange (int testValue, int midPoint, int range);
int wristState = WRISTRAISED;

void switchboardTriggers(void){
	LEDs();
	compressor();
	
//checks each of the 4 containment pillar switches---------------
//might change if switchs are actually push buttons
	if (inRange(HOLDERFRONTRIGHTSWITCH, 30, HOLDERSWITCHHIGH)){
		holderFrontRightRaise();
	}else if (inRange(HOLDERFRONTRIGHTSWITCH, 30, HOLDERSWITCHLOW) || DROPALLHURDLESWITCH == ON){
		holderFrontRightDrop();
	}
	if (inRange(HOLDERFRONTLEFTSWITCH, 30, HOLDERSWITCHHIGH)){
		holderFrontLeftRaise();
	}else if (inRange(HOLDERFRONTLEFTSWITCH, 30, HOLDERSWITCHLOW) || DROPALLHURDLESWITCH == ON){
		holderFrontLeftDrop();
	}
	if (inRange(HOLDERREARRIGHTSWITCH, 30, HOLDERSWITCHHIGH)){
		holderRearRightRaise();
	}else if (inRange(HOLDERREARRIGHTSWITCH, 30, HOLDERSWITCHLOW) || DROPALLHURDLESWITCH == ON){
		holderRearRightDrop();
	}
	if (inRange(HOLDERREARLEFTSWITCH, 30, HOLDERSWITCHHIGH)){
		holderRearLeftRaise();
	}else if (inRange(HOLDERREARLEFTSWITCH, 30, HOLDERSWITCHLOW) || DROPALLHURDLESWITCH == ON){
		holderRearLeftDrop();
	}
	
//checks state of platform switch
	if (LIFTUPSWITCH == LIFTSWITCHON){
		liftRaise();
	}else if (LIFTDOWNSWITCH == LIFTSWITCHON){
		liftLower();
	}
	
	if (inRange(WRISTSWITCH, 30, WRISTSWITCHRAISE)){
		wristRaise();
	}else if (inRange(WRISTSWITCH, 30, WRISTSWITCHLOWER)){
		wristLower();
	}
		
/*---------------------------------------------------------------
------do not run these functions when the gripper is stowed------
---------------------------------------------------------------*/

//Checks grip switch---------------------------------------------
	if (inRange(GRIPPERSWITCH, 30, GRIPPERSWITCHOPEN)){
		gripOpen();
	}else if (inRange(GRIPPERSWITCH, 30, GRIPPERSWITCHCLOSE) || JOYSTICKGRIPSWITCH == ON){
		gripClose();
	}
}

void LEDs (void){
	if (HOLDERFRONTRIGHTRELAY == HOLDERRAISED){
		FRONT_RIGHT_LED = LEDON;
	}else{
		FRONT_RIGHT_LED = LEDOFF;
	}
	if (HOLDERFRONTLEFTRELAY == HOLDERRAISED){
		FRONT_LEFT_LED = LEDON;
	}else{
		FRONT_LEFT_LED = LEDOFF;
	}
	if (HOLDERREARRIGHTRELAY == HOLDERRAISED){
		REAR_RIGHT_LED = LEDON;
	}else{
		REAR_RIGHT_LED = LEDOFF;
	}
	if (HOLDERREARLEFTRELAY == HOLDERRAISED){
		REAR_LEFT_LED = LEDON;
	}else{
		REAR_LEFT_LED = LEDOFF;
	}
	STOW_LED = isStowed? LEDON:LEDOFF;
}

/*void prepare (void){
	queue_arm(&queue, ARMSTOPTOP, 5);
	queue_pneumatics(&queue, WRIST_UP);
	holderRearRightRaise();
	holderRearLeftRaise();
	holderFrontRightDrop();
	holderFrontLeftDrop();
}

void release (void){
	queue_pneumatics(&queue, OPEN_GRIP);
	queue_pneumatics(&queue, RIGHT_FRONT_HOLDER_UP | LEFT_FRONT_HOLDER_UP | RIGHT_REAR_HOLDER_UP | LEFT_REAR_HOLDER_UP );
	queue_arm(queue, ARMSTOPSTORE, 5);
}*/

int inRange (int testValue, int range, int midPoint){
	int highBound = midPoint + range;
	int lowBound = midPoint - range;
	if (testValue <= highBound && testValue >= lowBound)
		return TRUE;
	else
		return FALSE;
}

void gripOpen (void){
	if (isStowed == FALSE){
		GRIPRELAY = GRIPOPENED;
	}
}

void gripClose (void){
	GRIPRELAY = GRIPCLOSED;
}

void holderFrontRightRaise (void){
	HOLDERFRONTRIGHTRELAY = HOLDERRAISED;
}

void holderFrontRightDrop (void){
	HOLDERFRONTRIGHTRELAY = HOLDERDROPPED;
}

void holderFrontLeftRaise (void){
	HOLDERFRONTLEFTRELAY = HOLDERRAISED;
}

void holderFrontLeftDrop (void){
	HOLDERFRONTLEFTRELAY = HOLDERDROPPED;
}

void holderRearRightRaise (void){
	HOLDERREARRIGHTRELAY = HOLDERRAISED;
}

void holderRearRightDrop (void){
	HOLDERREARRIGHTRELAY = HOLDERDROPPED;
}

void holderRearLeftRaise (void){
	HOLDERREARLEFTRELAY = HOLDERRAISED;
}

void holderRearLeftDrop (void){
	HOLDERREARLEFTRELAY = HOLDERDROPPED;
}

void liftRaise (void){
	if (getArmState() != ARMSTOPTOP || (getArmState() == ARMSTOPTOP && getWristState() == WRISTLOWERED))
		LIFTRELAY = LIFTRAISED;
}

void liftLower (void){
	LIFTRELAY = LIFTLOWERED;
}

void wristRaise (void){
	int height;
	height = getArmState();
	if (height == ARMSTOPSTORE || (height == ARMSTOPTOP && LIFTRELAY == LIFTLOWERED)){
		UPWRIST = WRISTENABLED;
		DOWNWRIST = WRISTDISABLED;
		wristState = WRISTRAISED;
		if (height == ARMSTOPSTORE)
			isStowed = TRUE;
	}
}

void wristLower (void){
	UPWRIST = WRISTDISABLED;
	DOWNWRIST = WRISTENABLED;
	wristState = WRISTLOWERED;
	isStowed = FALSE;
}

int getWristState (void){
	return wristState;
}

void compressor (void){
	if (PRESSUREVALVE == LOWPRESSURE){
		COMPRESSOR_LED = OILEDON;
		COMPRESSORRELAY = COMPRESSORON;
	}else{
		COMPRESSOR_LED = OILEDOFF;
		COMPRESSORRELAY = COMPRESSOROFF;
	}
}

