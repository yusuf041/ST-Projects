#define _IOS_
#include "io.h"

// GPIO portlari dizisi
static GPIO_TypeDef *s_GPIO_Ports[] = {
  GPIOA,
  GPIOB,
  GPIOC,
  GPIOD,
};

void IO_Set_AlternateFunc(int idx, int af)
{
	s_ios[idx].af = af;
}


void IO_Init(int idx, int mode)
{
  GPIO_InitTypeDef ioInit;
  
  //GPIO_StructInit(&ioInit);
  
  switch (mode) {
    case IO_MODE_INPUT:
      ioInit.Mode = GPIO_MODE_INPUT;
      ioInit.Pull = GPIO_NOPULL;
      break;
      
    case IO_MODE_OUTPUT:
        ioInit.Mode = GPIO_MODE_OUTPUT_PP;
        ioInit.Pull = GPIO_NOPULL;
      break;
      
    case IO_MODE_ALTERNATE:
        ioInit.Mode = GPIO_MODE_AF_PP;
        ioInit.Pull = GPIO_NOPULL;
        ioInit.Alternate = s_ios[idx].af;
      break;

  case IO_MODE_ANALOG:
      ioInit.Mode = GPIO_MODE_ANALOG;
      ioInit.Pull = GPIO_NOPULL;
      break;   
      
    case IO_MODE_INPUT_PD:
        ioInit.Mode = GPIO_MODE_INPUT;
        ioInit.Pull = GPIO_PULLDOWN;
      break;
      
    case IO_MODE_INPUT_PU:
        ioInit.Mode = GPIO_MODE_INPUT;
        ioInit.Pull = GPIO_PULLUP;
      break;
      
    case IO_MODE_OUTPUT_OD:
        ioInit.Mode = GPIO_MODE_OUTPUT_OD;
        ioInit.Pull = GPIO_NOPULL;
      break;
      
    case IO_MODE_OUTPUT_OD_PU:
        ioInit.Mode = GPIO_MODE_OUTPUT_OD;
        ioInit.Pull = GPIO_PULLUP;
      break;
      
    case IO_MODE_ALTERNATE_OD:
        ioInit.Mode = GPIO_MODE_AF_OD;
        ioInit.Pull = GPIO_NOPULL;
        ioInit.Alternate = s_ios[idx].af;
      break;
      
    case IO_MODE_ALTERNATE_OD_PU:  
        ioInit.Mode = GPIO_MODE_AF_OD;
        ioInit.Pull = GPIO_PULLUP;
        ioInit.Alternate = s_ios[idx].af;
      break;    
  }
  
  ioInit.Speed = GPIO_SPEED_FREQ_HIGH;
  ioInit.Pin = 1 << s_ios[idx].pin;
  
  HAL_GPIO_Init(s_GPIO_Ports[s_ios[idx].port], &ioInit);
}

int IO_Read(int idx)
{
  uint32_t mask;
  GPIO_TypeDef *ioPort;
  
  ioPort = s_GPIO_Ports[s_ios[idx].port]; 
  mask = (1 << s_ios[idx].pin);

  return ((ioPort->IDR & mask) != 0);
}

void IO_Write(int idx, int val)
{
  uint32_t mask;
  GPIO_TypeDef *ioPort;
  
  ioPort = s_GPIO_Ports[s_ios[idx].port]; 
  mask = (1 << s_ios[idx].pin);
  
  if (val)
    ioPort->ODR |= mask;
  else
    ioPort->ODR &= ~mask; 
}



