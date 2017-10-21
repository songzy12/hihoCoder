#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 1000;

int dp[maxn+5][maxn+5];
int num[maxn+5];
int sum[maxn+5];

int get_dp(int i, int j) {
    if (dp[i][j] != -1)
        return dp[i][j];
    if (i == j)
        return dp[i][j] = num[i];
    if (i > j)
        return dp[i][j] = 0;
    dp[i][j] = max(num[i] + sum[j+1] - sum[i+1] - get_dp(i+1,j), 
                   num[j] + sum[j] - sum[i] - get_dp(i, j-1));
    return dp[i][j];
}

int main() {
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
       cin>>num[i]; 
    }
    memset(sum, 0, sizeof sum);
    memset(dp, -1, sizeof dp);
    
    for (int i = 1; i <= n; ++i) {
        sum[i] = sum[i-1] + num[i-1];
    }
    cout<<get_dp(0, n-1)<<endl;
    return 0;
}