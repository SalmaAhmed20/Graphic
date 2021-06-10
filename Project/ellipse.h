#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#include <cmath>
#include <iostream>
using namespace std;
void EllipsDirect(HDC hdc,int xc,int yc,int x,int y,COLORREF color)
{
    cout<<"Direct Algorithm " <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
    cout<<"points"<<x<<" "<<y<<endl;


    double a =abs(xc-x);
    double b =abs(yc-y);
    //start draw from x = -a to x =a
    double xloop =-1*a;
    double yn,y2,r;
    //delta of change in x
    double dt = 1/((a+b)/2);
    while(xloop<=a)
    {
        //to get y  of xloop y =(+-)b *√1-(x/a)^2 from ellipse equation
        //x^2/a^+y^2/b^=1
        r =sqrt(1-pow((xloop/a),2));
        yn=b*r;
        y2=-1*b*r;
        SetPixel(hdc,xloop+xc,yn+yc,color);
        SetPixel(hdc,xloop+xc,y2+yc,color);
        xloop=xloop+dt;
    }
}
void EllipsPolar(HDC hdc,int xc,int yc,int x,int y,COLORREF color)
{
    cout<<"Polar Algorithm " <<endl;
    cout<<" center " << xc <<","<<yc<<endl;
     double a =abs(xc-x);
     double b =abs(yc-y);
     //start from theta = 0 to theta 350
     //every point (x,y)has its own theta
     double th = 0;
     double dt = 1/((a+b)/2);
     double xloop,yloop;
     double twopi =2*M_PI;
     while(th <= twopi )
     {
         xloop=a*cos(th);
         yloop=b*sin(th);
         th=th+dt;
         SetPixel(hdc,xloop+xc,yloop+yc,color);
     }
}
