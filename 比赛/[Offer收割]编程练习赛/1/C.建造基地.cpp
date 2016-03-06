#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

int N, M, K, T;
int A[100], B[100], A_[100], B_[100];
map<int, long long> cache;

bool possible() {
    int temp;
    for (int i = 0; i < M; ++i) {
        temp = B[i];
        for (int i = 0 ; i < N - 1; ++i) {
            if (temp == 0)
                break;
            temp /= T;
        }
        if (temp > 0)
            return true;
    }
    return false;
}

long long dp(int target, int current, int k) {
    if (target <= 0)
        return current;
    if (cache.find(target) != cache.end()){
        return cache[target];
    }
    long long ans = 9223372036854775807;
    for (int i = 0; i < k; ++i) {
        ans = min(ans, dp(target - B_[i], current + A_[i], k));
    }
    cache[target] = ans;
    return ans;
}

long long compute() {
    // A: cost, B: build, K: target
    // min sum cost, s.t. sum build >= target
    int k = 0;
    cache.clear();
    for (int i = 0; i < M; ++i)
        if (B[i] > 0) {
            A_[k] = A[i];
            B_[k++] = B[i];
        }
    // k is the size of B_ now
    long long ans = dp(K, 0, k);
    
    for (int i = 0; i < M; ++i)
        B[i] /= T;
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int Q;
    cin>>Q;
    while (Q--) {
        cin>>N>>M>>K>>T;
        for (int i = 0; i < M; ++i)
            cin>>A[i];
        for (int i = 0; i < M; ++i)
            cin>>B[i];
        if (!possible())
            cout<<"No Answer"<<endl;
        else {
            long long ans = 0;
            for (int i = 1; i <= N; ++i)
                ans += compute();
            cout<<ans<<endl;
        }
    }
	return 0;
}