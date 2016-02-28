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

const int MAX_N = 10000;
const int MAX_WEIGHT = 10000;
int weight[MAX_N + 5];

int compute(int L, int R) {
    int ans = MAX_WEIGHT;
    for (int i = L; i <= R; ++i) 
        if (weight[i] < ans)
            ans = weight[i];
    return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        scanf("%d", &weight[i]);
    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int op;
        scanf("%d", &op);
        if (op) {
            int P, W;
            scanf("%d %d", &P, &W);
            weight[P-1] = W;
        } else {
            int L, R;
            scanf("%d %d", &L, &R);
            printf("%d\n", compute(L - 1, R - 1));
        }
    }
	return 0;
}