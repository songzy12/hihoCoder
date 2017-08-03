#include<iostream>
#include<cstring>
using namespace std;

const int p = 1e9+7;
const int maxn = 100;

long long dp[maxn+5];

long long pow(int n) {
    if (n == 1)
        return 2;
    long long temp = pow(n >> 1);
    return (temp * temp * (n & 1 ? 2 : 1)) % p;
}

long long get_dp(int n) {
    dp[0] = 1;
    dp[1] = 2;
    for (int i = 2; i <= n; ++i)
        dp[i] = (dp[i-1] + dp[i-2]) % p;
    return dp[n];
}

long long solve(int n) {
    return (p + pow(n) - get_dp(n)) % p;
}

int main() {
    memset(dp, -1, sizeof dp);
    int n;
    cin>>n;
    cout<<solve(n)<<endl;
    return 0;
}