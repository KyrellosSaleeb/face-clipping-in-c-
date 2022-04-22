/* 
First 2 clicks To draw circle window 
1) click single left button down to determine center of circle window
2) click single left button down to determine any point on circle window

To draw firse small circle (right eye) witn 2 clicks
3) click single right button down to determine center of first small circle
4) click single right button down to determine any point on first small circle

To draw second small circle (left eye) witn 2 clicks
5) click single right button down to determine center of second small circle
6) click single right button down to determine any point on second small circle

To draw curve with 4 clicks 
7) click single right button down to determine point 1 of bezeir curve
8) click single right button down to determine point 2 of bezeir curve
9) click single right button down to determine point 3 of bezeir curve
10) click single right button down to determine point 4 of bezeir curve

To draw line 1 witn 2 clicks
11) click single right button down to determine start point of first line
12) click single right button down to determine end point of first line

To draw line 2 witn 2 clicks
13) click single right button down to determine start point of second line
14) click single right button down to determine end point of second line

To draw line 3 witn 2 clicks
15) click single right button down to determine start point of third line
16) click single right button down to determine end point of third line
*/

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <iostream>
#include <tchar.h>
#include <windows.h>
#include <math.h>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

/**********************************************************************************************************************************************/
#define  RED RGB(255,0,0)
#define BLUE RGB(0,0,255)

//global variables
static int choice = 0;
int p;
static int xc1 = 0, yc1 = 0;
int x, y, x2, y2;
int R1, R2;
static int n = 0;
int x_0, sx_0, x_1, sx_1, y_0, sy_0, y_1, sy_1;

/**********************************************************************************************************************************************/
//clipping circle (responsible for color of shape inside and outside circle window)
bool Clipping(int x, int y, int R, int point_x, int point_y)
{
    p = sqrt(pow(x - point_x, 2.0) + pow(y - point_y, 2.0));

    if (p <= R)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**********************************************************************************************************************************************/
int Round(double x)
{
    return (int)(x + 0.5);
}

/**********************************************************************************************************************************************/
//draw circle window 
void draw8Points(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    SetPixel(hdc, xc + x, yc + y, color);
    SetPixel(hdc, xc - x, yc + y, color);
    SetPixel(hdc, xc - x, yc - y, color);
    SetPixel(hdc, xc + x, yc - y, color);
    SetPixel(hdc, xc + y, yc + x, color);
    SetPixel(hdc, xc - y, yc + x, color);
    SetPixel(hdc, xc - y, yc - x, color);
    SetPixel(hdc, xc + y, yc - x, color);
}
//polar circle algorithm
void draw_Circle_window(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    double x = R, y = 0;
    double theta = 0, dtheta = 1.0 / R;
    draw8Points(hdc, xc, yc, R, 0, color);
    while (x > y)
    {
        theta += dtheta;
        x = R * cos(theta);
        y = R * sin(theta);
        draw8Points(hdc, xc, yc, Round(x), Round(y), color);
    }
}

/**********************************************************************************************************************************************/
//draw line (hair) 
void draw_Parametric_line(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    for (double t = 0; t < 1; t += 0.001)
    {
        int point_x = x1 + (t * dx);
        int point_y = y1 + (t * dy);
        bool flag = Clipping(xc1, yc1, R1, point_x, point_y);
        if (flag == true)
        {
            SetPixel(hdc, point_x, point_y, RGB(0, 0, 255));
        }
        else
        {
            SetPixel(hdc, point_x, point_y, RGB(255, 0, 0));
        }
    }
}

/**********************************************************************************************************************************************/
//draw circle (eye)
void draw8Points2(HDC hdc, int xc, int yc, int x, int y, COLORREF color)
{
    bool flag1 = Clipping(xc1, yc1, R1, xc + x, yc + y);
    if (flag1 == true)
    {
        SetPixel(hdc, xc + x, yc + y, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc + x, yc + y, RGB(255, 0, 0));
    }

    bool flag2 = Clipping(xc1, yc1, R1, xc - x, yc + y);
    if (flag2 == true)
    {
        SetPixel(hdc, xc - x, yc + y, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc - x, yc + y, RGB(255, 0, 0));
    }

    bool flag3 = Clipping(xc1, yc1, R1, xc - x, yc - y);
    if (flag3 == true)
    {
        SetPixel(hdc, xc - x, yc - y, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc - x, yc - y, RGB(255, 0, 0));
    }

    bool flag4 = Clipping(xc1, yc1, R1, xc + x, yc - y);
    if (flag4 == true)
    {
        SetPixel(hdc, xc + x, yc - y, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc + x, yc - y, RGB(255, 0, 0));
    }

    bool flag5 = Clipping(xc1, yc1, R1, xc + y, yc + x);
    if (flag5 == true)
    {
        SetPixel(hdc, xc + y, yc + x, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc + y, yc + x, RGB(255, 0, 0));
    }

    bool flag6 = Clipping(xc1, yc1, R1, xc + y, yc - x);
    if (flag6 == true)
    {
        SetPixel(hdc, xc + y, yc - x, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc + y, yc - x, RGB(255, 0, 0));
    }

    bool flag7 = Clipping(xc1, yc1, R1, xc - y, yc - x);
    if (flag7 == true)
    {
        SetPixel(hdc, xc - y, yc - x, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc - y, yc - x, RGB(255, 0, 0));
    }

    bool flag8 = Clipping(xc1, yc1, R1, xc - y, yc + x);
    if (flag8 == true)
    {
        SetPixel(hdc, xc - y, yc + x, RGB(0, 0, 255));
    }
    else
    {
        SetPixel(hdc, xc - y, yc + x, RGB(255, 0, 0));
    }
}

void draw_small_Circles(HDC hdc, int xc, int yc, int R, COLORREF color)
{
    double x = R, y = 0;
    double theta = 0;
    double dtheta = 1.0 / R;
    draw8Points2(hdc, xc, yc, R, 0, color);
    while (x > y)
    {
        theta += dtheta;
        x = R * cos(theta);
        y = R * sin(theta);
        draw8Points2(hdc, xc, yc, Round(x), Round(y), color);
    }
}

/***********************************************************************************************************************************************/
//draw curve with 4 clicks by bezier algorithm
void draw_curve(HDC hdc, int x_0, int sx_0, int x_1, int sx_1, int y_0, int sy_0, int y_1, int sy_1)
{
    int x[4] = { x_0,sx_0,x_1,sx_1 };
    int y[4] = { y_0,sy_0,y_1,sy_1 };
    double t;
    for (t = 0.0; t < 1.0; t += 0.001)
    {
        double put_x = (pow(1 - t, 3) * x[0]) + (3 * t * pow(1 - t, 2) * x[1]) + (3 * t * t * (1 - t) * x[2]) + (pow(t, 3) * x[3]);
        double put_y = (pow(1 - t, 3) * y[0]) + (3 * t * pow(1 - t, 2) * y[1]) + (3 * t * t * (1 - t) * y[2]) + (pow(t, 3) * y[3]);
        
        bool flag1 = Clipping(xc1, yc1, R1, Round(put_x), Round(put_y));
        if (flag1 == true)
        {
            SetPixel(hdc, Round(put_x), Round(put_y), RGB(0, 0, 255));
        }
        else
        {
            SetPixel(hdc, Round(put_x) , Round(put_y), RGB(255, 0, 0));
        }
    }
}

/**********************************************************************************************************************************************/

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Code::Blocks Template Windows App"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        900,                 /* The programs width */
        500,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );
    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    hdc = GetDC(hwnd);

    switch (message)                  /* handle the messages */
    {
    label:
    case WM_LBUTTONDOWN:
        if (n == 0)
        {
            xc1 = LOWORD(lParam);
            yc1 = HIWORD(lParam);
            n++;
        }
        else if (n == 1)
        {
            R1 = (int)sqrt(pow(LOWORD(lParam) - xc1, 2.0) + pow(HIWORD(lParam) - yc1, 2.0));
            draw_Circle_window(hdc, xc1, yc1, R1, RGB(0, 0, 0));
            choice = 1;
            n = 0;
        }
        break;

    case WM_RBUTTONDOWN:
        switch (choice)
        {
        case 1:
            if (n == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                n++;
            }
            else if (n == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                R2 = (int)sqrt(pow(x2 - x, 2.0) + pow(y2 - y, 2.0));
                draw_small_Circles(hdc, x, y, R2, RGB(0, 0, 0));
                choice = 2;
                n = 0;
            }
            break;

        case 2:
            if (n == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                n++;
            }
            else if (n == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                R2 = (int)sqrt(pow(x2 - x, 2.0) + pow(y2 - y, 2.0));
                draw_small_Circles(hdc, x, y, R2, RGB(0, 0, 0));
                choice = 3;
                n = 0;
            }
            break;

        case 3:
            if (n == 0) {
                x_0 = LOWORD(lParam);
                y_0 = HIWORD(lParam);
                n++;
            }
            else if (n == 1) {
                sx_0 = LOWORD(lParam);
                sy_0 = HIWORD(lParam);
                n++;
            }
            else if (n == 2) {
                x_1 = LOWORD(lParam);
                y_1 = HIWORD(lParam);
                n++;
            }
            else if (n == 3) {
                sx_1 = LOWORD(lParam);
                sy_1 = HIWORD(lParam);
                draw_curve(hdc, x_0, sx_0, x_1, sx_1, y_0, sy_0, y_1, sy_1);
                choice = 4;
                n = 0;
            }
            break;
            
        case 4:
            if (n == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                n++;
            }
            else if (n == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                draw_Parametric_line(hdc, x, y, x2, y2, RGB(0, 0, 0));
                choice = 5;
                n = 0;
            }
            break;

        case 5:
            if (n == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                n++;
            }
            else if (n == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                draw_Parametric_line(hdc, x, y, x2, y2, RGB(0, 0, 0));
                choice = 6;
                n = 0;
            }
            break;

        case 6:
            if (n == 0)
            {
                x = LOWORD(lParam);
                y = HIWORD(lParam);
                n++;
            }
            else if (n == 1)
            {
                x2 = LOWORD(lParam);
                y2 = HIWORD(lParam);
                draw_Parametric_line(hdc, x, y, x2, y2, RGB(0, 0, 0));
                choice = 7;
                n = 0;
            }
            break;

        case 7:
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;

    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);

    }
    return 0;
}
