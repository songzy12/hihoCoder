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

const int MAXN = 100;
string name[MAXN+5];
int father[MAXN+5];
map<string, int> all;
bool visited[MAXN+5];

string query(string name1, string name2){
	// name1, name2 may not in map all, but name1 == name2
	if(name1 == name2)
		return name1; 
	memset(visited, false, sizeof visited);
	int num1 = all[name1], num2 = all[name2];
	while(num1){
		visited[num1] = true;
		num1 = father[num1];
	}
	while(num2 && !visited[num2]){
		num2 = father[num2];
	}
	return num2 ? name[num2] : "-1";
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int N;
	cin>>N;
	string Father, Son;
	int id = 1;
	for(int i = 0; i < N; ++i){
		cin>>Father>>Son;
		if(all.count(Father) == 0){
			all[Father] = id;
			name[id] = Father;
			id ++;
		}
		if(all.count(Son) == 0){
			all[Son] = id;
			name[id] = Son;
			id ++;
		}
		father[all[Son]] = all[Father];
	}
	int M;
	cin>>M;
	string name1, name2;
	for(int i = 0; i < M; ++i){
		cin>>name1>>name2;
		cout<<query(name1, name2)<<endl;
	}
	return 0;
}