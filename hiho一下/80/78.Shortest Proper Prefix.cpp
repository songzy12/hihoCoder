#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<cstdio>
#include<climits>
#include<cmath>
#include<cstring>

using namespace std;
const int MAXN = 2000000;

struct Trie {
    Trie* son[26];
    int cnt;
};

Trie tries[MAXN+5] = {0};
int num_tries = 1;

void build_tire(Trie *p,char * s) {
	for(int i = 0; s[i]; i++) {
		int x = s[i]-'a';
		if(p->son[x]==0) {
			p->son[x] = &tries[num_tries++];
		}
		p = p->son[x];
		p->cnt++;
	}
}

int traversal(Trie *p) {
	int res = 0;
	for (int i = 0; i < 26; ++i) 
        if(p->son[i]) {
            if(p->son[i]->cnt<=5) res++;
            else res += traversal(p->son[i]);
        }
	return res;
}

char s[MAXN];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", s);
		build_tire(&tries[0],s);
	}
	printf("%d\n",traversal(&tries[0]));
	return 0;
}