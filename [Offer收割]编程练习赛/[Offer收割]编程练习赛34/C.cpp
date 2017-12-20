#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxn = 2000;
const int maxk = 2000;

double dp[maxn+5][maxk+5];
double suffix[maxn+5][maxn+5];
double prefix[maxn+5];
double A[maxn+5];

int main() {
    int n, K;
    cin>>n>>K;
    for (int i = 0; i < n; ++i)
        cin>>A[i];
    sort(A, A+n);
    
    prefix[0] = 0;
    for (int i = 1; i <= n; ++i)
        prefix[i] = prefix[i-1] + A[i-1];
    
    // prefix[i]: sum(A[:i])
    
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            suffix[i][j] = 0;
            double a = (prefix[j+1] - prefix[i]) / (j+1-i);
            for (int k = i; k <= j; ++k) {
                suffix[i][j] += (a - A[k]) * (a - A[k]);
            }
            //printf("suffix[%d][%d]: %lf\n", i, j, suffix[i][j]);
        }
    }
    
    for (int i = 0; i < n; ++i) {
        dp[i][1] = suffix[0][i];
    }
    
    for (int k = 2; k <= K; ++k) {
        for (int i = 0; i < n; ++i) {
            dp[i][k] = dp[i][k-1];
            for (int j = 0; j < i; ++j) {
                //printf("dp[%d][%d]: %lf, dp[%d][%d]: %lf, suffix[%d][%d]: %lf\n", i, k, dp[i][k], j, k-1, dp[j][k-1], j+1, i, suffix[j+1][i]);
                dp[i][k] = min(dp[i][k], dp[j][k-1]+suffix[j+1][i]);
            }            
        }
    }
    printf("%.3f\n", dp[n-1][K]);
    return 0;
}

// 四边形不等式
// 多邮局选址问题