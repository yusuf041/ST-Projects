#ifndef _TIMER_H
#define _TIMER_H

#define INPUT_TIMER_FREQ 				1000000
#define TIMER_OVERFLOW_RATE 			65535

enum {
	TIM_BASE,
	TIM_PWM,
	TIM_OC,
	TIM_IC,
};
typedef enum {
  TIMER_1,
  TIMER_2,
  TIMER_3,
  TIMER_4,
  TIMER_5,
  TIMER_6,
  TIMER_8,
  TIMER_9,
  TIMER_10,
  TIMER_11,
  TIMER_12,
  TIMER_13,
  TIMER_14,
}TIMER_t;

enum {
	TIM_CH1,
	TIM_CH2,
	TIM_CH3,
	TIM_CH4,
	TIM_CH_ALL,
};

#define T1_FREQ         CLOCK_FREQ
#define T2_FREQ         (CLOCK_FREQ / 2)
#define T3_FREQ         (CLOCK_FREQ / 2)

void Timer_Reset(int tmNo);
unsigned Timer_GetCount(int tmNo);
void Timer_Start(int tmNo);
void Timer_Stop(int tmNo);
void Timer_Init(TIMER_t tmNo, unsigned prescale, unsigned period, unsigned repeat);
void Timer_IntConfig(int tmNo, int priority, int ch);

void TIM_IC_INIT(TIMER_t tmNo, unsigned prescale, unsigned period, unsigned repeat,int ch);
void TIM_PWM_INIT(int tmNo,int idx, uint32_t ch, uint32_t duty);
void Timer_Pwm_Start(int tmNo, uint32_t ch);
void Timer_IC_Start(int tmNo, uint32_t ch);

#endif  /* _TIMER_H */
