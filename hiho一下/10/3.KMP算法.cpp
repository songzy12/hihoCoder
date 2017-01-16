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
#define DEBUG
using namespace std;
const int MAXP = 1e4;
int next_[MAXP+1];

int get_next(string p){
	int len = p.size();
	int j = 0;
	next_[0] = next_[1] = 0; // length prefix && suffix of p[:i]
	for(int i = 1; i <= len; ++i){
		while(j > 0 && p[i] != p[j]) // j is next_[i]
			j = next_[j];
		if(p[i] == p[j]) // if not, then j = 0
			j++; // next_ time, just start from j
        next_[i+1]=j;
	}
}

int match(string p, string t){
	get_next(p);
	int j = 0, ans = 0;
	for(int i = 0; i < t.size(); ++i){
		while(j > 0 && t[i] != p[j])
			j = next_[j];
		if(t[i] == p[j])
			j ++; // j is current length of matched pattern
		if(j == p.size()){
			ans ++;
			j = next_[j];
		}
	}
	return ans;
}

int main(){
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	while(n--){
		string p, t;
		cin>>p>>t;
		cout<<match(p, t)<<endl;
	}
	return 0;
}