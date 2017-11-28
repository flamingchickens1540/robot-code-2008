#ifndef _ACTION_H_
#define _ACTION_H_

#define ACTION_STRAFE 				0
#define ACTION_TURN 				1
#define ACTION_PAUSE 				2
#define ACTION_PNEUMATIC			3
#define ACTION_ARM					4

#define WRIST_UP					1
#define WRIST_DOWN					2
#define CLOSE_GRIP					4
#define OPEN_GRIP					8
#define RIGHT_REAR_HOLDER_UP		16
#define RIGHT_FRONT_HOLDER_UP		32
#define LEFT_REAR_HOLDER_UP			64
#define LEFT_FRONT_HOLDER_UP		128
#define RIGHT_REAR_HOLDER_DOWN		256
#define RIGHT_FRONT_HOLDER_DOWN		512
#define LEFT_REAR_HOLDER_DOWN		1024
#define LEFT_FRONT_HOLDER_DOWN		2048
#define RAISE_PLATFORM				4096
#define LOWER_PLATFORM				8192

//Arbitrary cap
#define NUM_ACTIONS	10	
//max number of actions in queue

struct arm_action {
	int state;
	int timeout;	//JP why did you remove this?
};

struct strafe_action {
	unsigned char xspeed, yspeed;	//vertical and horizontal speeds
	int time;
};

struct turn_action {
	unsigned char speed;
	int time;
};

struct pause_action {
	int time;
};

struct pneumatic_action {
	int flags;
	// int time:  don't need this, because will always be 0
	// above comment: don't need it, because will always be obvious :/
};

union all_actions {
	struct strafe_action strafe;
	struct turn_action turn;
	struct pause_action pause;
	struct pneumatic_action pneumatic;
	struct arm_action arm;
};

struct action {
	unsigned char id;
	union all_actions actions;
};

struct action_queue {
	int progress;
	int head, num_actions;
	struct action actions[NUM_ACTIONS];
};

void init_action_queue(struct action_queue * queue);
int update_action_queue(struct action_queue * queue);
void kill_action_queue(struct action_queue * queue);

int is_action_queue_done(struct action_queue * queue);
struct action * get_action(struct action_queue * queue);

int queue_pause(struct action_queue * queue, float seconds);
int queue_turn(struct action_queue * queue, float speed, float seconds);
int queue_strafe(struct action_queue * queue, float x, float y, float seconds);
int queue_arm(struct action_queue * queue, int arm_state, float timeout);
int queue_pneumatics(struct action_queue * queue, int flags);

#endif
