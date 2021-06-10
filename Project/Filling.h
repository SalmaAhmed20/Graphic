
#include <windows.h>
void parametricline(HDC hdc,int x1,int yY,int x2,int y2,COLORREF color)
{
    double dx=x2-x1;
    double dy=y2-yY;
    for(double t=0; t<1; t+=0.001)
    {
        int x=x1+(dx*t);
        int y=yY+(dy*t);
        SetPixel(hdc,x,y,color);
    }

}
// *************to draw first quarter*************
void Draw8points_Quarter_1(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    //first quarter
    SetPixel(hdc,xc+x,yc-y,color);
    parametricline(hdc,xc,yc,xc+x,yc-y,color);
    SetPixel(hdc,xc+y,yc-x,color);
    parametricline(hdc,xc,yc,xc+y,yc-x,color);

    /////////////////////////////////
    SetPixel(hdc,xc-x,yc-y,color);
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc+y,yc+x,color);
    SetPixel(hdc,xc-y,yc-x,color);

}
void Filling_Quarter_1(HDC hdc,int xc,int yc,int R,COLORREF color)//BY MIDPOINT Bresnham
{
     cout<<"Filling_Quarter_1" <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
    int x=0;
    int y=R;
    double d=1-R;
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
        Draw8points_Quarter_1(hdc,x,y,xc,yc,color);
    }

}

// *************to draw second quarter*************
void Draw8points_Quarter_2(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    //second quarter
    SetPixel(hdc,xc-x,yc-y,color);
    parametricline(hdc,xc,yc,xc-x,yc-y,color);
    SetPixel(hdc,xc-y,yc-x,color);
    parametricline(hdc,xc,yc,xc-y,yc-x,color);
    /////////////////////////////////
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc+y,yc-x,color);
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc+y,yc+x,color);

}

void Filling_Quarter_2(HDC hdc,int xc,int yc,int R,COLORREF color)//BY MIDPOINT Bresnham
{
     cout<<"Filling_Quarter_2" <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
    int x=0;
    int y=R;
    double d=1-R;
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
        Draw8points_Quarter_2(hdc,x,y,xc,yc,color);
    }

}

// *************to draw third quarter*************
void Draw8points_Quarter_3(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    //third quarter
    SetPixel(hdc,xc+x,yc+y,color);
    parametricline(hdc,xc,yc,xc+x,yc+y,color);
    SetPixel(hdc,xc+y,yc+x,color);
    parametricline(hdc,xc,yc,xc+y,yc+x,color);
    /////////////////////////////////
    SetPixel(hdc,xc-x,yc-y,color);
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc+y,yc-x,color);
    SetPixel(hdc,xc-x,yc+y,color);
    SetPixel(hdc,xc-y,yc+x,color);
    SetPixel(hdc,xc-y,yc-x,color);

}

void Filling_Quarter_3(HDC hdc,int xc,int yc,int R,COLORREF color)//BY MIDPOINT Bresnham
{
     cout<<"Filling_Quarter_3" <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
    int x=0;
    int y=R;
    double d=1-R;
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
        Draw8points_Quarter_3(hdc,x,y,xc,yc,color);
    }
}

// *************to draw fourth quarter*************
void Draw8points_Quarter_4(HDC hdc,int x,int y,int xc,int yc,COLORREF color)
{
    //fourth quarter
    SetPixel(hdc,xc-x,yc+y,color);
    parametricline(hdc,xc,yc,xc-x,yc+y,color);
    SetPixel(hdc,xc-y,yc+x,color);
    parametricline(hdc,xc,yc,xc-y,yc+x,color);
    /////////////////////////////////
    SetPixel(hdc,xc-x,yc-y,color);
    SetPixel(hdc,xc+x,yc-y,color);
    SetPixel(hdc,xc+y,yc-x,color);
    SetPixel(hdc,xc-y,yc-x,color);
    SetPixel(hdc,xc+x,yc+y,color);
    SetPixel(hdc,xc+y,yc+x,color);
}

void Filling_Quarter_4(HDC hdc,int xc,int yc,int R,COLORREF color)//BY MIDPOINT Bresnham
{
    cout<<"Filling_Quarter_4" <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
    int x=0;
    int y=R;
    double d=1-R;
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
        Draw8points_Quarter_4(hdc,x,y,xc,yc,color);
    }

}
