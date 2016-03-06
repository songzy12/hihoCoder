#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cstdio>  
#include <cstring> 
#define INF 99999999  
#define MAXN 20000  
using namespace std;  
// http://blog.csdn.net/u014157117/article/details/23714855
const int M = 100010;//边  
const int N = 500;  
      
struct Node//边，点f到点t，流量为c，费用为w  
{  
    int st, ed;  
    int flow, cost;  
    int next;  
}edge[M];  
      
int head[N], dis[N], q[N], pre[N], cnt;//cnt为已添加的边数，head为邻接表,dis为花费，pre为父亲节点  
bool vis[M];  
int n, m, s ,t;  
int graph[110][110];  
      
void init()  
{  
    memset(head, -1, sizeof(head));  
    cnt = 0;  
}  
      
void add_edge(int f, int t, int d1, int d2, int w)  
{//f到t的一条边，流量为d1,反向流量d2,花费w,反向边花费-w（可以反悔)  
    edge[cnt].st = f;  
    edge[cnt].ed = t;  
    edge[cnt].flow = d1;  
    edge[cnt].cost = w;  
    edge[cnt].next = head[f];  
    head[f] = cnt++;  
      
    edge[cnt].st = t;  
    edge[cnt].ed = f;  
    edge[cnt].flow = d2;  
    edge[cnt].cost = -w;  
    edge[cnt].next = head[t];  
    head[t] = cnt++;  
}  
      
bool spfa(int s, int t, int n)  
{  
    int i, tmp, l, r;  
    memset(pre, -1, sizeof(pre));  
    for(i = 0; i < n; ++i)  
    {  
        dis[i] = INF;  
    }  
    dis[s] = 0;  
    q[0] = s;  
    l = 0, r = 1;  
    vis[s] = true;  
    while(l != r)  
    {  
        tmp = q[l];  
        l = (l + 1) % (n + 1);  
        vis[tmp] = false;  
        for(i = head[tmp]; i!=-1; i = edge[i].next)  
        {  
            if(edge[i].flow && dis[edge[i].ed] > dis[tmp] + edge[i].cost)  
            {  
                dis[edge[i].ed] = dis[tmp] + edge[i].cost;  
                pre[edge[i].ed] = i;  
                if(!vis[edge[i].ed])  
                {  
                    vis[edge[i].ed] = true;  
                    q[r] = edge[i].ed;  
                    r = (r + 1) % (n + 1);  
                }  
            }  
        }  
    }  
    if(pre[t] == -1)  
    {  
        return false;  
    }  
    return true;  
}  
      
void MCMF(int s, int t, int n, int &flow, int &cost)  
{//起点s，终点t，点数n，最大流flow，最小花费cost  
    int tmp, arg;  
    flow = cost = 0;  
    while(spfa(s, t, n))  
    {  
        arg = INF;  
        tmp = t;  
        while(tmp != s)  
        {  
            arg = min(arg, edge[pre[tmp]].flow);  
            tmp = edge[pre[tmp]].st;  
        }  
        tmp = t;  
        while(tmp != s)  
        {  
            edge[pre[tmp]].flow -= arg;  
            edge[pre[tmp] ^ 1].flow += arg;  
            tmp = edge[pre[tmp]].st;  
        }  
        flow += arg;  
        cost += arg * dis[t];  
    }  
}  
      
int main()  
{  
    int x;  
    scanf("%d",&x);  
    for(int r = 1;r <= x;r++)  
    {  
        init();  
        scanf("%d%d",&m,&n);  
        for(int i = 1;i <= m;i++)  
        {  
            for(int j = 1;j <= n;j++)  
            {  
                scanf("%d",&graph[i][j]);  
                add_edge(i,2*m+j,1,0,graph[i][j]);  
                add_edge(i,2*m+n+j,1,0,graph[i][j]);  
                add_edge(i+m,2*m+n+j,1,0,graph[i][j]);  
                add_edge(i+m,2*m+j,1,0,graph[i][j]);  
            }  
        }  
        for(int i = 1;i <= m;i++)  
        {  
            add_edge(0,i,1,0,-MAXN);  
            add_edge(0,i+m,n,0,0);  
        }  
        t = 2 * m + 2 * n + 1;  
        for(int i = 1;i <= n;i++)  
        {  
            add_edge(i+2*m,t,1,0,-MAXN);  
            add_edge(2*m+n+i,t,m,0,0);  
        }  
        s = t + 1;  
        add_edge(s,0,n*m,0,0);  
        add_edge(0,t,n*m,0,0);  
        int flow ,cost;  
        MCMF(s,t,t+2,flow,cost);  
        printf("Case %d: %d\n",r,cost+(m+n)*MAXN);  
    }  
    return 0;  
} 