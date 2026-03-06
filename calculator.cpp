#include <windows.h>
#include <stdio.h>

HWND textF1, textF2;
char num1[100], num2[100], resultStr[100];

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = CreateSolidBrush(RGB(255, 182, 193)); // Pink background
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc)) return -1;

    CreateWindowW(L"myWindowClass", L"My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
                  100, 100, 250, 200, NULL, NULL, hInst, NULL);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        CreateWindowW(L"Static", L"Please input two numbers", WS_VISIBLE | WS_CHILD | SS_CENTER, 25, 10, 185, 20, hWnd, NULL, NULL, NULL);
        textF1 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 40, 135, 20, hWnd, NULL, NULL, NULL);
        textF2 = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 50, 70, 135, 20, hWnd, NULL, NULL, NULL);
       
        CreateWindowW(L"Button", L"+", WS_VISIBLE | WS_CHILD, 50, 110, 30, 25, hWnd, (HMENU)1, NULL, NULL);
        CreateWindowW(L"Button", L"-", WS_VISIBLE | WS_CHILD, 85, 110, 30, 25, hWnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"Button", L"*", WS_VISIBLE | WS_CHILD, 120, 110, 30, 25, hWnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"Button", L"/", WS_VISIBLE | WS_CHILD, 155, 110, 30, 25, hWnd, (HMENU)4, NULL, NULL);
        break;

    case WM_COMMAND:
        if (wp >= 1 && wp <= 4) {
            GetWindowText(textF1, num1, 100);
            GetWindowText(textF2, num2, 100);
            double a = atof(num1);
            double b = atof(num2);
            double res = 0;

            if (wp == 1) res = a + b;
            else if (wp == 2) res = a - b;
            else if (wp == 3) res = a * b;
            else if (wp == 4) res = (b != 0) ? a / b : 0;

            sprintf(resultStr, "%f", res);
            MessageBox(hWnd, resultStr, "Result", MB_OK);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}