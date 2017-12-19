#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 100000;
const int MAXM = 500000;
const int MOD = 142857;
int head[100001];
int p[500001];
int next_[500001];
int degree[100001];
int edgecnt;
int virus[1000001];

void addedge(int u, int v){
	++edgecnt;
	p [edgecnt] = v;
	next_[edgecnt] = head[u];
	head[u] = edgecnt;
	degree[v]++;
}

vector<int> queue;

int main(){
	memset(degree, 0, sizeof(degree));
	memset(head, 0, sizeof(head));
	memset(next_, 0, sizeof(next_));
	memset(virus, 0, sizeof(virus));
	int N, M, K;
	cin>>N>>M>>K;
	for(int i=0; i<K; i++){
		int a;
		cin>>a;
		virus[a] = 1;
	}
	edgecnt = 0;
	for(int i=0; i<M; i++){
		int u, v;
		cin>>u>>v;
		addedge(u,v);
	}
	int count = 0;
	queue.clear();
	for(int i=1; i<=N; i++)
		if(degree[i]==0)
			queue.push_back(i);
	while(queue.size()){
		int u = queue.back();
		queue.pop_back();
		count = (virus[u] + count) % MOD;
		if(!queue.size() && head[u]==0){
			cout<<count<<endl;
			break;
		}
		for(int i=head[u]; i; i = next_[i]){
			int v = p[i];
			degree[v]--;
			virus[v] = (virus[v] + virus[u]) % MOD;
			if(degree[v]==0)
				queue.push_back(v);
		}
	}
	return 0;
}