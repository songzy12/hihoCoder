#include<iostream>
#include<map>
#include<cstring>
#include<cstdio>
#include<stack>
using namespace std;

const int maxn = 50;
string grid[maxn];
bool visited[maxn][maxn];

map<string, int> shape;
map<int, int> area;
int count;
int N, M;

int dir[][2] = {{0,1},{0,-1},{1,0},{-1,0}};

bool check(int i, int j) {
    return i >= 0 && i < N && 
         j >= 0 && j < M && 
         grid[i][j] == '#' && 
         !visited[i][j];
}

void dfs(int i, int j) {
    //printf("i, j: %d %d\n", i, j);
    visited[i][j] = true;
    string shape_ = "";
    int area_ = 0;
    count++;
    
    stack<pair<int,int> > s;
    s.push({i, j});
    while (!s.empty()) {
        pair<int,int> t = s.top(); s.pop();
        int x0 = t.first;
        int y0 = t.second;
        for (int i = 0; i < 4; ++i) {
            int x1 = x0 + dir[i][0];
            int y1 = y0 + dir[i][1];
            if (check(x1, y1)) {
                //printf("x1, y1: %d %d\n", x1, y1);
    
                shape_.push_back(i+'0'); // this shape map is not valid
                area_ ++;
                s.push({x1,y1});
                visited[x1][y1] = true;
            } else {
                shape_.push_back(5+'0'); // add one char to make map unique
            }
        }
    }
    shape[shape_]++;
    area[area_]++;
}

void solve() {
    count = 0;
    memset(visited, false, sizeof visited);
    
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j) {   
            if (check(i, j)) {
                dfs(i, j);                
            }            
        }
}

int main() {
    cin>>N>>M;
    for (int i = 0; i < N; ++i)
            cin>>grid[i];
    solve();
    cout<<count<<" "<<area.size()<<" "<<shape.size();
}