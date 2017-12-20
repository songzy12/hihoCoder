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
const int p = 1e9+7;

int dfs(int n, int m, int last, int sum, long long mul) {
    if (sum == n) {
        if (mul % m == 0)
            return 1;
        return 0;
    } 
    int cnt = 0;
    for (int i = last + 1; i <= n - sum; ++i) {
        cnt += dfs(n, m, i, sum + i, mul * i);
        cnt %= p;
    }
        
    return cnt;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n, m;
    cin>>n>>m;
    cout<<dfs(n, m, 0, 0, 1)<<endl;
	return 0;
}

/*
gcd(Mul*L, M) = K * gcd(P * L, Q) = K * gcd(L, Q) 
= gcd(K * L, K * Q) = gcd(K * L, M)

f[Sum][Last][Gcd]
*/