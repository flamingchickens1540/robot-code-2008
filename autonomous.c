#include <stdio.h>
#include "ifi_frc.h"
#include "pwm.h"
#include "timers.h"
#include "interrupts.h"
#include "serial_ports.h"
#include "ifi_code.h"
#include "autonomous.h"

#include "catlin.h"

//Different hydrid modes
#define AUTO_MOVE HYBRIDMODE1
#define GET_BALL HYBRIDMODE2

//Different actions
#define NUDGE_LEFT 0
#define NUDGE_RIGHT 1
#define NUDGE_BACK 3
#define TURN_LEFT 4

#define DEADMAN_TIMELIM (CALLSPSEC * 5)

static int auto_move_allowed = TRUE;

static void read_IR(void);
static void update_hybrid_state(void);

static struct action_queue turn_queue;

void Autonomous_Init(void)
{
	if(GET_BALL)
		liftRaise();
	
	auto_move_allowed = AUTO_MOVE;
	
	init_action_queue(&turn_queue);
}

void Autonomous(void)
{
	compressor();
	
	mecanumDrive(127, 127, 127);	//default to doing nothing
	
	update_hybrid_state();
	
	read_IR();	//IR commands override EVERYTHING
}

int monitor_fake_auto(void)
{/*
	static int last_press = 0;
	static int in_fake_auto = 0;
	
	int is_pressed = inRange(PRHSWITCH, 9, PRHSWITCHSPARE);
	if (!last_press && is_pressed) {
		if (in_fake_auto) {
			in_fake_auto = 0;
		} else {
			Autonomous_Init();
			in_fake_auto = 1;
		}
	}
	
	last_press = is_pressed;
	return in_fake_auto;*/
	return 0;
}
//127mid 20low, 253up
static void read_IR(void)
{
	static int nudge_timer = 0;
	static int nudge_dir;
	static int last_command_time = 0;	//Time since last command given
	int forward_speed;
	
	if(last_command_time < DEADMAN_TIMELIM)
		last_command_time++;
	else
		auto_move_allowed = FALSE;
	
	if(IRGREEN) {
		nudge_timer = 8;
		nudge_dir = NUDGE_RIGHT;
		auto_move_allowed = TRUE;
		last_command_time = 0;
	}
	if(IRYELLOW) {
		nudge_timer = 8;
		nudge_dir = NUDGE_LEFT;
		auto_move_allowed = TRUE;
		last_command_time = 0;
	}
	if(IRORANGE) {
		nudge_timer = 60;
		nudge_dir = NUDGE_BACK;
		last_command_time = 0;
		auto_move_allowed = TRUE;
	}
	if(IRBLUE) {
		nudge_timer = 27;
		nudge_dir = TURN_LEFT;
		
		//Queue turn
		/*if (is_action_queue_done(&turn_queue)) {
			queue_turn(&turn_queue, 0.5, 0.7);
			//queue_strafe(&turn_queue, 0.0, 0.5, 1.4);
			//queue_turn(&turn_queue, 0.5, 0.5);
		}*/
		
		auto_move_allowed = TRUE;
		liftRaise();
		last_command_time = 0;
	}
	
	if(!GET_BALL)	//If we're not getting the ball, then go forward really fast
		forward_speed = 127 + 100;
	else
		forward_speed = 127 + 50;
	
	if(nudge_timer > 0) {
		nudge_timer--;
		if(nudge_dir == NUDGE_RIGHT)
			mecanumDrive(127, forward_speed, 127 + 60);
		if(nudge_dir == NUDGE_LEFT)
			mecanumDrive(127, forward_speed, 127 - 60);
		if(nudge_dir == TURN_LEFT)
			mecanumDrive(127, 127, 127 + 64);
		if(nudge_dir == NUDGE_BACK)
			mecanumDrive(127, 127 - 50, 127);
	}
	
#if DEBUGPERSON == KEVIN
	User_Byte1 = IRORANGE;
	User_Byte2 = IRYELLOW;
	User_Byte3 = IRGREEN;
	User_Byte4 = IRBLUE;
	User_Byte5 = AUTO_MOVE;
	User_Byte6 = GET_BALL;
#endif
}

static void update_hybrid_state(void)
{
	static int state = 0;
	static int timer = 0;
	switch (state) {
		case 0:
			if (auto_move_allowed)
				mecanumDrive(127, 190, 127);
			
			if (WOBBLEFRONTRIGHT == WOBBLETRUE || WOBBLEFRONTLEFT == WOBBLETRUE){
				this code isn't done
				a timer needs to be set for the next state
				state = 1;
			}
			break;
		case 1:
			
	}
	if (auto_move_allowed)
		mecanumDrive(127, 190, 127);
	
	update_action_queue(&turn_queue);
}

void Autonomous_Spin(void)
{

}
