#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
#define SZY
// what about new and delete?
int index;
int path[1<<15];
vector<int> m[1<<15];

void dfs(int node){
	for(int i=0; i<2; i++){
		int temp = m[node][i];
		if (temp!=-1){
			m[node][i] = -1;
			dfs(temp);
		}
	}
	path[index ++] = node & 1;
	return;
}
int main(){
#ifdef SZY
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif 
	int N;
	cin >> N;
	for(int i=0; i<(1<<(N-1));i++){
		m[i].push_back(((i & ((1<<(N-2))-1))<<1)+1);
		m[i].push_back((i & ((1<<(N-2))-1))<<1);
	}
	/*for(int i=0; i<(1<<(N-1)); i++)
		cout<<i<<" "<<m[i][0]<<" "<<m[i][1]<<endl;*/
	index = 0;
	dfs(0);
	for(int i=0; i<N-1; i++)
		path[index++] = 0;
	for(int i=0; i<(1<<N); i++)
		cout<<path[i];
	cout<<endl;
	return 0;
}