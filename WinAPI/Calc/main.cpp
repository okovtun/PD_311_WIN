#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<limits>
#include<stdio.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "Calc_PD_311";

CONST INT g_i_START_X = 10;
CONST INT g_i_START_Y = 10;

CONST INT g_i_BUTTON_SIZE = 50;
CONST INT g_i_INTERVAL = 5;
CONST INT g_i_BUTTON_DOUBLE_SIZE = g_i_BUTTON_SIZE * 2 + g_i_INTERVAL;

CONST INT g_i_DISPLAY_WIDTH = (g_i_BUTTON_SIZE + g_i_INTERVAL) * 5;
CONST INT g_i_DISPLAY_HEIGHT = 22;

CONST INT g_i_TITLE_HEIGHT = 39;
CONST INT g_i_WINDOW_WIDTH = g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16;
CONST INT g_i_WINDOW_HEIGHT = g_i_DISPLAY_HEIGHT + g_i_START_Y * 2 + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + g_i_TITLE_HEIGHT + 5;

CONST INT g_i_START_X_BUTTON = g_i_START_X;
CONST INT g_i_START_Y_BUTTON = g_i_START_Y * 2 + g_i_DISPLAY_HEIGHT;
CONST INT g_i_START_X_OPERATIONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3;
CONST INT g_i_START_X_CONTROL_BUTTONS = g_i_START_X_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4;

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
VOID PushButton(HWND parent, INT id);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = 0;
	wClass.cbSize = sizeof(wClass);	//cb - Count Bytes
	wClass.cbWndExtra = 0;
	wClass.cbClsExtra = 0;

	wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\calcXP.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\calcXP.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszMenuName = NULL;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		g_i_WINDOW_WIDTH, g_i_WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, hwnd, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

VOID SetSkin(HWND hwnd, LPSTR skin);

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CONST CHAR DEFAULT_SKIN[] = "square_green";
	switch (uMsg)
	{
	case WM_CREATE:
	{
		////////	Console		///////////////
		
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		std::cout << "Hello" << std::endl;
		//https://stackoverflow.com/questions/15543571/allocconsole-not-displaying-cout

		WIN32_FILE_ATTRIBUTE_DATA fInfo;
		GetFileAttributesEx("ButtonsBMP\\square_blue\\0.bmp", GetFileExMaxInfoLevel, &fInfo);
		std::cout << fInfo.dwFileAttributes << std::endl;
		//OutputDebugString("Hello world!");

		///////////////////////////////
		RECT rectWindow;
		RECT rectClient;
		GetWindowRect(hwnd, &rectWindow);
		GetClientRect(hwnd, &rectClient);
		int window_height = rectWindow.bottom - rectWindow.top;
		int title_height = window_height - rectClient.bottom;
		HWND hDisplay = CreateWindowEx
		(
			NULL, "Edit", "0",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_RIGHT/* | ES_READONLY*/,
			g_i_START_X, g_i_START_Y,
			g_i_DISPLAY_WIDTH, g_i_DISPLAY_HEIGHT,
			hwnd, (HMENU)IDC_EDIT_DISPLAY,
			NULL, NULL
		);
		////////////////////// Digits: //////////////////////////
		INT digit = 0;
		CHAR sz_digit[2]{};
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < 3; j++)
			{
				sz_digit[0] = '1' + digit;
				CreateWindowEx
				(
					NULL, "Button", sz_digit,
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
					g_i_START_X_BUTTON + j * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_START_Y_BUTTON + i * (g_i_BUTTON_SIZE + g_i_INTERVAL),
					g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,
					hwnd,
					(HMENU)(IDC_BUTTON_1 + digit++),
					NULL,
					NULL
				);
			}
		}
		HWND hButtonDigit0 = CreateWindowEx
		(
			NULL, "Button", "0",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			g_i_START_X_BUTTON, g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE,
			hwnd,
			(HMENU)IDC_BUTTON_0,
			NULL,
			NULL
		);
		SetSkin(hwnd, (LPSTR)DEFAULT_SKIN);
		HANDLE hImageDigit0 = LoadImage(NULL, "ButtonsBMP\\square_blue\\0.bmp", IMAGE_BITMAP, g_i_BUTTON_DOUBLE_SIZE, g_i_BUTTON_SIZE, LR_LOADFROMFILE);
		if (hImageDigit0 == NULL)
		{
			DWORD dwErrorMessageID = GetLastError();	//Функция GetLastError() возвращает числовой код последней возникшей ошибки выполненя.
			LPSTR lpszMessageBuffer = NULL;
			DWORD dwSize = FormatMessage
			(
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwErrorMessageID,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
				(LPSTR)&lpszMessageBuffer,
				0,
				NULL
			);
			MessageBox(hwnd, lpszMessageBuffer, "Error", MB_OK | MB_ICONERROR);
		}
		SendMessage(hButtonDigit0, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hImageDigit0);
		CreateWindowEx
		(
			NULL, "Button", ".",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X_BUTTON + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 3,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,

			hwnd,
			(HMENU)IDC_BUTTON_POINT,
			NULL,
			NULL
		);
		////////////////////// Operations: //////////////////////////
		CONST CHAR sz_operations[] = "+-*/";
		CHAR sz_operation[2] = "";
		for (int i = 0; i < 4; i++)
		{
			sz_operation[0] = sz_operations[i];
			CreateWindowEx
			(
				NULL, "Button", sz_operation,
				WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

				g_i_START_X_OPERATIONS, g_i_START_Y_BUTTON + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(3 - i),
				g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,

				hwnd,
				(HMENU)(IDC_BUTTON_PLUS + i),
				NULL,
				NULL
			);
		}

		CreateWindowEx
		(
			NULL, "Button", "<-",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X_CONTROL_BUTTONS, g_i_START_Y_BUTTON,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,

			hwnd,
			(HMENU)IDC_BUTTON_BSP,
			NULL,
			NULL
		);
		CreateWindowEx
		(
			NULL, "Button", "C",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X_CONTROL_BUTTONS, g_i_START_Y_BUTTON + g_i_BUTTON_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_SIZE,

			hwnd,
			(HMENU)IDC_BUTTON_CLEAR,
			NULL,
			NULL
		);

		CreateWindowEx
		(
			NULL, "Button", "=",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,

			g_i_START_X_CONTROL_BUTTONS, g_i_START_Y_BUTTON + g_i_BUTTON_DOUBLE_SIZE + g_i_INTERVAL,
			g_i_BUTTON_SIZE, g_i_BUTTON_DOUBLE_SIZE,

			hwnd,
			(HMENU)IDC_BUTTON_EQUAL,
			NULL,
			NULL
		);



	}
	break;
	case WM_COMMAND:
	{
		static double a = DBL_MIN, b = 0;
		static int operation = 0;
		static bool input = false;	//ввод операнда с клавиатуры
		static bool operation_input = false;	//ввод оператора с клавиатуры
		SetFocus(hwnd);
		CONST INT SIZE = 256;
		CHAR sz_display[SIZE]{};
		CHAR sz_digit[2]{};
		HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		if (LOWORD(wParam) >= IDC_BUTTON_0 && LOWORD(wParam) <= IDC_BUTTON_POINT)
		{
			if (!input)SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"");
			sz_digit[0] = LOWORD(wParam) - IDC_BUTTON_0 + '0';
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (LOWORD(wParam) == IDC_BUTTON_POINT)
			{
				if (strchr(sz_display, '.'))break;
				strcat(sz_display, ".");
			}
			else
			{
				if (sz_display[0] == '0' && strlen(sz_display) == 1)sz_display[0] = sz_digit[0];
				else strcat(sz_display, sz_digit);
				input = true;
			}
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_BSP)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			INT display_length = strlen(sz_display);
			if (display_length)
				sz_display[--display_length] = 0;
			if (display_length == 0)sz_display[0] = '0';
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
		}
		if (LOWORD(wParam) == IDC_BUTTON_CLEAR)
		{
			a = DBL_MIN;
			b = 0;
			operation = 0;
			input = false;
			operation_input = false;
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)"0");
		}
		if (LOWORD(wParam) >= IDC_BUTTON_PLUS && LOWORD(wParam) <= IDC_BUTTON_SLASH)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (input && a == DBL_MIN)
			{
				a = atof(sz_display);
				input = false;
			}
			//else b = atof(sz_display);
			if (input)SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
			operation = LOWORD(wParam);
			operation_input = true;
		}
		if (LOWORD(wParam) == IDC_BUTTON_EQUAL/* && operation_input*/)
		{
			SendMessage(hEditDisplay, WM_GETTEXT, SIZE, (LPARAM)sz_display);
			if (input)b = atof(sz_display);
			switch (operation)
			{
			case IDC_BUTTON_PLUS:	a += b; break;
			case IDC_BUTTON_MINUS:	a -= b; break;
			case IDC_BUTTON_ASTER:	a *= b; break;
			case IDC_BUTTON_SLASH:	a /= b; break;
			}
			sprintf(sz_display, "%f", a);
			SendMessage(hEditDisplay, WM_SETTEXT, 0, (LPARAM)sz_display);
			input = false;
			operation_input = false;
		}
	}
	break;
	case WM_KEYUP:
	{
		if (GetKeyState(VK_SHIFT) < 0 && LOWORD(wParam) == 0x38)
		{
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_ASTER, 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
		}
		else if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x30 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - 0x30 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(hwnd, WM_COMMAND, LOWORD(wParam - 0x60 + IDC_BUTTON_0), 0);
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, FALSE, 0);
		}
		switch (LOWORD(wParam))
		{
		case VK_DECIMAL:
		case VK_OEM_PERIOD:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_POINT), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, FALSE, 0);
			break;
		case VK_ADD:
		case VK_OEM_PLUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_PLUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_MINUS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, FALSE, 0);
			break;
		case VK_MULTIPLY:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_ASTER), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, FALSE, 0);
			break;
		case VK_OEM_2:
		case VK_DIVIDE:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_SLASH), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, FALSE, 0);
			break;

		case VK_BACK:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_BSP), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, FALSE, 0);
			break;
		case VK_ESCAPE:
			SendMessage(hwnd, WM_COMMAND, LOWORD(IDC_BUTTON_CLEAR), 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLEAR), BM_SETSTATE, FALSE, 0);
			break;
		case VK_RETURN:
			SendMessage(hwnd, WM_COMMAND, IDC_BUTTON_EQUAL, 0);
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, FALSE, 0);
			break;
		}

	}
	break;
	case WM_KEYDOWN:
	{
		if (GetKeyState(VK_SHIFT) < 0 && LOWORD(wParam) == 0x38)
			SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0);
		else if (LOWORD(wParam) >= 0x30 && LOWORD(wParam) <= 0x39)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x30 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}
		else if (LOWORD(wParam) >= 0x60 && LOWORD(wParam) <= 0x69)
		{
			SendMessage(GetDlgItem(hwnd, wParam - 0x60 + IDC_BUTTON_0), BM_SETSTATE, TRUE, 0);
		}
		switch (LOWORD(wParam))
		{
		case VK_DECIMAL:
		case VK_OEM_PERIOD: SendMessage(GetDlgItem(hwnd, IDC_BUTTON_POINT), BM_SETSTATE, TRUE, 0); break;
		case VK_ADD:
		case VK_OEM_PLUS:   SendMessage(GetDlgItem(hwnd, IDC_BUTTON_PLUS), BM_SETSTATE, TRUE, 0); break;
		case VK_SUBTRACT:
		case VK_OEM_MINUS:  SendMessage(GetDlgItem(hwnd, IDC_BUTTON_MINUS), BM_SETSTATE, TRUE, 0); break;
		case VK_MULTIPLY:   SendMessage(GetDlgItem(hwnd, IDC_BUTTON_ASTER), BM_SETSTATE, TRUE, 0); break;
		case VK_OEM_2:
		case VK_DIVIDE:     SendMessage(GetDlgItem(hwnd, IDC_BUTTON_SLASH), BM_SETSTATE, TRUE, 0); break;

		case VK_BACK:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_BSP), BM_SETSTATE, TRUE, 0); break;
		case VK_ESCAPE:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_CLEAR), BM_SETSTATE, TRUE, 0); break;
		case VK_RETURN:		SendMessage(GetDlgItem(hwnd, IDC_BUTTON_EQUAL), BM_SETSTATE, TRUE, 0); break;
		}

	}
	break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdc = (HDC)wParam;
		SetBkMode(hdc, OPAQUE); SetBkColor(hdc, RGB(0, 0, 155));
		SetBkColor(hdc, RGB(0, 0, 100));
		HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 200));
		SetTextColor(hdc, RGB(255, 0, 0));
		SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);
		SendMessage(hwnd, WM_ERASEBKGND, wParam, 0);
		//SendMessage(GetDlgItem(hwnd, IDC_EDIT_DISPLAY), WM_SETTEXT, 0, (LPARAM)"0");
		////////////////////////////////////////////////////////////////
		/*HWND hEditDisplay = GetDlgItem(hwnd, IDC_EDIT_DISPLAY);
		HDC hdcEditDisplay = GetDC(hEditDisplay);
		SetBkMode(hdcEditDisplay, OPAQUE); SetBkColor(hdcEditDisplay, RGB(0, 0, 155));
		HBRUSH hBrushDisplay = CreateSolidBrush(RGB(0, 0, 200));
		SetTextColor(hdcEditDisplay, RGB(255, 0, 0));
		ReleaseDC(hwnd, hdcEditDisplay);*/

		return (LRESULT)hBrush;
	}
	break;
	case WM_CONTEXTMENU:
	{
		HMENU hMainMenu = CreatePopupMenu();
		HMENU hSubMenu = CreatePopupMenu();
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_STRING, CM_EXIT, "Exit");
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_SEPARATOR, 0, NULL);
		InsertMenu(hMainMenu, 0, MF_BYPOSITION | MF_POPUP, (UINT_PTR)hSubMenu, "Skins");
		InsertMenu(hSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_SQUARE_GREEN, "Square green");
		InsertMenu(hSubMenu, 0, MF_BYPOSITION | MF_STRING, CM_SQUARE_BLUE, "Square blue");

		BOOL item = TrackPopupMenuEx(hMainMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RETURNCMD, LOWORD(lParam), HIWORD(lParam), hwnd, NULL);
		switch (item)
		{
		case CM_SQUARE_BLUE: SetSkin(hwnd,  (LPSTR)"square_blue"); break;
		case CM_SQUARE_GREEN: SetSkin(hwnd, (LPSTR)"square_green"); break;
		case CM_EXIT:		DestroyWindow(hwnd); break;
		}

		HDC hdc = GetDC(hwnd);
		HDC hdcEdit = GetDC(GetDlgItem(hwnd, IDC_EDIT_DISPLAY));
		//SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdc, 0);
		SendMessage(hwnd, WM_CTLCOLOREDIT, (WPARAM)hdcEdit, 0);
		ReleaseDC(hwnd, hdcEdit);
		ReleaseDC(hwnd, hdc);
	}
	break;
	case WM_DESTROY:
		FreeConsole();
		PostQuitMessage(0);
		break;
	case WM_CLOSE:	DestroyWindow(hwnd); break;
	default:		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}

VOID PushButton(HWND parent, INT id)
{
	SendMessage(GetDlgItem(parent, id), BM_SETSTATE, TRUE, 0);
	Sleep(100);
	SendMessage(GetDlgItem(parent, id), BM_SETSTATE, FALSE, 0);
}

LPSTR FormatLastError()
{
	DWORD dwErrorMessageID = GetLastError();	//Функция GetLastError() возвращает числовой код последней возникшей ошибки выполненя.
	LPSTR lpszMessageBuffer = NULL;
	DWORD dwSize = FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dwErrorMessageID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
		(LPSTR)&lpszMessageBuffer,
		0,
		NULL
	);
	return lpszMessageBuffer;
}

VOID SetSkin(HWND hwnd, LPSTR skin)
{
	CHAR sz_file[MAX_PATH]{};
	for (int i = IDC_BUTTON_0; i <= IDC_BUTTON_9; i++)
	{
		HWND hButton = GetDlgItem(hwnd, i);
#ifdef DEBUG
		MessageBox(hwnd, FormatLastError(), "Error", MB_OK | MB_ICONERROR);
#endif // DEBUG

		sprintf(sz_file, "ButtonsBMP\\%s\\button_%i.bmp", skin, i - IDC_BUTTON_0);
		HANDLE hImage = LoadImage
		(
			GetModuleHandle(NULL),
			sz_file,
			IMAGE_BITMAP,
			i == IDC_BUTTON_0 ? g_i_BUTTON_DOUBLE_SIZE : g_i_BUTTON_SIZE,
			g_i_BUTTON_SIZE,
			LR_LOADFROMFILE
		);
#ifdef DEBUG
		MessageBox(hwnd, FormatLastError(), "Error", MB_OK | MB_ICONERROR);
#endif // DEBUG

		SendMessage(hButton, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)hImage);
#ifdef DEBUG
		MessageBox(hwnd, FormatLastError(), "Error", MB_OK | MB_ICONERROR);
#endif // DEBUG

	}
}