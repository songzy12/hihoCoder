// http://poj.org/problem?id=1981

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>

#define Mn 300//平面点集中点数

using namespace std;
const double eps = 1e-9;//精度调高点没跑~
const double pi = acos(-1.0);
#define sqr(x) ((x) * (x))

double R;//定长
struct point
{
    double x,y;
    void read()
    {
       scanf("%lf%lf",&x,&y);
    }

    void print()
    {
       printf("%lf%lf\n",x,y);
    }

    double friend dis(const point &a,const point &b)
    {
       return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
    }

}p[Mn + 5];

struct alpha
{
    double v;
    bool flag;
    bool friend operator <(const alpha &a,const alpha &b)//排序专用偏序关系
    {
       return a.v < b.v;
    }
}alp[Mn * Mn + 5];//C(N,2)*2的可能交点（可能极角）

void solve(int n, double R)
{
    //R = 1.0;//本题内为单位圆
    for(int i = 0;i < n;i++)
       p[i].read();
    int MAX = 0;
    for(int i = 0;i < n;i++)
    {
       int t = 0;
       for(int j = 0;j < n;j++)
       {
           if(i == j)
              continue;
           double theta,phi,D;
           D = dis(p[i],p[j]);
           if(D > 2.0 * R)//距离超界直接秒杀
              continue;
//关键部分
           theta = atan2(p[j].y - p[i].y,p[j].x - p[i].x);
           if(theta < 0)
              theta += 2 * pi;
           phi = acos(D / (2.0 * R));
           alp[t].v = theta - phi + 2 * pi;
           alp[t].flag = true;
           alp[t + 1].v = theta + phi + 2 * pi;
           alp[t + 1].flag = false;
           t += 2;
       }

       sort(alp,alp + t);
       int sum = 0;
       for(int j = 0;j < t;j++)
       {
           if(alp[j].flag)
              sum ++;
           else
              sum --;
           if(sum > MAX)
              MAX = sum;
       }
    }
    printf("%d\n",MAX + 1);
}

int main()
{
    int n;
    double r;
    cin>>n>>r;
    solve(n, r);
}