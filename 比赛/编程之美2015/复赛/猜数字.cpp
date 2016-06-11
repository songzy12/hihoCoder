#include <cstdio>
#include <cstring>
#include <climits>
#include <utility>
#include <vector>
#include <algorithm>

const int N = 200000;

int n, q, a[N], l[N], r[N], k[N], result[N], maximum[N << 1];

int get_id(int l, int r)
{
    return l + r | l != r; // m = l + r >> 1;
}

void insert(int l, int r, int k, int v)
{
    if (l <= k && k <= r) {
        int id = get_id(l, r);
        maximum[id] = std::max(maximum[id], v); 
		// maximum of [l, r]
        if (l < r) {
            int m = l + r >> 1;
            insert(l, m, k, v);
            insert(m + 1, r, k, v);
        }
    }
}

int query(int l, int r, int a, int b)
{
    if (b < l || r < a) {
        return INT_MIN;
    }
    if (a <= l && r <= b) {
        return maximum[get_id(l, r)];
    }
    int m = l + r >> 1;
    return std::max(query(l, m, a, b), query(m + 1, r, a, b));
}

void solve()
{
    std::vector <std::pair <int, int>> events;
    for (int i = 0; i < n; ++ i) {
        events.push_back({a[i], i});
    }
    for (int i = 0; i < q; ++ i) {
        events.push_back({k[i], n + i});
    }
    std::sort(events.begin(), events.end());
    for (int i = 0; i < n << 1; ++ i) {
        maximum[i] = INT_MIN;
    }
    for (const auto &e : events) {
        if (e.second < n) {
            insert(0, n - 1, e.second, e.first);
        } else {
            int i = e.second - n;
            int m = query(0, n - 1, l[i], r[i]);
			// by now all inserted <= k[i]
            if (m != INT_MIN) {
                result[i] = std::min(result[i], k[i] - m);
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++ t) {
        scanf("%d%d", &n, &q);
        for (int i = 0; i < n; ++ i) {
            scanf("%d", a + i);
        }
        for (int i = 0; i < q; ++ i) {
            scanf("%d%d%d", l + i, r + i, k + i);
            l[i] --;
            r[i] --;
        }
        for (int i = 0; i < q; ++ i) {
            result[i] = INT_MAX;
        }
        solve();
        for (int i = 0; i < n; ++ i) {
            a[i] *= -1;
        }
        for (int i = 0; i < q; ++ i) {
            k[i] *= -1;
        }
        solve();
        printf("Case #%d:\n", t);
        for (int i = 0; i < q; ++ i) {
            printf("%d\n", result[i]);
        }
    }
    return 0;
}
