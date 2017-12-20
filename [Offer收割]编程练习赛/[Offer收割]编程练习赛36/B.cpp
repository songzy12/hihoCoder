

#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int maxn = 10000;

int father[maxn*2 + 5];

int neg(int u) {
    return 2 * maxn + u;
}

int union_find(int u) {
    while (father[u] != -1 && father[father[u]] != -1) {
        u = father[u] = father[father[u]];
    }
    if (father[u] != -1)
        u = father[u];
    return u;
}

void union_(int u, int v) {
    if (u > v)
        swap(u, v);
    father[v] = u;
}

bool check(int u, int v, int x) {
    int father_u = union_find(u);
    int father_v = union_find(v);
    int father_neg_u = union_find(neg(u));
    int father_neg_v = union_find(neg(v));
    if (x == 0) {
        if (father_u == father_neg_v || father_v == father_neg_u)
            return false;
        union_(father_u, father_v);
        union_(father_neg_v, father_neg_u);
    } else {
        if (father_u == father_v || father_neg_u == father_neg_v)
            return false;
        union_(father_u, father_neg_v);
        union_(father_v, father_neg_u);
    }
    return true;
}

int main(){
    int t;
    cin>>t;
    while(t--) {
        memset(father, -1, sizeof father);

        int n, m;
        cin>>n>>m;
        bool flag = true;
        int p;
        for (int k = 0; k < m; ++k) {
            int u, v, x;
            cin>>x>>u>>v;
            if (!flag)
                continue;
            if(!check(u, v, x)) {
                flag = false;
                p = k + 1;
            }
        }
        if (flag) {
            cout<<"great"<<endl;
        } else {
            cout<<"sad"<<endl;
            cout<<p<<endl;
        }
    }
}
