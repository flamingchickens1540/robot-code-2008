/*******************************************************************************
* FILE NAME: mecanum.h
*
* DESCRIPTION:
*  This file contains the declarations for use with the mecanum drive library
*
* USAGE: The mecanum files should contain stuff specific to mecanum stuff.
*
*******************************************************************************/

#ifndef _mecanum_h
#define _mecanum_h

/*	call this function for joystick drive*/
void joystickMecanum(void);

/*	this function takes three unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)
	the third input is rotation component
	{0 is rotate full right, 255 is full left)
	this function also uses the adjustment
	variables set by mecanumTune*/
void mecanumDrive(unsigned char horizontal,unsigned char vertical,unsigned char rotation);

/*	this function takes three unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)
	the third input is rotation component
	{0 is rotate full right, 255 is full left)*/
void mecanumUntunedDrive(unsigned char horizontal,unsigned char vertical,unsigned char rotation);
/*	this function takes two unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)*/
void mecanumStrafe(unsigned char horizontal,unsigned char vertical);

/*	this function takes one unsigned char input
	255 is full forward, 0 is full backward*/
void driveForward(unsigned char power);

/*	this function takes one unsigned char input
	255 is full backward, 0 is full forward*/
void driveBackward(unsigned char power);

/*	this function takes one unsigned char input
	255 is full left, 0 is full right*/
void driveLeft(unsigned char power);

/*	this function takes one unsigned char input
	255 is full right, 0 is full left*/
void driveRight(unsigned char power);

/*	this function takes one unsigned char input
	255 is full left, 0 is full right*/
void rotateLeft(unsigned char power);

/*	this function takes one unsigned char input
	255 is full right, 0 is full left*/
void rotateRight(unsigned char power);

/*	rather self-explanatory,
	stops all motors*/
void mecanumStop(void);

/*	call this function to tune the variables
	used by mecanumDrive*/
void mecanumTune(void);

#endif