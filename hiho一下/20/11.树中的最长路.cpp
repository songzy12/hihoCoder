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

const int MAXN = 100000;

int head[MAXN + 5]; // node -> edge
int next_[2*MAXN + 5]; // edge -> edge
int u[2*MAXN + 5], v[2*MAXN + 5]; // edge -> node
int e = 0;

void add_edge(int p, int q){
	u[++e] = p;
	v[e] = q;
	next_[e] = head[p];
	head[p] = e;
}

void read_tree(int N){
	memset(head, 0, sizeof head);
	memset(next_, 0, sizeof next_);
	memset(u, 0, sizeof u);
	memset(v, 0, sizeof v);
	for(int i=0; i<N; ++i){
		int p, q;
		cin>>p>>q;
		add_edge(p, q);
		add_edge(q, p);
	}
}

int longest[MAXN+5], second[MAXN+5];
bool visited[MAXN+5];

void find_longest(int node){
	//cout<<node<<endl;
	int l1 = -1, l2 = -1;
	visited[node] = true;
	for(int e = head[node]; e; e = next_[e]){
		int v_ = v[e];
		if(visited[v_])
			continue;
		find_longest(v_);
		//cout<<v[e]<<" "<<longest[v_]<<" "<<second[v_]<<endl;
		if(longest[v_] > l1){
			l2 = l1;
			l1 = longest[v_];
		}else if(longest[v_] > l2){
			l2 = longest[v_];
		}
	}
	longest[node] = l1 + 1;
	second[node] = l2 + 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int N;
	cin>>N;
	read_tree(N);
	memset(longest, 0, sizeof longest);
	memset(second, 0, sizeof second);
	memset(visited, false, sizeof visited);
	find_longest(1);
	int res = 0;
	for(int i=1; i<=N; ++i){
		if(longest[i] + second[i] > res)
			res = longest[i] + second[i];
	}
	cout<<res<<endl;
	return 0;
}