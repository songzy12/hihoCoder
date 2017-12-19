#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1e5+5;
struct SOFTWARE
{
	int start;
	int num;
	int E[5];
}sft[maxn];

struct VERTEX
{
	int first;
}ver[maxn];

struct Node
{
	int id;
	int next;
}list[maxn];
int n,m,sign[maxn],cnt,vis[maxn];

void add(int e,int id)
{
	list[cnt].id = id;
	if(ver[e].first == -1) ver[e].first = cnt++;
	else
	{
		list[cnt].next = ver[e].first;
		ver[e].first = cnt++;
	}
}

void init()
{
	memset(vis,0,sizeof(vis));
	memset(list,-1,sizeof(list));
	memset(ver,-1,sizeof(ver));
	cnt = 0;
}

void dfs(int cur,int e)
{
	if(ver[e].first == -1) return;
	for(int i = ver[e].first; i != -1; i = list[i].next)
	{
		int k = list[i].id;
		vis[k]++;
		for(int j = 1; j <= sft[k].num; j++)
			dfs(k,sft[k].E[j]);
	}
}

int main()
{	
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		init();
		scanf("%d%d",&n,&m);
		for(int i = 1; i <= m; i++)
			scanf("%d",&sign[i]);
		for(int i = 1; i <= n; i++)
		{
			scanf("%d%d",&sft[i].start,&sft[i].num);
			add(sft[i].start,i);
			for(int j = 1; j <= sft[i].num; j++)
				scanf("%d",&sft[i].E[j]);
		}
		for(int i = 1; i <= m; i++)
			dfs(0,sign[i]);
		for(int i = 1; i <= n; i++)
			printf("%d ",vis[i]);
		printf("\n");
	}
	return 0;
}