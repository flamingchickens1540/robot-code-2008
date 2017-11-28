#include "catlin.h"

#include <stdio.h>	//For NULL
#include <math.h>	//For sqrt

static struct action * add_action(struct action_queue *queue);
static void del_head(struct action_queue *queue);

void init_action_queue(struct action_queue * queue)
{
	queue->progress = queue->head = queue->num_actions = 0;
}

int is_action_queue_done(struct action_queue *queue)
{
	return queue->num_actions == 0;
}

struct action * get_action(struct action_queue *queue)
{
	if(queue->num_actions == 0)
		return NULL;

	return &queue->actions[queue->head];
}

int queue_pause(struct action_queue *queue, float seconds)
{
	struct action *a = add_action(queue);
	
	a->id = ACTION_PAUSE;
	a->actions.pause.time = seconds * CALLSPSEC;
	
	return TRUE;
}

int queue_arm(struct action_queue * queue, int arm_state, float timeout)
{
	struct action *a = add_action(queue);
	
	a->id = ACTION_ARM;
	a->actions.arm.state = arm_state;
	a->actions.arm.timeout = timeout * CALLSPSEC;
	
	return TRUE;
}

//1.0 = fullspeed counterclockwise, 0.0 = nothing, -1.0 = fullspeed clockwise
int queue_turn(struct action_queue *queue, float speed, float seconds)
{
	struct action *a = add_action(queue);
	
	if(speed < -1.0 || speed > 1.0)
		return FALSE;
	
	a->id = ACTION_TURN;
	a->actions.turn.time = seconds * CALLSPSEC;
	
	//Convert to numbers sutable for Brynmore's mecanum code
	a->actions.turn.speed = 127 + 127 * speed;
	
	return TRUE;
}

//1.0 = full speed forward, 0.0 = nothing, -1.0 = full speed backward
int queue_strafe(struct action_queue * queue, float x, float y, float seconds)
{
	struct action *a = add_action(queue);
	
	if(x < -1.0 || x > 1.0 || y < -1.0 || y > 1.0)
		return FALSE;

	x = -x;	//Adjust for retard mecanum code
	
	a->id = ACTION_STRAFE;
	a->actions.strafe.time = seconds * CALLSPSEC;
	
	//Convert to numbers sutable for Brynmore's mecanum code
	a->actions.strafe.xspeed = 127 + 127 * x;
	a->actions.strafe.yspeed = 127 + 127 * y;
	
	return TRUE;
}

int queue_pneumatics(struct action_queue * queue, int flags) {
	struct action *a = add_action(queue);
	
	a->id = ACTION_PNEUMATIC;
	a->actions.pneumatic.flags = flags;

	return TRUE;
}


int update_action_queue(struct action_queue *queue)
{
	int action_done = FALSE;
	struct action *a;

	monitorArmSensors();
	
	if(queue->num_actions <= 0)
		return FALSE;
	
	a = get_action(queue);
	switch(a->id) {
		case ACTION_STRAFE:
			mecanumStrafe(a->actions.strafe.xspeed, a->actions.strafe.yspeed);
			if(a->actions.strafe.time < queue->progress++) {
				action_done = TRUE;
				mecanumStop(); 
			}
			break;
		case ACTION_TURN:
			rotateLeft(a->actions.turn.speed);
			if(a->actions.turn.time < queue->progress++) {
				action_done = TRUE;
				mecanumStop(); 
			}
			break;
		case ACTION_PAUSE:
			if(a->actions.pause.time < queue->progress++)
				action_done = TRUE;
			break;
		case ACTION_ARM:
			requestArmState(a->actions.arm.state);
			if(getArmState() == a->actions.arm.state || a->actions.arm.timeout < queue->progress++)
				action_done = TRUE;
			break;
		case ACTION_PNEUMATIC:
			if(a->actions.pneumatic.flags & WRIST_UP) wristRaise();
			if(a->actions.pneumatic.flags & WRIST_DOWN) wristLower();
			if(a->actions.pneumatic.flags & CLOSE_GRIP) gripClose();
			if(a->actions.pneumatic.flags & OPEN_GRIP) gripOpen();
			if(a->actions.pneumatic.flags & RIGHT_REAR_HOLDER_UP) holderRearRightRaise();
			if(a->actions.pneumatic.flags & RIGHT_FRONT_HOLDER_UP) holderFrontRightRaise();
			if(a->actions.pneumatic.flags & LEFT_REAR_HOLDER_UP) holderRearLeftRaise();
			if(a->actions.pneumatic.flags & LEFT_FRONT_HOLDER_UP) holderFrontLeftRaise();
			if(a->actions.pneumatic.flags & RIGHT_REAR_HOLDER_DOWN) holderRearRightDrop();
			if(a->actions.pneumatic.flags & RIGHT_FRONT_HOLDER_DOWN) holderFrontRightDrop();
			if(a->actions.pneumatic.flags & LEFT_REAR_HOLDER_DOWN) holderRearLeftDrop();
			if(a->actions.pneumatic.flags & LEFT_FRONT_HOLDER_DOWN) holderFrontLeftDrop();
			if(a->actions.pneumatic.flags & RAISE_PLATFORM) liftRaise();
			if(a->actions.pneumatic.flags & LOWER_PLATFORM) liftLower();
			
			action_done = TRUE;
			break;
	}
	
	if(action_done) {
		del_head(queue);
		queue->progress = 0;
	}

	monitorArmSensors();

	return TRUE;
}

static struct action * add_action(struct action_queue *queue)
{
	int index;
	
	//make sure there's room to add the action
	if(queue->num_actions >= NUM_ACTIONS)
		return NULL;
	
	//compute new index
	index = (queue->head + queue->num_actions) % NUM_ACTIONS;
	
	//There's now one more action
	queue->num_actions++;
	
	return &queue->actions[index];
}

static void del_head(struct action_queue *queue)
{
	//sanity
	if(queue->num_actions <= 0)
		return;
	
	//Move head forward
	queue->head++;
	queue->head %= NUM_ACTIONS;
	
	queue->num_actions--;
}
