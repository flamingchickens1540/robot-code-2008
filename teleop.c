#include <stdio.h>
#include "catlin.h"


char isStowed;
// scaled from 0 to 127
char maxSpeed = 127;
char softwareDriveSpeed = HURDLESPEED;
char softwareDriveButtonPressed = FALSE;
//Different states for teleop etc
void Initialization(void)
{
	// Setup the digital I/O pins. Use "INPUT" to setup the pin
	// as an input and "OUTPUT" to setup the pin as an output.
	digital_io_01 = INPUT;
	digital_io_02 = INPUT;
	digital_io_03 = INPUT;
	digital_io_04 = INPUT;
	digital_io_05 = INPUT;
	digital_io_06 = INPUT;
	digital_io_07 = INPUT;
	digital_io_08 = INPUT;
	digital_io_09 = INPUT;
	digital_io_10 = INPUT;
	digital_io_11 = INPUT;
	digital_io_12 = INPUT;
	digital_io_13 = INPUT;
	digital_io_14 = INPUT;
	digital_io_15 = INPUT;
	digital_io_16 = INPUT;
	digital_io_17 = INPUT;
	digital_io_18 = INPUT;


	// Initialize the digital outputs. If the pin is configured
	// as an input above, it doesn't matter what state you
	// initialize it to here.
	rc_dig_out01 = 0;
	rc_dig_out02 = 0;
	rc_dig_out03 = 0;
	rc_dig_out04 = 0;
	rc_dig_out05 = 0;
	rc_dig_out06 = 0;
	rc_dig_out07 = 0;
	rc_dig_out08 = 0;
	rc_dig_out09 = 0;
	rc_dig_out10 = 0;
	rc_dig_out11 = 0;
	rc_dig_out12 = 0;
	rc_dig_out13 = 0;
	rc_dig_out14 = 0;
	rc_dig_out15 = 0;
	rc_dig_out16 = 0;
	rc_dig_out17 = 0;
	rc_dig_out18 = 0;

	// initialize timers and external interrupts here
	// (see timers.c/.h and interrupts.c/.h)
	//Initialize_Int_1();
	//Initialize_Int_2();

	printf("IFI User Processor Initialized ...\r\n");
}


void Teleop_Init(void)
{
#ifdef CONSOLEIR
	Autonomous_Init();
#endif
}


//see the comment above Teleop_Init
void Teleop(void)
{
#ifdef CONSOLEIR
	Autonomous();
#else
	if (monitor_fake_auto()) {
		Autonomous();
		return;
	}
	//update_action_queue(&test);
	//if (!(JOYSTICKSOFTWAREOVERRIDE && is_software_drive))
	if (!(JOYSTICKSOFTWAREOVERRIDE))
	{
		monitor_auto();	
		if (softwareDriveButtonPressed == TRUE)
			maxSpeed = 127;
		joystickMecanum();
		softwareDriveButtonPressed = FALSE;
		
	}
	else
	{
		if (!is_software_drive)
		{
			joystickMecanum();
		}
		else
		{
			mecanumDrive(p4_x,127+softwareDriveSpeed,p3_x);
		}
		monitor_auto();	
		softwareDriveButtonPressed = TRUE;
	}
	monitorArmUi();
	monitorArmSensors();
	switchboardTriggers();
//	if (p4_sw_top)
//		maxSpeed = 30;
//	else if (p4_sw_aux2)
//		maxSpeed = 70;
//	else if (p4_sw_aux1)
//	{
//		maxSpeed = 127;
//		is_software_drive = FALSE;
//	}
	

	/*
	if (p1_y < 220 && p1_y > 200)
	{
		BRAKERELAY = BRAKERELEASED;
		ARMMOTOR = 127-23;
	}
	//Up
	else if (p1_y < 251 && p1_y > 241)
	{
		BRAKERELAY = BRAKERELEASED;
		ARMMOTOR = 127+123;
	}
	else 
	{
		ARMMOTOR = 127;
		BRAKERELAY = BRAKEENGAGED;
	}*/
	//Relay2_green = BRAKERELAY;
	//Switch1_LED = PRESSUREVALVE;

	//User_Byte1 = armheight/256;
	//User_Byte2 = armheight%256;

	//User_Byte5 = TOPARMLIMIT;
	//User_Byte6 = BOTTOMARMLIMIT;
	#if DEBUGPERSON == MAXSCHWARZ	
		
		User_Byte6 = maxSpeed; //\\
		
	#endif
#endif
}

void Teleop_Spin(void)
{

}
