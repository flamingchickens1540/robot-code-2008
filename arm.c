/*******************************************************************************
* FILE NAME: arm.c
*
* DESCRIPTION:
*  This file contains the code for the arm.
*
* USAGE:
*	To be included in catlin routines
*
*  Written by Rohan Jhunjhunwala
*
*******************************************************************************/
#include "catlin.h"
#include "stdio.h"

#define UP		10
#define DOWN 	-10

int currentArmState = ARMSTOPPED;
int armSideOfStore = ARMATSTORE;
int targetArmState;
int inProgToState;
int direction;
int armUpSpeed = ARMFULLUPSPEED;
int armDownSpeed = ARMFULLDOWNSPEED;
int prevMidLim = TRIPLIM;
int prevMidLim2 = TRIPLIM;

void changeArmState(int changeTo)
{
	switch (changeTo)
	{		
		case ARMSTOPBOTTOM:
			BRAKERELAY = BRAKEENGAGED;
			ARMMOTOR = ARMSTOPSPEED;
			currentArmState = ARMSTOPBOTTOM;
			break;
		
		case ARMSTOPSTORE:
			BRAKERELAY = BRAKEENGAGED;
			ARMMOTOR = ARMSTOPSPEED;
			currentArmState = ARMSTOPSTORE;
			break;
		
		case ARMSTOPTOP:
			BRAKERELAY = BRAKEENGAGED;
			ARMMOTOR = ARMSTOPSPEED;
			currentArmState = ARMSTOPTOP;
			break;			

		case ARMSTOPPED:
			BRAKERELAY = BRAKEENGAGED;
			ARMMOTOR = ARMSTOPSPEED;
			currentArmState = ARMSTOPPED;
			break;
	
		case ARMMOVEUP:
			BRAKERELAY = BRAKERELEASED;
			ARMMOTOR = armUpSpeed;
			currentArmState = ARMMOVEUP;
			break;
	
		case ARMMOVEDOWN:
			BRAKERELAY = BRAKERELEASED;
			ARMMOTOR = armDownSpeed;
			currentArmState = ARMMOVEDOWN;
			break;

		default:
			#if DEBUGPERSON == ROHAN
			Switch1_LED = 1;
			#endif
			break;
	}
}

void requestArmState(int reqState)
{
	if (getWristState() == WRISTRAISED)
	{
		return;
	}
	switch (reqState)
	{
		case ARMSTOPBOTTOM:
		targetArmState = ARMSTOPBOTTOM;
		inProgToState = ARMSTOPBOTTOM;
			switch (currentArmState)
			{
				case ARMSTOPBOTTOM: 
				case ARMMOVEDOWN:
					break;

				case ARMMOVEUP:
				case ARMSTOPPED:
				case ARMSTOPSTORE:
				case ARMSTOPTOP:
					changeArmState(ARMMOVEDOWN);
					break;
				
				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;
			
		case ARMSTOPTOP:
		inProgToState = ARMSTOPTOP;
		targetArmState = ARMSTOPTOP;
			switch (currentArmState)
			{
				
				case ARMSTOPPED:
				case ARMSTOPBOTTOM: 
				case ARMMOVEDOWN:
				case ARMSTOPSTORE:
					changeArmState(ARMMOVEUP);					
					break;
					
				case ARMMOVEUP: 
				case ARMSTOPTOP:
					break;

				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;
		case ARMSTOPSTORE:
		inProgToState = ARMSTOPSTORE;
		targetArmState = ARMSTOPSTORE;
			switch (currentArmState)
			{
				case ARMSTOPBOTTOM: 
					changeArmState(ARMMOVEUP);					
					break;

				case ARMSTOPTOP: 
					changeArmState(ARMMOVEDOWN);
					break;

				case ARMSTOPSTORE:
					break;

				case ARMMOVEUP:
				case ARMMOVEDOWN:
				case ARMSTOPPED:
					if (armSideOfStore == ARMABOVESTORE)
					{
						changeArmState(ARMMOVEDOWN);
					}
					else if (armSideOfStore == ARMBELOWSTORE)
					{
						changeArmState(ARMMOVEUP);
					}
					break;

				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;

		case ARMSTOPPED:
		inProgToState = REACHEDSTATE;
		targetArmState = ARMSTOPPED;
			switch (currentArmState)
			{
				case ARMMOVEUP: 
				case ARMMOVEDOWN:
					changeArmState(ARMSTOPPED);					
`					break;

				case ARMSTOPBOTTOM: 
				case ARMSTOPSTORE: 
				case ARMSTOPTOP: 
				case ARMSTOPPED:
					break;

				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;
			
		case ARMMOVEUP:
		targetArmState = ARMMOVEUP;
		inProgToState = REACHEDSTATE;
			switch (currentArmState)
			{
				case ARMSTOPPED:
				case ARMMOVEDOWN:
				case ARMSTOPBOTTOM:
				case ARMSTOPSTORE:
					changeArmState(ARMMOVEUP);					
					break;

				case ARMSTOPTOP:
				case ARMMOVEUP:
					break;

				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;
	
		case ARMMOVEDOWN:
		targetArmState = ARMMOVEDOWN;
		inProgToState = REACHEDSTATE;
			switch (currentArmState)
			{
				case ARMSTOPPED:
				case ARMMOVEUP:
				case ARMSTOPTOP:
				case ARMSTOPSTORE:
					changeArmState(ARMMOVEDOWN);					
					break;

				case ARMSTOPBOTTOM:
				case ARMMOVEDOWN:
					break;

				default:
					#if DEBUGPERSON == ROHAN
					Switch1_LED = 1;
					#endif
					break;
			}
			break;
		
		default:
			#if DEBUGPERSON == ROHAN
			Switch1_LED = 1;
			#endif
			break;
	}
}


void monitorArmSensors(void)
{
	armUpSpeed = ARMFULLUPSPEED;
	armDownSpeed = ARMFULLDOWNSPEED;
//	if (inProgToState == currentArmState)
//	{
//		inProgToState = REACHEDSTATE;
//	}
	
	if (ARMMOTOR > ARMSTOPSPEED+4)
	{
		direction = UP;
	}
	else if (ARMMOTOR < ARMSTOPSPEED-4)
	{
		direction = DOWN;
	}
	if (direction == UP && MIDDLEARMLIMIT == TRIPLIM) //&& prevMidLim != TRIPLIM && prevMidLim2 == TRIPLIM)
	{
		armSideOfStore = ARMABOVESTORE;
	}
	else if (direction == DOWN && MIDDLEARMLIMIT == TRIPLIM) // && prevMidLim != TRIPLIM && prevMidLim2 == TRIPLIM )
	{
		armSideOfStore = ARMBELOWSTORE;
	}
	
	if (targetArmState == ARMSTOPSTORE)
	{
		if (MIDDLEARMLIMIT == TRIPLIM)
		{
			changeArmState(ARMSTOPSTORE);
//			armSideOfStore = ARMATSTORE;
		}
		if (MIDDLEARMLIMIT != TRIPLIM && currentArmState == ARMSTOPSTORE && getWristState() != WRISTRAISED)
		{
			if (armSideOfStore == ARMABOVESTORE)
			{
				armDownSpeed = ARMSLOWDOWNSPEED;
				changeArmState(ARMMOVEDOWN);
			}
			else if (armSideOfStore == ARMBELOWSTORE)
			{
				armUpSpeed = ARMSLOWUPSPEED;
				changeArmState(ARMMOVEUP);
			}
		}
	}
	
	if ((TOPARMLIMIT == TRIPLIM) && ((targetArmState == ARMSTOPTOP)||(currentArmState == ARMMOVEUP)))
	{
		armSideOfStore = ARMABOVESTORE;
		changeArmState(ARMSTOPTOP);
	}

	if ((BOTTOMARMLIMIT == TRIPLIM) && ((targetArmState == ARMSTOPBOTTOM)||(currentArmState == ARMMOVEDOWN)))
	{
		armSideOfStore = ARMBELOWSTORE;
		changeArmState(ARMSTOPBOTTOM);
	}
	
	
	#if DEBUGPERSON == ROHAN
	User_Byte1 = armSideOfStore;
	User_Byte2 = MIDDLEARMLIMIT;
	User_Byte3 = currentArmState;
	User_Byte4 = targetArmState;
	User_Byte5 = prevMidLim;
	User_Byte6 = direction;
	#endif
	prevMidLim2 = prevMidLim;
	prevMidLim = MIDDLEARMLIMIT;
	
}

void monitorArmUi(void)
{
	if (ARMHEIGHTSWITCH < ARMGOUP+8 && ARMHEIGHTSWITCH > ARMGOUP-8)
	{
		requestArmState(ARMMOVEUP);
	}
	else if (ARMHEIGHTSWITCH < ARMGODOWN+8 && ARMHEIGHTSWITCH > ARMGODOWN-8)
	{
		requestArmState(ARMMOVEDOWN);
	}
	else if ((ARMHEIGHTSWITCH < ARMSTOP+8 && ARMHEIGHTSWITCH > ARMSTOP-8)&&(inProgToState == REACHEDSTATE))
	{
		requestArmState(ARMSTOPPED);
	}
	else if (ARMHEIGHTSWITCH < ARMGOHIGH+8 && ARMHEIGHTSWITCH > ARMGOHIGH-5)
	{
		requestArmState(ARMSTOPTOP);
	}
	else if (ARMHEIGHTSWITCH < ARMGOSTORE+8 && ARMHEIGHTSWITCH > ARMGOSTORE-8)
	{
		requestArmState(ARMSTOPSTORE);
	}
	else if (ARMHEIGHTSWITCH < ARMGOLOW+8 && ARMHEIGHTSWITCH > ARMGOLOW-8)
	{
		requestArmState(ARMSTOPBOTTOM);
	}
}

int getArmState(void)
{
	return currentArmState;
}
