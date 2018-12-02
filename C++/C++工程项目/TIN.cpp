#include<bits/stdc++.h>
using namespace std;
#define PI 3.1415926
struct triangleNode
{
    double coordinateX[3],coordinateY[3];   //坐标
    double triangleLength;            //周长
    double triangleArea;              //面积
    double triangSideleLength[3];        //边长
};
struct pointNode
{
    double x,y;
    
};
double dist(double xx,double yy,double xxx,double yyy)
{
    return sqrt((xx-xxx)*(xx-xxx)+(yy-yyy)*(yy-yyy));
}
double getTriangleCircumcircleRadius(triangleNode a)  //外接圆半径
{
    a.triangSideleLength[0]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[1],a.coordinateY[1]);
    a.triangSideleLength[1]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[2],a.coordinateY[2]);
    a.triangSideleLength[2]=dist(a.coordinateX[2],a.coordinateY[2],a.coordinateX[1],a.coordinateY[1]);
    double triangleCircumcircleRadius=0.5*(sqrt((a.triangSideleLength[0]+a.triangSideleLength[1]-a.triangSideleLength[2])
     *(a.triangSideleLength[0]-a.triangSideleLength[1]+a.triangSideleLength[2])
     *(a.triangSideleLength[1]+a.triangSideleLength[2]-a.triangSideleLength[0]))
    /(a.triangSideleLength[0]+a.triangSideleLength[1]+a.triangSideleLength[2]));
    return triangleCircumcircleRadius;
}
double getTriangleCircumcircleLength(triangleNode a)  //外接圆周长
{
    return 2*PI*getTriangleCircumcircleRadius(a);
}
double getTriangleCircumcircleArea(triangleNode a)  //外接圆面积
{
    return PI*getTriangleCircumcircleRadius(a)*getTriangleCircumcircleRadius(a);
}
double getTriangleLength(triangleNode a)            //三角形周长
{
    a.triangSideleLength[0]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[1],a.coordinateY[1]);
    a.triangSideleLength[1]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[2],a.coordinateY[2]);
    a.triangSideleLength[2]=dist(a.coordinateX[2],a.coordinateY[2],a.coordinateX[1],a.coordinateY[1]);
    return a.triangSideleLength[0]+a.triangSideleLength[1]+a.triangSideleLength[2];
}
double getTriangleArea(triangleNode a)            //三角形面积
{
    a.triangSideleLength[0]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[1],a.coordinateY[1]);
    a.triangSideleLength[1]=dist(a.coordinateX[0],a.coordinateY[0],a.coordinateX[2],a.coordinateY[2]);
    a.triangSideleLength[2]=dist(a.coordinateX[2],a.coordinateY[2],a.coordinateX[1],a.coordinateY[1]);
    double halfPerimeter=getTriangleArea(a)*0.5;  //半周长
    return sqrt(halfPerimeter*(halfPerimeter-a.triangSideleLength[0])*(halfPerimeter-a.triangSideleLength[1])*(halfPerimeter-a.triangSideleLength[2])); //海伦公式
}
int main()
{
   
}
