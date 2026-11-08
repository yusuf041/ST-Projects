#ifndef __SYSTEM_H
#define __SYSTEM_H



#define _STDIN  0
#define _STDOUT 1
#define _STDERR 2

#undef  CLOCKS_PER_SEC
#define CLOCKS_PER_SEC  1000

typedef unsigned long  clock_t;  // uint32_t ile aynı tip. uint32_t de //#include <stdint.h> görmek istiyor.

clock_t clock(void);

void __delay(unsigned long ncy);
int __ints(int stat);

#define CLOCK_FREQ      168000000

#define INSTR_FREQ      CLOCK_FREQ
#define US_CYCLES       (INSTR_FREQ / 1000000)
#define MS_CYCLES       (INSTR_FREQ / 1000)

#define DelayUs(us)     __delay((us) * US_CYCLES)
#define DelayMs(ms)     __delay((ms) * MS_CYCLES)


void Sys_Init(void);
void Sys_ConsoleInit(void);
void Sys_IoInit(void);
void Sys_Tick_Time(void);

#endif
