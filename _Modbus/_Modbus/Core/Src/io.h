#ifndef _IO_H
#define _IO_H

#include "stm32f4xx_hal.h"

// IO Modlari
enum {
  IO_MODE_INPUT,
  IO_MODE_OUTPUT,
  IO_MODE_ALTERNATE,
  IO_MODE_ANALOG,
  
  IO_MODE_INPUT_PD,
  IO_MODE_INPUT_PU,
  IO_MODE_OUTPUT_OD,
  IO_MODE_OUTPUT_OD_PU,
  IO_MODE_ALTERNATE_OD,
  IO_MODE_ALTERNATE_OD_PU,  
};

enum {
  IO_PORT_A,
  IO_PORT_B,
  IO_PORT_C,
  IO_PORT_D,
};

typedef struct {
  int port;
  int pin;
  int af;
} IO_PIN;

//////////////////////////////////////////////////////////

// I/O pin listesi
enum {

IOP_HeardLED,
  IOP_LED,  // heart bit

  IOP_UART4_TX,  // Uart TX pin header
  IOP_UART4_RX,  //Uart RX pin header
  IOP_485_DE,    // max 485 drive enable transmit mode PC6
  IOP_485_RE,    // max 485 receiver enable listen mode PC7

  IOP_TIM1,

  IOP_BUTON,

};

#ifdef _IOS_
static IO_PIN s_ios[] = {

 { IO_PORT_D, 13 },  // GREEN LED
  { IO_PORT_D, 12 },  // GREEN LED

  { IO_PORT_C, 10 },  // UART4 TX
  { IO_PORT_C, 11 },  // UART4 RX

  { IO_PORT_C, 6 },  // max 485 drive enable transmit mode PC6  DE
   { IO_PORT_C, 7 },  // max 485 receiver enable listen mode PC7  RE

  {IO_PORT_A, 8},  // UART4_RX

  {IO_PORT_A, 0},  // buton

};
#endif

//////////////////////////////////////////////////////////

void IO_Init(int idx, int mode);
int IO_Read(int idx);
void IO_Write(int idx, int val);
void IO_Set_AlternateFunc(int idx, int af);

#endif  /* _IO_H */
