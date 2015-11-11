#ifndef _TESTDLG_H_
#define _TESTDLG_H_

#include "WM.h"

// Defines button ids.
#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_BUTTON_0 (GUI_ID_USER + 0x01)
#define ID_BUTTON_1 (GUI_ID_USER + 0x02)
#define ID_BUTTON_2 (GUI_ID_USER + 0x03)

// Button handlers.
WM_HWIN firstBtn;
WM_HWIN secondBtn;
WM_HWIN thirdBtn;

//! Creates test dialog.
WM_HWIN CreateTestDlg();

#endif // _TESTDLG_H_
