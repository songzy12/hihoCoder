#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

constexpr int MOD = 1e9 + 7;
constexpr int MAXN = 1e6 + 1e5;
constexpr int dirs[] = {-1, 0, 1, 0, -1};

int N, M, K, Q;

int pa[MAXN];
int mat[1020][1020];

int find(int u) {
    if (pa[u] == u)
        return u;
    return pa[u] = find(pa[u]);
}

void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u > v)
        swap(u, v);
    pa[v] = u;
}

int main() {
    // freopen("in.txt", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> N;
    int a, b;
    int cur = 0;
    for (int i = 0; i < MAXN; i++)
        pa[i] = i;
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        a++, b++;
        mat[a][b] = 1;
        int t[4] = {-1, -1, -1, -1};
        bool all_empty = true;
        for (int d = 0; d < 4; d++) {
            int xx = a + dirs[d];
            int yy = b + dirs[d+1];
            if (mat[a+dirs[d]][b+dirs[d+1]] == 1) {
                all_empty = false;
                t[d] = xx * 1001 + yy;
            }
        }
        if (all_empty) {
            cur += 1;
            cout << cur << '\n';
            continue;
        }
        sort(t, t+4);
        merge(t[3], a * 1001 + b);
        for (int j = 2; j >= 0; j--) {
            if (t[j] != -1) {
                t[3] = find(t[3]);
                t[j] = find(t[j]);
                if (t[3] != t[j]) {
                    merge(t[3], t[j]);
                    cur -= 1;
                }
            }
            else
                break;
        }
        cout << cur << '\n';
    }
    return 0;
}
