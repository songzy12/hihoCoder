// simple BFS
// 就是如果一个块所在的0101矩阵包含于另一个块所在的0101矩阵，
// 要注意输出其中一个的时候不要将属于另一个块的11也输出出来
// 这个可以结合前面那个Bool数组，改成一个Integer数组，用来标记是第几个块，
// 然后输出的时候判断只有当前块的11才输出

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

char s[505][505];
int vis[505][505];
int n,m;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
vector<pii> v[500*501];

bool inside(int x,int y){
    if(x<0||y<0||x>=n||y>=m) return false;
    return true;
}
void dfs(int x,int y,int id){
    vis[x][y]=1;
    v[id].push_back(mk(x,y));
    for(int i=0;i<4;i++){
        int xx=x+dx[i];
        int yy=y+dy[i];
        if(inside(xx,yy)&&s[xx][yy]=='1'&&!vis[xx][yy]){
            dfs(xx,yy,id);
        }
    }
}
int vv[505][505];
void print(int id){
    int x1=1e9,x2=-1,y1=1e9,y2=-1;
    for(int i=0;i<v[id].size();i++){
        int x=v[id][i].first;
        int y=v[id][i].second;
        x1=min(x1,x);
        x2=max(x2,x);
        y1=min(y1,y);
        y2=max(y2,y);
    }
    int r=x2-x1+1;
    int c=y2-y1+1;
    for(int i=0;i<v[id].size();i++){
        int x=v[id][i].first;
        int y=v[id][i].second;
        int xx=x-x1;
        int yy=y-y1;
        vv[xx][yy]=1;
    }
    printf("%d %d\n",r,c);
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d",vv[i][j]);
            vv[i][j]=0;
        }
        printf("\n");
    }
}
int main(){
    scanf("%d%d",&n,&m);
    mem(vis,0);
    for(int i=0;i<n;i++){
        scanf("%s",s[i]);
        //printf("%s",s[i]);
    }
    int num=0;
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++){
            if(s[i][j]=='1'&&!vis[i][j]){
                num++;
                dfs(i,j,num);
            }
        }
    }
    mem(vv,0);
    for(int i=1;i<=num;i++){
        print(i);
    }
    return 0;
}
