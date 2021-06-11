#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <math.h>
using namespace std;
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
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
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               CW_USEDEFAULT,       /* Windows decides the position */
               CW_USEDEFAULT,       /* where the window ends up on the screen */
               544,                 /* The programs width */
               375,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*Circle clipping: if point p is inside clipping circle (distance between p and circle center <= radius of clipping circle)*/

int cR; //the radius of the clipping circle
int CXC, CYC;  //center point of the clipping Circle
int option =0;
int R=0,G=0,B=0;
void isInsideClip(HDC hdc,int x, int y)
{
    int dist =sqrt(pow((x-CXC),2)+pow((y-CYC),2));
    if(dist <= cR )
    {
        SetPixel(hdc,x,y,RGB(1,1,255));
    }
    else

    {
        SetPixel(hdc,x,y,RGB(255,1,1));
    }
}
void drawLineDDA(HDC hdc, int x1,int yy, int x2, int y2)
{
    int dy = y2 - yy, dx = x2 - x1;
    isInsideClip(hdc,x1,yy);
    if(abs(dx) >= abs(dy))  // slope <= 1
    {
        int x = x1, xInc = (dx>0?1:-1);
        double y = yy, yInc = (double)dy/dx * xInc;
        while(x != x2)
        {
            x +=xInc, y+=yInc;
            isInsideClip(hdc,x,round(y));
        }

    }
    else
    {
        int y = yy, yInc = (dy>0?1:-1);
        double x = x1, xInc = (double)dx/dy * yInc;
        while(y != y2)
        {
            y +=yInc, x+=xInc;
            isInsideClip(hdc,round(x),y);
        }


    }

}
void Draw8Points(HDC hdc,int x,int y,int xc,int yc)
{
    if(option==4 || option == 0)
    {

        SetPixel(hdc,xc+x,yc+y,RGB(R,G,B));
        SetPixel(hdc,xc-x,yc+y,RGB(R,G,B));
        SetPixel(hdc,xc+x,yc-y,RGB(R,G,B));
        SetPixel(hdc,xc-x,yc-y,RGB(R,G,B));

        SetPixel(hdc,xc-y,yc+x,RGB(R,G,B));
        SetPixel(hdc,xc+y,yc-x,RGB(R,G,B));
        SetPixel(hdc,xc+y,yc+x,RGB(R,G,B));
        SetPixel(hdc,xc-y,yc-x,RGB(R,G,B));
    }
    else
    {
        isInsideClip(hdc,xc+x,yc+y);
        isInsideClip(hdc,xc-x,yc+y);
        isInsideClip(hdc,xc+x,yc-y);
        isInsideClip(hdc,xc-x,yc-y);

        isInsideClip(hdc,xc-y,yc+x);
        isInsideClip(hdc,xc+y,yc-x);
        isInsideClip(hdc,xc+y,yc+x);
        isInsideClip(hdc,xc-y,yc-x);
    }

}
void midpoint(HDC hdc,int xc,int yc,int r)
{
    int x=0;
    int y=r;
    double d=1-r;
    while(x<y)
    {
        if(d<=0)
        {
            d=d+2*x+3;
            x++;
        }
        else
        {
            d=d+2*(x-y)+5;
            x++;
            y--;
        }
        Draw8Points(hdc,x,y,xc,yc);
    }
}

void drawTwo(HDC hdc,int x,int y,int xc,int yc)
{
    isInsideClip(hdc,xc+x,yc+y);
    isInsideClip(hdc,xc-x,yc+y);

    isInsideClip(hdc,xc-y,yc+x);
    isInsideClip(hdc,xc+y,yc+x);



}
void midpointHalf(HDC hdc,int xc,int yc,int r)
{
    int x=0;
    int y=r;
    double d=1-r;
    while(x<y)
    {
        if(d<=0)
        {
            d=d+2*x+3;
            x++;
        }
        else
        {
            d=d+2*(x-y)+5;
            x++;
            y--;
        }
        drawTwo(hdc,x,y,xc,yc);
    }
}

/*  This function is called by the Windows function DispatchMessage()  */
int x1,x2,yy,y2;//line
int rr,x_c,y_c,x_2,y_2; //circle or half circle


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    HDC hdc =GetDC(hwnd);
    if(option==5)
    {
        PostQuitMessage (0);
        return 0;
    }
    switch (message)
    {
    case WM_LBUTTONDOWN:
        if(option == 0 || option ==4 ) //Clipping circle
        {
            x_c=LOWORD(lParam);
            y_c=HIWORD(lParam);

        }
        else if(option == 1) //Line
        {
            x1 = LOWORD(lParam);
            yy = HIWORD(lParam);

        }
        else if(option == 2) //Circle
        {
            x_c=LOWORD(lParam);
            y_c=HIWORD(lParam);
        }
        else if(option==3)  //curve
        {
            x_c=LOWORD(lParam);
            y_c=HIWORD(lParam);
        }
        break;
    //second coordination
    case WM_RBUTTONDOWN:
        if(option == 0 || option ==4 ) //Clipping circle
        {
            x_2=LOWORD(lParam);
            y_2=HIWORD(lParam);
            rr=sqrt(pow((x_2-x_c),2)+pow((y_2-y_c),2));
            cR = rr;
            CXC = x_c;
            CYC = y_c;
            midpoint(hdc,x_c,y_c,rr);

        }

        else if(option==1) //Line
        {

            x2 = LOWORD(lParam);
            y2 = HIWORD(lParam);
            drawLineDDA(hdc,x1,yy,x2,y2);
        }
        else if(option == 2)
        {
            x_2=LOWORD(lParam);
            y_2=HIWORD(lParam);
            rr=sqrt(pow((x_2-x_c),2)+pow((y_2-y_c),2));
            midpoint(hdc,x_c,y_c,rr);
        }
        else if(option==3)
        {
            x_2=LOWORD(lParam);
            y_2=HIWORD(lParam);
            rr=sqrt(pow((x_2-x_c),2)+pow((y_2-y_c),2));
            midpointHalf(hdc,x_c,y_c,rr);

        }
        cout<<"Please Enter the number of the shape to draw\n";
        cout<<"1) Line\n";
        cout<<"2) Circle\n";
        cout<<"3) curve\n";
        cout<<"4) New window\n";
        cout<<"5) Close\n";
        cin>>option;
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
