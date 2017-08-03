#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;

const int maxn = 500;
vector<int> edges[maxn+5];
bool visited[maxn+5];

void bfs(int node) {
    queue<int> q;
    q.push(node);
    while (!q.empty()) {
        int t = q.front(); q.pop();
        if (!visited[t]) {
            visited[t] = true;
            for (int i = 0; i < edges[t].size(); ++i)
                q.push(edges[t][i]);
        }
    }
    return;
}

bool check(int n) {
    for (int i = 1; i <= n; i++)
        if (!visited[i])
            return false;
    return true;
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        
        int N, M;
        cin>>N>>M;
        
        for (int i = 1; i <= N; ++i) {
            visited[i] = false;
            edges[i].clear();
        }
        int x, y;
        for (int i = 0; i < M; ++i) {
            cin>>x>>y;
            edges[x].push_back(y);
            edges[y].push_back(x);
        }
        
        if (M != N-1) {
            puts("NO");
            continue;
        }
        bfs(1);
        puts(check(N)?"YES":"NO");        
    }
}