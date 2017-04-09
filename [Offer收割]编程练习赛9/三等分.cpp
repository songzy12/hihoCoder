// the partition node may be under the same subtree

#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <fstream>
// #include <unordered_set>

using namespace std;

#define FF first
#define SS second
#define MP make_pair
#define PB push_back
#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
#define FOR(i, n, m) for(int i = n; i <= m; i++)
#define REP(i, n, m) for(int i = n; i >= m; i--)
#define ll long long

typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL, LL> PLL;
typedef unsigned long long ULL;

/****************************define***************************************/
const int mod = 1e9 + 7;
const int maxn = 100010;


int n;
int v[maxn], sz[maxn], p[maxn];
vector<int> nd[maxn];
int s;
int cn = 0, cn2 = 0;
ll ans = 0;

void Dfs_sz(int u){
        sz[u] += v[u];
        int t = nd[u].size();
        FOR(i, 0, t-1) {
            Dfs_sz(nd[u][i]);
            sz[u] += sz[nd[u][i]];
            }
        }
void Dfs(int u){
        //printf("node %d. ans %d. cn %d. cn2 %d. sz %d\n", u, ans, cn, cn2, sz[u]);
        if(sz[u] == s/3) {
            ans += cn + cn2;
            //printf("node %d. ans %d\n", u, ans);
            }
        if(p[u] != 0 && sz[u] == s*2/3) cn2++;
        int t = nd[u].size();
        FOR(i, 0, t-1){
            Dfs(nd[u][i]);
            }
        if(sz[u] == s/3) cn++;
        if(p[u] != 0 && sz[u] == s*2/3) cn2--;
        }

int main(){
        int t;
        cin >> t;
        while(t--){
            cn = 0, cn2 = 0;
            s = 0, ans = 0;
            FOR(i, 0, maxn-1) nd[i].clear();
            memset(sz, 0, sizeof(sz));

            int n, root=-1;
            cin >> n;
            FOR(i, 1, n) {
                cin >> v[i] >> p[i];
                s += v[i];
                nd[p[i]].PB(i);
                if(p[i] == 0) root=i;
                }
            if(s % 3 != 0) cout << 0 << endl;
            else{
                Dfs_sz(root);
                Dfs(root);
                printf("%lld\n", ans);
                }
            }
        return 0;
        }
