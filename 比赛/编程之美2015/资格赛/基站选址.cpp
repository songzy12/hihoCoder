#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<map>
#include<algorithm>
#include<string>
#include<set>
using namespace std;
int n,m,na,nb;
int ax[1010],ay[1010],bx[1010],by[1010];
long long s1,s2,x,y,s,d,ans,sy,sx;
void calc(int x,int y)
{
	s=0;
	for(int k=1;k<=na;k++)
	s+=(ax[k]-x)*1LL*(ax[k]-x)+(ay[k]-y)*1LL*(ay[k]-y);
	d=1000000000000000000; // an arbitrary big number 
	for(int k=1;k<=nb;k++)
	d=min(d,abs(bx[k]-x)+abs(by[k]-y)*1LL); // just find out the minimum
	if(s+d<ans){ans=s+d;sx=x;sy=y;}
}
void task()
{
	scanf("%d%d%d%d",&n,&m,&na,&nb);
	s1=s2=0;
	for(int i=1;i<=na;i++){
		scanf("%d%d",&ax[i],&ay[i]);
		s1+=ax[i];
		s2+=ay[i];
	}
	for(int i=1;i<=nb;i++)
	scanf("%d%d",&bx[i],&by[i]);
	x=s1/na,y=s2/na;
	ans=1000000000000000000;
    for(int i=x-1;i<=x+1;i++)
    for(int j=y-1;j<=y+1;j++)
	// the boundary condition
    if(i>=1 && i<=n && j>=1 && j<=m)
    calc(i,j);
	cout<<ans<<endl;
}
int main()
{
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++)
	{
		printf("Case #%d: ",i);
		task();
	}
}