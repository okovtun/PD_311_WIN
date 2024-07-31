#include<Windows.h>
#include<cstdio>
#include"resource.h"

//CONST CHAR g_sz_INVITATION[] = "¬‚Â‰ËÚÂ ‚‡¯Â ËÏˇ";
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
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			if (i == CB_ERR)MessageBox(hwnd, "ƒÎˇ Ì‡˜‡Î‡ Ò‰ÂÎ‡ÈÚÂ ‚‡¯ ‚˚·Ó", "Warning", MB_OK | MB_ICONWARNING);
			{
				CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};//—Œƒ≈–∆»“ —“–Œ ” Õ≈œ–Œ—ƒ≈—“¬≈ÕÕÕŒ —◊»“¿ÕÕ”ﬁ »« COMBOBOX
			CHAR sz_message[SIZE]{};//—Œƒ≈–∆»“  ŒÕ≈◊ÕŒ≈ —ŒŒ¡Ÿ«≈Õ»≈,  Œ“Œ–Œ≈ ¡”ƒ≈“ ¬€¬Œƒ»“‹—ﬂ ¬ MESSAGEBOX
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_buffer);
			sprintf(sz_message, "¬˚ ‚˚·‡ÎË ÔÛÌÍÚ π%i, ÒÓ ÁÌ‡˜ÂÌËÂÏ %s", i, sz_buffer);
			MessageBox(hwnd, sz_message, "You choice", MB_OK | MB_ICONINFORMATION);
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