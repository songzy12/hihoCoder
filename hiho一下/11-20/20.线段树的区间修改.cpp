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
int weight[MAXN+5];
int tree[MAXN << 2];
int lazy[MAXN << 2];
int L, R, sum, W;

int build(int o, int lc, int rc) {
    // tree[o] corresponds to weight[lc..rc]
    if (lc == rc) {
        lazy[o] = -1;
        return tree[o] = weight[lc];
    } 
    int mid = (lc + rc) >> 1; 
    int ll = build(o * 2 + 1, lc , mid);
    int rr = build(o * 2 + 2, mid + 1, rc);
    lazy[o] = -1;
    return tree[o] = ll + rr;
}

void query(int o, int lc, int rc) {
    if (L <= lc && rc <= R) {
        sum += tree[o];
    } else {
        int mid = (lc + rc) >> 1;
        if (lazy[o] != -1) {
            lazy[2 * o + 1] = lazy[o];
            tree[2 * o + 1] = (mid - lc + 1) * lazy[o];
            
            lazy[2 * o + 2] = lazy[o];
            tree[2 * o + 2] = (rc - mid) * lazy[o];
            
            lazy[o] = -1;
        }
        if (L <= mid) 
            query(o * 2 + 1, lc, mid);
        if (mid + 1 <= R) 
            query(o * 2 + 2, mid + 1, rc);
    }
}

void update(int o, int lc, int rc) {
    if (L <= lc && rc <= R) {
        lazy[o] = W;
        tree[o] = (rc - lc + 1) * W;
    } else {
        int mid = (lc + rc) >> 1;
        if (lazy[o] != -1) {
            lazy[2 * o + 1] = lazy[o];
            tree[2 * o + 1] = (mid - lc + 1) * lazy[o];
            
            lazy[2 * o + 2] = lazy[o];
            tree[2 * o + 2] = (rc - mid) * lazy[o];
            
            lazy[o] = -1;
        }
        if(L <= mid) update(o * 2 + 1, lc, mid);
		if(mid + 1 <= R) update(o * 2 + 2, mid + 1, rc);
		tree[o] = tree[o * 2 + 1] + tree[o * 2 + 2];
    }
}

void print_weight(int n) {
    for (int i = 1; i <= n; ++i) 
        cout<<weight[i]<<" ";
    cout<<endl;
}

void print_tree(int n) {
    for (int i = 0; i <= 2 * n; ++i)
        cout<<tree[i]<<" ";
    cout<<endl;
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
    //print_weight(N);
    build(0, 1, N);
    //print_tree(N);
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int op;
        scanf("%d", &op);
        if (op) {
            scanf("%d %d %d", &L, &R, &W);
            update(0, 1, N);
            //print_tree(N);
        } else {
            scanf("%d %d", &L, &R);
            sum = 0;
            query(0, 1, N);
            printf("%d\n", sum);
        }
    }
	return 0;
}