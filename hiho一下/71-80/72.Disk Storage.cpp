#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<cstdio>
#include<climits>
#include<cmath>
#include<cstring>

using namespace std;

const int maxn = 100000;
int r[maxn];

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    int n, m, h, r_;
    cin>>n>>m>>h>>r_;
    for (int i = 0; i < n; ++i)
        cin>>r[i];
    sort(r, r + n);
    
    int s = 0;
    int ans = min(h, n); // if no break
    for (int i = 0; i < n; ++i) {
        if (i && r[i] - r[i-1] > m) // i > 0
            s = 0;
        if (r[i] > r_ + s) {
            ans = min(i, h);
            break;
        }
        s++;
    }
    cout<<ans<<endl;
	return 0;
}