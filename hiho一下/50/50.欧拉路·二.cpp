#include<iostream>
#include<cstdio>
#include<cstring> // memset
#define SZY
using namespace std;
// just use adjacency matrix, and care for multi-edges
const int MAXN = 1000;
const int MAXM = 5000;
int G [MAXN+1][MAXN+1]; // keep it simple
int degree[MAXN+1];
int M, N;

void DFS(int u){
	for(int i=1; i<=N; i++){
		if(G[u][i] > 0){ // multi-edge
		//	cout<<u<<" "<<i<<endl;
			G[u][i] --;
			G[i][u] --;
			DFS(i);
		}
	}
	cout<<u<<" "; // algorithm
}

int main(){
#ifdef SZY
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
#endif
	memset(G, 0, sizeof(G));
	memset(degree, 0, sizeof(degree));
	cin>>N>>M;
	for(int i=0; i<M; i++){
		int u, v;
		cin>>u>>v;
		G[u][v]++;
		G[v][u]++;
		degree[u]++;
		degree[v]++;
	}
	int u = 1;
	for(int i=1; i<=N; i++) //not MAXN
		if(degree[i] % 2 == 1){
			u = i;
			break;
		}
	//cout<<"u: "<<u<<endl;
	DFS(u);
	return 0;
}