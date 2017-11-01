#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 100, maxm = 600;

double dp[maxn+5][maxm+5];

double solve(int n, int m) {
    // denominator: 6**n 
    // numerator: a_1 + \dots + a_n = m, 1 <= a_i <= 6
    
    // it can be solved using dp: dp[i][j] for ways to sum m using n
    
    // dp[n][m] = (dp[n-1][m-1] + ... + dp[n-1, m-6]) / 6
    
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == 0) {
                dp[i][j] = 0;
                continue;
            }
            if (i == 1) {
                dp[i][j] = (j >= 1 && j <= 6) ? 1 / 6.0 : 0;
                continue;
            }
            for (int k = 1; k <= 6; ++k) {
                if (j - k <= 0)
                    break;
                dp[i][j] += dp[i-1][j-k];
            }
            dp[i][j] /= 6.0;
        }
    }
    return dp[n][m];
}

int main() {
    int n, m;
    cin>>n>>m;
    printf("%.2f\n", solve(n, m) * 100);
    return 0;
}