#include<iostream>
#include<cstring>
#include<queue>
#include<map>

using namespace std;

const int maxk = 5;
const int maxn = 100;
const int maxm = 100;

string grid[maxn];

int K;
int N, M, a, b, c, d;

map<pair<int,int>, int> key;

map<pair<pair<int, int>, int>, bool> visited;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int solve() {
    queue< pair<pair<pair<int,int>, int>,int> > q;
    pair<pair<int, int>, int> p = make_pair(make_pair(a, b),0);
    visited[p] = true;
    q.push(make_pair(p, 0));
    while (!q.empty()) {
        int keys = q.front().first.second; 
        int x = q.front().first.first.first;
        int y = q.front().first.first.second;
        int step = q.front().second;
        q.pop();
        if (x == c && y == d)
            return step;
        for (int i = 0; i < 4; ++i) {
            if (x + dx[i] < 0 || x + dx[i] >= N || y + dy[i] < 0 || y + dy[i] >= M) 
                continue;
            int _x = x + dx[i];
            int _y = y + dy[i];
            if (grid[_x][_y] == '#')
                continue;
            if (grid[_x][_y] != '.' && !(keys & (1 << (grid[_x][_y] - 'A'))))
                continue;
            pair<pair<int,int>, int> p = make_pair(make_pair(_x, _y), keys);
            p.second |= key[{_x,_y}];
            if (visited[p])
                continue;
            q.push(make_pair(p, step + 1));
            visited[p] = true;
        }
    }
    return -1; // remember this
}

int main() {
    cin>>N>>M>>K>>a>>b>>c>>d;
    for (int i = 0; i < N; ++i)
        cin>>grid[i];
    for (int i = 0; i < K; ++i) {
        int x, y;
        cin>>x>>y;
        key[{x,y}] = 1 << i;
    }
    cout<<solve()<<endl;
    return 0;
}
