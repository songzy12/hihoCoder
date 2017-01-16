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
int a[100][100], best[100];
int main(){
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n;
	cin>>n;
	for(int i=0; i<n; ++i)
		for(int j=0; j<=i; ++j)
			cin>>a[i][j];
	for(int i=0; i<n; ++i)
		best[i] = a[n-1][i];
	for(int i=n-2; i>=0; --i)
		for(int j=0; j<=i; ++j)
			best[j] = a[i][j] + max(best[j], best[j+1]);
	cout<<best[0]<<endl;
	return 0;
}