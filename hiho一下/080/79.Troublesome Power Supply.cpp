#include <iostream>
#include <cstdio>
#include <algorithm>
#include <memory.h>
using namespace std;

const int maxn = 20002;
const int maxm = 200002;

struct Node {
  int v;
  int next;
}edge[maxm << 1];
int head[maxn], dfn[maxn], low[maxn], belong[maxn];
bool vis[maxn], instack[maxn];
int m,n,idx,top,tmpdfn,totcnt;

void init() {
  memset(head,-1,sizeof(head));
  memset(vis, false, sizeof(vis));
  memset(instack, false, sizeof(instack));
  idx = top = tmpdfn = totcnt = 0;
  return;
}

void addedge(int u, int v) {
  edge[idx].v = v;
  edge[idx].next = head[u];
  head[u] = idx++;
  return;
}

void read() {
  scanf("%d%d", &n,&m);
  int u, v, s;
  for (int i=0;i<m;i++) {
    scanf("%d%d%d", &u,&v,&s);
    // order does not matter
    if (s == 0) {
      addedge(u*2-1, v*2);
      addedge(v*2-1, u*2);
    } else {
      addedge(u*2, v*2-1);
      addedge(v*2, u*2-1);
    }
  }
  return;
}

void dfs(int st, int* stk) {
  dfn[st] = low[st] = tmpdfn++;
  vis[st] = instack[st] = true;
  stk[top++] = st;
  for (int i=head[st]; i!=-1; i=edge[i].next) {
    if (!vis[edge[i].v]) {
      dfs(edge[i].v, stk);
      low[st] = min(low[st], low[edge[i].v]);
    } else if (instack[edge[i].v]) {
      low[st] = min(low[st], dfn[edge[i].v]);
    }
  }
  if (dfn[st] == low[st]) {
    int u;
    do {
      u = stk[--top];
      // totcnt is the component id
      belong[u] = totcnt;
      instack[u] = false;
    } while (u != st);
    totcnt++;
  }
  return;
}

void solve() {
  static int stack[maxn];
  for (int i=1;i<=n*2;i++) {
    if (!vis[i]) {
      dfs(i, stack);
    }
  }
  bool flag = true;
  for (int i=1;i<=n;i++) {
    // one is for true, one is for false
    if (belong[i*2-1] == belong[i*2]) {
      flag = false;
      break;
    }
  }
  puts(flag ? "Yes" : "No");
  return;
}

int main() {
  int cas;
  scanf("%d", &cas);
  while (cas--) {
    init();
    read();
    solve();
  }
  return 0;
}
