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

const int MAXN = 1000000;
const int MAX_WEIGHT = 10000;
int weight[MAXN+5];
int tree[MAXN << 2];
int L, R, mmin, P, W;

int build(int o, int lc, int rc) {
    // tree[o] corresponds to weight[lc..rc]
    if (lc == rc) {
        return tree[o] = weight[lc];
    } 
    int mid = (lc + rc) >> 1;
    int ll = build(o * 2 + 1, lc , mid);
    int rr = build(o * 2 + 2, mid + 1, rc);
    return tree[o] = min(ll, rr);
}

void query(int o, int lc, int rc) {
    if (L <= lc && rc <= R) {
        mmin = min(mmin, tree[o]);
    } else {
        int mid = (lc + rc) >> 1;
        if (L <= mid) 
            query(o * 2 + 1, lc, mid);
        if (mid < R) 
            query(o * 2 + 2, mid + 1, rc);
    }
}

void update(int o, int lc, int rc) {
    if (lc == rc) {
        tree[o] = W;
    } else {
        int mid = (lc + rc) >> 1;
        if(P <= mid) update(o * 2 + 1, lc, mid);
		else update(o * 2 + 2, mid + 1, rc);
		tree[o] = min(tree[o * 2 + 1], tree[o * 2 + 2]);
    }
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
        scanf("%d", &weight[i]);
    build(0, 1, N);
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int op;
        scanf("%d", &op);
        if (op) {
            scanf("%d %d", &P, &W);
            update(0, 1, N);
        } else {
            scanf("%d %d", &L, &R);
            mmin = MAX_WEIGHT;
            query(0, 1, N);
            printf("%d\n", mmin);
        }
    }
	return 0;
}