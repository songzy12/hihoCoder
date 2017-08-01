#include <bits/stdc++.h> 

using namespace std;
 
typedef long long ll;
const int maxn = 100005;

vector<int> v[maxn];

int n;

bool vs[maxn];

int sg[maxn];

void dfs(int x, int p)
{
    sg[x] = 0;
    for(int i=0;i<v[x].size();i++)
    {
        int toit = v[x][i];
        if(toit!=p)
        {
            dfs(toit, x);
            sg[x] ^= (1 + sg[toit]);
        }
    }
}
int main() 
{
    int t, a, b;
    cin >> t;
    string s = "";
    while(t--)
    {
        cin >> n;
        for(int i=1;i<=n;i++)
        {
            v[i].clear();
            vs[i] = 0;
        }
        for(int i=1;i<n;i++)
        {
            cin >> a >> b;
            v[a].push_back(b);
            vs[b] = 1;
        }
        int root;
        for(int i=1;i<=n;i++)
        {
            if(!vs[i])
            {
                root = i;
                break;
            }
        }
        dfs(root, 0);
        if(sg[root])
            s += '1';
        else
            s += '0';
        int res = 0;
        for(int i=0;i<v[root].size();i++)
        {
            int toit = v[root][i];
            res ^= sg[toit];
        }
        if(res)
            s += '1';
        else
            s += '0';
    }
    cout << s << endl;
}