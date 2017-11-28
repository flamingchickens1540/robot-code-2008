#include "mecanum.h"
#include "catlin.h"
#include <stdio.h>

//#define MECANUMTUNING

/*	these four functions return a tweaked power
	value for each motor given a base power
	by default: return power multiplied by ratio
	value interpolated between respective slow and
	fast ratio values (**ratio and **ratio2)*/
int modifyRightFront(int power);
int modifyRightRear(int power);
int modifyLeftFront(int power);
int modifyLeftRear(int power);
/*	this function reads the joystick buttons to
	increment the slow constant ratios during
	tuning mode*/
void mecanumTuneSlow(void);
void mecanumSetRightFront(int power);
void mecanumSetRightRear(int power);
void mecanumSetLeftFront(int power);
void mecanumSetLeftRear(int power);
/*	this function checks to see whether any of the
	motor values are outside the large deadzone
	after motors have been set, and if none are,
	power to all motors is cut*/
void mecanumCrop(void);
/*	absolute value function*/
int abs(int value);
/*	clamps the input value between min and max*/
int clampValue(int value,int min,int max);
/*	small deadzone - no motor can be set between
	127-deadzone and 127+deadzone*/
int deadzone=5;
/*	large deadzone - if all motors are between
	127+deadzone2 and 127-deadzone2, power to
	all motors is cut*/
int defaultdeadzone=30,deadzone2=30;
/*	speed at which slow values are calibrated*/
float minSpeed=30.0/127.0;				//			<-------		REMEMBER TO SET MINSPEED TO DEADZONE2/127!!!  INITIALIZING ONLY LIKES CONSTANTS!!!

/*	constant adjustments for three joystick axes					variables with 2s are for slow speed, variables without are for high speed
	jsh=horizontal,jsv=vertical,jsr=rotation
	jsh, jsv, jsr add constant value to joystick
	axes at high speeds*/
int jsh=-2;
int jsv=0;
int jsr=-8;
/*	constant adjustment for joysticks at low speed*/
int jsh2=0;
int jsv2=1;
int jsr2=-3;

/*	linear adjustment for individual wheels
	at high speed*/
float rfratio=347.0/255.0;
float rrratio=215.0/255.0;
float lfratio=277.0/255.0;
float lrratio=257.0/255.0;
/*	linear adjustment for individual wheels
	at low speed*/
float rfratio2=1.0/(.98*.98*.98);
float rrratio2=1.0;
float lfratio2=1.0/(.98*.98*.98);
float lrratio2=1.0;
/*	counts for user byte display
	ratio2's are .98^-count*/
int rfratiocount=3;
int rrratiocount=0;
int lfratiocount=3;
int lrratiocount=0;
/*	code uses alpha value to smoothly transition between
	ratios at full speed and at low speed
	1 is full speed, 0 is slow speed
	DO NOT SET ALPHA VALUE, code does automatically*/
float alpha=1;

/*	last checked values of trig and top buttons,
	used only during tuning, lastp4top actually
	stores aux2, labeled top for consistency*/
char lastp1trig=0;
char lastp2trig=0;
char lastp3trig=0;
char lastp4trig=0;
char lastp1top=0;
char lastp2top=0;
char lastp3top=0;
char lastp4top=0;
char lastp4leftbutton=0;
char lastp4rightbutton=0;
char lastp4up=0;
char lastp4down=0;
char lastp4left=0;
char lastp4right=0;

/*	call this function to tune the variables
	used by mecanumDrive
	DO NOT USE JOYSTICKS 3 AND 4 TO DRIVE!!!
	put the joystick 3 vertical axis
	adjustment wheel forward to enter tuning
	mode, and put wheel back to exit tuning mode
	the axis adjustment wheels on joysticks 3
	and 4 adjust the corresponding axes on
	joysticks 2 and 1 respectively
	the analog wheels on 1, 2, 3, and 4 adjust
	the rear left, rear right, front right, and
	front left motors
	put wheels back to dampen motors, and put
	wheels forward to enhance motors*/
void mecanumTune(void)
{
	lrratio=(((float)p1_wheel)+127)/255;		//puts ratios in range 127-382
	rrratio=(((float)p2_wheel)+127)/255;		//(centered at 255) and divides by 255
	rfratio=(((float)p3_wheel)+127)/255;		//to put ratios in range .5-1.5
	lfratio=(((float)p4_wheel)+127)/255;		//
	jsh=(int)(p4_x);
	if(jsh>200)jsh=200;
	if(jsh<100)jsh=100;
	jsh=(jsh-150)/5;							//p4_x=139
	jsv=(int)(p4_y);
	if(jsv>200)jsv=200;
	if(jsv<100)jsv=100;
	jsv=(jsv-150)/5;							//p4_y=153
	jsr=(int)(p3_x);
	if(jsr>200)jsr=200;
	if(jsr<100)jsr=100;
	jsr=(jsr-150)/5;							//p3_x=109
	mecanumTuneSlow();
}
/*	this function uses the buttons on the joysticks
	to tune the slow ratio values*/
void mecanumTuneSlow(void)
{
	int maxAdjust=15;
	int up=0;
	int down=0;
	int left=0;
	int right=0;
	if(p1_sw_top&&!lastp1top)
	{
		lrratiocount--;
		lrratio2*=.98;
	}
	if(p1_sw_trig&&!lastp1trig)
	{
		lrratiocount++;
		lrratio2/=.98;
	}
	if(p2_sw_top&&!lastp2top)
	{
		rrratiocount--;
		rrratio2*=.98;
	}
	if(p2_sw_trig&&!lastp2trig)
	{
		rrratiocount++;
		rrratio2/=.98;
	}
	if(p3_sw_top&&!lastp3top)
	{
		rfratiocount--;
		rfratio2*=.98;
	}
	if(p3_sw_trig&&!lastp3trig)
	{
		rfratiocount++;
		rfratio2/=.98;
	}
	lastp1top=p1_sw_top;
	lastp2top=p2_sw_top;
	lastp3top=p3_sw_top;
	lastp1trig=p1_sw_trig;
	lastp2trig=p2_sw_trig;
	lastp3trig=p3_sw_trig;
	if(p4_sw_trig&&p4_sw_top)
	{
		if(p4_sw_aux1)
		{
			if(p4_sw_aux2)
				up=1;
			else
				down=1;
		}
		else
		{
			if(p4_sw_aux2)
				right=1;
			else
				left=1;
		}
		if(up&&!lastp4up)
			jsv2++;
		if(down&&!lastp4down)
			jsv2--;
		if(left&&!lastp4left)
			jsh2++;
		if(right&&!lastp4right)
			jsh2--;
		lastp4up=up;
		lastp4down=down;
		lastp4left=left;
		lastp4right=right;
		if(jsv2<-maxAdjust)jsv2=-maxAdjust;
		if(jsv2>maxAdjust)jsv2=maxAdjust;
		if(jsh2<-maxAdjust)jsh2=-maxAdjust;
		if(jsh2>maxAdjust)jsh2=maxAdjust;
	}
	else
	{
		if(p4_sw_aux2&&!lastp4top)
		{
			lfratiocount--;
			lfratio2*=.98;
		}
		if(p4_sw_trig&&!lastp4trig)
		{
			lfratiocount++;
			lfratio2/=.98;
		}
		if(p4_sw_aux1&&!lastp4rightbutton)
			jsr2--;
		if(p4_sw_top&&!lastp4leftbutton)
			jsr2++;
		lastp4top=p4_sw_aux2;
		lastp4trig=p4_sw_trig;
		lastp4leftbutton=p4_sw_top;
		lastp4rightbutton=p4_sw_aux1;
		if(jsr2<-maxAdjust)jsr2=-maxAdjust;
		if(jsr2>maxAdjust)jsr2=maxAdjust;
		lastp4up=lastp4down=lastp4left=lastp4right=0;
	}

}
int modifyRightFront(int power)
{
	float ratio=alpha*rfratio+(1.0-alpha)*rfratio2;
	return (int)(ratio*power);
}
int modifyRightRear(int power)
{
	float ratio=alpha*rrratio+(1.0-alpha)*rrratio2;
	return (int)(ratio*power);
}
int modifyLeftFront(int power)
{
	float ratio=alpha*lfratio+(1.0-alpha)*lfratio2;
	return (int)(ratio*power);
}
int modifyLeftRear(int power)
{
	float ratio=alpha*lrratio+(1.0-alpha)*lrratio2;
	return (int)(ratio*power);
}
/*	call this function for joystick drive*/
void joystickMecanum(void)
{
	int vert;
#ifdef MECANUMTUNING
	unsigned char x=p1_x;
	unsigned char y=p1_y;
	unsigned char z=p2_x;
	unsigned char d=20;
	if(x>127-d&&x<127+d)
		x=127;
	if(y>127-d&&y<127+d)
		y=127;
	if(z>127-d&&z<127+d)
		z=127;
	mecanumTuneSlow();
	mecanumDrive(x,y,z);
#else
	if (!JOYSTICKSPEEDSWITCH)
		//vert = clampValue(VERTICALAXIS, 127-SYMMETRICALSPEED, 127+SYMMETRICALSPEED);
		if (p4_y > 127+SYMMETRICALSPEED)
			vert = 127+SYMMETRICALSPEED;
		else if (p4_y < 127-SYMMETRICALSPEED)
			vert = 127-SYMMETRICALSPEED;
		else vert = p4_y;
	else
		vert = p4_y;
	mecanumDrive(p4_x,vert,p3_x);
#endif
#if DEBUGPERSON == BEN
	User_Byte1 = jsh2;
	User_Byte2 = jsv2;
	User_Mode_byte = jsr2;
	User_Byte3 = lfratiocount;
	User_Byte4 = rfratiocount;
	User_Byte5 = lrratiocount;
	User_Byte6 = rrratiocount;
#endif
}
/*	this function takes three unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)
	the third input is rotation component
	{0 is rotate full right, 255 is full left)
	this function also uses the adjustment
	variables set by mecanumTune*/
void mecanumDrive(unsigned char horizontal,unsigned char vertical,unsigned char rotation)
{
	int px=(int)horizontal;
	int py=(int)vertical;

	
	int turn=(int)rotation;
	int rf,rr,lf,lr;
	int h,v,r;
	

	if(px==255)
		px=254;
	if(py==255)
		py=254;
	if(turn==255)
		turn=254;
	px-=127;
	py-=127;
	turn-=127;
	turn*=2;
	turn/=3;

	//turn=clampValue(turn,-45,45);				//these three lines limit
	//px=clampValue(px,-45,45);					//joystick axes to +-35
	//py=clampValue(py,-45,45);					//to tune at slow speeds

	alpha=(clampValue(abs(turn+py+px),0,127)+clampValue(abs(turn+py-px),0,127)+clampValue(abs(-turn+py-px),0,127)+clampValue(abs(-turn+py+px),0,127))/508.0;
	alpha=(alpha-minSpeed)/(1.0-minSpeed);		//<-------  alpha set to semi-alpha
	h=alpha*jsh+(1.0-alpha)*jsh2;				//			  value so that 0 corresponds
	v=alpha*jsv+(1.0-alpha)*jsv2;				//			   to slow speed instead of 
	r=alpha*jsr+(1.0-alpha)*jsr2;				//			  stopped
	px+=h;				//should still be an alpha
	py+=v;				//value in theory, but might
	turn+=r;			//have value slightly lower
	rf=turn+py+px;		//than 0 in practice
	rr=turn+py-px;
	lf=-turn+py-px;
	lr=-turn+py+px;
	/*
	if(rf<0)rf=(int)(1.097*(float)rf);
	if(rr<0)rr=(int)(1.126*(float)rr);
	if(lf>0)lf=(int)(1.139*(float)lf);
	if(lr>0)lr=(int)(1.103*(float)lr);
	*/
	mecanumSetRightFront(modifyRightFront(rf)+127);
	mecanumSetRightRear(modifyRightRear(rr)+127);
	mecanumSetLeftFront(modifyLeftFront(lf)+127);
	mecanumSetLeftRear(modifyLeftRear(lr)+127);
	mecanumCrop();
}
/*	this function takes three unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)
	the third input is rotation component
	{0 is rotate full right, 255 is full left)*/
void mecanumUntunedDrive(unsigned char horizontal,unsigned char vertical,unsigned char rotation)
{
	int px=(int)horizontal;
	int py=(int)vertical;
	int turn=(int)rotation;
	int rf,rr,lf,lr;
	if(px==255)
		px=254;
	if(py==255)
		py=254;
	if(turn==255)
		turn=254;
	px-=127;
	py-=127;
	turn-=127;
	turn*=2;
	turn/=3;
	rf=turn+py+px;
	rr=turn+py-px;
	lf=-turn+py-px;
	lr=-turn+py+px;
	mecanumSetRightFront(rf+127);
	mecanumSetRightRear(rr+127);
	mecanumSetLeftFront(lf+127);
	mecanumSetLeftRear(lr+127);
	mecanumCrop();
}
/*	this function takes two unsigned char inputs
	the first input is left-right component
	(0 is full right, 255 is full left)
	the second input is forward-backward component
	(0 is full back, 255 is full forward)*/
void mecanumStrafe(unsigned char horizontal,unsigned char vertical)
{
	mecanumDrive(horizontal,vertical,127);
}
/*	this function takes one unsigned char input
	255 is full forward, 0 is full backward*/
void driveForward(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive(127,(unsigned char)((int)power),127);
}
/*	this function takes one unsigned char input
	255 is full backward, 0 is full forward*/
void driveBackward(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive(127,(unsigned char)((int)(254-power)),127);
}
/*	this function takes one unsigned char input
	255 is full left, 0 is full right*/
void driveLeft(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive((unsigned char)((int)power),127,127);
}
/*	this function takes one unsigned char input
	255 is full right, 0 is full left*/
void driveRight(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive((unsigned char)((int)(254-power)),127,127);
}
/*	this function takes one unsigned char input
	255 is full left, 0 is full right*/
void rotateLeft(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive(127,127,(unsigned char)((int)power));
}
/*	this function takes one unsigned char input
	255 is full right, 0 is full left*/
void rotateRight(unsigned char power)
{
	if(power==255)power=254;
	mecanumDrive(127,127,(unsigned char)((int)(254-power)));
}
/*	rather self-explanatory,
	stops all motors*/
void mecanumStop()
{
	FRONTLEFTMOTOR=FRONTRIGHTMOTOR=REARLEFTMOTOR=REARRIGHTMOTOR=127;
}
void mecanumSetRightFront(int power)
{
	int x=power;
  	if(x<(127-maxSpeed))x=(127-maxSpeed);
	if(x<0)x=0;
	if(x>(127+maxSpeed))x=(127+maxSpeed);
  	if(x>254)x=254;
	FRONTRIGHTMOTOR=127;
	if(x<127-deadzone||x>127+deadzone)FRONTRIGHTMOTOR=(254-x);
}
void mecanumSetRightRear(int power)
{
	int x=power;
	if(x<(127-maxSpeed))x=(127-maxSpeed);
	if(x<0)x=0;
	if(x>(127+maxSpeed))x=(127+maxSpeed);
	if(x>254)x=254;
	REARRIGHTMOTOR=127;
	if(x<127-deadzone||x>127+deadzone)REARRIGHTMOTOR=(254-x);
}
void mecanumSetLeftFront(int power)
{
	int x=power;
	if(x<(127-maxSpeed))x=(127-maxSpeed);
	if(x<0)x=0;
	if(x>(127+maxSpeed))x=(127+maxSpeed);
	if(x>254)x=254;
	FRONTLEFTMOTOR=127;
	if(x<127-deadzone||x>127+deadzone) FRONTLEFTMOTOR=x;
}
void mecanumSetLeftRear(int power)
{
	int x=power;
	if(x<(127-maxSpeed))x=(127-maxSpeed);
	if(x<0)x=0;
	if(x>(127+maxSpeed))x=(127+maxSpeed);
	if(x>254)x=254;
	REARLEFTMOTOR=127;
	if(x<127-deadzone||x>127+deadzone)REARLEFTMOTOR=x;
}

//	this function checks to see whether any of the
//	motor values are outside the large deadzone
//	after motors have been set, and if none are,
//	power to all motors is cut
	
void mecanumCrop(void)
{
	if(FRONTRIGHTMOTOR<127+deadzone2&&FRONTRIGHTMOTOR>127-deadzone2&&
		FRONTLEFTMOTOR<127+deadzone2&&FRONTLEFTMOTOR>127-deadzone2&&
		REARRIGHTMOTOR<127+deadzone2&&REARRIGHTMOTOR>127-deadzone2&&
		REARLEFTMOTOR<127+deadzone2&&REARLEFTMOTOR>127-deadzone2)
	{
		FRONTRIGHTMOTOR=FRONTLEFTMOTOR=REARRIGHTMOTOR=REARLEFTMOTOR=127;
		deadzone2=defaultdeadzone;
	}
	else deadzone2=defaultdeadzone-2;							//			<-------			set deadzone2 here to defaultdeadzone, minus a small amount
}
/*	absolute value function*/
int abs(int value)
{
	if(value<0)
		return -value;
	return value;
}
/*	clamps the input value between min and max*/
int clampValue(int value,int min,int max)
{
	if(value>max)
		return max;
	if(value<min)
		return min;
	return value;
}
