#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std; // max, min

const int N = 100003;
const int L = 101;

struct hashnode {
	char str[L];
	struct hashnode *next;
} nodes[N<<1], *hashtable[N<<1];

struct treenode{
	int firstson;
	int nextbro;
	int LastVisited;
	treenode() : firstson(-1), nextbro(-1), LastVisited(-1){}
};

int hashcode(char *str){
	unsigned int seed = 13131;
	unsigned int hash = 0;
	while (*str) 
		hash = hash * seed + (*str++);
	return (hash & 0x7FFFFFFF);
}

int hashfind(int hashkey, char *s){
	struct hashnode *node;
	// hashtable[hashkey] is the hashnode with hashkey 
    for(node = hashtable[hashkey]; node && strcmp(node->str, s); node = node->next)
		;
	return node == NULL ? -1 : (node - nodes);
}

int hashid; // hashid is the count
int hashinsert(int hashkey, char *s){
	strcpy(nodes[hashid].str, s);
    // nodes is sequential, hashtable is hash table
	nodes[hashid].next = hashtable[hashkey];
	hashtable[hashkey] = &nodes[hashid];
	return hashid++;
}

int mindepth[N << 1][18];
int PosOfmdepth[N << 1][18];
int depth_index = 1;
void dfs(int id, treenode *tree, int depth){
    // depth_index is the index of tree node in sequence, starting from 1
	mindepth[depth_index][0] = depth;
	PosOfmdepth[depth_index][0] = id;
	tree[id].LastVisited = depth_index++;
	int nextid = tree[id].firstson;
	while(nextid != -1) {
		dfs(nextid, tree, depth + 1);
		nextid = tree[nextid].nextbro;
		// back to id, then go nextbro
		mindepth[depth_index][0] = depth;
		PosOfmdepth[depth_index][0] = id;
		tree[id].LastVisited = depth_index++;
	}
	return;
}

void RMQ_ST_init(int n) {
	for(int j = 1; (1 << j) <= n; ++j) {
		for(int i = 1; (i + (1 << j) - 1) <= n; ++i) {
			if(mindepth[i][j - 1] > mindepth[i + (1 << (j - 1))][j - 1]) {
				mindepth[i][j] = mindepth[i + (1 << (j - 1))][j - 1];
				PosOfmdepth[i][j] = PosOfmdepth[i + (1 << (j - 1))][j - 1];
			} else {
				mindepth[i][j] = mindepth[i][j - 1];
				PosOfmdepth[i][j] = PosOfmdepth[i][j - 1];
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int ha, hb, fid, sid;
	char str1[101], str2[101];
	int n;
	scanf("%d", &n);
	treenode *tree = new treenode[n + 1];
	for (int i = 0; i < n; ++i) {
    // while (n--) { 
		scanf("%s%s", &str1, &str2);
		
        ha = hashcode(str1) % N;
		hb = hashcode(str2) % N;
		fid = hashfind(ha, str1);
		sid = hashfind(hb, str2);
		if(fid == -1) // == not =!
			fid = hashinsert(ha, str1);
		if(sid == -1)
			sid = hashinsert(hb, str2);
		
        tree[sid].nextbro = tree[fid].firstson;
		tree[fid].firstson = sid;
	}
	
    dfs(0, tree, 0);
	RMQ_ST_init(2 * n + 1); // we use n here!!!
	
    int m;
	scanf("%d", &m);
	while(m--) {
		scanf("%s%s", str1, str2);
	
        ha = hashcode(str1) % N;
		hb = hashcode(str2) % N;
		fid = hashfind(ha, str1);
		sid = hashfind(hb, str2);
		
        int R = tree[fid].LastVisited; // LastVisited is the index
		int L = tree[sid].LastVisited;
		if (R < L) { 
		// actually it is not father and son
			int temp = L;
			L = R;
			R = temp;
		}
		int pos;
		if (R - L > 0) {
			int T = log(R - L) / log(2); // log_2(R-L)
			if (mindepth[L][T] > mindepth[R - (1 << T) + 1][T])
				pos = PosOfmdepth[R - (1 << T) + 1][T];
			else
				pos = PosOfmdepth[L][T];
		} else {
			pos = PosOfmdepth[L][0];
		}
		printf("%s\n", nodes[pos].str);
	}
	delete[] tree;
	return 0;
}