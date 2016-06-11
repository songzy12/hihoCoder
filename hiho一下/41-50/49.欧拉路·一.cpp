#include<iostream>
#include<cstdio>
#define SZY
using namespace std;
// connected!
int node[10001];
int main(){
#ifdef SZY
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int N, M;
	cin>>N>>M;
	int u,v;
	fill(node, node+N+1, 0);
	for(int i=1; i<=M; i++){
		cin>>u>>v;
		node[u] ++;
		node[v] ++;
	}
	int count = 0;
	for(int i=1; i<=N; i++)
		if(node[i] % 2)
			count += 1;
	if (count == 0 || count == 2)
		cout<<"Full"<<endl;
	else
		cout<<"Part"<<endl;
	return 0;
}