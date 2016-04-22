#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int need[100000], favor[100000], left_[100000+1];

int main(){
	int n, m;
	cin>>n>>m;
	for(int i = 0; i < n; ++i)
		cin>>need[i]>>favor[i];
	memset(left_, 0, sizeof left_);
	for(int i = 0; i < n; ++i)
		for(int j = m; j >= need[i]; j--)
		// reverse order: we need old front value when compute back
			left_[j] = max(left_[j], left_[j-need[i]] + favor[i]);
	int ans = 0;
	for(int i = 0; i < m; ++i)
		ans = max(ans, left_[i]);
	cout<<ans<<endl;
	return 0;
}