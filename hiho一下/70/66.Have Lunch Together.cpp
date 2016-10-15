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
    // �ڵ�ͼ�� && ��Ϊǽ��ͬʱҲ��Ϊ����
    return (0 <= x && x < N && 0 <= y && y < M) &&\
    (map[x][y] == '.' || map[x][y] == 'S');
}

const int dir[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} }; // ��������
vector< pair<int, int> > seq;    // ��һ��vector���洢BFS�Ķ���

void BFS(int startX, int startY) {
    // �����������
    step[ startX ][ startY ] = 0;
    seq.push_back( make_pair(startX, startY) );

    int i = 0;
    while (i < (int) seq.size()) {
        for (int dr = 0; dr < 4; ++dr) {
            // ��չ�µĽڵ�
            int tempX = seq[i].first  + dir[dr][0];
            int tempY = seq[i].second + dir[dr][1];

            if (inMap(tempX, tempY) && step[tempX][tempY] == INT_MAX) {
                step[tempX][tempY] = step[ seq[i].first ][ seq[i].second ] + 1;
                // ����������λʱ�����ٽ�����չ
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
    // �����ͼ
    for (int i = 0; i < N; i++) 
        cin>>map[i];
    // �������H
    
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
            // ��ǰλ��ΪS���ҿ��Ե���
            if (map[i][j] == 'S' && step[i][j] != INT_MAX) {
                // ����±��Ƿ�������S
                if (map[i - 1][j] == 'S' && step[i - 1][j] != INT_MAX && ret > step[i][j] + step[i - 1][j])
                    ret = step[i][j] + step[i - 1][j];
                // ����ұ��Ƿ�������S
                if (map[i][j - 1] == 'S' && step[i][j - 1] != INT_MAX && ret > step[i][j] + step[i][j - 1])
                    ret = step[i][j] + step[i][j - 1];
            }
    
    
    if (ret < INT_MAX)
        cout<<ret<<endl;
    else
        cout<<"Hi and Ho will not have lunch."<<endl;

	return 0;
}