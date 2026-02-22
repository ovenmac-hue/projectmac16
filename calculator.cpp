#include <windows.h>
#include <stdio.h>

HWND testfield, buttonplus, buttonminus, buttonmultiply, buttondivide , Input1, Input2;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE: {
			testfield = CreateWindowEx(WS_EX_CLIENTEDGE,"Static","Please input two numbers",WS_CHILD|WS_VISIBLE|WS_BORDER,
				30, /* x */
				20, /* y */
				180, /* width */
				20, /* height */
				hwnd,NULL,NULL,NULL);

			 Input1 = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,
				60, /* x */
				50, /* y */
				120, /* width */
				20, /* height */
				hwnd,NULL,NULL,NULL);
			 Input2 = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","",WS_CHILD|WS_VISIBLE|WS_BORDER,
				60, /* x */
				80, /* y */
				120, /* width */
				20, /* height */
				hwnd,NULL,NULL,NULL);

			buttonplus = CreateWindowEx(0,"BUTTON","+",WS_CHILD|WS_VISIBLE,
				20, /* x */
				110, /* y */
				40, /* width */
				40, /* height */
				hwnd,(HMENU)1,NULL,NULL);
			buttonminus = CreateWindowEx(0,"BUTTON","-",WS_CHILD|WS_VISIBLE,
				70, /* x */
				110, /* y */
				40, /* width */
				40, /* height */
				hwnd,(HMENU)2,NULL,NULL);
			buttonmultiply = CreateWindowEx(0,"BUTTON","*",WS_CHILD|WS_VISIBLE,
				120, /* x */
				110, /* y */
				40, /* width */
				40, /* height */
				hwnd,(HMENU)3,NULL,NULL);
			buttondivide = CreateWindowEx(0,"BUTTON","/",WS_CHILD|WS_VISIBLE,
				170, /* x */
				110, /* y */
				40, /* width */
				40, /* height */
				hwnd,(HMENU)4,NULL,NULL);
			
			break;
		}

		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case 1: {
					char buffer1[256], buffer2[256];
					GetWindowText(Input1, buffer1, 256);
					GetWindowText(Input2, buffer2, 256);
					double num1 = atof(buffer1);
					double num2 = atof(buffer2);
					double result = num1 + num2;
					char resultBuffer[256];
					sprintf(resultBuffer, "Result: %f", result);
					SetWindowText(testfield, resultBuffer);
					break;
				}
				case 2: {
					char buffer1[256], buffer2[256];
					GetWindowText(Input1, buffer1, 256);
					GetWindowText(Input2, buffer2, 256);
					double num1 = atof(buffer1);
					double num2 = atof(buffer2);
					double result = num1 - num2;
					char resultBuffer[256];
					sprintf(resultBuffer, "Result: %f", result);
					SetWindowText(testfield, resultBuffer);
					break;
				}
				case 3: {
					char buffer1[256], buffer2[256];
					GetWindowText(Input1, buffer1, 256);
					GetWindowText(Input2, buffer2, 256);
					double num1 = atof(buffer1);
					double num2 = atof(buffer2);
					double result = num1 * num2;
					char resultBuffer[256];
					sprintf(resultBuffer, "Result: %f", result);
					SetWindowText(testfield, resultBuffer);
					break;
				}
				case 4: {
					char buffer1[256], buffer2[256];
					GetWindowText(Input1, buffer1, 256);
					GetWindowText(Input2, buffer2, 256);
					double num1 = atof(buffer1);
					double num2 = atof(buffer2);
					if (num2 != 0) {
						double result = num1 / num2;
						char resultBuffer[256];
						sprintf(resultBuffer, "Result: %f", result);
						SetWindowText(testfield, resultBuffer);
						break;
					} else {
						SetWindowText(testfield, "Error: Division by zero");
						break;
					}
				}
			} 
			break;
		}	

		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_HOTLIGHT +1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
