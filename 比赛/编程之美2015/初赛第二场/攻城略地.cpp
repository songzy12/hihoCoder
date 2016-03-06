#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <cstring>
using namespace std;

typedef unsigned long long ULL;

int n, m, k;
ULL w[1000010];
int color[1000010], C;
vector<list<int> > graph;
map<ULL, int> count_;
ULL ans;

void color_graph()
{
    C = 0;
    memset(color, 0, sizeof(color));
    for (int i = 0; i < n; ++i) {
        if (color[i] == 0) {
            ++C;
            ULL minWeight = 0x7FFFFFFF;
            queue<int> que;
            que.push(i);
            while (!que.empty()) {
                int now = que.front();
                if (w[now] < minWeight)
                    minWeight = w[now];
                que.pop();
                for (list<int>::iterator iter = graph[now].begin(); iter != graph[now].end(); ++iter) {
                    int next = *iter;
                    if (color[next] == 0) {
                        color[next] = C;
                        que.push(next);
                    }
                }
            }
            ans += minWeight;
            count_[minWeight]--;
        }
    }
}

void Main(int caseNumber)
{
    count_.clear();
    cin >> n >> m >> k;
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
        count_[w[i]]++;
    }
    graph.clear();
    graph.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    ans = 0;
    color_graph();
    if (k > m - (n - C)) {
        int delta = k - (m - (n - C));
        for (map<ULL, int>::iterator iter = count_.begin(); iter != count_.end(); ++iter) {
            if (delta <= iter->second) {
                ans += iter->first * delta;
                break;
            }
            else {
                ans += iter->first * iter->second;
                delta -= iter->second;
            }
        }
    }
    cout << "Case #" << caseNumber << ": " << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i)
        Main(i);
}
