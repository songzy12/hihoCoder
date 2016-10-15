#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
#define NIL 0
#define SZY

const int MAXN = 20000;
const int MAXM = 100000;

int head[MAXN+1];
int p[2*MAXM+1], next_[2*MAXM+1];
static int edgecnt = 0;

void addedge(int u, int v){
	++edgecnt;
	p [edgecnt] = v; 
	next_[edgecnt] = head[u];
	head[u] = edgecnt;
}

int visit[MAXN+1], dfn[MAXN+1], low[MAXN+1], parent[MAXN+1];

int articulation[MAXN+1];
static int n_node = 0;
pair<int, int> bridge[MAXM+1];
static int n_edge = 0;

bool cmp(pair<int, int> u, pair<int, int> v){
	if(u.first != v.first)
		return u.first < v.first;
	return u.second < v.second;
}

void dfs(int u) {
	//记录dfs遍历次序
	static int counter = 0;	
	//记录节点u的子树数
	int children = 0;
	visit[u] = 1;
	//初始化dfn与low
	dfn[u] = low[u] = ++counter;
	for(int i = head[u]; i; i = next_[i]) {
		int v = p[i];
		//节点v未被访问，则(u,v)为树边
		if(!visit[v]) {
			children++;
			parent[v] = u;
			dfs(v);
			low[u] = min(low[u], low[v]);
			//case (1)
			if(parent[u] == NIL && children > 1) {
				articulation[u] = 1;
				n_node ++;
				//printf("articulation point: %d\n", u);
			}
			//case (2)
			if(parent[u] != NIL && low[v] >= dfn[u]) {
				articulation[u] = 1;
				n_node ++;
				//printf("articulation point: %d\n", u);
			}
			//bridge
			if(low[v] > dfn[u]) {
				bridge[n_edge++]= u < v ? pair<int, int>(u, v) : pair<int, int>(v, u);
				//printf("bridge: %d %d\n", u, v);
			}
		}
		//节点v已访问，则(u,v)为回边
		else if(v != parent[u]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int main(){
#ifdef SZY
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int N, M;
	cin>>N>>M;
	for(int m = 0; m < M; m++){
		int u, v;
		cin>>u>>v;
		addedge(u, v);
		addedge(v, u);
	}
	dfs(1);
	sort(bridge, bridge + n_edge, cmp);
	if (n_node != 0)
		for(int i=1; i<=N; i++){
			if(articulation[i])
				cout<<i<<" ";
		}
	else
		cout<<"Null";
	cout<<endl;
	for(int i=0; i<n_edge; i++)
		cout<<bridge[i].first<<" "<<bridge[i].second<<endl;
	return 0;
}