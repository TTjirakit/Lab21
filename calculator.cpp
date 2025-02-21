#include <windows.h>
#include <stdio.h>

HWND hEdit1, hEdit2, hButtonAdd, hButtonSub, hButtonMul, hButtonDiv;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
        case WM_CREATE: {
            CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 10, 200, 20, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 50, 40, 150, 20, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 50, 70, 150, 20, hwnd, NULL, NULL, NULL);
            
            hButtonAdd = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 50, 100, 30, 30, hwnd, (HMENU) 1, NULL, NULL);
            hButtonSub = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 90, 100, 30, 30, hwnd, (HMENU) 2, NULL, NULL);
            hButtonMul = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 100, 30, 30, hwnd, (HMENU) 3, NULL, NULL);
            hButtonDiv = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 170, 100, 30, 30, hwnd, (HMENU) 4, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
                char text1[100], text2[100];
                GetWindowText(hEdit1, text1, 100);
                GetWindowText(hEdit2, text2, 100);
                double num1 = atof(text1);
                double num2 = atof(text2);
                double result = 0;
                char resultText[100];
                
                switch(LOWORD(wParam)) {
                    case 1: result = num1 + num2; break;
                    case 2: result = num1 - num2; break;
                    case 3: result = num1 * num2; break;
                    case 4: 
                        if (num2 == 0) {
                            MessageBox(hwnd, "Cannot divide by zero", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2; 
                        break;
                }
                
                sprintf(resultText, "%f", result);
                MessageBox(hwnd, resultText, "Result", MB_OK);
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
	wc.hbrBackground = CreateSolidBrush(RGB(250, 192, 0)); 
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(0,"WindowClass","My Calculator",WS_VISIBLE|WS_OVERLAPPED|WS_SYSMENU,
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