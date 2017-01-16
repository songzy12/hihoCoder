#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 10000 + 10;

int n, m, color[MAXN];
vector<int> G[MAXN];

int scan(){
	char c;
	while(c = getchar(), c < '0' || '9' < c)
		;
	int ret = c - '0';
	while(c = getchar(), '0' <= c && c <= '9')
		ret = ret * 10 + c - '0';
	return ret;
}

void init(){
	memset(color, 0, sizeof(color));
	for(int i = 1; i <= n; ++i){
		G[i].clear();
	}
}

void input(){
	int u, v;
	n = scan();
	m = scan();
	init();
	while(m--){
		u = scan();
		v = scan();
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

bool dfs(int x){
	for(int i = 0; i < G[x].size(); ++i){
		int t = G[x][i];
		if(color[x] == color[t]) return false;
		if(!color[t]){
            // 1 to 2, 2 to 1
			color[t] = 3 - color[x];
			if(!dfs(t)) return false;
		}
	}
	return true;
}

bool solve(){
	for(int i = 1; i <= n; ++i){
        // 0: not set yet
		if(!color[i]){
			color[i] = 1;
			if(!dfs(i)) return false;
		}
	}
	return true;
}

int main(){
	int t = scan();
	while(t--){
		input();
		if(solve()){
			puts("Correct");
		}else{
			puts("Wrong");
		}
	}
	return 0;
}