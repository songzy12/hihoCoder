// 你能统计出一共有多少个不同的子矩形是完全由白色单位正方形组成的吗

// https://leetcode.com/problems/maximal-rectangle/

#include <map>
#include <set>
#include <stack>
#include <queue>
#include <cmath>
#include <string>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#pragma comment(linker,"/STACK:102400000,102400000")

using namespace std;
#define   MAX           100005
#define   MAXN          1000005
#define   maxnode       105
#define   sigma_size    30
#define   lson          l,m,rt<<1
#define   rson          m+1,r,rt<<1|1
#define   lrt           rt<<1
#define   rrt           rt<<1|1
#define   middle        int m=(r+l)>>1
#define   LL            long long
#define   ull           unsigned long long
#define   mem(x,v)      memset(x,v,sizeof(x))
#define   lowbit(x)     (x&-x)
#define   pii           pair<int,int>
#define   bits(a)       __builtin_popcount(a)
#define   mk            make_pair
#define   limit         10000

//const int    prime = 999983;
const int    INF   = 0x3f3f3f3f;
const LL     INFF  = 0x3f3f;
const double pi    = acos(-1.0);
const double inf   = 1e18;
const double eps   = 1e-8;
const LL     mod   = 1e9+7;
const ull    mx    = 133333331;

/*****************************************************/
inline void RI(int &x) {
      char c;
      while((c=getchar())<'0' || c>'9');
      x=c-'0';
      while((c=getchar())>='0' && c<='9') x=(x<<3)+(x<<1)+c-'0';
 }
/*****************************************************/

int r[15],c[15];
int main(){
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=0;i<k;i++){
        scanf("%d%d",&r[i],&c[i]);
    }
    LL ans=(LL)n*(n+1)/2*(LL)m*(m+1)/2;
    for(int i=1;i<(1<<k);i++){
        int num=bits(i);
        int x1=1e9,x2=-1,y1=1e9,y2=-1;
        for(int j=0;j<k;j++){
            if((1<<j)&i){
                x1=min(x1,r[j]);
                x2=max(x2,r[j]);
                y1=min(y1,c[j]);
                y2=max(y2,c[j]);
            }
        }
        // 容斥原理
        if(num%2) ans-=(LL)x1*y1*(n-x2+1)*(m-y2+1);
        else ans+=(LL)x1*y1*(n-x2+1)*(m-y2+1);
    }
    cout<<ans<<endl;
    return 0;
}
