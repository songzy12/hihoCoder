#include <stdio.h>
#include <limits.h>
#include <memory.h>
#include <queue>

using namespace std;

#define MAXN 10005
#define MAXM 200010

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

int U[MAXM], V[MAXM], W[MAXM];
int gfirst[MAXN];
int gnext[MAXM];

bool vis[MAXN];

int bfs(int st, int T, int C, int K) {
	queue<pair<int,int> > Q;
	Q.push(make_pair(st, 0));
	vis[st] = true;

	while(!Q.empty()) {

		int u = Q.front().first;
		int k = Q.front().second;
		Q.pop();

		for(int e=gfirst[u];e!=-1;e=gnext[e]) {
			int v = V[e];
			int w = W[e];
			if(w > C)
				continue;
			if(vis[v])
				continue;
			if(v == T)
				return C;
			if(k+1 >= K)
				continue;

            // k is the layer number
			Q.push(make_pair(v, k+1)); 
			vis[v] = true;
		}
	}
	return -1;
}


int solve(int N, int M, int T, int K, int minC, int maxC) {
	if(T == 0)
		return 0;

	int st = minC;
	int ed = maxC;

	int R = maxC;
	
	while(st <= ed) {
		int m = (st+ed)/2;

		for(int i=0;i<N;i++)
			vis[i] = false;

		//int z = dfs(0, T, 0, m, K, 0);
		int z = bfs(0, T, m, K);

		if(z == -1) {// not found
			st = m+1;
		}
		else {
			R = m;
			ed = m-1;
		}
	}
	return R;
}


void add_edge(int u, int v, int w, int e){
	U[e] = u;
	V[e] = v;
	W[e] = w;
	gnext[e] = gfirst[u];
	gfirst[u] = e;
}


int main() {
	int N,M,K,T;

	while(scanf("%d %d %d %d", &N, &M, &K, &T) != EOF) {

		memset(gfirst, -1, sizeof(gfirst));
		T--;
		int e = 0;
		int maxC = 0;
		int minC = INT_MAX;
		for(int i=0;i<M;i++){
			int u,v,w;
			scanf("%d %d %d", &u, &v, &w);
			u--; v--;

			minC = MIN(w, minC);
			maxC = MAX(w, maxC);


			add_edge(u,v,w,e++);
			add_edge(v,u,w,e++);
		}


		int ans = solve(N, M, T, K, minC, maxC);
		printf("%d\n", ans);
	}
	return 0;
}