#include<Windows.h>
#include"resource.h"

CONST CHAR* values[] = { "This","is","my","first","Combo","Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
		for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)values[i]);
		}
		break;
	}
		
	case WM_COMMAND:
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}