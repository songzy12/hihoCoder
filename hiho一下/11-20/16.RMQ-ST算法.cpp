#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;
// constant weight
// min rather than sum
// TLE: 1876ms vs 528ms
// convert cin, cout to scanf, printf
const int MAXN = 1000000;
const int MAXL = 20;
//int pre_calc[MAXN][MAXL];
int pre_calc[MAXL][MAXN];

int log2(int n) {
	int res = -1;
	while(n) {
		res ++;
		n >>= 1;
	}
	return res;
}

void compute(int n){
	int len = log2(n);
	for(int i = 1; i <= len; ++i) {
		int ll = n - (1<<i); // don't repeat yourself
		for(int j = 0; j <= ll; ++j) {
			//pre_calc[j][i] = min(pre_calc[j][i-1], pre_calc[j+(1<<(i-1))][i-1]);
			pre_calc[i][j] = min(pre_calc[i-1][j], pre_calc[i-1][j+(1<<(i-1))]);
		}
	}
}

int main(){

#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n, q, i = 0; 
	scanf("%d", &n);
	//for(int i = 0; i < n; ++i)
	while(i < n){
		// 2**0 = 1
		//cin>>pre_calc[i][0];
		//cin>>pre_calc[0][i++];
		scanf("%d", &pre_calc[0][i++]);
	}
	compute(n);
	//cin>>q;
	scanf("%d", &q);
	int l, r;
	//for(int i = 0; i < q; ++i) {
	while(q--){
		//cin>>l>>r;
		scanf("%d %d", &l, &r);
		int j = log2(r-l+1);
		// off by one, 1<=Li<=Ri<=N
		//cout<<min(pre_calc[l-1][j], pre_calc[r-(1<<j)][j])<<endl;
		//cout<<min(pre_calc[j][l-1], pre_calc[j][r-(1<<j)])<<endl;
		printf("%d\n", min(pre_calc[j][l-1], pre_calc[j][r-(1<<j)]));
	}
	return 0;
}