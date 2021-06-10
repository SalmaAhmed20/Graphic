#include <vector>

union OUTcode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};
void PointClipping(HDC hdc, int x,int y,int xleft,int ytop,int xright,int ybottom,COLORREF color)
{
    cout<<"Point Clipping Algorithm" <<endl;
//    cout<<" center " << xc <<","<<yc<<endl;
if(x>=xleft && x<= xright && y>=ytop && y<=ybottom)
    SetPixel(hdc,x,y,color);
}
//to give each point its code like[1,1,0,0]
OUTcode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OUTcode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y<ytop)
        out.top=1;
    else if(y>ybottom)
        out.bottom=1;
    return out;
}
//finding Intersection point for x (vertical)
void VIntersection(double xs,double ys,double xe,double ye,int x,double *xi,double *yi)
{
    *xi=x;
    *yi=ys+(x-xs)*(ye-ys)/(xe-xs);
}
//finding Intersection point for y (Horizontal)
void HIntersection(double xs,double ys,double xe,double ye,int y,double *xi,double *yi)
{
    *yi=y;
    *xi=xs+(y-ys)*(xe-xs)/(ye-ys);
}

void CohenSuthClipping(HDC hdc,int xs,int ys,int xe,int ye,int xleft,int ytop,int xright,int ybottom)
{
     cout<<"CohenSuth Clipping Algorithm" <<endl;
//    cout<<" center " << xc <<","<<yc<<endl;
    double x1=xs,y1=ys,x2=xe,y2=ye;
    OUTcode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);//Get out code for start point
    OUTcode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);//Get out code for end point
    //we will be in this loop to we decide the type of this line
    while( (out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                VIntersection(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)
                HIntersection(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)
                VIntersection(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersection(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        else
        {
            if(out2.left)
                VIntersection(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                HIntersection(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                VIntersection(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersection(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {

        MoveToEx(hdc,round(x1),round(y1),NULL);
        LineTo(hdc,round(x2),round(y2));
    }
}

