#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int maxn = 100010;
vector<int> a[maxn];
vector<int> g[maxn];
int d[maxn];
bool v[maxn];
int n, m, s, t;

queue<int> q;
void spfa() {
    // shortest path faster algorithm
    d[s] = 0; //source
    q.push(s);
    while (!q.empty()) {
        int k = q.front();
        q.pop();
        v[k] = 1;
        for (int i = 0; i < a[k].size(); ++i) {
            if (d[k] + g[k][i] < d[a[k][i]]) {
                // for points a[k][i] adjacent to k, 
                // what if first go to k, then go to a[k][i]
                d[a[k][i]] = d[k] + g[k][i]; //update any way
                if (!v[a[k][i]]) {
                    // not the current k
                    // not in the queue
                    q.push(a[k][i]);
                    v[a[k][i]] = 1;
                }
            }
        }
        v[k] = 0;
    }
    
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    
    cin>>n>>m>>s>>t;
    for (int i = 1; i <= m; ++i) {
        int x, y, z;
        cin>>x>>y>>z;
        a[x].push_back(y);
        g[x].push_back(z);
        a[y].push_back(x);
        g[y].push_back(z);
    }
    memset(v, 0, sizeof v);
    memset(d, 0x3f, sizeof d); // 0011 1111
    spfa();
    cout<<d[t]<<endl;
}