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
int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	double tax[7] = {0};
	double rate[] = {0.03, 0.1, 0.2, 0.25, 0.3, 0.35, 0.45};
	double base[] = {0, 1500, 4500, 9000, 35000, 55000, 80000};
	for(int i=1; i<7; ++i){
		tax[i] = tax[i-1]+(base[i]-base[i-1])*rate[i-1];
		//cout<<base[i-1]<<"~"<<base[i]<<"("<<rate[i-1]<<"): "<<tax[i]<<endl;
	}
	
	double M;
	cin>>M;
	int ans = 0;
	for(int i=1; i<7; ++i){
		if(M < tax[i]){
			//cout<<M<<"-"<<tax[i-1]<<")/"<<rate[i-1]<<"+"<<base[i-1]<<endl;
			ans = (M - tax[i-1]) / rate[i-1] + base[i-1];
			break;
		}
	}
	if(ans == 0)
		ans = (M - tax[6]) / rate[6] + base[6];
	cout<<ans+3500<<endl;
	return 0;
}