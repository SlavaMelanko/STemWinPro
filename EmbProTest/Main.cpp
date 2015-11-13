#include "Main.h"
#include "WM.h"

extern "C"
{
#include "Init.h"
#include "TestDlg.h"
}

#include <stdlib.h>
#include <cstring>

#include <vector>

#include <FreeRTOS.h>
#include <task.h>

//
// Function declarations.
//

//! Provides the GUI with current state of the touch screen.
void BSP_Pointer_Update(void);
//! Checks background events.
void BSP_Background(void);

//
// Variable declarations.
//

uint8_t GUI_Initialized = 0;

class Person
{
public:
	Person()
		: id(101010101)
		, name(1024, 'a')
		, address(1024, 'b')
	{
	}
	~Person()
	{
	}
public:
	int id;
	std::vector<char> name;
	std::vector<char> address;
};

Person mfp;

// Task to be created.
void vTaskCode(void * pvParameters)
{
	for (int i = 100000; i != 0; --i)
	{
		/* Task code goes here. */
	}
}

// Function that creates a task.
void vOtherFunction(void)
{
	static unsigned char ucParameterToPass;
	TaskHandle_t xHandle = NULL;

	/*
	Create the task, storing the handle.  Note that the passed parameter 
	ucParameterToPass must exist for the lifetime of the task, so in this 
	case is declared static. If it was just an automatic stack variable 
	it might no longer exist, or at least have been corrupted, by the time
	the new task attempts to access it.
	*/
	xTaskCreate( vTaskCode,
		"NAME",
		configMINIMAL_STACK_SIZE,
		&ucParameterToPass,
		tskIDLE_PRIORITY, 
		&xHandle);
	configASSERT(xHandle);

	// Use the handle to delete the task.
	if (xHandle != NULL)
	{
		vTaskDelete(xHandle);
	}
}

int main(void)
{
	InitHard();

	vOtherFunction();

	// Init the STemWin GUI Library.
	GUI_Init();
	GUI_Initialized = 1;

	// Activate the use of memory device feature.
	WM_SetCreateFlags(WM_CF_MEMDEV);

	WM_HWIN hDlg = CreateTestDlg();

	while (1)
	{
		GUI_Delay(10);
	}
}

// Period elapsed callback in non blocking mode.
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	BSP_Background();
}

/*
	TIM MSP Initialization.
	This function configures the hardware resources used in this application:
	- Peripheral's clock enable;
	- Peripheral's GPIO Configuration.
*/
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	// 1- Enable peripherals and GPIO Clocks.
	// TIMx Peripheral clock enable.
	__HAL_RCC_TIM3_CLK_ENABLE();

	// 2- Configure the NVIC for TIMx.
	// Set the TIMx priority.
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);

	// Enable the TIMx global Interrupt.
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

void BSP_Background(void)
{
#if 0
	BSP_LED_Toggle(LED3);
	BSP_LED_Toggle(LED4);
#endif

	// Capture input event and update cursor.
	if(GUI_Initialized == 1)
		BSP_Pointer_Update();
}

void BSP_Pointer_Update(void)
{
	GUI_PID_STATE TS_State;
	static TS_StateTypeDef prev_state;
	TS_StateTypeDef  ts;
	uint16_t xDiff, yDiff;

	BSP_TS_GetState(&ts);

	TS_State.Pressed = ts.TouchDetected;

	if (ts.TouchDetected)
	{
		xDiff = (prev_state.X > ts.X) ? (prev_state.X - ts.X) : (ts.X - prev_state.X);
		yDiff = (prev_state.Y > ts.Y) ? (prev_state.Y - ts.Y) : (ts.Y - prev_state.Y);

		if ((prev_state.TouchDetected != ts.TouchDetected) || (xDiff > 3) || (yDiff > 3))
		{
			prev_state = ts;

			TS_State.Layer = 0;
			TS_State.x = ts.X;
			TS_State.y = ts.Y;

			GUI_TOUCH_StoreStateEx(&TS_State);
		}
	}
	else
	{
		// Use -1 if touch is not pressed.
		TS_State.Layer = 0;
		TS_State.x = -1;
		TS_State.y = -1;

		GUI_TOUCH_StoreStateEx(&TS_State);
	}
}

#ifdef  USE_FULL_ASSERT
/*
	Reports the name of the source file and the source line number
	where the assert_param error has occurred.
*/
void assert_failed(uint8_t* file, uint32_t line)
{
	/*
	User can add his own implementation to report the file name and line number,
		ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)
	*/

	printf("Wrong parameters value: file %s on line %d\r\n", file, line);

	while (1)
	{
	}
}
#endif
