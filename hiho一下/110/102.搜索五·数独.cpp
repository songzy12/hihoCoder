// http://hihocoder.com/contest/hiho102/problem/1
// http://hihocoder.com/problemset/problem/1321
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
using namespace std;

// there will be 81 * 4 = 324 constraints
// there will be 9 * 9 * 9 = 729 possible choices
// so the 01 matrix will be like 729 rows * 324 columns

// what we need do is to choose exactly 9 * 9 rows 
// such that every column contains 1

// set (i, j, k): what if row i column j is set to be number k

const int m = 324;
const int n = 729;

int matrix[9*9*9][9*9*4];

void set(int i, int j, int k) {
	int id = i * 9 + j;
	int pid = id * 9 + k;
	
	// 第i行存在k
	matrix[pid][i * 9 + k] = 1;
	// 第j列存在k
	matrix[pid][81 + j * 9 + k] = 1;
	
	int t = i / 3 * 3 + j / 3; // NOTE: 蠢！！！
	// 第t个九宫格存在k
	matrix[pid][162 + t * 9 + k] = 1;
	
	// 每个格子只能存一个数字
	matrix[pid][243 + id] = 1;
	return;
}

int board[9][9];

void create() {
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) 
			if (board[i][j] == 0) {
				for (int k = 0; k < 9; ++k)
					set(i, j, k);
			}
			else 
				set(i, j, board[i][j]-1);
}

struct node {
	node *left, *right, *up, *down;
	int x, y;

	node() {
		left = this;
		right = this;
		up = this;
		down = this;
		x = y = 0;
	}
	node (int i, int j) {
		left = this; // here we cannot directly call node()
		right = this;
		up = this;
		down = this;
		x = i;
		y = j;
	}
};

node * nodes[n * m];
int id[n][m];

node * columnHead[m];
int cnt_y[m];

node * build() {
	
	node* head = new node();
	node* pre = head;
	for (int i = 0; i < m; ++i) {
		node *p = new node(-1, i);

		p->right = pre->right;
		p->left = pre;
		pre->right->left = p;
		pre->right = p;

		pre = p;
		columnHead[i] = p;
	}

	int cnt = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] == 1) {
				id[i][j] = cnt;
				nodes[cnt] = new node(i, j);
				cnt++; // note the position of cnt++
			}
		}

	for (int j = 0; j < m; ++j) {
		node *p;
		node *pre = columnHead[j];
		for (int i = 0; i < n; ++i) {
			if (matrix[i][j] == 1) {
				cnt_y[j]++;
				
				p = nodes[id[i][j]];

				p->down = pre->down;
				p->up = pre;
				pre->down->up = p;
				pre->down = p;

				pre = p;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		pre = NULL;
		for (int j = 0; j < m; ++j) {
			if (matrix[i][j] == 1) {
				if (pre == NULL)
					pre = nodes[id[i][j]];
				else {
					node *p = nodes[id[i][j]];
					p->right = pre->right;
					p->left = pre;
					pre->right->left = p;
					pre->right = p;
					pre = p;
				}
			}
		}
	}
	return head;
}

int ans[n];

void remove(int col) {
	node *p = columnHead[col];
	p->right->left = p->left;
	p->left->right = p->right;
	node *p2 = p->down;
	while (p2 != p) {
		node *p3 = p2->right;
		while (p3 != p2) {
			p3->down->up = p3->up;
			p3->up->down = p3->down;
			cnt_y[p3->y]--;
			p3 = p3->right;
		}
		p2 = p2->down;
	}
}

void resume(int col) {
	node *p = columnHead[col];
	p->right->left = p;
	p->left->right = p;
	node *p2 = p->down;
	while (p2 != p) {
		node *p3 = p2->right;
		while (p3 != p2) {
			p3->down->up = p3;
			p3->up->down = p3;
			cnt_y[p3->y]++;
			p3 = p3->right;
		}
		p2 = p2->down;
	}
}

node * findMinCnt(node *head) {
	node *res = head->right;
	int min_cnt = cnt_y[res->y];
	
	node *cur = res;
	while (cur != head) {
		// NOTE: 这里在 cur != head, 但是 cur == head->left 的时候 
		// 会导致 cur = head, 然后 cnt_y[cur->y] = 0
		// 所以结果会一直是返回 head
		// cur = cur->right; 
		if (cnt_y[cur->y] < min_cnt) {
			min_cnt = cnt_y[cur->y];
			res = cur;
		}
		cur = cur->right;
	}
	return res;
}

int dance(int depth, node* head) {
	node *p = head->right;
	if (p == head)
		return depth;
	p = findMinCnt(head);
	node *p2 = p->down;
	if (p2 == p)
		return -1;

	remove(p->y);
	while (p2 != p) {
		ans[depth] = p2->x;
		node *p3 = p2->right;
		while (p3 != p2) {
			remove(p3->y);
			p3 = p3->right;
		}

		int temp = dance(depth+1, head);
		if (temp != -1)
			return temp;

		p3 = p2->left;
		while (p3 != p2) {
			resume(p3->y);
			p3 = p3->left;
		}

		p2 = p2->down;
	}
	resume(p->y);
	return -1;
}

void solve() {
	create();
	node *head = build();
	
	//for (int i = 0; i < n; ++i) {
	//	for (int j = 0; j < m; ++j) {
	//		cout<<matrix[i][j]<<" ";
	//	}
	//	cout<<endl;
	//}
	
	int depth = dance(0, head);
	
	if (depth != -1) {
		for (int i = 0; i < depth; ++i) {
			int x = ans[i] / 81;
			int y = ans[i] % 81 / 9;
			int k = ans[i] % 9;
			board[x][y] = k + 1;
		}		
	}
}

void init() {
    memset(board, 0, sizeof board);
    memset(id, 0, sizeof id);
    memset(matrix, 0, sizeof matrix);
	memset(cnt_y, 0, sizeof cnt_y);
    for(auto x : columnHead) //使用C11新特性初始化为NULL，方便
        x = NULL;
    for(auto x : nodes)
        x = NULL;
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out_.txt", "w", stdout);
	int t;
	cin>>t;
	while (t--) {
		init(); // NOTE: init!!!
		for (int i = 0; i < 9; ++i)
			for (int j = 0; j < 9; ++j)
				cin>>board[i][j];
		solve();
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j)
				cout<<board[i][j]<<" ";
			cout<<endl;
		}
		
	}
	return 0;
}
