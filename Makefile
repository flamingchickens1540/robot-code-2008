# Exported from MPLAB IDE project `ifi_frc.mcp' on Sat Feb 09 18:04:45 2008.

"ifi_frc.cof" : "autonomous.o" "disabled.o" "ifi_code.o" "ifi_frc.o" "interrupts.o" "pwm.o" "serial_ports.o" "teleop.o" "timers.o" "arm.o" "mecanum.o" "action.o" "pneumatics.o" "auto_util.o"
	"C:\mcc18\bin\mplink.exe" /l"C:\mcc18\lib" "C:\max\nemo\18f8722.lkr" "C:\max\nemo\autonomous.o" "C:\max\nemo\disabled.o" "C:\max\nemo\ifi_code.o" "C:\max\nemo\ifi_frc.o" "C:\max\nemo\interrupts.o" "C:\max\nemo\pwm.o" "C:\max\nemo\serial_ports.o" "C:\max\nemo\teleop.o" "C:\max\nemo\timers.o" "C:\max\nemo\arm.o" "C:\max\nemo\mecanum.o" "C:\max\nemo\action.o" "C:\max\nemo\pneumatics.o" "C:\max\nemo\auto_util.o" "C:\max\nemo\ifi_frc_8722.lib" /m"ifi_frc.map" /w /o"ifi_frc.cof"

"autonomous.o" : "autonomous.c" "C:\max\nemo\autonomous.c" "C:\mcc18\h\stdio.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\max\nemo\autonomous.c" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\autonomous.h" "C:\max\nemo\catlin.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "autonomous.c" -fo="autonomous.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"disabled.o" : "disabled.c" "C:\max\nemo\disabled.c" "C:\mcc18\h\stdio.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\max\nemo\disabled.c" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "disabled.c" -fo="disabled.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"ifi_code.o" : "ifi_code.c" "C:\max\nemo\ifi_code.c" "C:\mcc18\h\adc.h" "C:\mcc18\h\delays.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\ifi_code.c" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "ifi_code.c" -fo="ifi_code.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"ifi_frc.o" : "ifi_frc.c" "C:\max\nemo\ifi_frc.c" "C:\mcc18\h\stdio.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_frc.c" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\autonomous.h" "C:\max\nemo\disabled.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "ifi_frc.c" -fo="ifi_frc.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"interrupts.o" : "interrupts.c" "C:\max\nemo\interrupts.c" "C:\max\nemo\interrupts.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\catlin.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "interrupts.c" -fo="interrupts.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"pwm.o" : "pwm.c" "C:\max\nemo\pwm.c" "C:\max\nemo\pwm.h" "C:\max\nemo\pwm.c" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "pwm.c" -fo="pwm.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"serial_ports.o" : "serial_ports.c" "C:\max\nemo\serial_ports.c" "C:\mcc18\h\stdio.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\serial_ports.c" "C:\mcc18\h\p18f8722.h" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "serial_ports.c" -fo="serial_ports.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"teleop.o" : "teleop.c" "C:\max\nemo\teleop.c" "C:\mcc18\h\stdio.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\max\nemo\teleop.c" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "teleop.c" -fo="teleop.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"timers.o" : "timers.c" "C:\max\nemo\timers.c" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "timers.c" -fo="timers.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"arm.o" : "arm.c" "C:\max\nemo\arm.c" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\mcc18\h\stdio.h" "C:\max\nemo\arm.c" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "arm.c" -fo="arm.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"mecanum.o" : "mecanum.c" "C:\max\nemo\mecanum.c" "C:\max\nemo\mecanum.h" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\mcc18\h\stdio.h" "C:\max\nemo\mecanum.c" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "mecanum.c" -fo="mecanum.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"action.o" : "action.c" "C:\max\nemo\action.c" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\mcc18\h\stdio.h" "C:\mcc18\h\math.h" "C:\max\nemo\action.c" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "action.c" -fo="action.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"pneumatics.o" : "pneumatics.c" "C:\max\nemo\pneumatics.c" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\mcc18\h\stdio.h" "C:\max\nemo\pneumatics.c" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h" "C:\mcc18\h\stdarg.h" "C:\mcc18\h\stddef.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "pneumatics.c" -fo="pneumatics.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

"auto_util.o" : "auto_util.c" "C:\max\nemo\auto_util.c" "C:\max\nemo\ifi_frc.h" "C:\max\nemo\pwm.h" "C:\max\nemo\interrupts.h" "C:\max\nemo\serial_ports.h" "C:\max\nemo\ifi_code.h" "C:\max\nemo\mecanum.h" "C:\max\nemo\action.h" "C:\max\nemo\arm.h" "C:\max\nemo\pneumatics.h" "C:\max\nemo\auto_util.c" "C:\max\nemo\catlin.h" "C:\mcc18\h\p18cxxx.h" "C:\mcc18\h\p18f8722.h" "C:\max\nemo\timers.h" "C:\max\nemo\teleop.h" "C:\max\nemo\catlin_aliases.h" "C:\max\nemo\auto_util.h"
	"C:\mcc18\bin\mcc18.exe" -p=18F8722 "auto_util.c" -fo="auto_util.o" -k -mL -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	del "autonomous.o" "disabled.o" "ifi_code.o" "ifi_frc.o" "interrupts.o" "pwm.o" "serial_ports.o" "teleop.o" "timers.o" "arm.o" "mecanum.o" "action.o" "pneumatics.o" "auto_util.o" "ifi_frc.cof" "ifi_frc.cod" "ifi_frc.hex" "ifi_frc.lst" "ifi_frc.map"

