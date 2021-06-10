#include "math.h"
#include <iostream>
using namespace std;
void Parametricline(HDC hdc,int x1,int y1,int x2,int y2,COLORREF C)
{
    cout<<"Parametric line algorithm "<<endl;
    cout<<"Line Length "<<sqrt(pow((x1-x2),2)-pow((y1-y2),2)) <<" unit" <<endl;
    double dx=x2-x1;
    double dy=y2-y1;
    for(double t=0; t<1; t+=0.001)
    {
        int x=x1+(dx*t);
        int y=y1+(dy*t);
        SetPixel(hdc,x,y,C);
    }
}

void LineDDA(HDC hdc, int x1,int yy, int x2, int y2,COLORREF C)
{
    cout<<"DDA line algorithm "<<endl;
    cout<<"Line Length "<<sqrt(pow((double)(x1-x2),2)-pow((double)(yy-y2),2)) <<" unit" <<endl;
    int dy = y2 - yy, dx = x2 - x1;
    if(abs(dx) >= abs(dy))  // slope <= 1
    {
        int x = x1, xInc = (dx>0?1:-1);
        double y = yy, yInc = (double)dy/dx * xInc;
        while(x != x2)
        {
            x +=xInc, y+=yInc;
            SetPixel(hdc,x,y,C);
        }

    }
    else
    {
        int y = yy, yInc = (dy>0?1:-1);
        double x = x1, xInc = (double)dx/dy * yInc;
        while(y != y2)
        {
            y +=yInc, x+=xInc;
            SetPixel(hdc,x,y,C);
        }
    }
}
void LineMidPoint(HDC hdc,int xc,int yc,int x2,int y2,COLORREF rgb)
{
    cout<<"Mid point line algorithm "<<endl;
    cout<<"Line Length "<<sqrt(pow((xc-x2),2)-pow((yc-y2),2)) <<" unit" <<endl;
    int dx = x2 - xc ;
    int dy = y2 - yc ;
    int X3,Y3 ;
    double m = (double) dy / dx;

    if (abs(dx)>abs(dy))
    {
        if (xc>x2)
        {
            swap(xc,x2);
            swap(yc,y2);
            dx*=-1;
            dy*=-1;
        }
        X3=xc;
        Y3=yc;
        if (m>=0 && m<=1)
        {
            int d = dx  -2 * dy;
            int d1 = 2 *(dx - dy);
            int d2 = -2 * dy;
            SetPixel(hdc,X3,Y3, rgb);
            while(X3!=x2)
            {
                X3++;
                if(d<0)
                {
                    d+=d1;
                    Y3++;
                }
                else
                    d+=d2;
                SetPixel(hdc,X3,Y3, rgb);
            }
        }
        else if (-1 <= m&&m<=0  )
        {
            int d =-1* dx -2 * dy;;
            int d1 =-2 * dx - 2 * dy;
            int d2 = -2 * dy;
            while(X3!=x2)
            {
                X3++;
                if (d>0)
                {
                    Y3--;
                    d+=d1 ;
                }
                else
                    d+=d2;
                SetPixel(hdc,X3,Y3, rgb);
            }
        }
    }
    else
    {
        if (yc>y2)
        {
            swap(xc,x2);
            swap(yc,y2);
            dx*=-1;
            dy*=-1;
        }
        X3=xc;
        Y3=yc;
        if (m>1)
        {
            int d = 2*dx - dy ;
            int d1 = 2*(dx - dy );
            int d2 = 2 * dx;
            while(Y3!=y2)
            {
                Y3++;
                if (d>0)
                {
                    d+=d1;
                    X3++;
                }
                else
                {
                    d+=d2;
                }
                SetPixel(hdc,X3,Y3, rgb);
            }
        }
        else if (m<=-1)
        {
            int d = 2*dx + dy;
            int d1 =2 *(dx + dy);
            int d2 = 2 *dx;
            SetPixel(hdc,X3,Y3, rgb);
            while(Y3!=y2)
            {
                Y3++;
                if (d<0)
                {
                    d+=d1;
                    X3--;
                }
                else
                    d+=d2;
                SetPixel(hdc,X3,Y3, rgb);
            }
        }
    }
}
