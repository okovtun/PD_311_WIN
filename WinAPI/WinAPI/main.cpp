#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//HIWORD - старшее слово
//LOWORD - младшее слово

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//hInstance - это *.exe-модуль нашей программы
	//hPrevInst - этот параметр использовался в комбинированном коде IA-16/IA-32 (Win98)
	//			  на сегодня не актуален.
	//lpCmdLine - LongPointer to Command prompt, эта командная строка передается в функцию WinMain при запуске программы.
	//			  lpCmdLine представляет собой массив строк, нулевым элементом которого всегда является полный путь к *.exe-файлу.

	/*MessageBox(NULL, "HelloWorld!\nЭто окно сообщения, детка", "Hello WinAPI", MB_ABORTRETRYIGNORE | MB_ICONSTOP | MB_DEFBUTTON3 | MB_HELP | MB_TOPMOST);
	std::cout << typeid(char).name() << std::endl;
	std::cout << typeid(wchar_t).name() << std::endl;
	WndProc*/

	int a = 2;
	{
		int a = 3;
	}

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//hwnd - Handler to Window (дескриптор окна)
	switch (uMsg)
	{
		//WM_ - Windows Message
	case WM_INITDIALOG:	//Отрабатывает только один раз, при создании окна
		//H - Handler (обработчик, дескриптор)
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON_BTC));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
	}
	break;
	case WM_COMMAND:	//Здесь обраьатываются нажатия на кнопки, ввод текста, и любые изменения состояния окна.
		switch (LOWORD(wParam))
		{
		case IDOK:		MessageBox(hwnd, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONINFORMATION); break;
		case IDCANCEL:	EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:		//Отрабатывает при нажатии на кнопку X (Закрыть)
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}