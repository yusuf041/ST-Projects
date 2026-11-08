#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "io.h"
#include "system.h"
#include "fifo.h"
#include "timer.h"
#include "Modbus.h"


unsigned char lBuf[SZ_BUF + 1];

extern volatile uint8_t button_flag;

void init(void)
{

	Sys_Init();

	Sys_Tick_Time();

	Sys_ConsoleInit();

	  IO_Write(IOP_HeardLED, 0);
	  IO_Write(IOP_LED, 0);
	  IO_Init(IOP_HeardLED, IO_MODE_OUTPUT);
	  IO_Init(IOP_BUTON, IO_MODE_INPUT_PD);
}

void Task_LED(void)
{
  static enum {
    I_LED_ON,
    S_LED_ON,
    
    I_LED_OFF,
    S_LED_OFF
  } state = I_LED_ON;
  
  static clock_t t0, t1;
  
  t1 = clock();
  
  switch (state) {
  case I_LED_ON:
      IO_Write(IOP_HeardLED, 1);     // LED on

      t0 = t1;     // Son ON olma ba�lang�� zaman�
      state = S_LED_ON;
      //break;
    
  case S_LED_ON:
    if (t1 - t0 >= CLOCKS_PER_SEC / 10)
      state = I_LED_OFF;
    break;
    
  case I_LED_OFF:
      IO_Write(IOP_HeardLED, 0);     // LED off

      t0 = t1;     // Son OFF olma ba�lang�� zaman�
      state = S_LED_OFF;
      //break;

  case S_LED_OFF:
    if (t1 - t0 >= CLOCKS_PER_SEC / 1.5 )
      state = I_LED_ON;
    break;
  }
}


#if 0
void Task_Print(void)
{
  static unsigned long count;
  unsigned char row, col;
  
  OLED_GetCursor(&row, &col);
  OLED_SetCursor(0, 0);
  printf("SAYI=%10lu", ++count);
  OLED_SetCursor(row, col);
}
#endif


void Task_Iuart(void) {

	char *ptr = "yusuf napiyorsun kardess";

if (button_flag != 0) {

	IUART_Send_data(ptr, strlen(ptr));

	button_flag = 0 ;  //interrupt progressed
}


}

int main()
{
  // �al��ma zaman� yap�land�rmalar�
  init();

  
  //OLED_SetFont(FNT_LARGE);
//  own_uart_init();
 // uint32_t clk = HAL_RCC_GetPCLK2Freq();  //84mHz civarı eğer 16mHz ise clock config yanlış demektir

  // G�rev �evrimi


  // MB_init(9600);


 // mb_timer_init();


  //MB_init(9600);

//char *val = "deneme";

  while (1) 
  {
//	//  own_send_uart_line_data(size_return);
	//  DelayMs(1000);
	 // Task_Iuart();
	 Task_LED();
	 mb_task();

	// IUART_Send_data(val, strlen(val));
	 // DelayMs(1000);
  }
  
  //return 0;
}
