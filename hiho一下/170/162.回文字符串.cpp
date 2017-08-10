#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 100;

int dp[maxn][maxn];
string s;

int get_dp(int i, int j) {
    if (dp[i][j] != -1)
        return dp[i][j];
    if (i == j)
        return dp[i][j] = 0;
    if (i > j)
        return dp[i][j] = 0;
    if (s[i] == s[j])
        return get_dp(i+1,j-1);
    int temp = get_dp(i+1, j-1);
    temp = min(temp, get_dp(i, j-1));
    temp = min(temp, get_dp(i+1, j));
    return dp[i][j] = temp+1;
}

int solve(string s) {
    memset(dp, -1, sizeof dp);
    return get_dp(0, s.size()-1);
}

int main() {
    cin>>s;
    cout<<solve(s)<<endl;
    return 0;
}