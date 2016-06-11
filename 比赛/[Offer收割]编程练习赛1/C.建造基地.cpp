#include<stdio.h>
#include<cstring>
#include<iostream>
#define N 10005
using namespace std;
typedef long long LL;LL f[N],ans;
int a[N],b[N],Q,n,m,K,T,i;

inline int DP(){
	memset(f,60,sizeof(f));
	LL INF=f[0],now=f[0];
    f[0]=0;
	for (int i=0;i<K;i++)
		if (f[i]<INF)
			for (int j=1;j<=m;j++)
				if (i+b[j]<K) 
                    f[i+b[j]]=min(f[i+b[j]],f[i]+a[j]);
				else 
                    now=min(now,f[i]+a[j]);
	for (int i=1;i<=m;i++) 
        b[i]/=T;
	ans+=now;
    return now<INF;
}

int main(){
	scanf("%d",&Q);
	while (Q--){
		scanf("%d%d%d%d",&n,&m,&K,&T);
		for (i=1;i<=m;i++)
			scanf("%d",&a[i]);
		for (i=1;i<=m;i++)
			scanf("%d",&b[i]);
		ans=0;
        for (i=1;i<=n;i++) 
			if (!DP()) 
                break;
		if (i<=n) 
            puts("No Answer");
		else 
            cout<<ans<<endl;
  }
}