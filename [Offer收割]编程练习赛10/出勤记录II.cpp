#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int p = 1e9+7;
const int maxn = 100000;
const int maxl = 2;
const int maxa = 1;
long long dp[maxn+1][maxl+1][maxa+1]; 
// dp[n][l][a]: n position left, before that, l continous L, a A

long long compute(int n, int l, int a) {
    if (dp[n][l][a] != 0)
        return dp[n][l][a];
    if (n == 0) {
        return dp[n][l][a] = 1;
    }
    // O
    dp[n][l][a] += compute(n-1, 0, a);
    dp[n][l][a] %= p;
    // A
    if (a > 0) {
        dp[n][l][a] += compute(n-1, 0, a-1);
        dp[n][l][a] %= p;
    }
    // L
    if (l != 2) {
        dp[n][l][a] += compute(n-1, l+1, a);
        dp[n][l][a] %= p;
    }
    return dp[n][l][a];
}

int solve(int n){
   return compute(n, 0, 1);
}

int main() {
    freopen("in.txt", "r", stdin);
    memset(dp, 0, sizeof dp);
    int N;
    cin>>N;
    cout<<solve(N)<<endl;
}