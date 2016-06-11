#include<iostream>
#include<vector>
#include<cstring>
#include<cstdlib>
using namespace std;

const int maxn = 100005;
struct Node{
	vector<int> neigh;
	vector<int> son;
}nodes[maxn];
int father[maxn];
int cargo[maxn];
int cargo2[maxn];

void add(int x, int y){
	nodes[x].neigh.push_back(y);
	nodes[y].neigh.push_back(x);
}

void dfs(int x){
	nodes[x].son.clear();
	for(int i=0; i<nodes[x].neigh.size(); i++){
		int temp = nodes[x].neigh[i];
		if(temp!=father[x]){
			nodes[x].son.push_back(temp);
			father[temp] = x;
			dfs(temp);
		}
	}
}

int set_cargo2(int s){
	if(cargo2[s]!=-1)
		return cargo2[s];
	int temp = cargo[s];
	for (int i=0; i<nodes[s].son.size(); i++)
		temp += set_cargo2(nodes[s].son[i]);
	cargo2[s] = temp;
	return temp;
}

int cost(int x, int s){
	int max = 0;
	if (x!=s)
		return cargo2[x];
	for(int i=0; i<nodes[x].son.size(); i++){
		int temp = cost(nodes[x].son[i], s);
		//cout<<"x: "<<x<<" son: "<<nodes[x].son[i]<<" temp: "<< temp<<endl;
		if(temp > max)
			max = temp;
	}
	return max;
}

void solve(int t){
	memset(father, 0, sizeof(father));
	int n, s;
	cin>>n>>s;
	for(int i=1; i<=n; i++)
		nodes[i].neigh.clear();
	for(int i=0; i< n-1; i++){
		int x, y;
		cin>>x>>y;
		add(x, y);
	}
	for(int i=1; i<=n; i++){
		cin>>cargo[i];
	}
	dfs(s);
	memset(cargo2, -1, sizeof(cargo2));	
	set_cargo2(s);
	/*for(int i=1; i<=n; i++)
		cout<<cargo2[i]<<endl;*/
	cout<<"Case #"<<t<<": "<<cost(s, s)<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
		solve(t);
	return 0;
}