#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<list>
#include<iomanip>
#include<climits>

using namespace std;

const int MAXN = 100;
const int MAXM = 100;
string map[MAXN + 5];
int step[MAXN + 5][MAXM + 5];
int N, M;

bool inMap(int x, int y) {
    // 在地图内 && 不为墙壁同时也不为行人
    return (0 <= x && x < N && 0 <= y && y < M) &&\
    (map[x][y] == '.' || map[x][y] == 'S');
}

const int dir[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} }; // 方向数组
vector< pair<int, int> > seq;    // 用一个vector来存储BFS的队列

void BFS(int startX, int startY) {
    // 将起点存入队列
    step[ startX ][ startY ] = 0;
    seq.push_back( make_pair(startX, startY) );

    int i = 0;
    while (i < (int) seq.size()) {
        for (int dr = 0; dr < 4; ++dr) {
            // 扩展新的节点
            int tempX = seq[i].first  + dir[dr][0];
            int tempY = seq[i].second + dir[dr][1];

            if (inMap(tempX, tempY) && step[tempX][tempY] == INT_MAX) {
                step[tempX][tempY] = step[ seq[i].first ][ seq[i].second ] + 1;
                // 当发现是座位时，不再进行扩展
                if (map[tempX][tempY] != 'S') seq.push_back( make_pair(tempX, tempY) );
            }
        }
        ++i;
    }

    return ;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    cin>>N>>M;
    int startX = -1, startY = -1;
    // 读入地图
    for (int i = 0; i < N; i++) 
        cin>>map[i];
    // 查找起点H
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; ++j) {
            if (map[i][j] == 'H') {
                startX = i, startY = j;
                i = N;
                break;
            }
        }
    }
     
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            step[i][j] = INT_MAX; // not "==" !
    
    BFS(startX, startY);
    
    int ret = INT_MAX;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            // 当前位置为S，且可以到达
            if (map[i][j] == 'S' && step[i][j] != INT_MAX) {
                // 检查下边是否有相邻S
                if (map[i - 1][j] == 'S' && step[i - 1][j] != INT_MAX && ret > step[i][j] + step[i - 1][j])
                    ret = step[i][j] + step[i - 1][j];
                // 检查右边是否有相邻S
                if (map[i][j - 1] == 'S' && step[i][j - 1] != INT_MAX && ret > step[i][j] + step[i][j - 1])
                    ret = step[i][j] + step[i][j - 1];
            }
    
    
    if (ret < INT_MAX)
        cout<<ret<<endl;
    else
        cout<<"Hi and Ho will not have lunch."<<endl;

	return 0;
}