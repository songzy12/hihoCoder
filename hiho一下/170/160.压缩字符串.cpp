//设S[1..n]是一个长度为n的字符串，best(S)是S的最短压缩，那么best(S)可能为三种形式中最短的一种：
//1) 原串形式：best(S) = S。例如CCD最短压缩就是CCD本身。
//2) 拼接形式： best(S[1..n]) = best(S[1..i]) + best(S[i+1..n])。
//3) 嵌套形式： best(S[1..n]) = k的位数 + 2 + best(S[1..n/k])，其中k>1且是n的约数，S是由k个S[1..n/k]循环拼接而成。
//也就是说S[1..n]可以表示成k(s[1..n/k])，这时k(s[1..n/k])的长度是k的位数 + 一对括号的长度2 + best(S[1..n/k)

#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxl = 100;

int dp[maxl+1][maxl+1];

string s;

bool check(int k, int l, int r) {
    // where s can be viewed as a part repeated for k times.
    if ((r - l + 1) % k != 0)
        return false;
    int t = (r - l + 1) / k; // each length is t
    for (int i = 0; i < t; ++i) {
        for (int j = 1; j < k; ++j) {
            if (s[l + j*t + i] != s[l + i]) // l + i !!!!!
                return false;
        }
    }
    return true;
}

int len(int k) {
    int len = 0;
    while (k) {
        len++;
        k /= 10;
    }
    return len;
}

int get_dp(int l, int r) {
    // the minimum from l to r
    if (dp[l][r] != -1)
        return dp[l][r];
    if (l > r)
        return dp[l][r] = 0;
    if (l == r)
        return dp[l][r] = 1;
    int ans = r - l + 1; // origin
    for (int i = l; i < r; ++i) {
        int temp = get_dp(l,i)+get_dp(i+1,r); // partiton of (l,i) and (i+1,r)
        if (temp < ans) {
            ans = temp;
        }
    }
    for (int k = 2; k <= r - l + 1; ++k) { 
        // k == r - l + 1 is also ok
        if (check(k, l, r)) {
            int temp = 2 + get_dp(l, l + (r - l + 1) / k - 1) + len(k);
            if (temp < ans) {
                ans = temp;
            }
        }
    }

    return dp[l][r] = ans;
}

int solve() {
    memset(dp, -1, sizeof dp);
    return get_dp(0, s.size()-1);
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        cin>>s;
        cout<<solve()<<endl;
    }
} 