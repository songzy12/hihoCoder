#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;

const int maxn = 800;
int grid[maxn][maxn];
bool visited[maxn][maxn];
int dist[maxn][maxn];
queue<pair<int, int> > q;

int main() {
    int n, m;
    cin>>n>>m;
    for (int i = 0; i <n; ++i) {
        string line;
        cin>>line;
        for (int j = 0; j < m; ++j) {
            grid[i][j] = line[j]-'0';
            if (grid[i][j] == 0) {
                q.push({i, j});
                visited[i][j] = true;
                dist[i][j] = 0;
            } else {
                visited[i][j] = false;
                dist[i][j] = 10000;
            }
        }
    }
    
    int cur_dist = 0;
    while (!q.empty()) {
        cur_dist++;
        queue<pair<int,int> > p;
        while (!q.empty()) {
            pair<int, int> temp = q.front(); q.pop();
            int x = temp.first, y = temp.second;
            int dx_[] = {-1, 1, 0, 0};
            int dy_[] = {0, 0, -1, 1};
            for (int i = 0; i < 4; ++i) {
                int dx = dx_[i], dy = dy_[i];
                if (x+dx >= 0 && x+dx < n && y+dy >= 0 && y+dy < m && !visited[x+dx][y+dy]) {
                    visited[x+dx][y+dy] = true;
                    dist[x+dx][y+dy] = cur_dist;
                    p.push({x+dx, y+dy});
                }
            }
        }
        q = p;        
    }
    
    for (int i = 0; i <n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout<<dist[i][j]<<" ";
        }
        cout<<endl;
    }
}
