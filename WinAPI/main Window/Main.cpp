#include <Windows.h>


CONST CHAR g_sz_WINDOW_CLASS[] = "My First Window";//name classes my window

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)rgistr window
	WNDCLASSEX wc;//создаем экземпляр(объект) структуры, описывающей класс окна
	ZeroMemory(&wc, sizeof(wc));// обнуляем этот экземпляр(объект)
	//1.инициализируем поля объекта:
	// 1.1 размеры
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	//1.2 Внешний вид
	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico",IMAGE_ICON,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "shell.ico",IMAGE_ICON,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hCursor =(HCURSOR) LoadImage(hInstance, "cursor\\Background.ani",IMAGE_CURSOR,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//1.3 Основные Параметры класса 
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;//Указатель на процедуру окна
	wc.hInstance = hInstance;//дискриптор приложения(экземпляр)запущенный*ехе-файла приложения
	//Класс окна создан и проинициализирован, теперь нужно его зарегистрировать в ОС
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Clascc registarion failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	// 2)create window
	HWND hwnd = CreateWindowEx
	(
		NULL,                     //dwExStyle(расширенные стили) 
		g_sz_WINDOW_CLASS,        //window class(класс окна)
		g_sz_WINDOW_CLASS,        //window title(заголовок)
		WS_OVERLAPPEDWINDOW,      //WS_-Window Style. WS_OVERLAPPEDWINDOW -стиль главного окна, который будет родителем для других окон
		CW_USEDEFAULT, CW_USEDEFAULT,     //Позиция окна х у
		CW_USEDEFAULT, CW_USEDEFAULT,      //размер окна
		NULL,          //Родительское окно
		NULL,          //Для главного окна(WS_OVERLAPPEDWINDOW) -это hMenu(Строка меню)
					   // Для дочернего окна-это его ID_,по которому его можно найти с помощью функции GetDlgIte,();
		hInstance,
		NULL
	);
	
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windiow Creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//задает режим отображения окна: свернуто в окно, развернуто на весь экран
	UpdateWindow(hwnd);// 
	//3 Запуск цикла сообщений
	MSG msg;
	while (GetMessage(&msg,0,0,0)>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

INT  CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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