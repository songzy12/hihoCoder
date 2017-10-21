// BIT: this is a new knowledge point

#include<iostream>
#include<cstdio>
using namespace std;

const int maxn = 1000;
int N;

long long BIT2[maxn+5][maxn+5];
long long p = 1e9+7;

int lowbit(int x) {
    return x & (-x);
}

void add(int x, int y, long long val) {
    for(int i = x; i <= N; i += lowbit(i)) {
        for(int j = y; j <= N; j += lowbit(j)) {
            BIT2[i][j] += val;
            BIT2[i][j] %= p;
        }
    }
}

long long sum(long long x, long long y) {
    int ret = 0;
    for(int i = x; i > 0; i -= lowbit(i)) {
        for(int j = y; j > 0; j -= lowbit(j)) {
            ret += BIT2[i][j];
            ret %= p;
        }
    }
    return ret;
}

int main() {
    int m;
    cin>>N>>m;
    for (int i = 0; i < m; ++i) {
        string op;
        cin>>op;
        if (op[0] == 'A') {
            int x, y, val;
            cin>>x>>y>>val;
            add(x + 1, y + 1, val);
        } else {
            int x1, y1, x2, y2;
            cin>>x2>>y2>>x1>>y1;
            cout<<(p + sum(x1 + 1, y1 + 1) - sum(x1 + 1, y2) - sum(x2, y1 + 1) + sum(x2, y2)) % p<<endl;
        }
    }
    return 0;
}