#include<cstdio>
#include<vector>
#include<algorithm>
#define inf -2147483647
#define NN  105
#define MM 1000000
using namespace std;

vector<int>e[NN];

int n,m,k;
int dp[NN][NN];
int vv[NN];

void dfs(int u,int v)
{
    // u as root, select 1 node
	dp[u][1] = vv[u];
	for(int i = 0;i<e[u].size();i++)
	{
        // v is the father of u.
		if(e[u][i] == v)continue; 
		dfs(e[u][i],u);
        
        // by now, dp[u][] has not taken e[u][i] into account
        for(int x = m;x >= 1;x--)
		{
			if(dp[u][x] > inf)
                for(int y = 0;y <= m - x;y++)
                    if(dp[e[u][i]][y] != inf)
                        // e[u][i] as root, select y nodes at most.
                        dp[u][x+y] = max(dp[u][x+y],dp[u][x] + dp[e[u][i]][y]);
		}
	}
} //dfs
int main(void)
{
	int t;
	scanf("%d%d%d", &n,&k,&m);
	for(int i = 1;i<=n;i++)
	  scanf("%d", &vv[i]);
	for(int i = 1;i<=k;i++){
	  int rec;
	  scanf("%d", &rec);
      // make sure rec is selected
	  vv[rec] += MM; 
	}
	for(int i = 1;i<n;i++)
	{
		int t1,t2;
		scanf("%d%d", &t1,&t2);
		e[t1].push_back(t2);
		e[t2].push_back(t1);
	}
	for(int i = 0;i<=100;i++)
	    for(int j = 0;j<=100;j++)
        	dp[i][j] = inf;
	dfs(1,0);
	printf("%d\n", max(-1, dp[1][m] - k*MM));
	return 0;
} //main

