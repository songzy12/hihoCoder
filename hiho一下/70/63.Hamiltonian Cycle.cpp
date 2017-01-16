#include<iostream>
#include<cstdio>
using namespace std;

const int MAXN = 14;

int edge[ MAXN ];
int p[1 << MAXN];
int cnt;

void dfs(int nowVertex, int unused) {
    if (!unused) {
        cnt += (edge[nowVertex] & 1); // whether we can go back to 1
        return ;
    }
    int rest = unused & edge[ nowVertex ];
    while (rest) {
        int tp = rest & (-rest); // pick the last 1
        dfs(p[ tp ], unused - tp);
        rest -= tp;
    }
    return ;
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        p[ 1 << i ] = i + 1; // from bit to index
    while (m--) {
        int u, v;
        scanf("%d %d", &u, &v);
        edge[u] |= 1 << (v - 1); // adjacent nodes
    }
    dfs(1, (1 << n) - 2); // remove last bit, s.t., node 1
    printf("%d\n", cnt);
    return 0;
}