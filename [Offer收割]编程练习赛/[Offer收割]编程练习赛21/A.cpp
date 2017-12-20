#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxn = 1e5;
const int p = 1e9+7;

long long k;
long long A[maxn];

long long _pow[maxn+1];

void init() {
    _pow[0] = 1;
    for (int i = 1; i <= maxn; ++i)
        _pow[i] = (_pow[i-1] * 2) % p;
}

int main() {
    int n;
    cin>>n>>k;
    for (int i = 0; i < n; ++i)
        cin>>A[i];
    sort(A, A+n);
    init();
    int head = 0, tail = n - 1;
    long long ans = 0;
    while (head <= tail) {
        while (head <= tail && A[head] + A[tail] > k)
            tail--;
        if (head > tail)
            break;
        //printf("head: %d, tail: %d\n", head, tail);
        int count = tail - head;
        ans = (ans + _pow[count]) % p;
        head ++;
    }
    cout<<ans<<endl;
}