#include <math.h>
#include <windows.h>
void draweight(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc-x,yc-y,color);

    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc+y,yc-x,color);
    SetPixel(hdc,xc+y,yc+x,color);
    SetPixel(hdc,xc-y,yc-x,color);
}


void midpoint(HDC hdc,int xc,int yc,int r,COLORREF color)
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
        draweight(hdc,x,y,xc,yc,color);
    }
}

void CircleDirect(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int R2=R*R;
    while(x<y)
    {
        x++;
        y=round(sqrt((double)(R2-x*x)));
        draweight(hdc,x,y,xc,yc,color);
    }
}

void CirclePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=R,y=0;
    double theta=0,dtheta=1.0/R;
    draweight(hdc,xc,yc,x,y,color);
    while(x>y)
    {
        theta+=dtheta;
        x=round(R*cos(theta));
        y=round(R*sin(theta));
        draweight(hdc,x,y,xc,yc,color);
    }
}

void CircleIterativePolar(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    double x=R,y=0;
    double dtheta=1.0/R;
    double cdtheta=cos(dtheta),sdtheta=sin(dtheta);
    draweight(hdc,xc,yc,R,0,color);
    while(x>y)
    {
        double x1=x*cdtheta-y*sdtheta;
        y=x*sdtheta+y*cdtheta;
        x=x1;
        draweight(hdc,x,y,round(xc),round(yc),color);
    }
}

void modified_midpoint(HDC hdc,int xc,int yc, int R,COLORREF color)
{
    int x=0,y=R;
    int d=1-R;
    int c1=3, c2=5-2*R;
    draweight(hdc,xc,yc,x,y,color);
    while(x<y)
    {
        if(d<0)
        {
            d+=c1;
            c2+=2;
        }
        else
        {
            d+=c2;
            c2+=4;
            y--;
        }
        c1+=2;
        x++;
        draweight(hdc,x,y,xc,yc,color);
    }
}

