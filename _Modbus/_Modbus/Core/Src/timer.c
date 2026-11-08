#include <stdio.h>
#include <string.h>

#include "io.h"
#include "system.h"
#include "timer.h"
#include "stm32f4xx_hal.h"

static TIM_TypeDef *s_TimTab[] = {
   TIM1, TIM2, TIM3, TIM4, TIM5,TIM6,TIM8,TIM9,TIM10,TIM11,TIM12,TIM13,TIM14,
};

static TIM_HandleTypeDef s_hTmTab[12];

static IRQn_Type s_TimIrqTab[] = {
	TIM1_CC_IRQn,
  TIM2_IRQn,
  TIM3_IRQn,
  TIM4_IRQn,
  TIM5_IRQn,
  TIM6_DAC_IRQn,
  TIM7_IRQn,
  TIM8_UP_TIM13_IRQn,
  TIM1_BRK_TIM9_IRQn,
  TIM1_TRG_COM_TIM11_IRQn,
  TIM8_BRK_TIM12_IRQn,
  TIM8_TRG_COM_TIM14_IRQn,
};

static uint32_t s_tim_ch_list[] = {
		TIM_CHANNEL_1,
		TIM_CHANNEL_2,
		TIM_CHANNEL_3,
		TIM_CHANNEL_4,
		TIM_CHANNEL_ALL,
};

void Timer_Reset(int tmNo)
{
__HAL_TIM_SET_COUNTER(&s_hTmTab[tmNo],0);
}
                 
unsigned Timer_GetCount(int tmNo)
{
return __HAL_TIM_GET_COUNTER(&s_hTmTab[tmNo]);
}

void Timer_Start(int tmNo)
{
HAL_TIM_Base_Start(&s_hTmTab[tmNo]);
}

void Timer_Stop(int tmNo)
{
HAL_TIM_Base_Start(&s_hTmTab[tmNo]);
}

void Timer_IC_Start(int tmNo, uint32_t ch)
{
HAL_TIM_IC_Start(&s_hTmTab[tmNo], s_tim_ch_list[ch]);
}

void Timer_Pwm_Start(int tmNo, uint32_t ch) {
HAL_TIM_PWM_Start(&s_hTmTab[tmNo], s_tim_ch_list[ch]);
}


void Timer_Init(TIMER_t tmNo, unsigned prescale, unsigned period, unsigned repeat)
{

  // 1) Timer birimine clock isareti sagliyoruz
	switch (tmNo) {
		case TIMER_1:
					__HAL_RCC_TIM1_CLK_ENABLE();  // timer1 clock activation
					break;
		case TIMER_2:
					__HAL_RCC_TIM2_CLK_ENABLE();  // timer2 clock activation
					break;
		case TIMER_3:
					__HAL_RCC_TIM3_CLK_ENABLE();  // timer3 clock activation
					break;
		case TIMER_4:
					__HAL_RCC_TIM4_CLK_ENABLE();  // timer4 clock activation
					break;
		case TIMER_5:
					__HAL_RCC_TIM5_CLK_ENABLE();  // timer5 clock activation
					break;
		case TIMER_6:
						__HAL_RCC_TIM6_CLK_ENABLE();  // timer6 clock activation
						break;
		case TIMER_8:
					__HAL_RCC_TIM8_CLK_ENABLE();  // timer8 clock activation
					break;
		case TIMER_9:
					__HAL_RCC_TIM9_CLK_ENABLE();  // timer9 clock activation
					break;
		case TIMER_10:
					__HAL_RCC_TIM10_CLK_ENABLE();  // timer10 clock activation
					break;
		case TIMER_11:
					__HAL_RCC_TIM11_CLK_ENABLE();  // timer11 clock activation
					break;
		case TIMER_12:
					__HAL_RCC_TIM12_CLK_ENABLE();  // timer12 clock activation
					break;
		case TIMER_13:
					__HAL_RCC_TIM13_CLK_ENABLE();  // timer13 clock activation
					break;
		case TIMER_14:
					__HAL_RCC_TIM14_CLK_ENABLE();  // timer14 clock activation
					break;
		default:
			break;
	}

	//memset(&s_hTmTab[tmNo], 0, sizeof(TIM_HandleTypeDef));

  // 2) Timer parametrelerini ayarliyoruz ( under handle roof)

	s_hTmTab[tmNo].Instance = s_TimTab[tmNo];
	s_hTmTab[tmNo].Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	s_hTmTab[tmNo].Init.CounterMode = TIM_COUNTERMODE_UP;
	s_hTmTab[tmNo].Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	s_hTmTab[tmNo].Init.Period = period - 1;
	s_hTmTab[tmNo].Init.Prescaler = prescale - 1;
	s_hTmTab[tmNo].Init.RepetitionCounter = repeat - 1;
	HAL_TIM_Base_Init(&s_hTmTab[tmNo]); //structer a atanan değerler registerlara yazılıyor.

  // 3) Timer counter register'ini sifirliyoruz
  Timer_Reset(tmNo);
}

void TIM_PWM_INIT(int tmNo,int idx, uint32_t ch, uint32_t duty)
{
	// TIM1 CH1 PA8 port GPIO CONFIG

 IO_Init(idx, IO_MODE_ALTERNATE);

//OUTPUT COMPARE SETTİNGS
// pwm settings
	TIM_OC_InitTypeDef OC_init;

	OC_init.OCFastMode = TIM_OCFAST_DISABLE;
	OC_init.OCIdleState = TIM_OCIDLESTATE_RESET;
	OC_init.OCMode = TIM_OCMODE_PWM1;
	OC_init.Pulse = duty;
	OC_init.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	OC_init.OCNPolarity =TIM_OCNPOLARITY_HIGH;
	OC_init.OCPolarity =TIM_OCNPOLARITY_HIGH;
	HAL_TIM_PWM_Init(&s_hTmTab[tmNo]);
	HAL_TIM_PWM_ConfigChannel(&s_hTmTab[tmNo], &OC_init, s_tim_ch_list[ch]);

}

void TIM_IC_INIT(TIMER_t tmNo, unsigned prescale, unsigned period, unsigned repeat,int ch)
{
// peripheral config <->
IO_Init(IOP_TIM1, IO_MODE_ALTERNATE);  // {IO_PORT_A, 8, GPIO_AF1_TIM1}, PE9

Timer_Init(tmNo,prescale,period,repeat);   //TIM1 - TIMER_t tmNo, unsigned prescale, unsigned period, unsigned repeat
// Timer çalışma config timer_init içeriğinde.
TIM_IC_InitTypeDef IC_Init;

IC_Init.ICFilter = 0;
IC_Init.ICPolarity = TIM_ICPOLARITY_RISING;
IC_Init.ICPrescaler = TIM_ICPSC_DIV1;
IC_Init.ICSelection = TIM_ICSELECTION_DIRECTTI;
HAL_TIM_IC_Init(&s_hTmTab[tmNo]);
HAL_TIM_IC_ConfigChannel(&s_hTmTab[tmNo], &IC_Init, TIM_CHANNEL_1);

Timer_IntConfig(tmNo,1,TIM_CHANNEL_1);
}

void Timer_IntConfig(int tmNo, int priority, int ch)
{
/*
HAL_NVIC_SetPriority(TIM1_CC_IRQn, 1, 1);
HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);

HAL_TIM_IC_Start_IT(&s_hTmTab[tmNo], TIM_CHANNEL_1);
*/

HAL_NVIC_SetPriority(TIM6_DAC_IRQn, priority, priority);
HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn);

HAL_TIM_Base_Start_IT(&s_hTmTab[tmNo]);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TIMER Interrupt Handlers Theread

volatile uint32_t g_period;
volatile uint8_t g_captured;

void TIM1_CC_IRQHandler(void)
{
	static uint32_t cap0, cap1;

	if (TIM1->SR & TIM_SR_CC1IF)
	{
		//cap1 = TIM1->CCR1;
		//if((cap1 - cap0) < 0) {
			//g_period = ((cap1 + TIMER_OVERFLOW_RATE) - cap0) ;
			//cap0 = cap1;

		cap1 = TIM1->CCR1;
		if((cap1 - cap0) < 0){
			g_period = ((cap1 + TIMER_OVERFLOW_RATE) - cap0) ;  //overflow condition
		} else {
			g_period = cap1 - cap0 ;
		}

		cap0 = cap1;
		g_captured = 1 ;
	    TIM1->SR &= ~TIM_SR_CC1IF;

	}

}
