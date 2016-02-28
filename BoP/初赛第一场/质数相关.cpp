#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
typedef long long ll;
using namespace std;
#define sspeed ios_base::sync_with_stdio(0);cin.tie(0)
#define maxn 200001
#define mod 10007
#define eps 1e-9
// size of max match + size of max independent set = # vertices
// size of max match = size of min vertex cover
// size of min vertex cover + size of max independent set = # vertices
int Num;
char CH[20];
const int inf=0x3f3f3f3f;

const int MAXN = 500001;
bool flag[MAXN];
int primes[MAXN], pi;
void GetPrime()
{
    int i, j;
    pi = 0;
    memset(flag, false, sizeof(flag));
    for (i = 2; i < MAXN; i++)
        if (!flag[i])
        {
            primes[i] = 1;//素数标识为1
            for (j = i; j < MAXN; j += i)
                flag[j] = true;
        }
}

vector<int> q[maxn];
int vis[maxn];
int match[maxn];
int a[maxn];
bool cmp(int b,int c)
{
    return b>c;
}
int dfs(int x)
{
    for(int i=0;i<q[x].size();i++)
    {
        if(vis[q[x][i]]==0)
        {
            vis[q[x][i]]=1;
            if(match[q[x][i]]==-1||dfs(match[q[x][i]]))
            {
                match[q[x][i]]=x;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    GetPrime();
    primes[1]=0;
	int t;
	cin>>t;
    for(int cas=1;cas<=t;cas++)
    {
        memset(match,-1,sizeof(match));
        int n;
		cin>>n;
        for(int i=0;i<n;i++)
            q[i].clear();
        for(int i=0;i<n;i++)
            cin>>a[i];
        sort(a,a+n,cmp);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j)
                    continue;
                int b=a[j];
                int c=a[i];
                if(b<c)
                    swap(b,c);
                if(b%c==0&&primes[b/c])
                {
                    q[j].push_back(i);
                }
            }
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            memset(vis,0,sizeof(vis));
            if(dfs(i))
                ans++;
        }
        printf("Case #%d: %d\n",cas,n-ans/2);
    }
	return 0;
}