#include<iostream>
#include<vector>
using namespace std;

const int maxn = 1000;
int father[maxn+5];
vector<int> sons[maxn+5];

void dfs(int node, int parent) {
    for (int i = 0; i < sons[node].size(); ++i) {
        if (sons[node][i] == parent)
            continue;
        int cur = sons[node][i];
        father[cur] = node; 
        dfs(cur, node);        
    }
}

int main() {
    int N, K;
    cin>>N>>K;
    for (int i = 0; i < N-1; ++i) {
        int a, b;
        cin>>a>>b;
        sons[a].push_back(b);
        sons[b].push_back(a);
    }
    dfs(K, 0);
    for (int i = 1; i <= N; ++i)
        cout<<father[i]<<" ";
    cout<<endl;
    return 0;
}