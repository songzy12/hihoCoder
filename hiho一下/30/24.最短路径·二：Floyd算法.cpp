#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

const int maxm = 1000, maxn = 100;
int d[maxn + 5][maxn + 5];

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int N, M;
    cin>>N>>M;
    
    memset(d, 0x3f, sizeof d);
    
    for (int i = 1; i <= N; ++i)
        d[i][i] = 0;
    
    for (int i = 0; i < M; ++i) {
        int u, v, length;
        cin>>u>>v>>length;
        if (d[u][v] > length) // multiple edges
            d[u][v] = d[v][u] = length;
    }
    
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            for (int k = 1; k <= N; ++k)
                d[k][j] = d[j][k] = min(d[j][k], d[j][i] + d[i][k]);
                
    for (int j = 1; j <= N; ++j) {
        for (int k = 1; k <= N; ++k)
            cout<<d[j][k]<<" ";
        cout<<endl;
    }
    
	return 0;
}