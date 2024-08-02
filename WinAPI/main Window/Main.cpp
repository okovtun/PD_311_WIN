#include <Windows.h>


CONST CHAR g_sz_WINDOW_CLASS[] = "My First Window";//name classes my window

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1)rgistr window
	WNDCLASSEX wc;//������� ���������(������) ���������, ����������� ����� ����
	ZeroMemory(&wc, sizeof(wc));// �������� ���� ���������(������)
	//1.�������������� ���� �������:
	// 1.1 �������
	wc.style = 0;
	wc.cbSize = sizeof(wc);
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	//1.2 ������� ���
	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIcon = (HICON)LoadImage(hInstance, "palm.ico",IMAGE_ICON,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hIconSm = (HICON)LoadImage(hInstance, "shell.ico",IMAGE_ICON,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hCursor =(HCURSOR) LoadImage(hInstance, "cursor\\Background.ani",IMAGE_CURSOR,LR_DEFAULTSIZE, LR_DEFAULTSIZE,LR_LOADFROMFILE);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;

	//1.3 �������� ��������� ������ 
	wc.lpszClassName = g_sz_WINDOW_CLASS;
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = (WNDPROC)WndProc;//��������� �� ��������� ����
	wc.hInstance = hInstance;//���������� ����������(���������)����������*���-����� ����������
	//����� ���� ������ � ������������������, ������ ����� ��� ���������������� � ��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Clascc registarion failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	// 2)create window
	HWND hwnd = CreateWindowEx
	(
		NULL,                     //dwExStyle(����������� �����) 
		g_sz_WINDOW_CLASS,        //window class(����� ����)
		g_sz_WINDOW_CLASS,        //window title(���������)
		WS_OVERLAPPEDWINDOW,      //WS_-Window Style. WS_OVERLAPPEDWINDOW -����� �������� ����, ������� ����� ��������� ��� ������ ����
		CW_USEDEFAULT, CW_USEDEFAULT,     //������� ���� � �
		CW_USEDEFAULT, CW_USEDEFAULT,      //������ ����
		NULL,          //������������ ����
		NULL,          //��� �������� ����(WS_OVERLAPPEDWINDOW) -��� hMenu(������ ����)
					   // ��� ��������� ����-��� ��� ID_,�� �������� ��� ����� ����� � ������� ������� GetDlgIte,();
		hInstance,
		NULL
	);
	
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windiow Creation failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);//������ ����� ����������� ����: �������� � ����, ���������� �� ���� �����
	UpdateWindow(hwnd);// 
	//3 ������ ����� ���������
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