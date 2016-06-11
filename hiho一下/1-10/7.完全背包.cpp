#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int need[100000], favor[100000], _left[100000+1];

int main(){
	int n, m;
	cin>>n>>m;
	for(int i = 0; i < n; ++i)
		cin>>need[i]>>favor[i];
	memset(_left, 0, sizeof _left);
	for(int i = 0; i < n; ++i)
		for(int j = need[i]; j <= m; j
		// when we have j tickets, max value got from first i gift
		// normal order: we need new front value when compute back
			_left[j] = max(_left[j], _left[j-need[i]] + favor[i]);
		// in complete knapsack, _left[j] is the max value got from first i gift with j tickets
		// while in 01 knapsack, _left[j] is the max value got from first i-1 gift with j tickets
	int ans = 0;
	for(int i = 0; i <= m; ++i)
		ans = max(ans, _left[i]);
	cout<<ans<<endl;
	return 0;
}