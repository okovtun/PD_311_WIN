#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* values[] = { "This", "is", "my", "first", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(values) / sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
		SendMessage(hCombo, CB_SETCURSEL, 0, 0);
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);	//1) Получаем индекс выбранного элемента
			/*if (i == CB_ERR)
				MessageBox(hwnd, "Для начала сделайте Ваш выбор", "Warning", MB_OK | MB_ICONWARNING);
			else*/
			{
				CONST INT SIZE = 256;
				CHAR sz_buffer[SIZE]{};	//содержит строку, непосредственно считанную из ComboBox
				CHAR sz_message[SIZE]{};//содержит конечное сообщение, которое будет выводиться в MessageBox
				SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
				sprintf(sz_message, "Вы выбрали пункт №%i, со значением %s", i, sz_buffer);
				//https://legacy.cplusplus.com/reference/cstdio/sprintf/?kw=sprintf
					//https://legacy.cplusplus.com/reference/cstdio/printf/
				MessageBox(hwnd, sz_message, "Your choice", MB_OK | MB_ICONINFORMATION);
			}
		}
		break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;

	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}