#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
#define SZY
const int M = 100000;
const int N = 20000;
int node[M + 1];
int next_node[M + 1];
int to[N + 1];

long long value[N + 1];
int new_p[M][2];

int dfn[N + 1];
int low[N + 1];
bool visit[N + 1];
int stk[N + 1];
int top_stk[N + 1];
bool mark[N + 1];
int top = 0;

long long max_value[N + 1];

void dfs(int u)
{
	static int id = 0;
	visit[u] = true;
	stk[top++] = u; // an array to implement a stack
	mark[u] = true;
	dfn[u] = low[u] = ++id;
	for (int i = to[u]; i; i = next_node[i])
	{
		if (!visit[node[i]])
		{
			dfs(node[i]);
			low[u] < low[node[i]] ? 1 : low[u] = low[node[i]];
			// another way to use if else 
		}
		else
		{
			if (mark[node[i]]) // node[i] in stack or not
			{
				low[u] < dfn[node[i]] ? 1 : low[u] = dfn[node[i]];
			}
		}
	}

	top_stk[u] = u; //top_stk to denote the group
	if (low[u] == dfn[u])
	{
		while (stk[--top] != u)
		{
			top_stk[stk[top]] = u;
			value[u] += value[stk[top]];
			mark[stk[top]] = false;
		}
		mark[u] = false;
	}
}

void dfs2(int u)
{
	max_value[u] = value[u];
	long long max_temp = 0;
	for (int i = to[u]; i; i = next_node[i])
	{
		if (!max_value[node[i]])
		{
			dfs2(node[i]);
		}
		max_temp < max_value[node[i]] ? max_temp = max_value[node[i]] : 1;
	}
	max_value[u] += max_temp; // it is the same another way back
}

int main()
{

#ifdef SZY	
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int n, m;
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &value[i]);
	}

	int e = 0;
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		scanf("%d %d", &u, &v);
		new_p[i][0] = u;
		new_p[i][1] = v;
		node[++e] = v; // end point of edge e
		next_node[e] = to[u]; 
		// next node with same start point of edge e 
		to[u] = e; // first edge with start point u
	}
	dfs(1);
	e = 0;
	memset(node, 0, sizeof node);
	memset(to, 0, sizeof to);
	memset(next_node, 0, sizeof next_node);
	for (int i = 0; i < m; ++i)
	{
		int u, v;
		u = top_stk[new_p[i][0]]; // new group of node u
		v = top_stk[new_p[i][1]];
		if (u == v)
		{
			continue;
		}
		node[++e] = v;
		next_node[e] = to[u];
		to[u] = e;
	}
	dfs2(1);
	printf("%lld\n", max_value[1]);
	return 0;
}