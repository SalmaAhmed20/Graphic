#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include "Windows.h"
#include <tchar.h>
#include <windows.h>
#include "lines.h"
#include "menuh.h"
#include "Circle.h"
#include "ellipse.h"
#include "Filling.h"
#include<vector>
#include "fstream"
#include "clipping.h"


/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

struct Shape
{
    string Algorithms;
    int x_c,y_c,x2,y2,x3,y3,x4,y4;
    int r,g,b;
};
HINSTANCE hinst ;
int id;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
int WINAPI WinMain (HINSTANCE hThisInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow)
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
    // wincl.hCursor = LoadCursor (hinst, IDC_ARROW);
    wincl.hCursor = LoadCursor (NULL,IDC_HAND );
    wincl.lpszMenuName = MAKEINTRESOURCE(ID);                 /* No menu */
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
               600,                 /* The programs width */
               600,                 /* and height in pixels */
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

bool lparam,lInt,lmidpoint
,circle_direct,cpolar,cpolarIterative,circle_midpoint1,circle_midpoint2
,ellipse_direct,ellipse_polar
,Q1,Q2,Q3,Q4
,save,load,exitt
,clippingP,clippingL
, red=false,blue=false,green=false
,bckgrnd,cursor;
int x_c,y_c,x2,y2,x3,y3,x4,y4,rr;
COLORREF rgb=RGB(0,0,0);
int numOfPoints=0;
vector<Shape>shapes;
void Operation()
{
    //line
    lparam=false,lInt=false,lmidpoint=false;
    //circle
    circle_direct  = false,  cpolar = false,cpolarIterative=false,circle_midpoint1=false,circle_midpoint2=false;
    //Ellipse
    ellipse_direct=false,ellipse_polar=false;
    //filling
    Q1 = false,Q2=false,Q3=false,Q4=false;
    //File
    save = false, load = false, exitt = false;
    //Clipping
    clippingP = false,clippingL = false;
    //Windows
    bckgrnd =false,cursor=false;
}
void SaveFile()
{
    ofstream Save;
    Save.open ("Save.txt");
    for(int i = 0; i <shapes.size(); i++)
    {
        Save << shapes[i].Algorithms;
        Save << " ";
        Save << shapes[i].x_c;
        Save << " ";
        Save << shapes[i].y_c;
        Save << " ";
        Save << shapes[i].x2;
        Save << " ";
        Save << shapes[i].y2;
        Save << " ";
        Save << shapes[i].r;
        Save << " ";
        Save << shapes[i].g;
        Save << " ";
        Save << shapes[i].b;
        Save << " ";
    }
    Save.close();
}
void draw(Shape s, HWND hwnd)
{
    HDC hdc = GetDC(hwnd);
    if (s.Algorithms =="Parametricline" )
        Parametricline(hdc,s.x_c,s.y_c,s.x2,s.y2,RGB(s.r,s.g,s.b));
    else if (s.Algorithms =="LineDDA" )
        LineDDA(hdc,s.x_c,s.y_c,s.x2,s.y2,RGB(s.r,s.g,s.b));
    else if (s.Algorithms =="LineMidPoint" )
        LineMidPoint(hdc,s.x_c,s.y_c,s.x2,s.y2,RGB(s.r,s.g,s.b));
    else if (s.Algorithms =="midpoint" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        midpoint(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="CircleDirect" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        CircleDirect(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="CirclePolar" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        CirclePolar(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="CircleIterativePolar" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        CircleIterativePolar(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="modified_midpoint" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        modified_midpoint(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="Filling_Quarter_1" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        Filling_Quarter_1(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="Filling_Quarter_2" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        Filling_Quarter_2(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms=="Filling_Quarter_3" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        Filling_Quarter_3(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="Filling_Quarter_4" )
    {
        int rr=sqrt(pow((s.x2-s.x_c),2)+pow((s.y2-s.y_c),2));
        Filling_Quarter_4(hdc,s.x_c,s.y_c,rr,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="EllipsDirect" )
    {
        EllipsDirect(hdc,s.x_c,s.y_c,s.x2,s.y2,RGB(s.r,s.g,s.b));
    }
    else if (s.Algorithms =="EllipsPolar" )
    {

        EllipsPolar(hdc,s.x_c,s.y_c,s.x2,s.y2,RGB(s.r,s.g,s.b));
    }
}
void loadddd(HWND hwnd)
{
    vector<Shape> shhape2;
    ifstream fn("Save.txt");
    if (!fn.is_open())
    {
        cout << "File Doesn't Exist"<<endl;
    }
    else
    {
        while (!fn.eof())
        {
            Shape s;
            fn >> s.Algorithms;
            if(fn.eof())
                break;
            fn >> s.x_c;
            fn >> s.y_c;
            fn >> s.x2;
            fn >> s.y2;
            fn >> s.r;
            fn >> s.g;
            fn >> s.b;
            shhape2.push_back(s);
            shapes.push_back(s);

        }
        fn.close();
        for(int i =0; i<shhape2.size(); i++)
            draw(shhape2[i],hwnd);

    }
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {

    case WM_COMMAND:
        id = LOWORD(wParam);
        switch (id)
        {
        case ID_SAVE :
            Operation();
            save=true;
            SaveFile();
            break;
        case ID_FILE_LOAD:
            Operation();
            load = true;
            loadddd(hwnd);
            break;
        case ID_EXIT :
            exit(0);
            break;
        case ID_DDA:
            Operation();
            lInt = true;
            break;
        case ID_LMID:
            Operation();
            lmidpoint=true;
            break;
        case ID_LPARA:
            Operation();
            lparam=true;
            break;
        ////-----------------
        case ID_DIRCT:
            Operation();
            circle_direct=true;
            break;
        case ID_POLAR:
            Operation();
            cpolar=true;
            break;
        case ID_ITPOLAR:
            Operation();
            cpolarIterative=true;
            break;
        case ID_CMID:
            Operation();
            circle_midpoint1=true;
            break;
        case ID_MCMID:
            Operation();
            circle_midpoint2=true;
            break;
        /////-------
        case ID_ELLISP_DIRECT:
            Operation();
            ellipse_direct=true;
            break;
        case ID_ELLISP_POLAR:
            Operation();
            ellipse_polar=true;
            break;
        ////----------
        case ID_Q1:
            Operation();
            Q1=true;
            break;
        case ID_Q2:
            Operation();
            Q2=true;
            break;
        case ID_Q3:
            Operation();
            Q3=true;
            break;
        case ID_Q4:
            Operation();
            Q4=true;
            break;
        ////-----------
        case ID_POINT:
            Operation();
            clippingP=true;
            break;
        case ID_LINE:
            Operation();
            clippingL=true;
            break;
        ////-----------
        case ID_COLOR_RED:
            Operation();
            red=true;
            blue=false;
            green=false;
            break;
        case ID_COLOR_BLUE:
            Operation();
            blue=true;
            green=false;
            red=false;
            break;
        case ID_COLOR_G:
            Operation();
            green=true;
            blue=false;
            red=false;
            break;
        ////--------------------------
        case ID_WINDOW_BACKGROUND:
            Operation();
            bckgrnd=true;
            break;
        case ID_WINDOW_CURSOR:
            Operation();
            cursor=true;
            break;
        case ID_WINDOW_Clear:
            Operation();
            cout<<"clearing the screen"<<endl;
            CloseWindow(hwnd);
            ShowWindow(hwnd,1);
            shapes.clear();
            break;

        }
        if (bckgrnd)
        {
            static HBRUSH bkbrush = NULL;
            COLORREF bkcolor = RGB(255, 255, 255);
            if(bkbrush)
                DeleteObject(bkbrush);
            bkbrush = CreateSolidBrush(bkcolor);
            SetClassLongPtr(hwnd, GCL_HBRBACKGROUND, (LONG)bkbrush);
            InvalidateRect(hwnd, NULL, TRUE);

        }
        if(cursor)
        {
            HCURSOR hCursor =LoadCursor (hinst, IDC_ARROW);;
            SetCursor(hCursor);
        }
        break;
    case WM_RBUTTONDOWN :
        x_c=LOWORD(lParam);
        y_c=HIWORD(lParam);
        break;
    case WM_LBUTTONDOWN :

        x2=LOWORD(lParam);
        y2=HIWORD(lParam);
        //Calling Functions
        if (exitt)
        {
            exit(0);
        }
        else if (lInt)
        {
            if(red)
            {
                LineDDA(hdc,x_c,y_c,x2,y2,RGB(255,1,1));
                Shape s;
                s.Algorithms="LineDDA";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                LineDDA(hdc,x_c,y_c,x2,y2,RGB(1,1,255));
                Shape s;
                s.Algorithms="LineDDA";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                LineDDA(hdc,x_c,y_c,x2,y2,RGB(1,255,1));
                Shape s;
                s.Algorithms="LineDDA";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                LineDDA(hdc,x_c,y_c,x2,y2,rgb);
                Shape s;
                s.Algorithms="LineDDA";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }

            ReleaseDC(hwnd,hdc);
        }
        else if (lparam)
        {
            if(red)
            {
                Parametricline(hdc,x_c,y_c,x2,y2,RGB(255,1,1));
                Shape s;
                s.Algorithms="Parametricline";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                Parametricline(hdc,x_c,y_c,x2,y2,RGB(1,1,255));
                Shape s;
                s.Algorithms="Parametricline";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                Parametricline(hdc,x_c,y_c,x2,y2,RGB(1,255,1));
                Shape s;
                s.Algorithms="Parametricline";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                Parametricline(hdc,x_c,y_c,x2,y2,rgb);
                Shape s;
                s.Algorithms="Parametricline";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);
        }
        else if (lmidpoint)
        {
            if(red)
            {
                LineMidPoint(hdc,x_c,y_c,x2,y2,RGB(255,1,1));
                Shape s;
                s.Algorithms="LineMidPoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                LineMidPoint(hdc,x_c,y_c,x2,y2,RGB(1,1,255));
                Shape s;
                s.Algorithms="LineMidPoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                LineMidPoint(hdc,x_c,y_c,x2,y2,RGB(1,255,1));
                Shape s;
                s.Algorithms="LineMidPoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;

                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }

            else
            {
                LineMidPoint(hdc,x_c,y_c,x2,y2,rgb);
                Shape s;
                s.Algorithms="LineMidPoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }


            ReleaseDC(hwnd,hdc);
        }

        else if (circle_direct)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                CircleDirect(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="CircleDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                CircleDirect(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="CircleDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }

            else if(green)
            {
                CircleDirect(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="CircleDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }

            else
            {
                CircleDirect(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="CircleDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }


            ReleaseDC(hwnd,hdc);
        }

        else if (circle_midpoint1)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                midpoint(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }

            else if(blue)
            {
                midpoint(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }

            else if(green)
            {
                midpoint(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }

            else
            {
                midpoint(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }

            ReleaseDC(hwnd,hdc);
        }
        else if (circle_midpoint2)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                modified_midpoint(hdc,x_c,y_c,rr,RGB(255,1,1));
                midpoint(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="modified_midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                modified_midpoint(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="modified_midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);

            }

            else if(green)
            {
                modified_midpoint(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="modified_midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                modified_midpoint(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="modified_midpoint";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);
        }
        else if (cpolar)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                CirclePolar(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="CirclePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                CirclePolar(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="CirclePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                CirclePolar(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="CirclePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                CirclePolar(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="CirclePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);
        }

        else if (cpolarIterative)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                CircleIterativePolar(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="CircleIterativePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }

            else if(blue)
            {
                CircleIterativePolar(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="CircleIterativePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }

            else if(green)
            {
                CircleIterativePolar(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="CircleIterativePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                CircleIterativePolar(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="CircleIterativePolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);
        }
        else if(Q1)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                Filling_Quarter_1(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="Filling_Quarter_1";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                Filling_Quarter_1(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="Filling_Quarter_1";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                Filling_Quarter_1(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="Filling_Quarter_1";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                Filling_Quarter_1(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="Filling_Quarter_1";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);

        }
        else if(Q2)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                Filling_Quarter_2(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="Filling_Quarter_2";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                Filling_Quarter_2(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="Filling_Quarter_2";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                Filling_Quarter_2(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="Filling_Quarter_1";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                Filling_Quarter_2(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="Filling_Quarter_2";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);

        }
        else if(Q3)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                Filling_Quarter_3(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="Filling_Quarter_3";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                Filling_Quarter_3(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="Filling_Quarter_3";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                Filling_Quarter_3(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="Filling_Quarter_3";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);

            }
            else
            {
                Filling_Quarter_3(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="Filling_Quarter_3";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.b=0;
                s.g=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);

        }
        else if(Q4)
        {
            rr=sqrt(pow((x2-x_c),2)+pow((y2-y_c),2));
            if(red)
            {
                Filling_Quarter_4(hdc,x_c,y_c,rr,RGB(255,1,1));
                Shape s;
                s.Algorithms="Filling_Quarter_4";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                Filling_Quarter_4(hdc,x_c,y_c,rr,RGB(1,1,255));
                Shape s;
                s.Algorithms="Filling_Quarter_4";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                Filling_Quarter_4(hdc,x_c,y_c,rr,RGB(1,255,1));
                Shape s;
                s.Algorithms="Filling_Quarter_4";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                Filling_Quarter_4(hdc,x_c,y_c,rr,rgb);
                Shape s;
                s.Algorithms="Filling_Quarter_4";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);

        }
        else if (ellipse_direct)
        {

            if(red)
            {
                EllipsDirect(hdc,x_c,y_c,x2,y2,RGB(255,1,1));
                cout<<"------------------------------"<<endl;
                Shape s;
                s.Algorithms="EllipsDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                EllipsDirect(hdc,x_c,y_c,x2,y2,RGB(1,1,255));
                Shape s;
                s.Algorithms="EllipsDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                EllipsDirect(hdc,x_c,y_c,x2,y2,RGB(1,255,1));
                Shape s;
                s.Algorithms="EllipsDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                EllipsDirect(hdc,x_c,y_c,x2,y2,rgb);
                Shape s;
                s.Algorithms="EllipsDirect";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.b=0;
                s.g=0;
                shapes.push_back(s);
            }

            ReleaseDC(hwnd,hdc);
        }

        else if (ellipse_polar)
        {
            if(red)
            {
                EllipsPolar(hdc,x_c,y_c,x2,y2,RGB(255,1,1));
                Shape s;
                s.Algorithms="EllipsPolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=255;
                s.g=1;
                s.b=1;
                shapes.push_back(s);
            }
            else if(blue)
            {
                EllipsPolar(hdc,x_c,y_c,x2,y2,RGB(1,1,255));
                Shape s;
                s.Algorithms="EllipsPolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=1;
                s.b=255;
                shapes.push_back(s);
            }
            else if(green)
            {
                EllipsPolar(hdc,x_c,y_c,x2,y2,RGB(1,255,1));
                Shape s;
                s.Algorithms="EllipsPolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=1;
                s.g=255;
                s.b=1;
                shapes.push_back(s);
            }
            else
            {
                EllipsPolar(hdc,x_c,y_c,x2,y2,rgb);
                Shape s;
                s.Algorithms="EllipsPolar";
                s.x_c=x_c;
                s.y_c=y_c;
                s.x2=x2;
                s.y2=y2;
                s.r=0;
                s.g=0;
                s.b=0;
                shapes.push_back(s);
            }
            ReleaseDC(hwnd,hdc);
        }

        else if (clippingP)
        {
            Rectangle(hdc,x_c,y_c,x2,y2);
            if(red)
            {
                PointClipping(hdc,x3,y3,x_c,y_c,x2,y2,RGB(255,1,1));
            }
            else if(blue)
            {
                PointClipping(hdc,x3,y3,x_c,y_c,x2,y2,RGB(1,1,255));
            }
            else if(green)
            {
                PointClipping(hdc,x3,y3,x_c,y_c,x2,y2,RGB(1,255,1));
            }
            else
            {
                PointClipping(hdc,x3,y3,x_c,y_c,x2,y2,rgb);
            }
            ReleaseDC(hwnd,hdc);

        }
        else if (clippingL)
        {
            Rectangle(hdc,x_c,y_c,x2,y2);
            CohenSuthClipping(hdc,x3,y3,x4,y4,x_c,y_c,x2,y2);
            ReleaseDC(hwnd,hdc);
        }
        else if (bckgrnd)
        {
            for(unsigned int i=0; i<shapes.size(); i++)
                draw(shapes[i],hwnd);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
