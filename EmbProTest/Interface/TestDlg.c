#include "TestDlg.h"
#include "DIALOG.h"

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
	{ WINDOW_CreateIndirect, "Window", ID_WINDOW_0, 0, 0, 240, 320, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "FirstBtn", ID_BUTTON_0, 10, 30, 220, 40, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "SecondBtn", ID_BUTTON_1, 10, 75, 220, 40, 0, 0, 0 },
	{ BUTTON_CreateIndirect, "ThirdBtn", ID_BUTTON_2, 10, 120, 220, 40, 0, 0, 0 },
};

static void _cbDialog(WM_MESSAGE* msg)
{
	WM_HWIN item;
	int id = 0;
	int code = 0;

	switch (msg->MsgId)
	{
	case WM_INIT_DIALOG:
		firstBtn = WM_GetDialogItem(msg->hWin, ID_BUTTON_0);
		BUTTON_SetText(firstBtn, "First");

		secondBtn = WM_GetDialogItem(msg->hWin, ID_BUTTON_1);
		BUTTON_SetText(secondBtn, "Second");

		thirdBtn = WM_GetDialogItem(msg->hWin, ID_BUTTON_2);
		BUTTON_SetText(thirdBtn, "Third");

		break;
	case WM_NOTIFY_PARENT:
		id = WM_GetId(msg->hWinSrc);
		code = msg->Data.v;

		switch(id)
		{
		case ID_BUTTON_0:
			switch(code)
			{
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;
		case ID_BUTTON_1:
			switch(code)
			{
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;
		case ID_BUTTON_2:
			switch(code)
			{
			case WM_NOTIFICATION_CLICKED:
				break;
			case WM_NOTIFICATION_RELEASED:
				break;
			}
			break;
		}

		break;
	case WM_PAINT:
#if 0
		GUI_DrawBitmap(&bmMainBackground, 0, 0);
		BUTTON_SetBitmap(secondBtn, BUTTON_BI_PRESSED, &bmBtnLargePressed);
		BUTTON_SetBitmap(secondBtn, BUTTON_BI_UNPRESSED, &bmBtnLargePlain);
		BUTTON_SetBitmap(firstBtn, BUTTON_BI_PRESSED, &bmBtnLargePressed);
		BUTTON_SetBitmap(firstBtn, BUTTON_BI_UNPRESSED, &bmBtnLargePlain);
		BUTTON_SetBitmap(backBtn, BUTTON_BI_PRESSED, &bmBtnPressed1);
		BUTTON_SetBitmap(backBtn, BUTTON_BI_UNPRESSED, &bmBtnPlain1);
#endif
		break;
	default:
		WM_DefaultProc(msg);

		break;
	}
}

WM_HWIN CreateTestDlg()
{
	WM_HWIN hWin = GUI_CreateDialogBox(
		_aDialogCreate, GUI_COUNTOF(_aDialogCreate), &_cbDialog, WM_HBKWIN, 0, 0);

	return hWin;
}
