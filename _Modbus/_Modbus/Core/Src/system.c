#include <stdio.h>

#include "io.h"
#include "system.h"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
volatile uint8_t button_flag;

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

////////////////////////////////////////////////////

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Sys_IoInit(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
}

void Sys_Init(void)
{
  //SysTick_Config(SystemCoreClock / CLOCKS_PER_SEC);

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();  // systick_ enable in hal_init

  /* Configure the system clock */
  SystemClock_Config();

  Sys_IoInit();
}

///////////////////////////////////////////////////

void Sys_Tick_Time(void)
{
	static int count;

	if(IO_Read(IOP_BUTON) != 0) {
		count++;

		if(count >= 100) {
			count = 0;
			button_flag = 1 ;
		}
	}


}

clock_t clock(void)
{
	return (clock_t)HAL_GetTick();
}

// stdout dosyasını LCD modüle yönlendirmek için
// başlangıç işlemleri
void Sys_ConsoleInit(void)
{
  setvbuf(stdout, NULL, _IONBF, 0);
}

///////////////////////////////////////////////
// Console output (stdout yönlendirme)
//
#if 1
void _putch(unsigned char c)
{

}

size_t _write(int handle, const unsigned char *buffer, size_t size)
{
  size_t nChars = 0;

  if (buffer == NULL)
    return 0;

  if (handle != _STDOUT && handle != _STDERR)
    return 0;

  while (size--) {
    _putch(*buffer++);
    ++nChars;
  }

  return nChars;
}
#endif







