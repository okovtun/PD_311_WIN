#include<Windows.h>

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
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
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
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Закпуск цикла сообщений:



	return 0;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}