#include<Windows.h>
#include"resource.h"

//#define TEXT_ELEMENTS
#ifdef TEXT_ELEMENTS
#define IDC_STATIC_TEXT		1000
#define IDC_EDIT			1001
#define IDC_BUTTON			1002  
#endif // TEXT_ELEMENTS

#define IDC_STATIC	1000
#define IDC_COMBO	1001
#define IDC_BUTTON	1002

/*
System Classes:
	"Button", "Edit", "ComboBox", "ListBox", "Static", "MDIClient" (Multi-Document Interface)
	"Button": WS_PUSHBUTTON, WS_CHECKBOX, WS_RADIOBUTTON.......
Все классы окон должны быть загистрированы в ОС;
Класс окна - это самая обычная строка (NULL-Terminated Line);
*/

CONST CHAR g_sz_WINDOW_CLASS[] = "My first Window";	//имя нашего класса окна

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//////////////////////////////////////////////////////////////////////////////////
	//////////////				I) Регистрация класса окна:				//////////////
	//////////////////////////////////////////////////////////////////////////////////
	WNDCLASSEX wc;	//создаем экземпляр (объект) структуры, описывающей класс окна
	ZeroMemory(&wc, sizeof(wc));	//обнуляем этот экземпляр (объект)

	//			Инициализируем поля объекта:

	//1.1) Размеры:
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;

	//1.2) Внешний вид:
	wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "shell.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = (HCURSOR)LoadImage(hInstance, "starcraft-original\\Background.ani", IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//1.3) Основные параметры класса:
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;	//Указатель на процедуру окна
	wc.hInstance = hInstance;	//Дескриптор приложения (запущеный экзмемпляр *.exe-файла нашего приложения)

	//Класс окна создан, теперь нужно зарегистрировать его в операционной системе:
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	HWND hwnd = CreateWindowEx
	(
		NULL,				//dwExStyle	- расширенные стили
		g_sz_WINDOW_CLASS,	//Window class - класс окна
		g_sz_WINDOW_CLASS,	//Window title - заголовок окна
		WS_OVERLAPPEDWINDOW,//WS_ - Window Style. WS_OVERLAPPEDWINDOW - это стиль главного окна, которое будет родителес для других окон
		CW_USEDEFAULT, CW_USEDEFAULT, //Позиция окна
		CW_USEDEFAULT, CW_USEDEFAULT, //Размер окна
		NULL,		//Родительское окно
		NULL,		//Для главного окна (WS_OVERLAPPEDWINDOW) - это hMenu (Строка меню - ряд кнопок под строкой заголовка: Файл, Правка, Вид Вставка.....)
					//Для дочернего окна - это его ID_, по которому его можно найти при помощи функции GetDlgItem();
		hInstance,
		NULL
	);
	//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задает режим отображения окна: Свернуто в окно, размернуто ра весь экран, свернуто в панель задач
	//https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow

	UpdateWindow(hwnd);			//

	//3) Запуск цикла сообщений:

	MSG msg;
	while (GetMessage(&msg, 0, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}



INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
#ifdef TEXT_ELEMENTS
		HWND hStatic = CreateWindowEx
		(
			NULL,		//EX_STYLE
			"Static",	//WindowClass
			"This is static text",	//WindowName - WindowTitle
			WS_CHILDWINDOW | WS_VISIBLE,	//Style
			100, 10,	//Position
			200, 20,	//Dimensions
			hwnd,		//Parent Window
			(HMENU)IDC_STATIC_TEXT,//ResourceID
			NULL,	//GetModuleHandle(NULL)	если оставить 'NULL', то возтмет 'hInstance' родительского окна
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL, "Edit", "Введите текст",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_CENTER,
			100, 30,
			200, 20,
			hwnd,
			(HMENU)IDC_EDIT,
			NULL,
			NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			200, 55,
			100, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			NULL,
			NULL
		);
#endif // TEXT_ELEMENTS

		HWND hStatic = CreateWindowEx(
			NULL, "Static", "Выберите указатель мыши:",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			200, 20,
			hwnd,
			(HMENU)IDC_STATIC,
			NULL,
			NULL
		);
		HWND hCombo = CreateWindowEx(
			NULL, "ComboBox", "",
			WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
			10, 25,
			200, 200,
			hwnd,
			(HMENU)IDC_COMBO,
			NULL,
			NULL
		);
		HWND hButton = CreateWindowEx(
			NULL, "Button", "Применить",
			WS_CHILD | WS_VISIBLE,
			110, 50,
			100, 28,
			hwnd,
			(HMENU)IDC_BUTTON,
			NULL,
			NULL
		);

		CHAR sz_current_dir[MAX_PATH]{};
		SetCurrentDirectory("starcraft-original");
		GetCurrentDirectory(MAX_PATH, sz_current_dir);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_current_dir);

		WIN32_FIND_DATA file_data;
		ZeroMemory(&file_data, sizeof(file_data));
		HANDLE hFile = FindFirstFile("*", &file_data);
		for (; FindNextFile(hFile, &file_data);)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)file_data.cFileName);
		}
		FindClose(hFile);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
#ifdef TEXT_ELEMENTS
		case IDC_BUTTON:
		{
			HWND hStaticText = GetDlgItem(hwnd, IDC_STATIC_TEXT);
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hStaticText, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
#endif // TEXT_
		case IDC_BUTTON:
		{
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO);
			int i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			CHAR sz_selected_cursor[_MAX_FNAME]{};
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)sz_selected_cursor);
			HCURSOR hCursor = (HCURSOR)LoadImage(NULL, sz_selected_cursor, IMAGE_CURSOR, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
			SetCursorPos(300, 300);
			SendMessage(hwnd, WM_SETCURSOR, 0, (LPARAM)sz_selected_cursor);
			//SetCursor(hCursor);
			return FALSE;//https://stackoverflow.com/questions/19257237/reset-cursor-in-wm-setcursor-handler-properly
		}
			break;
		}
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		/*switch (MessageBox(hwnd, "Вы действительно хотите закрыть окно,", "Че, серьезно?", MB_YESNO | MB_ICONQUESTION))
		{
		case IDYES:
			MessageBox(hwnd, "Лучше двери закройте", "Info", MB_OK | MB_ICONINFORMATION);
			DestroyWindow(hwnd);
		case IDNO:break;
		}*/
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}