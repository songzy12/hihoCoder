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

int stack[MAXN+1];
int group[MAXN+1];
int top;

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
	//cout<<u<<" ";
	static int counter = 0;	
	int children = 0;
	visit[u] = 1;
	dfn[u] = low[u] = ++counter;
	
	int temp = top;
	stack[++top] = u;
	
	for(int i = head[u]; i; i = next_[i]) {
		int v = p[i];
		if(!visit[v]) {
			children++;
			parent[v] = u;
			dfs(v);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]) {
				bridge[n_edge++]= u < v ? pair<int, int>(u, v) : pair<int, int>(v, u);
			}
		}
		else if(v != parent[u]) {
			low[u] = min(low[u], dfn[v]);
		}
	}
	//cout<<u<<" "<<low[u]<<" "<<dfn[u]<<endl;
	if(low[u] == dfn[u]){
		sort(stack+temp+1, stack+top+1);
		for(int i = temp + 1; i <= top; i++)
			group[stack[i]] = stack[temp+1];
		top = temp;
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
	top = 0;
	dfs(1);
	//cout<<endl;
	cout<<n_edge + 1<<endl;
	for(int n = 1; n <= N; n++)
		cout<<group[n]<<" ";
	cout<<endl;
	return 0;
}