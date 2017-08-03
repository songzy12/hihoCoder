#include<iostream>
#include<queue>
#include<cstring>
using namespace std;

const int maxn = 100;

int grid[maxn][maxn];
bool visited[maxn][maxn];

int ans;

pair<int,int> dir[] = {{0,1},{0,-1},{1,0},{-1,0}};
int N, M;

int check(int i, int j) {
    if (i < 0 || i >= N || j < 0 || j >= M)
        return false;
    return true;
}

void bfs(int x, int y) {
    queue<pair<int,int> > q;
    q.push({x,y});
    while (!q.empty()) {
        pair<int,int> t = q.front(); q.pop();
        int x0 = t.first, y0 = t.second;
        if (visited[x0][y0]) // one may be added twice
            continue;
        visited[x0][y0] = true;
        ans += 4;
        for (int i = 0; i < 4; ++i) {
            int x1 = x0 + dir[i].first;
            int y1 = y0 + dir[i].second;
            if (check(x1, y1) && visited[x1][y1])
                ans-=2;
        }
        //cout<<x0<<" "<<y0<<" "<<ans<<endl;
        for (int i = 0; i < 4; ++i) {
            int x1 = x0 + dir[i].first;
            int y1 = y0 + dir[i].second;
            if (check(x1, y1) && !visited[x1][y1] && grid[x1][y1] == grid[x0][y0]) {
                q.push({x1, y1});
            }
        }
    }
    return ;
}

int main() {
    int x, y;
    cin>>N>>M>>x>>y;
    for (int n = 0; n < N; ++n)
        for (int m = 0; m < M; ++m)
            cin>>grid[n][m];
    memset(visited, false, sizeof visited);
    ans = 0;
    bfs(x, y);
    cout<<ans<<endl;
}