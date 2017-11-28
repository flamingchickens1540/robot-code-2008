
#ifndef _arm_h
#define _arm_h
void requestArmState(int reqState);
int getArmState(void);
void monitorArmSensors(void);
void monitorArmUi(void);
extern int armheight;
#define REACHEDSTATE		0
#define ARMSTOPBOTTOM		1
#define ARMSTOPSTORE		2
#define ARMSTOPTOP			3
#define ARMSTOPPED			4
#define ARMMOVEUP			5
#define ARMMOVEDOWN			6
#define ARMSLOWUP			7
#define ARMSLOWDOWN			8
#define ARMENCB				rc_dig_in07 
#define ARMGOHIGH			253
#define ARMGOSTORE			215
#define ARMGOLOW			190
#define ARMGODOWN			168
#define ARMGOUP				150
#define ARMSTOP				20
#define TRIPLIM				0
#define ARMFULLUPSPEED		(127+100)
//#define ARMFULLDOWNSPEED	(127-23)
#define ARMFULLDOWNSPEED	(127-15)
#define ARMSLOWUPSPEED		(127+40)
#define ARMSLOWDOWNSPEED    (127-8)
#define ARMSTOPSPEED		127
#define ARMABOVESTORE		1
#define ARMATSTORE			0
#define ARMBELOWSTORE		-1
#endif