#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int N, M;
int SP = 0;
const int MAXN = 50001;
char str[50001];

struct sTreeNode {
    int left, right; // boundary
    int base, add; // actual = base + add
    int delta, step; // associated with operation 4
    int lch, rch; // indices of children
} tree[ MAXN << 2 ];

void createTree(int rt, int left, int right) {
    tree[rt].left = left, tree[rt].right = right;
    tree[rt].delta = tree[rt].step = 0;
    tree[rt].add = 0;

    if (left == right) { 
        tree[rt].base = str[ left ] - 'A';
        tree[rt].lch = tree[rt].rch = 0;
        return ;
    }

    tree[rt].base = -1;
    tree[rt].lch = rt * 2, tree[rt].rch = rt * 2 + 1;

    int mid = (tree[rt].left + tree[rt].right) >> 1;
    createTree(tree[rt].lch, left, mid);
    createTree(tree[rt].rch, mid + 1, right);
    return ;
}
void update(int rt, int left, int right, int key, int type) {
    if (!rt) return ;
    if (tree[rt].right < left || tree[rt].left > right) return ;
    if (left <= tree[rt].left && tree[rt].right <= right) {
		if (type == 1) {
		    tree[rt].base = key;
		    tree[rt].delta = 0, tree[rt].step = 0;
		    tree[rt].add = 0;
		}
		if (type == 2) {
		    tree[rt].add += key;
		}

		if (type == 4) {
		    tree[rt].delta += key + (tree[rt].left - left);
		    tree[rt].step++;
		}

    }  else {
		int mid = (tree[rt].left + tree[rt].right) / 2;
        // -1 means not the same
		if (tree[rt].base == -1) {
            // lch
		    tree[ tree[rt].lch ].delta += tree[rt].delta;
		    tree[ tree[rt].lch ].step  += tree[rt].step;
		    tree[ tree[rt].lch ].add   += tree[rt].add;
		    // rch
		    tree[ tree[rt].rch ].delta += tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].step;
		    tree[ tree[rt].rch ].step  += tree[rt].step;
		    tree[ tree[rt].rch ].add   += tree[rt].add;
		}   else {
		    tree[ tree[rt].lch ].base = tree[ tree[rt].rch ].base = tree[rt].base;
		    tree[ tree[rt].lch ].delta = tree[rt].delta;
		    tree[ tree[rt].rch ].delta = tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].step;
		    tree[ tree[rt].lch ].step = tree[ tree[rt].rch ].step = tree[rt].step;
		    tree[ tree[rt].lch ].add  = tree[ tree[rt].rch ].add  = tree[rt].add;
		}          
        // clear all flags
        tree[rt].base = -1;
        tree[rt].delta = tree[rt].step = 0;
        tree[rt].add = 0;

        update(tree[rt].lch, left, right, key, type);
        update(tree[rt].rch, left, right, key, type);
    }
    return ;
}

int f[ MAXN ];    // 记录每个叶子节点的数值
void getResult(int rt) {
    if (!rt) return ;
    if (tree[rt].base != -1) {
        int delta = tree[rt].delta;
        for (int i = tree[rt].left; i <= tree[rt].right; ++i)
            f[i] = tree[rt].base + tree[rt].add + delta, delta += tree[rt].step;
    } else {
        int mid = (tree[rt].left + tree[rt].right) / 2;
        // lch
        tree[ tree[rt].lch ].delta += tree[rt].delta;
        tree[ tree[rt].lch ].step  += tree[rt].step;
        tree[ tree[rt].lch ].add   += tree[rt].add;
        // rch
        tree[ tree[rt].rch ].delta += tree[rt].delta + (mid - tree[rt].left + 1) * tree[rt].step;
        tree[ tree[rt].rch ].step  += tree[rt].step;
        tree[ tree[rt].rch ].add   += tree[rt].add;

        getResult(tree[rt].lch);
        getResult(tree[rt].rch);
    }
    return ;
}

void showResult() {
	getResult(1);
	for (int i = 0; i < N; ++i) {
		printf("%c", (char)((f[(i+SP)%N]%26) + 'A'));
	}
	printf("\n");
}
int main() {
	
	scanf("%d%d", &N, &M);
	scanf("%s", str);
    // params: index of tree, left bound, right bound
	createTree(1, 0, N-1); 
	//showResult();
	int n = N;
	for (int i = 0; i < M; ++i) {
		char cmd[5];
		int type;
		scanf("%s", cmd);
		scanf("%d", &type);
        // turn the ith to the jth rotators to character X
		if (type == 1) {
			int i, j;
			char c;
			scanf("%d %d %c", &i, &j, &c);
			int _i = (i-1+SP)%n;
			int _j = (j-1+SP)%n;
			if (_i <= _j) {
				update(1, _i, _j, c-'A', 1);
			}
			else {
				update(1, _i, n-1, c-'A', 1);
				update(1, 0, _j, c-'A', 1);
			}
			
			//showResult();
		}
        // turn the ith to the jth rotators up K times
		else if (type == 2) {
			int i, j, K;
			scanf("%d%d%d", &i, &j, &K);
			int _i = (i-1+SP)%n;
			int _j = (j-1+SP)%n;
			K %= 26;
			if (_i <= _j) {
				update(1, _i, _j, K, 2);
			}
			else {
				update(1, _i, n-1, K, 2);
				update(1, 0, _j, K, 2);
			}
			
			//showResult();
		}
        // move the K leftmost rotators to the rightmost end
		else if (type == 3) {
			int K;
			scanf("%d", &K);
			SP += K; // SP is the start point
			SP %= n;	
			//showResult();
		}
		else if (type == 4){
			int i, j;
			scanf("%d %d", &i, &j);
			int _i = (i-1+SP)%n;
			int _j = (j-1+SP)%n;
			if (_i <= _j) {
				update(1, _i, _j, 1, 4);
			}
			else {
				update(1, _i, n-1, 1, 4);
				update(1, 0, _j, n-_i+1, 4);
			}
		}

		//showResult();
		
	}
	showResult();
}