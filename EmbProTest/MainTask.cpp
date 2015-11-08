#include "GUI.h"

void MainTask()
{
	GUI_Clear();
	GUI_SetFont(&GUI_Font20_1);
	GUI_DispStringAt("Hello world!", (LCD_GetXSize() - 100) / 2, (LCD_GetYSize() - 20) / 2);
	while (1)
		;
}
