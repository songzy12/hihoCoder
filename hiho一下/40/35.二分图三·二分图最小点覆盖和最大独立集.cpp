// 最小点覆盖的点数 = 二分图最大匹配
// 最大独立集的点数 = 总点数 - 二分图最大匹配

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;


#define maxn 1001
#define maxm 10001

int n, m;
int tag[maxn];
int vis[maxn];
int match[maxn];
int first[maxn];
int adj[maxm], to[maxm], top;

void add(int u, int v)
{
    adj[top] = first[u];
    to[top] = v;
    first[u] = top++;
}

void dfs_tag(int u)
{
    int v;
    for(int i = first[u]; i != -1; i = adj[i]){
        v = to[i];
        if(!tag[v]){
            tag[v] = (tag[u] == 1)? 2 : 1;
            dfs_tag(v);
        }
    }
}

int dfs(int u)
{
    int v;
    for(int i = first[u]; i != -1; i = adj[i]){
        v = to[i];
        if(vis[v])
            continue;
        vis[v] = 1;
        if(!match[v]){
            match[v] = u;
            match[u] = v;
            return 1;
        }
        else{
            // dfs the match of point v
            if(dfs(match[v])){
                match[u] = v;
                match[v] = u;
                vis[v] = 0;
                return 1;
            }
        }
    }

    return 0;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    while(~scanf("%d%d", &n, &m)){
        top = 0;
        memset(first, -1, sizeof(first));
        memset(tag, 0, sizeof(tag));
        memset(match, 0, sizeof(match));

        int u,v;
        for(int i = 0; i < m; i++){
            scanf("%d%d", &u, &v);
            add(u,v);
            add(v,u);
        }

        for(int i  = 1; i <= n; i++)
        // divide nodes into two groups(1 or 2)
        if(!tag[i]){
            tag[i] = 1;
            dfs_tag(i);
        }

        int ans = 0;
        for(int i = 1; i <= n; i++)
        // only search from one side(1)
        if(tag[i] == 1 && !match[i]){
            memset(vis, 0, sizeof(vis));
            // dfs returns 1 or 0
            ans += dfs(i);
        }
        printf("%d\n%d\n", ans, n - ans);
    }
    return 0;
}
