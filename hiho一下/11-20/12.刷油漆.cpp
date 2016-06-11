#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

const int MAXN = 100;
int f[MAXN+5][MAXN+5], header[MAXN+5];
int next_[MAXN], to[MAXN];
int N, M;

void dfs(int);

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	cin>>N>>M;
	
	for(int i = 1; i <= N; ++i)
		cin>>f[i][1];
	for(int i = 1; i < N; ++i){
		int u, v;
		cin>>u>>v;
		to[i] = v;
		next_[i] = header[u];
		header[u] = i;
	}
	dfs(1);
	cout<<f[1][M]<<endl;
	return 0;
}

void dfs(int t){
	int p = header[t];
	while(p){
		dfs(to[p]);
		p = next_[p];
	}
	
	p = header[t];
	while(p){
		for(int j = M; j > 1; --j){
			for(int i = 1; i < j; ++i){
				f[t][j] = max(f[t][j], f[t][j-i] + f[to[p]][i]);
				// by far f[t][j-i] has not taken to[p] into account
				// first update f[t][M], then f[t][M-1] ...
				// updating f[t][M] will refer to f[t][M-1] ...
			}
		}
		p = next_[p];
	}
}