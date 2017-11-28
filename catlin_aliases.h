/*******************************************************************************
* FILE NAME: catlin_aliases.h
*
* DESCRIPTION:
*  This file contains the catlin alias declarations.
*
* USAGE:
*	NO EDITING SHOULD HAPPEN TO THIS FILE WITHOUT THE
*	CONSENT OF THE SOFTWARE MANAGER OR MENTOR
*
*******************************************************************************/

#ifndef __catlin_aliases_h_
#define __catlin_aliases_h_

/* Constant Declarations */


/* These are basics that should always have values */
#ifndef FALSE
#define FALSE				0
#endif
#ifndef TRUE
#define TRUE				1
#endif
#define YES					1
#define NO					0
#define	MAX					255
#define	MIN					0
#define	NEUTRAL				127
#define	FULLFORWARD			255
#define	FULLBACK			0
#define STOPPED				127
#define ON					1
#define OFF					0
#define	LEDON				0 
#define LEDOFF				1 
#define OILEDON				1
#define OILEDOFF			0
#define	SWITCHOFF			1
#define	SWITCHON			0
#define CALLSPSEC			38.17

#define NEMO 0
#define DORY 1

#define ROBOTNAME NEMO

// Measured as speed above 127
#define POSTHURDLESPEED		30

/* These values have been changed to accomidate the fubar overpass of Las Vegas.
#define HURDLESPEED			50*/
#define HURDLESPEED			55
#define PLACESPEED			40
#define SYMMETRICALSPEED	53	//this constant makes forward/back the same as left/right
/***** PWMs *****/
#define FRONTRIGHTMOTOR pwm01
#define FRONTLEFTMOTOR pwm02
#define REARLEFTMOTOR pwm03
#define REARRIGHTMOTOR pwm06
#define ARMMOTOR pwm05

/***** Relays *****/
#define RELAYON 1
#define RELAYOFF 0

// Don't refer to the wrist constants directly.  Use the function to the correct setting.
#define DOWNWRIST relay1_fwd
#define UPWRIST relay1_rev
// These wrist constants refer to the value of the "up" relay.  The "down" relay should ALWAYS be opposite
// Enabled is raised, Disabled is lowered
#define WRISTENABLED 1
#define WRISTDISABLED 0

#define GRIPRELAY relay2_fwd
#define GRIPCLOSED RELAYOFF
#define GRIPOPENED RELAYON

#define BRAKERELAY relay2_rev
#define BRAKEENGAGED RELAYOFF
#define BRAKERELEASED RELAYON

#define LIFTRELAY relay3_fwd
#define LIFTLOWERED RELAYOFF
#define LIFTRAISED RELAYON

#define HOLDERFRONTLEFTRELAY relay4_fwd
#define HOLDERFRONTRIGHTRELAY relay4_rev
#define HOLDERREARLEFTRELAY relay5_fwd
#define HOLDERREARRIGHTRELAY relay5_rev
#define HOLDERDROPPED RELAYOFF
#define HOLDERRAISED RELAYON

// Never enable both relay6_fwd and relay6_rev at the same time.  You will fry the compressor.
#define COMPRESSORRELAY relay6_fwd
#define COMPRESSOROFF RELAYOFF
#define COMPRESSORON RELAYON

/***** Digital IOs *****/
#define PRESSUREVALVE rc_dig_in18
#define LOWPRESSURE 0
#define HIGHPRESSURE 1

// Interrupts
#define TOPARMLIMIT rc_dig_in03
#define BOTTOMARMLIMIT rc_dig_in04
#define MIDDLEARMLIMIT rc_dig_in05

#define WOBBLEFRONTRIGHT rc_dig_in01
#define WOBBLEFRONTLEFT rc_dig_in02
#define WOBBLEREARRIGHT rc_dig_in10
#define WOBBLEREARLEFT rc_dig_in11
#define WOBBLETRUE 0

#define DUALIR
//#define SINGLEIR
//#define CONSOLEIR

#ifdef DUALIR
#define IRORANGE (rc_dig_in12 == ON || rc_dig_in06 == ON)
#define IRGREEN (rc_dig_in13 == ON || rc_dig_in07 == ON)
#define IRBLUE (rc_dig_in14 == ON || rc_dig_in08 == ON)
#define IRYELLOW (rc_dig_in15 == ON || rc_dig_in09 == ON)
#endif

#ifdef SINGLEIR
#define IRORANGE (rc_dig_in12 == ON)
#define IRGREEN (rc_dig_in13 == ON)
#define IRBLUE (rc_dig_in14 == ON)
#define IRYELLOW (rc_dig_in15 == ON)
#endif

#ifdef CONSOLEIR
#define IRGREEN inRange(PRHSWITCH, 9, PRHSWITCHPLACE)
#define IRYELLOW inRange(PRHSWITCH, 9, PRHSWITCHRELEASE)
#define IRORANGE inRange(PRHSWITCH, 9, PRHSWITCHPREPARE)
#define IRBLUE inRange(PRHSWITCH, 9, PRHSWITCHSPARE)
#endif

/***** Analog In *****/
#define HYBRIDMODE1 rc_dig_in16
#define HYBRIDMODE2 rc_dig_in17

/***** OI ******/

// Old console

// New console
#define HORIZONTALAXIS p4_x
#define VERTICALAXIS p4_y
#define ROTATIONAXIS p3_x

#define HOLDERFRONTLEFTSWITCH p2_y
#define HOLDERFRONTRIGHTSWITCH p2_x
#define HOLDERREARLEFTSWITCH p2_aux
#define HOLDERREARRIGHTSWITCH p2_wheel
#define HOLDERSWITCHHIGH 246
#define HOLDERSWITCHLOW 15

#define LIFTUPSWITCH p2_sw_top
#define LIFTDOWNSWITCH p2_sw_trig
#define LIFTSWITCHON 1
#define LIFTSWITCHOFF 0

#define WRISTSWITCH p1_wheel
#define WRISTSWITCHRAISE 253
#define WRISTSWITCHLOWER 16

#define GRIPPERSWITCH p1_aux
#define GRIPPERSWITCHOPEN 246
#define GRIPPERSWITCHCLOSE 15

#define STOWSWITCH p1_sw_trig
#define STOWSWITCHON 1
#define STOWSWITCHOFF 0

#define ARMHEIGHTSWITCH p1_x

#define PRHSWITCH p1_y

#if ROBOTNAME == NEMO
#define PRHSWITCHPLACE			165
#define PRHSWITCHPREPARE		185
#define PRHSWITCHRELEASE		211
//#define PRHSWITCHCANCELALL		159
#define PRHSWITCHHURDLE			254
#define PRHSWITCHSPARE			149
#endif

#if ROBOTNAME == DORY
#define PRHSWITCHPLACE			225
#define PRHSWITCHPREPARE		180
#define PRHSWITCHRELEASE		160
#define PRHSWITCHHURDLE			246
#endif


// Digital
//#define HURDLESWITCH			p1_sw_aux1

#define JOYSTICKPLACESWITCH		p4_sw_top
#define JOYSTICKHURDLESWITCH	p3_sw_top
#define JOYSTICKGRIPSWITCH		p4_sw_trig
#define JOYSTICKSOFTWAREOVERRIDE p3_sw_aux1
#define JOYSTICKSPEEDSWITCH		p3_sw_aux2

#define CANCELSWITCH	p1_sw_aux1
#define DROPALLHURDLESWITCH p1_sw_top

// Set this to your name 

#define NOPERSON 0
#define EMESS	1
#define KEVIN	2
#define BEN		3
#define ROHAN	4
#define ANDREW	5
#define MAXSCHWARZ 	6

#define DEBUGPERSON KEVIN

//LED Definitions
#define FRONT_RIGHT_LED			Pwm1_green
#define FRONT_LEFT_LED			Pwm2_green
#define REAR_RIGHT_LED			Pwm1_red
#define REAR_LEFT_LED			Pwm2_red
#define HURDLE_LED				Relay1_green
#define SPARE_LED				Relay2_green
#define STOW_LED				Relay1_red
#define PLACE_LED				Relay2_red
#define COMPRESSOR_LED			Switch1_LED

#endif
