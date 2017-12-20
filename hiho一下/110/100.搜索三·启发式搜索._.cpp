/*
链接:
题目：
题意：
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cctype>
#include<queue>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ull inf = ~0ull;
const double eps = 1e-10;
const int maxn = 1e4+1000;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define lrt rt<<1
#define rrt rt<<1|1
int  m, k, n, len;
int p[10];
void init()//求阶乘；
{
    int t = 1;
    p[0] = 1;
    for(int i = 1; i<=9; i++){
        t *= i;
        p[i] = t;
    }
}
int JO(int v[])//奇偶排列必须相同；
{
    int cnt, sum=0;
    for(int i = 0; i < len; i++){
        if(v[i]==0) continue;
        cnt = 0;
        for(int j = 0; j < i; j++){
            if(v[j]==0) continue;
            if(v[j]<v[i]) cnt++;
        }
        sum += cnt;
    }
    return sum%2;
}
struct node
{
    int v[10];
    int x, y;
    int step, f;//f = step + e; e临时求；
    bool operator < (const node&k) const{
        if(f==k.f) return step>k.step;
        return f>k.f;
    }
}t;
int goalid, base[]={1,2,3,4,5,6,7,8,0}, id;
int flag[370000];
int Cantor(int v[])//一个排列是全排列中的第几排列；从0开始；
{
    int x = 0;
    for(int i = 0; i < len; i++){
        int tp = 0;
        for(int j = i+1; j < len; j++){
            if(v[j]<v[i]){
                tp++;
            }
        }
        x = x + tp*p[len-(i+1)];
    }
    return x;
}
int hx[9][2] = {{2,2},{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1}};
int Eval(int *v)//可以所有的哈希顿距离和，也可以有多少个不同的位置；
{
   /* int cnt = 0;
    for(int i = 0; i < len; i++){
        if(base[i]!=v[i]) cnt++;
    }
    return cnt;*/
    int sum = 0, x, y;
    for(int i = 0; i < len; i++){
        if(v[i]==0) continue;
        x = i/3, y = i%3;
        sum += abs(hx[v[i]][0]-x)+abs(hx[v[i]][1]-y);
    }
    return sum;
}
priority_queue<node> qu;
int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};
int solve()
{
    while(!qu.empty()) qu.pop();
    qu.push(t);
    while(!qu.empty()){
        t = qu.top();
        qu.pop();
        int x = t.x, y = t.y, bcol;
	   printf("Cantor: %d, g: %d\n", Cantor(t.v), t.step);
        t.step++;
				
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j)
				printf("%d ", t.v[3*i+j]);
			printf("\n");
		}
		printf("\n");
		
		
        bcol = x*3+y;
        for(int k = 0; k < 4; k++){
            int xx = x+dir[k][0];
            int yy = y+dir[k][1];
            if(xx>=0&&xx<3&&yy>=0&&yy<3){
                int col = xx*3+yy;
                swap(t.v[col],t.v[bcol]);
                id = Cantor(t.v);

                if(id==goalid) return t.step;
                if(flag[id]==0){
					printf("neighbor: %d\n", id);
                   flag[id] = 1;
                   t.x = xx, t.y = yy;
                   t.f = t.step+Eval(t.v);
				   printf("g: %d, h: %d\n", t.step, Eval(t.v));
                   qu.push(t);
                }
                swap(t.v[col],t.v[bcol]);
            }
        }
    }
    return -1;
}
int main()
{
	freopen("in.txt", "r", stdin);
	freopen("out_.txt", "w", stdout);
    int T;
    len = 9;
    init();
    goalid = Cantor(base);
    cin>>T;
  //  cout<<hx[8][0]<<" "<<hx[8][1]<<endl;
    while(T--){
        memset(flag, 0, sizeof flag);
        for(int i = 0; i < 9; i++){
            scanf("%d",&t.v[i]);
            if(t.v[i]==0){
                t.x = i/3, t.y = i%3;
            }
        }
        if(JO(t.v)^JO(base)){
            printf("No Solution!\n");
            continue;
        }
		
		// TODO:
        id = Cantor(t.v);
				
		printf("Cantor: %d, f: %d\n", id, Eval(t.v));
		
        if(id==goalid){
            printf("0\n"); continue;
        }
        flag[id] = 1;
        t.step = 0;
        t.f = t.step + Eval(t.v);//t.f 越大，优化越好；
        int ans = solve();
        if(ans==-1)printf("No Solution!\n");
        else printf("%d\n",ans);
    }
    return 0;
}

