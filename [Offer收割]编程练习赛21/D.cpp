#include <map>
#include <cmath>
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 100000 + 10;
const int MAXM = 1000 + 10;
const int MOD = 1000000007;
int N, M, A[MAXN];
long long ret;
long long CX[MAXM], CY[MAXM];

void input_data()
{
    scanf("%d%d", &N, &M);
    for (int i = 0; i < N; i ++) {
        scanf("%d", &A[i]);
    }
}

long long calc_pow(int x, int y) {
    if (y == 0) return 1LL;
    long long z = calc_pow(x, y / 2);
    z = z * z % MOD;
    if (y & 1) z = z * x % MOD;
    return z;
}

long long calc(int x, int y) {
    long long ret = 0;
    CX[0] = CY[0] = 1;
    for (int i = 1; i <= M; i ++) {
        CX[i] = CX[i - 1] * (x - i + 1) % MOD;
        CX[i] = CX[i] * calc_pow(i, MOD - 2) % MOD;
        CY[i] = CY[i - 1] * (y - i + 1) % MOD;
        CY[i] = CY[i] * calc_pow(i, MOD - 2) % MOD;
    }
    for (int i = 1; i <= M; i ++) {
        ret += CY[i] * CX[M - i];
        ret %= MOD;
    }
    //printf("%d %d %lld\n", x, y, ret);
    return ret;
}

void solve()
{
    int cnt[2];
    ret = 0;
    for (int i = 0; i < 20; i ++) {
        cnt[0] = cnt[1] = 0;
        for (int j = 0; j < N; j ++) {
            cnt[(A[j]>>i)&1] ++;
        }
        //printf("%lld ", calc(cnt[0], cnt[1]) << i);
        ret += calc(cnt[0], cnt[1]) << i;
        ret %= MOD;
    }
}

void output_result()
{
    printf("%lld\n", ret);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    int Test = 1;
    scanf("%d", &Test);
    while (Test --) {
        input_data();
        solve();
        output_result();
    }
    return 0;
}
