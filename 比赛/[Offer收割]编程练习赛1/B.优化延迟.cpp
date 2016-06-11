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

int P[100005];

long long penalty(int buffer_size, int N) {
    vector<int> buffer;
    long long ans = 0, temp;
    if (!buffer_size) {
        for (int i = 1; i <= N; ++i)
            ans += i * P[i];
        return ans;
    }
    for (int i = 1; i <= buffer_size; ++i) {
        buffer.push_back(P[i]);
    }
    make_heap(buffer.begin(), buffer.end());
    for (int i = buffer_size + 1; i <= N; ++i) {
        pop_heap(buffer.begin(), buffer.end());
        temp = buffer.back();
        ans += temp * (i - buffer_size);
        buffer.pop_back();
        buffer.push_back(P[i]);
        push_heap(buffer.begin(), buffer.end());
    }
    for (int i = N - buffer_size + 1; i <= N; ++i) {
        pop_heap(buffer.begin(), buffer.end());
        temp = buffer.back();
        ans += temp * i;
        buffer.pop_back();
    }
    return ans;
}

int binary_search(int left, int right, long long Q, int N) {
    while (left < right) {
        int middle = (left + right) >> 1;
        if (penalty(middle, N) > Q) 
            left = middle + 1;
        else 
            right = middle;
    }
    return left;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	long long N, Q; // 1 <= Q <= 1013
    cin>>N>>Q;
    for (int i = 1; i <= N; ++i) {
        cin>>P[i];
    }
    if (penalty(N, N) > Q)
        cout<<-1<<endl;
    else 
        cout<<binary_search(1, N, Q, N)<<endl;
	return 0;
}