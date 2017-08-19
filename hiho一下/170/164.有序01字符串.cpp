#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 1000;
int cnt0[maxn+5];
int dp[maxn+5];
int solve(string s) {
    memset(cnt0, 0, sizeof cnt0);
    memset(dp, 0, sizeof dp);
    for (int t = s.size() - 1; t >= 0; --t) {
        cnt0[t] = cnt0[t+1] + (s[t] == '0' ? 1: 0);
    }
    for (int t = s.size() - 1; t >= 0; --t) {
        if (s[t] == '1') {
            dp[t] = min(1 + dp[t+1], cnt0[t+1]);
        } else {
            dp[t] = dp[t+1]; 
        }
    }
    return dp[0];
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        string s;
        cin>>s;
        cout<<solve(s)<<endl;
    }
    return 0;
}