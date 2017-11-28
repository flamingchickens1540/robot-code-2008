#ifndef _AUTO_UTIL_H_
#define _AUTO_UTIL_H_

int prepare(void);
int release(void);
int hurdle(void);
int place(void);
int stow(void);
int takeoff(void);
int displace_catch(void);

void monitor_auto(void);

extern int frWobbleCount;
extern int flWobbleCount;
extern int is_software_drive;
extern int is_hurdling;
extern int is_placing;
extern int is_preparing;
extern int is_releasing;
extern int is_stowing;
//extern int is_takingoff;
extern int is_displace_catching;
#endif
