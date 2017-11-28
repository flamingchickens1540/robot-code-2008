#include "catlin.h"

//void updateWobbleSwitches(void);

static struct action_queue queue;
//static struct action_queue queue;

//static int rrWobbleCount = 0;
//static int rlWobbleCount = 0;
// int frWobbleCount = 0;
 //int flWobbleCount = 0;
// static int rlWobbleState = ! WOBBLETRUE; // not wobble true
//static int rrWobbleState = ! WOBBLETRUE; // not wobble true
//static int flWobbleState = ! WOBBLETRUE; // not wobble true
//static int frWobbleState = ! WOBBLETRUE; // not wobble true

int is_hurdling = FALSE;
int is_placing = FALSE;
int is_preparing = FALSE;
int is_releasing = FALSE;
int is_stowing = FALSE;
//int is_takingoff = FALSE;
int is_displace_catching = FALSE;
int is_software_drive = FALSE;

static int queue_being_used = FALSE;


#define MAKE_MONITOR_FUNC(func, callback, condition, is_doing) \
void func(void); \
void func () \
{ \
	if( (condition) && !queue_being_used) { \
		is_doing = TRUE; \
	} \
	if(is_doing) { \
		is_doing = callback (); \
	} \
} \

#define MAKE_MONITOR_FUNC_LED(func, callback, condition, is_doing, led_name) \
void func(void); \
void func () \
{ \
	if( (condition) && !queue_being_used) { \
		is_doing = TRUE; \
	} \
	led_name = LEDOFF; \
	if(is_doing) { \
		led_name = LEDON; \
		is_doing = callback (); \
	} \
} \

MAKE_MONITOR_FUNC(monitor_prepare, prepare, inRange(PRHSWITCH, 9, PRHSWITCHPREPARE), is_preparing)
MAKE_MONITOR_FUNC(monitor_release, release, inRange(PRHSWITCH, 9, PRHSWITCHRELEASE), is_releasing)
MAKE_MONITOR_FUNC_LED(monitor_hurdle, hurdle, inRange(PRHSWITCH, 9, PRHSWITCHHURDLE) || JOYSTICKHURDLESWITCH == ON, is_hurdling, HURDLE_LED)
MAKE_MONITOR_FUNC_LED(monitor_place, place, inRange(PRHSWITCH, 9, PRHSWITCHPLACE) || JOYSTICKPLACESWITCH == ON, is_placing, PLACE_LED)
MAKE_MONITOR_FUNC(monitor_stow, stow, STOWSWITCH == STOWSWITCHON, is_stowing)
//MAKE_MONITOR_FUNC_LED(monitor_takeoff, takeoff, inRange(PRHSWITCH, 9, PRHSWITCHSPARE), is_takingoff, SPARE_LED)
MAKE_MONITOR_FUNC_LED(monitor_displace_catch, displace_catch, inRange(PRHSWITCH, 9, PRHSWITCHSPARE), is_displace_catching, SPARE_LED)
void monitor_auto()
{
	monitor_prepare();
	monitor_release();
	monitor_hurdle();
	monitor_place();
	monitor_stow();
//	monitor_takeoff();
	monitor_displace_catch();
}

int displace_catch(void)
{
	static int is_first_call = TRUE;
	static int state = 0;
	
	if(is_first_call) {
		init_action_queue(&queue);
		state = 0;
		is_first_call = FALSE;
	}
	
	switch(state) {
		case 0:
			liftRaise();
			holderFrontRightDrop();
			holderFrontLeftDrop();
			holderRearRightDrop();
			holderRearLeftDrop();
			break;
		case 1:
			if(WOBBLEFRONTLEFT == WOBBLETRUE || WOBBLEFRONTRIGHT == WOBBLETRUE) {
				state = 2;
			}
			break;
		case 2:
			if(WOBBLEREARLEFT == WOBBLETRUE || WOBBLEREARRIGHT == WOBBLETRUE)
				state = 3;
			break;
		case 3:
			if(WOBBLEFRONTLEFT == WOBBLETRUE || WOBBLEFRONTRIGHT == WOBBLETRUE)
				state = 4;
			break;
		case 4:
			if(WOBBLEREARLEFT == WOBBLETRUE || WOBBLEREARRIGHT == WOBBLETRUE) {
				queue_pneumatics(&queue, LOWER_PLATFORM);
				queue_pause(&queue, 0.3);
				queue_pneumatics(&queue, RIGHT_REAR_HOLDER_UP | RIGHT_FRONT_HOLDER_UP | LEFT_REAR_HOLDER_UP | LEFT_FRONT_HOLDER_UP);
				state = 5;
			}
		case 5:
			if(is_action_queue_done(&queue)) {
				is_first_call = FALSE;
				return FALSE;
			}
			break;
	}
	
	update_action_queue(&queue);
	
	return TRUE;
}

int takeoff()
{
	static int is_first_call = TRUE;
	
	if (is_first_call)
	{
		init_action_queue(&queue);
		//queue_pneumatics(&queue, LOWER_PLATFORM | WRIST_DOWN);
		//queue_pause(&queue, 2.0);
		queue_pneumatics(&queue, OPEN_GRIP);
		queue_arm(&queue, ARMSTOPTOP, 6.0);
		queue_pneumatics(&queue, OPEN_GRIP);
		queue_pneumatics(&queue, WRIST_UP | RIGHT_FRONT_HOLDER_DOWN | LEFT_FRONT_HOLDER_DOWN);
		queue_pause(&queue, 2.3);
		queue_pneumatics(&queue, CLOSE_GRIP);
		queue_pause(&queue, 3.0);
		queue_pneumatics(&queue, WRIST_DOWN);
		queue_pause(&queue, 4.0);
		queue_arm(&queue, ARMSTOPSTORE, 6.0);
		is_first_call = FALSE;
		queue_being_used = TRUE;
	}
	
	if (is_action_queue_done(&queue) || CANCELSWITCH == ON)
	{
		is_first_call = TRUE;
		queue_being_used = FALSE;
		if(CANCELSWITCH == ON)
			requestArmState(getArmState());
		return FALSE;
	}
	
	update_action_queue(&queue);
	
	return TRUE;
}

int prepare()
{
	static int is_first_call = TRUE;
	
	if(is_first_call) {
		init_action_queue(&queue);
		queue_pneumatics(&queue, LOWER_PLATFORM | RIGHT_REAR_HOLDER_UP | LEFT_REAR_HOLDER_UP | RIGHT_FRONT_HOLDER_DOWN | LEFT_FRONT_HOLDER_DOWN);
		queue_arm(&queue, ARMSTOPTOP, 6.0);
		queue_pneumatics(&queue, WRIST_UP);
		is_first_call = FALSE;
		queue_being_used = TRUE;
	}
	
	if(is_action_queue_done(&queue) || CANCELSWITCH == ON)
	{
		is_first_call = TRUE;
		queue_being_used = FALSE;
		if(CANCELSWITCH == ON)
			requestArmState(getArmState());
		return FALSE;
	}
	
	update_action_queue(&queue);
	
	return TRUE;
}


int release()
{
	static int is_first_call = TRUE;
	
	if(is_first_call) {
		init_action_queue(&queue);
		queue_pneumatics(&queue, OPEN_GRIP | RIGHT_REAR_HOLDER_UP | LEFT_REAR_HOLDER_UP | RIGHT_FRONT_HOLDER_UP | LEFT_FRONT_HOLDER_UP);
		queue_pause(&queue, 1.5);
		queue_pneumatics(&queue, WRIST_DOWN);
		queue_pause(&queue, 1.0);
		//queue_pneumatics(&queue, CLOSE_GRIP);
		queue_arm(&queue, ARMSTOPBOTTOM, 4.0);
		is_first_call = FALSE;
		queue_being_used = TRUE;
	}

	if(is_action_queue_done(&queue) || CANCELSWITCH == ON) {
		queue_being_used = FALSE;
		is_first_call = TRUE;
		if(CANCELSWITCH == ON)
			requestArmState(getArmState());
		return FALSE;
	}
	
	update_action_queue(&queue);
	
	return TRUE;
}

int hurdle()
{
	static int is_first_call = TRUE;
	static char has_been_tripped = FALSE;
	static int wobble_r = FALSE, wobble_l = FALSE;
	if(is_first_call) {
		if (LIFTRELAY != LIFTRAISED)
			return FALSE;
		init_action_queue(&queue);
		is_software_drive = TRUE;
		softwareDriveSpeed = HURDLESPEED;
		has_been_tripped = FALSE;
		// Eric wanted the platform to be manually controlled
		//queue_pneumatics(&queue, RAISE_PLATFORM);
		//queue_pause(&queue, 1.0);
		queue_pneumatics(&queue, LEFT_FRONT_HOLDER_DOWN | RIGHT_FRONT_HOLDER_DOWN);
		is_first_call = FALSE;
		wobble_l = wobble_r = FALSE;
		queue_being_used = TRUE;
		
		#if DEBUGPERSON == EMESS
			User_Byte1 = 1; 
		#endif


	}
	
	if(WOBBLEFRONTRIGHT == WOBBLETRUE)
		wobble_r = TRUE;
	if(WOBBLEFRONTLEFT == WOBBLETRUE)
		wobble_l = TRUE;
	
	//Check to see if both of the front two wobbles have been wobbled
	if((wobble_l && wobble_r) && !has_been_tripped) {
		holderRearLeftDrop();
		holderRearRightDrop();
		
		#if DEBUGPERSON == EMESS
//			User_Byte1 = 2;
		#endif

		is_software_drive = FALSE;
		queue_strafe(&queue, 0, -0.2, 0.25);
		queue_strafe(&queue, 0, -0.25, 1.0);
		queue_strafe(&queue, 0, 0.2, 0.1);
		//queue_pause(&queue, 1.0);
		//queue_strafe(&queue, 1.0, 0, 1.0);
		has_been_tripped = TRUE;
		//queue_pause(&queue, 1.0);
		

	}
	
	#if DEBUGPERSON == EMESS
			//User_Byte2 = is_action_queue_done(&queue); 
	#endif

	if ((wobble_l && wobble_r) && is_action_queue_done(&queue))
	{
		
		#if DEBUGPERSON == EMESS
			User_Byte1 = 3;
		#endif

		maxSpeed = 127;
		is_first_call = TRUE;
		is_software_drive = FALSE;
		queue_being_used = FALSE;
		return FALSE;
	}
	
	if (CANCELSWITCH == ON)
	{
		is_first_call = TRUE;
		is_software_drive = FALSE;
		queue_being_used = FALSE;
		return FALSE;
	}
	
	//Just in case
	/*if(WOBBLEREARLEFT == WOBBLETRUE)
		holderRearLeftDrop();
	if(WOBBLEREARRIGHT == WOBBLETRUE)
		holderRearRightDrop();*/
	
	/*if(rlWobbleCount > 0 && rrWobbleCount > 0 && is_action_queue_done(&queue)) {
		is_first_call = TRUE;
		queue_being_used = FALSE;
		maxSpeed = 127;
		is_software_drive = FALSE;
		return FALSE;
	}*/
	
	update_action_queue(&queue);
	//updateWobbleSwitches();
	
	return TRUE;
}

int place()
{
	static int is_first_call = TRUE;
	static char has_been_tripped = FALSE;
	static int wobble_r = FALSE, wobble_l = FALSE;
	if(is_first_call) {
		if (LIFTRELAY != LIFTRAISED)
			return FALSE;
		init_action_queue(&queue);
		is_software_drive = TRUE;
		softwareDriveSpeed = PLACESPEED;
		has_been_tripped = FALSE;
		// Eric wanted the platform to be manually controlled
		//queue_pneumatics(&queue, RAISE_PLATFORM);
		//queue_pause(&queue, 1.0);
		queue_pneumatics(&queue, LEFT_FRONT_HOLDER_DOWN | RIGHT_FRONT_HOLDER_DOWN);
		is_first_call = FALSE;
		//rlWobbleCount = rrWobbleCount = 0;
		//flWobbleCount = frWobbleCount = 0;
		wobble_r = wobble_l = FALSE;
		queue_being_used = TRUE;
		
		#if DEBUGPERSON == EMESS
			User_Byte1 = 1; 
		#endif
	}
	
	if(WOBBLEFRONTRIGHT == WOBBLETRUE)
		wobble_r = TRUE;
	if(WOBBLEFRONTLEFT == WOBBLETRUE)
		wobble_l = TRUE;
	
	//Check to see if both of the front two wobbles have been wobbled
	if((wobble_r && wobble_l) && !has_been_tripped){
		liftLower();
		holderRearLeftDrop();
		holderRearRightDrop();
		
		#if DEBUGPERSON == EMESS
			User_Byte1 = 2;
		#endif

		is_software_drive = FALSE;
		queue_strafe(&queue, 0, -0.2, 0.25);
		queue_strafe(&queue, 0, -0.25, 0.45);
		queue_strafe(&queue, 0, 0.2, 0.1);
		//queue_pause(&queue, 1.0);
		//queue_strafe(&queue, 1.0, 0, 1.0);
		has_been_tripped = TRUE;
		//queue_pause(&queue, 1.0);
		

	}
	
	#if DEBUGPERSON == EMESS
//			User_Byte2 = is_action_queue_done(&queue); 
	#endif

	if ((wobble_r && wobble_l) && is_action_queue_done(&queue))
	{
		
		#if DEBUGPERSON == EMESS
			//User_Byte1 = 3;
		#endif

		//maxSpeed = 0;
		is_first_call = TRUE;
		is_software_drive = FALSE;
		queue_being_used = FALSE;
		return FALSE;
	}
	
	if (CANCELSWITCH == ON)
	{
		is_first_call = TRUE;
		is_software_drive = FALSE;
		queue_being_used = FALSE;
		return FALSE;
	}
	
	//Just in case
	/*if(WOBBLEREARLEFT == WOBBLETRUE)
		holderRearLeftDrop();
	if(WOBBLEREARRIGHT == WOBBLETRUE)
		holderRearRightDrop();*/
	
	/*if(rlWobbleCount > 0 && rrWobbleCount > 0 && is_action_queue_done(&queue)) {
		is_first_call = TRUE;
		queue_being_used = FALSE;
		//maxSpeed = 0;
		return FALSE;
	}*/
	
	update_action_queue(&queue);
	//updateWobbleSwitches();
	
	return TRUE;
}


int stow()
{
	static int is_first_call = TRUE;
	
	if(is_first_call) {
		init_action_queue(&queue);
		queue_pneumatics(&queue, CLOSE_GRIP);
		queue_arm(&queue, ARMSTOPSTORE, 6.0);
		queue_pause(&queue, 0.5);
		queue_pneumatics(&queue, WRIST_UP);
		is_first_call = FALSE;
		queue_being_used = TRUE;
	}
	
	if(is_action_queue_done(&queue) || CANCELSWITCH == ON)
	{
		is_first_call = TRUE;
		isStowed = TRUE;
		queue_being_used = FALSE;
		if(CANCELSWITCH == ON)
			requestArmState(getArmState());
		return FALSE;
	}
	
	update_action_queue(&queue);
	
	return TRUE;
}

//Adds one to each wobblecount if the wobble is wobbling
//void updateWobbleSwitches() {
	//If it's started wobbling, then flag it as wobbling and increment the count of wobbles
//	/*
//	if(WOBBLEFRONTLEFT == WOBBLETRUE) {
//		if(flWobbleState != WOBBLETRUE) {
//			flWobbleState = WOBBLETRUE;
//			flWobbleCount++;
//		}
//	}
//	//If it's stopped wobbling, then change the state
//	if(WOBBLEFRONTLEFT != WOBBLETRUE) {
//		if(flWobbleState == WOBBLETRUE) flWobbleState = ! WOBBLETRUE;
//	}
//	if(WOBBLEFRONTRIGHT == WOBBLETRUE) {
//		if(frWobbleState != WOBBLETRUE) {
//			frWobbleState = WOBBLETRUE;
//			frWobbleCount++;
//		}
//	}
//	if(WOBBLEFRONTRIGHT != WOBBLETRUE) {
//		if(frWobbleState == WOBBLETRUE) frWobbleState = ! WOBBLETRUE;
//	}*/
	/*if(WOBBLEREARRIGHT == WOBBLETRUE) {
		if(rrWobbleState != WOBBLETRUE) {
			rrWobbleState = WOBBLETRUE;
			rrWobbleCount++;
		}
	}
	if(WOBBLEREARRIGHT != WOBBLETRUE) {
		if(rrWobbleState == WOBBLETRUE) rrWobbleState = ! WOBBLETRUE;
	}
	if(WOBBLEREARLEFT == WOBBLETRUE) {
		if(rlWobbleState != WOBBLETRUE) {
			rlWobbleState = WOBBLETRUE;
			rlWobbleCount++;
		}
	}
	if(WOBBLEREARLEFT != WOBBLETRUE) {
		if(rlWobbleState == WOBBLETRUE) rlWobbleState = ! WOBBLETRUE;
	}*/
//}
