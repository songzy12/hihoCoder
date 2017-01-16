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
int group[MAXN*2+5];

int query(int i){
	while(group[i] != i){
		group[i] = group[group[i]];
		i = group[i];
	}
	return i;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int N;
	cin>>N;
	int op;
	string name1, name2;
	map<string, int> id;
	int total = 1;
	for(int i = 0; i < MAXN*2+5; ++i)
		group[i] = i;
		
	while(N--){
		cin>>op>>name1>>name2;
		if(op){
			// name1 == name2
			if(name1 == name2){
				cout<<"yes"<<endl;
				continue;
			}
			if(!id.count(name1) || !id.count(name2)){
				cout<<"no"<<endl;
				continue;
			}
			if(query(id[name1]) == query(id[name2])){
				cout<<"yes"<<endl;
			}else{
				cout<<"no"<<endl;
			}
		}else{
			if(!id.count(name1)){
				id[name1] = total;
				total++;
			}
			if(!id.count(name2)){
				id[name2] = total;
				total++;
			}
			// group[id[name1]] = group[id[name2]];
			group[query(id[name1])] = query(id[name2]);
		}
	}
	return 0;
}