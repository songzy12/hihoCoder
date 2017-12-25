
// http://hihocoder.com/contest/hiho101/problem/1

// dancing link is different from skip list

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int maxm = 100;
const int maxn = 100;
int m, n;

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

node * nodes[maxn*maxm];

node * columnHead[maxm+5];

int board[maxn+5][maxm+5];
int id[maxn+5][maxm+5];


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
			if (board[i][j] == 1) {
				id[i][j] = cnt;
				nodes[cnt] = new node(i, j);
				cnt++; // note the position of cnt++
			}
		}

	for (int j = 0; j < m; ++j) {
		node *p;
		node *pre = columnHead[j];
		for (int i = 0; i < n; ++i) {
			if (board[i][j] == 1) {
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
			if (board[i][j] == 1) {
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

int ans[maxm];

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
			p3 = p3->right;
		}
		p2 = p2->down;
	}
}

bool dance(int depth, node* head) {
	node *p = head->right;
	if (p == head)
		return true;
	node *p2 = p->down;
	if (p2 == p)
		return false;

	remove(p->y);
	while (p2 != p) {
		ans[depth] = p2->x;
		node *p3 = p2->right;
		while (p3 != p2) {
			remove(p3->y);
			p3 = p3->right;
		}

		if (dance(depth+1, head))
			return true;

		p3 = p2->left;
		while (p3 != p2) {
			resume(p3->y);
			p3 = p3->left;
		}

		p2 = p2->down;
	}
	resume(p->y);
	return false;
}

bool solve() {
	node *head = build();
	fflush(stdout);
	return dance(0, head);
}

int main() {
	freopen("in.txt", "r", stdin);
	int t;
	cin>>t;
	while (t--) {
		cin>>n>>m;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j)
				cin>>board[i][j];
		cout<<(solve()?"Yes":"No")<<endl;
	}
}
