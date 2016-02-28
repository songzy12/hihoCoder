#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

vector<int> unionset;
vector<bool> visited;
vector<int> result;

vector<list<int> > rlist;
vector<pair<int, int> > req;
typedef list<int>::iterator iter;
const int N = 100003;
const int L = 101;

struct hashnode {
	char str[L];
	struct hashnode *next;
} nodes[N << 1], *hashtable[N];

int hashid;

int hashfind(int hashkey, char *s) {
	struct hashnode *node;
	for(node = hashtable[hashkey]; node && strcmp(node->str, s); node = node->next)
		;
	return node == NULL ? -1 : (node-nodes);
}

int hashinsert(int hashkey, char *s) {
	strcpy(nodes[hashid].str, s);
	nodes[hashid].next = hashtable[hashkey];
	hashtable[hashkey] = &nodes[hashid];
	return hashid++;
}

int hashcode(char *str) {
	unsigned int seed = 13131;
	unsigned int hash = 0;
	while (*str) {
		hash = hash * seed + (*str++);
	}
	return (hash & 0x7FFFFFFF);
}

struct treenode {
	int firstson;
	int nextbro;
	treenode() : firstson(-1), nextbro(-1) {}
};

int findparty(int key){
	if (key != unionset[key]) {
		unionset[key] = findparty(unionset[key]);
	}	
	return unionset[key];
}

void union1(int a, int b) {
	int A = findparty(a);
	int B = findparty(b);
	if(A != B)
		unionset[B] = A;
}

void dfs(int id, treenode *tree) {
	visited[id] = true;
	int id1 = tree[id].firstson;
	while(id1 != -1) {
		dfs(id1, tree);
		union1(id, id1);
		id1 = tree[id1].nextbro;
	}
	// when we quit id, we can answer requests containing id
	for(iter it = rlist[id].begin(); it != rlist[id].end(); ++it){
		if(result[*it] == -1) {
			if(req[*it].first == id)
				id1 = req[*it].second;
			else 
				id1 = req[*it].first;
			if(visited[id1])
				result[*it] = findparty(id1);
		}
	}
	return;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int n, m;
	char str1[101], str2[101];
	int fid, sid, ha, hb;
	scanf("%d", &n);
	treenode *tree = new treenode[n + 1];
	unionset.resize(n + 1);
	unionset[0] = 0;
	visited.resize(n + 1, false);
	for(int i = 1; i <= n; ++i) {
		// this is a tree, there are at most n + 1 different persons
		unionset[i] = i; // so i starts from 1
		scanf("%s%s", str1, str2);
		ha = hashcode(str1) % N;
		hb = hashcode(str2) % N;
		fid = hashfind(ha, str1);
		sid = hashfind(hb, str2);
		
		if (fid == -1) {
			fid = hashinsert(ha, str1);
		}
		if (sid == -1) {
			sid = hashinsert(hb, str2);
		}
		tree[sid].nextbro = tree[fid].firstson;
		tree[fid].firstson = sid;
	}
	
	scanf("%d", &m);
	result.resize(m, -1);
	rlist.resize(n + 1);
	req.resize(m);
	for(int i = 0; i < m; ++i) {
		scanf("%s%s", str1, str2);
		ha = hashcode(str1) % N;
		hb = hashcode(str2) % N;
		fid = hashfind(ha, str1);
		sid = hashfind(hb, str2);
		if(fid == sid)
			result[i] = sid;
		else {
			req[i] = pair<int, int>(fid, sid);
			// to find requests containing id quickly.
			rlist[fid].push_back(i); 
			rlist[sid].push_back(i);
		}
	}
	dfs(0, tree);
	// the first person is father of all the others
	for(int i = 0; i < m; ++i)
		printf("%s\n", nodes[result[i]].str);
	return 0;
}