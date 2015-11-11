#include "Init.h"
#include "Main.h"

//
// Function declarations.
//

//! Initializes the STM32F429I - DISCO's LCD and LEDs resources.
static void BSP_Config();
//! Configures the system clock to 180 MHz.
static void SystemClock_Config();
//! Configures the time handler.
static void TIM_Config();

//
// Variable declaration.
//

//! Time Base Handle Structure.
TIM_HandleTypeDef TimHandle;

void InitHard()
{
	/*
	STM32F4xx HAL library initialization:
		- Configure the Flash prefetch, instruction and Data caches;
		- Configure the Systick to generate an interrupt each 1 msec;
		- Set NVIC Group Priority to 4;
		- Global MSP (MCU Support Package) initialization.
	*/
	HAL_Init();

	BSP_Config();

	SystemClock_Config();

	TIM_Config();
}

static void BSP_Config(void)
{
	// Initialize STM32F429I-DISCO's LEDs.
#if 0
	BSP_LED_Init(LED3);
	BSP_LED_Init(LED4);
#endif

	// Initializes the SDRAM device.
	BSP_SDRAM_Init();

	// Initialize the Touch screen.
	BSP_TS_Init(240, 320);

	// Enable the CRC Module.
	__HAL_RCC_CRC_CLK_ENABLE();
}

static void SystemClock_Config()
{
	/*
	The system Clock is configured as follow :
		System Clock source            = PLL (HSE)
		SYSCLK(Hz)                     = 180000000
		HCLK(Hz)                       = 180000000
		AHB Prescaler                  = 1
		APB1 Prescaler                 = 4
		APB2 Prescaler                 = 2
		HSE Frequency(Hz)              = 8000000
		PLL_M                          = 8
		PLL_N                          = 360
		PLL_P                          = 2
		PLL_Q                          = 7
		VDD(V)                         = 3.3
		Main regulator output voltage  = Scale1 mode
		Flash Latency(WS)              = 5
	*/
	
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	// Enable Power Control clock.
	__HAL_RCC_PWR_CLK_ENABLE();

	/*
	The voltage scaling allows optimizing the power consumption when the device is 
	clocked below the maximum system frequency, to update the voltage scaling value 
	regarding system frequency refer to product datasheet.
	*/
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	// Enable HSE Oscillator and activate PLL with HSE as source.
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	// Activate the Over-Drive mode.
	HAL_PWREx_EnableOverDrive();

	// Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers.
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

static void TIM_Config()
{
	// Compute the prescaler value to have TIM3 counter clock equal to 10 KHz.
	const uint32_t uwPrescalerValue = (uint32_t)((SystemCoreClock / 2) / 10000) - 1;

	// Set TIMx instance.
	TimHandle.Instance = TIM3;

	/*
	Initialize TIM3 peripheral as follows:
		- Period = 500 - 1;
		- Prescaler = ((SystemCoreClock/2)/10000) - 1;
		- ClockDivision = 0;
		- Counter direction = Up.
	*/
	TimHandle.Init.Period = 500 - 1;
	TimHandle.Init.Prescaler = uwPrescalerValue;
	TimHandle.Init.ClockDivision = 0;
	TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	
	if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
	{
		while (1)
		{
		}
	}

	// Start the TIM Base generation in interrupt mode.
	if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
	{
		while (1)
		{
		}
	}
}
