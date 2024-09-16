#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<Richedit.h>
#include<CommCtrl.h>
#include<iostream>
#include"resource.h"

#define tab '\t'

CONST CHAR g_sz_WINDOW_CLASS[] = "Text Editor (PD_311)";

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
CHAR* FormatLastError();
BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName, CHAR sz_title[]);
BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName, CHAR sz_title[]);
LPSTR FormatFileTime(FILETIME filetime, CONST CHAR sz_message[], CHAR sz_buffer[]);
VOID SetFileDataToStatusBar(HWND hwnd, CONST CHAR szFileName[], CHAR sz_title[]);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	setlocale(LC_ALL, "");
	system("chcp 1251");
	//1)Ðåãèñòðàöèÿ êëàññà îêíà:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));

	wClass.style = 0;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "ICO\\txt.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "ICO\\txt.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wClass.hCursor = LoadCursor(hInstance, IDC_ARROW);
	HBITMAP background = (HBITMAP)LoadImage(hInstance, "IMG\\background.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wClass.hbrBackground = CreatePatternBrush(background);

	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = MAKEINTRESOURCE(IDR_MAIN_MENU);

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2)Ñîçäàíèå îêíà
	HWND hwnd = CreateWindowEx
	(
		WS_EX_ACCEPTFILES,
		g_sz_WINDOW_CLASS,
		g_sz_WINDOW_CLASS,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	std::cout << FormatLastError() << std::endl;
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	std::cout << "\n------------------------------------------------\n" << std::endl;
	std::cout << lpCmdLine << std::endl;
	CHAR sz_title[MAX_PATH]{};
	if(strlen(lpCmdLine))LoadTextFileToEdit(GetDlgItem(hwnd, IDC_EDIT), lpCmdLine, sz_title);
	std::cout << "\n------------------------------------------------\n" << std::endl;
	UpdateWindow(hwnd);

	//3)Çàïóñê öèêëà ñîîáùåíèé:
	MSG msg;
	///////////////////////////////////////////////////////////////////////////////////
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	////	!!!!!!!!!		ÍÈÊÎÃÄÀ ÍÅ ÏÈØÈÒÅ ÇÄÅÑÜ 'hwnd'			!!!!!!!!!!!!!	///
	//while (GetMessage(&msg, hwnd, 0, NULL) > 0)
	///////////////////////////////////////////////////////////////////////////////////
	while (GetMessage(&msg, 0, 0, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	FreeConsole();
	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hRichEdit20 = LoadLibrary("riched20.dll");
	static HINSTANCE comCtrl32 = LoadLibrary("ComCtl32.dll");
	//static INITCOMMONCONTROLSEX icce;
	static CHAR sz_title[MAX_PATH]{};
	static CHAR szFileName[MAX_PATH] = "";
	static BOOL bnChanged = FALSE;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//InitCommonControlsEx(&icce);
		RECT windowRect;
		RECT clientRect;
		GetWindowRect(hwnd, &windowRect);
		GetClientRect(hwnd, &clientRect);
		std::cout << "Window:" << windowRect.left << tab << windowRect.top << tab << windowRect.right << tab << windowRect.bottom << std::endl;
		std::cout << "Client:" << clientRect.left << tab << clientRect.top << tab << clientRect.right << tab << clientRect.bottom << std::endl;
		HWND hEdit = CreateWindowEx
		(
			WS_EX_CLIENTEDGE, RICHEDIT_CLASS, "",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
			0, 0,
			windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top,
			hwnd,
			(HMENU)IDC_EDIT,
			NULL,
			NULL
		);
		SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_CHANGE);

		//				Status bar:
		HWND hStatus = CreateWindowEx
		(
			NULL, STATUSCLASSNAME, "Status bar",
			WS_CHILD | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd,
			(HMENU)IDC_STATUS,
			NULL,
			NULL
		);
		//1) Filepath;
		//2) Save status;
		//3) Number of words;
		//4) Window size;
		//5) File size;
		//6) Creation date;
		//7) Date of change;
		INT dimensions[] = { 500, 600, 700, 800, 900, 1100, -1 };
		//INT dimensions[] = { -1, -1, -1, -1, -1, -1, -1 };
		SendMessage(hStatus, SB_SETPARTS, sizeof(dimensions) / sizeof(dimensions[0]), (LPARAM)dimensions);

		DragAcceptFiles(hwnd, TRUE);
		//RegisterDragDrop();
	}
	break;
	case WM_SIZE:
	{
		RECT windowRect;
		RECT clientRect;
		RECT statusRect;
		GetWindowRect(hwnd, &windowRect);
		GetClientRect(hwnd, &clientRect);
		GetWindowRect(GetDlgItem(hwnd, IDC_STATUS), &statusRect);
		std::cout << "Window:" << windowRect.left << tab << windowRect.top << tab << windowRect.right << tab << windowRect.bottom << std::endl;
		std::cout << "Client:" << clientRect.left << tab << clientRect.top << tab << clientRect.right << tab << clientRect.bottom << std::endl;
		std::cout << "Status:" << statusRect.left << tab << statusRect.top << tab << statusRect.right << tab << statusRect.bottom << std::endl;
		std::cout << "\n--------------------------------------------\n";
		DWORD dwStatusHeight = statusRect.bottom - statusRect.top;
		MoveWindow(GetDlgItem(hwnd, IDC_EDIT), 10, 10, clientRect.right - 20, clientRect.bottom - 20 - dwStatusHeight, TRUE);
		MoveWindow(GetDlgItem(hwnd, IDC_STATUS), 0, 0, 0, 0, TRUE);
	}
	break;
	case WM_DROPFILES:
	{
		HDROP hDrop = (HDROP)wParam;
		DragQueryFile(hDrop, 0, szFileName, MAX_PATH);
		std::cout << "WM_DROPFILES: " << szFileName << std::endl;
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		LoadTextFileToEdit(hEdit, szFileName, sz_title);
		DragFinish(hDrop);
		//UpdateWindow(hwnd);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_FILE_OPEN:
		{
			BOOL cancel = FALSE;
			if (bnChanged)
			{
				switch (MessageBox(hwnd, "Ñîõðàíèòü èçìåíåíèÿ?", "Ôàéë áûë èçìåíåí", MB_YESNOCANCEL | MB_ICONQUESTION))
				{
				case IDYES:		SendMessage(hwnd, WM_COMMAND, ID_FILE_SAVE, 0);
				case IDNO:		break;
				case IDCANCEL:	cancel = TRUE;
				}
			}
			//CHAR szFileName[MAX_PATH]{};
			if (cancel)break;
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0C Plus Plus files (*.cpp | *.h)\0*.cpp;*.h\0All files (*.*)\0*.*\0";
			ofn.lpstrDefExt = "txt";
			//std::cout << "Hello" << std::endl;
			//std::cout << sizeof("Hello") << std::endl;
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

			if (GetOpenFileName(&ofn))
			{
				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				LoadTextFileToEdit(hEdit, szFileName, sz_title);
				bnChanged = FALSE;
				SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 0, (LPARAM)ofn.lpstrFile);
				std::cout << "Title before: " << sz_title << std::endl;
				SetFileDataToStatusBar(hwnd, szFileName, sz_title);
				std::cout << "Title after: " << sz_title << std::endl;
			}
		}
		break;
		case ID_FILE_SAVE:
		{
			if (strlen(szFileName))
				SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName, sz_title);
			else
				SendMessage(hwnd, WM_COMMAND, LOWORD(ID_FILE_SAVEAS), 0);
			SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 1, (LPARAM)"Ñîõðàíåí");
		}
		break;
		case ID_FILE_SAVEAS:
		{
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFilter = "Text files: (*.txt)\0*.txt\0C Plus Plus files (*.cpp | *.h)\0*.cpp;*.h\0All files: (*.*)\0*.*\0";
			//https://stackoverflow.com/questions/39130256/mfc-openfilename-structure-m-ofn-lpstrcustomfilter
			/*To specify multiple filter patterns for a single display string,
			use a semicolon to separate the patterns (for example, "*.TXT;*.DOC;*.BAK").*/
			ofn.lpstrDefExt = "txt";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			if (GetSaveFileName(&ofn))
			{
				SaveTextFileFromEdit(GetDlgItem(hwnd, IDC_EDIT), szFileName, sz_title);
				SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 0, (LPARAM)ofn.lpstrFile);

				sprintf(sz_title, "%s - %s", g_sz_WINDOW_CLASS, strrchr(szFileName, '\\') + 1);
				std::cout << sz_title << std::endl;
				SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
				SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 1, (LPARAM)"Ñîõðàíåí");
			}
		}
		break;
		/////////////////////////////////////////////////////////////////////
		case IDC_EDIT:
		{
			if (HIWORD(wParam) == EN_CHANGE)	//Doesn't work with MULTILINE & WM_SETTEXT simultanously.
			{
				bnChanged = TRUE;
				//std::cout << "File was changed" << std::endl;
				SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 1, (LPARAM)"Èçìåíåí");

				HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
				HWND hStatus = GetDlgItem(hwnd, IDC_STATUS);
				DWORD dwTextLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
				LPSTR lpstrBuffer = (LPSTR)GlobalAlloc(GPTR, dwTextLen + 1);
				SendMessage(hEdit, WM_GETTEXT, dwTextLen + 1, (LPARAM)lpstrBuffer);

				//https://legacy.cplusplus.com/reference/cstring/strtok/
				CHAR delimiters[] = " ,.!?;-()[]<>{}\"\':\\/\n";
				int i = 0;
				for (char* pch = strtok(lpstrBuffer, delimiters); pch; pch = strtok(NULL, delimiters))
				{
					std::cout << pch << "\t" << strlen(pch) << std::endl;
					i++;
				}
				CHAR sz_status[MAX_PATH]{};
				sprintf(sz_status, "%i %s", i, "ñëîâ");	SendMessage(hStatus, SB_SETTEXT, 2, (LPARAM)sz_status);
				sprintf(sz_status, "%s %i", "äëèíà: ", dwTextLen);	SendMessage(hStatus, SB_SETTEXT, 3, (LPARAM)sz_status);
				GlobalFree(lpstrBuffer);
			}
		}
		break;
		}
		break;
	case WM_DESTROY:
		FreeLibrary(comCtrl32);
		FreeLibrary(hRichEdit20);
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:	return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}
CHAR* FormatLastError()
{
	DWORD errorID = GetLastError();
	LPSTR lpszBuffer = NULL;
	DWORD dwSize = FormatMessage
	(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorID,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_RUSSIAN_RUSSIA),
		(LPSTR)&lpszBuffer,
		0,
		NULL
	);
	return lpszBuffer;
}

BOOL LoadTextFileToEdit(HWND hEdit, LPCSTR lpszFileName, CHAR sz_title[])
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		if (dwFileSize != UINT_MAX)
		{
			LPSTR lpszFileText = (LPSTR)GlobalAlloc(GPTR, dwFileSize + 1);
			if (lpszFileText)
			{
				DWORD dwRead = 0;
				if (ReadFile(hFile, lpszFileText, dwFileSize, &dwRead, NULL))
				{
					if (SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)lpszFileText))bSuccess = TRUE;
				}
				GlobalFree(lpszFileText);
			}
			CloseHandle(hFile);
		}
	}
	SetFileDataToStatusBar(GetParent(hEdit), lpszFileName, sz_title);
	return bSuccess;
}
BOOL SaveTextFileFromEdit(HWND hEdit, LPCSTR lpszFileName, CHAR sz_title[])
{
	BOOL bSuccess = FALSE;
	HANDLE hFile = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD dwTextLength = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
		if (dwTextLength)
		{
			LPSTR lpszText = (LPSTR)GlobalAlloc(GPTR, dwTextLength + 1);
			if (lpszText)
			{
				if (SendMessage(hEdit, WM_GETTEXT, dwTextLength + 1, (LPARAM)lpszText))
				{
					DWORD dwWritten;
					if (WriteFile(hFile, lpszText, dwTextLength, &dwWritten, NULL))bSuccess = TRUE;
				}
				GlobalFree(lpszText);
			}
		}
		CloseHandle(hFile);
	}
	SetFileDataToStatusBar(GetParent(hEdit), lpszFileName, sz_title);
	return bSuccess;
}

LPSTR FormatFileTime(FILETIME filetime, CONST CHAR sz_message[], CHAR sz_buffer[])
{
	//CHAR sz_buffer[MAX_PATH]{};
	ZeroMemory(sz_buffer, MAX_PATH);
	FILETIME localTime;
	ZeroMemory(&localTime, sizeof(localTime));
	FileTimeToLocalFileTime(&filetime, &localTime);
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(sysTime));
	FileTimeToSystemTime(&localTime, &sysTime);
	sprintf
	(
		sz_buffer,
		"%s:%02d.%02d.%02d %02d:%02d:%02d",
		sz_message,
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond
	);
	std::cout << sz_buffer << std::endl;
	return sz_buffer;
}

VOID SetFileDataToStatusBar(HWND hwnd, CONST CHAR szFileName[], CHAR sz_title[])
{
	//CHAR sz_title[MAX_PATH]{};
	sprintf(sz_title, "%s - %s", g_sz_WINDOW_CLASS, strrchr(szFileName, '\\') + 1);
	std::cout << sz_title << std::endl;
	SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);

	WIN32_FIND_DATA fileData;
	ZeroMemory(&fileData, sizeof(fileData));
	HANDLE hFile = FindFirstFile(szFileName, &fileData);
	std::cout << "\n==================================\n" << std::endl;
	std::cout << fileData.cFileName << "\t" << fileData.nFileSizeLow << "\t" << "\n";
	std::cout << "\n==================================\n" << std::endl;
	CHAR sz_buffer[MAX_PATH]{};
	sprintf(sz_buffer, "%i B", fileData.nFileSizeLow);
	SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 4, (LPARAM)sz_buffer);
	/*FILETIME localTime;
	ZeroMemory(&localTime, sizeof(localTime));
	FileTimeToLocalFileTime(&fileData.ftCreationTime, &localTime);
	SYSTEMTIME sysTime;
	ZeroMemory(&sysTime, sizeof(sysTime));
	FileTimeToSystemTime(&localTime, &sysTime);
	ZeroMemory(sz_buffer, MAX_PATH);
	sprintf
	(
		sz_buffer,
		"%s:%02d.%02d.%02d %02d:%02d:%02d",
		"Äàòà ñîçäàíèÿ: ",
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond
	);
	std::cout << sz_buffer << std::endl;*/
	SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 5,
		(LPARAM)FormatFileTime(fileData.ftCreationTime, "Äàòà ñîçäàíèÿ", sz_buffer));
	SendMessage(GetDlgItem(hwnd, IDC_STATUS), SB_SETTEXT, 6,
		(LPARAM)FormatFileTime(fileData.ftLastWriteTime, "Äàòà èçìåíåíèÿ", sz_buffer));

}