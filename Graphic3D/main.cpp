#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <tchar.h>

#include "Math/Vec4.hpp"
#include "Math/Mat4.hpp"
#include "Graphic3D/Graphic3D.h"

using namespace std;

void PrintVector(const Vec4f& vec)
{
    cout << "Vec4(" << vec.x() << ", " << vec.y() << ", " << vec.z() << ", " << vec.w() << ")";
}

void PrintMatrix(const Mat4f& mat)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << setw(4) << mat[i][j];
        }

        cout << endl;
    }
}

void InputMatrix(Mat4f& mat)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << "mat[" << i << "][" << j << "] = ";
            cin >> mat[i][j];
            cin.get();
        }
    }
}

#define CLASS_NAME TEXT("__graph_3d__")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;
    }

    return FALSE;
}

int main(int argc, char *argv[])
{
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;

    wcex.cbClsExtra = 0;
    wcex.cbSize = sizeof(wcex);
    wcex.cbWndExtra = 0;
    wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.lpfnWndProc = WndProc;
    wcex.lpszClassName = CLASS_NAME;
    wcex.lpszMenuName = NULL;
    wcex.style = CS_DBLCLKS;

    RegisterClassEx(&wcex);
    hWnd = CreateWindowEx(NULL, CLASS_NAME, TEXT("Graphic3D"),
        WS_OVERLAPPEDWINDOW &~WS_SIZEBOX &~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
        640, 480, NULL, NULL, GetModuleHandle(NULL), NULL);
    ShowWindow(hWnd, SW_SHOW);

    Graphic3D graph(hWnd);

    graph.vertices(DrawType::LINE_STRIP, {
        Vec4f(-1, 1, 1, 1),
        Vec4f( 1, 1, 1, 1),
        Vec4f( 1, -1, 1, 1),
        Vec4f(-1, -1, 1, 1)
    });

    DWORD fps = 100;
    DWORD t_interval = 1000 / fps;
    DWORD t_now, t_last = GetTickCount();
    DWORD t_delta, t_begin = GetTickCount();
    DWORD frame = 0;
    float seconds;
    TCHAR title[100];

    while (true) {
        PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
        if (msg.message == WM_QUIT) {
            break;
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            t_now = GetTickCount();
            t_delta = t_now - t_last;

            if (t_delta >= t_interval) {
                frame++;
                seconds = (t_now - t_begin) / 1000.0f;
                t_last = t_now - (t_delta % t_interval);

                graph.update(t_delta / 1000.0f);
                graph.render();

                _stprintf_s(title, TEXT("Graphic3D - %f FPS"), float(frame) / seconds);
                SetWindowText(hWnd, title);
            }
        }
    }

    return 0;
}