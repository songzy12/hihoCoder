#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=200005,maxm=1000005;
int N,M,dis[maxn],H[maxn],pH[maxn],tot;
int y[maxm],z[maxm],next[maxm],last[maxn];
inline void _getnum(int &xx)
{
    char tt=getchar();
    while(tt<'0'||tt>'9')tt=getchar();
    for(xx=0;tt>='0'&&tt<='9';tt=getchar())xx=xx*10+(tt-'0');
}
void _shift_up(int i)
{
    int j=i>>1,t=H[i];
    while(j>=1)
    {
        if(dis[H[j]]>dis[t])
        {
            H[i]=H[j];
            pH[H[i]]=i;
            i=j;j=i>>1;
        }
        else break;
    }
    H[i]=t;pH[H[i]]=i;
}
void _shift_down(int i)
{
    int j=i<<1,t=H[i];
    while(j<tot)
    {
        if(j+1<tot&&dis[H[j]]>dis[H[j+1]])j++;
        if(dis[t]>dis[H[j]])
        {
            H[i]=H[j];
            pH[H[i]]=i;
            i=j;j=i<<1;
        }
        else break;
    }
    H[i]=t;pH[H[i]]=i;
}
void _prim()
{
    int i,j,k,ans=0;
    for(i=1;i<=N;i++)
    {
        H[i]=pH[i]=i;
        dis[i]=999999999;
    }
    dis[1]=0;tot=N+1;
    for(i=1;i<=N;i++)
    {
        k=H[1];H[1]=H[--tot];pH[H[1]]=1;pH[k]=0;
        _shift_down(1);
        ans+=dis[k];
        for(j=last[k];j>0;j=next[j])
            if(pH[y[j]]!=0&&dis[y[j]]>z[j])
            {
                dis[y[j]]=z[j];
                _shift_up(pH[y[j]]);
            }
    }
    printf("%d",ans);
}
int main()
{
    int i,j,k,t;
    _getnum(N);_getnum(M);
    for(i=j=1;i<=M;i++)
    {
        _getnum(k);_getnum(t);_getnum(z[j]);
        y[j]=t;next[j]=last[k];last[k]=j++; // k to t
        y[j]=k;z[j]=z[j-1];next[j]=last[t];last[t]=j++; // t to k
    }
    _prim();
    return 0;
}