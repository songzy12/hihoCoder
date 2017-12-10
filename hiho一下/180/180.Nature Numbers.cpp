// http://hihocoder.com/contest/hiho180/problem/1

#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

int solve(long long n, int k) {
    vector<int> prefix;
    
    long long current = 1;
    for (int i = 0; i < k - 1; ++i)
        current *= 10;
    
    n += k * current;
    
    while (current) {
        prefix.push_back(n / (k * current));
        n %= k * current;
        current /= 10;
    }
    if (n == 0)
        return prefix[prefix.size() - 1];
    else 
        return prefix[n - 1];
}

int solve(long long n) {
    if (n < 10)
        return n;
    
    int k = 1;
    long long power_10 = 1;
    
    while (n > k * (power_10 * 10 - power_10)) {
        n -= k * (power_10 * 10 - power_10);
        k += 1;
        power_10 *= 10;
    }
    return solve(n, k);
}

int main() {
    // freopen("in.txt", "r", stdin);
    long long n;
    cin>>n;
    cout<<solve(n) <<endl;
    return 0;
}

// first compute which width part n is in.
// then compute (n_, w)