#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

const int MAXN = 100000;
const int MAXM = 500000;

int head[100001];
int p[500001];
int next_[500001];
int degree[100001];
int edgecnt;

void addedge(int u, int v){
	++edgecnt;
	p [edgecnt] = v;
	next_[edgecnt] = head[u];
	head[u] = edgecnt;
	degree[v]++;
}

vector<int> queue;

int main(){
	int T;
	cin>>T;
	for(int t=1; t<=T; t++){
		memset(degree, 0, sizeof(degree));
		memset(head, 0, sizeof(head));
		memset(next_, 0, sizeof(next_));
		int N, M;
		cin>>N>>M;
		edgecnt = 0;
		for(int i=0; i<M; i++){
			int u, v;
			cin>>u>>v;
			addedge(u,v);
		}
		queue.clear();
		for(int i=1; i<=N; i++)
			if(degree[i]==0)
				queue.push_back(i);
		while(queue.size()){
			int u = queue.back();
			queue.pop_back();
			for(int i=head[u]; i; i=next_[i]){
				int v = p[i];
				degree[v]--;
				if(degree[v]==0)
					queue.push_back(v);
			}
		}
		int i;
		for(i=1; i<=N; i++)
			if(degree[i]>0)
				break;
		if(i==N+1)
			cout<<"Correct"<<endl;
		else
			cout<<"Wrong"<<endl;
	}
	return 0;
}