#include <iostream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

#define rep(i,n) for(int i = 0; i < (int)(n); i++)

const int N = 9;
int bd[N][N];
int matrix[N*N*N][4*N*N];

void set(int i,int j,int k) {
	int id  = i * 9 + j;
	int pid = id * 9 + k;
	matrix[pid][0 * N * N + i * 9 + k] = 1;
	matrix[pid][1 * N * N + j * 9 + k] = 1;
	int t = i/3*3 + j/3;
	matrix[pid][2 * N * N + t * 9 + k] = 1;
	matrix[pid][3 * N * N + id       ] = 1;
}

void create() {
	memset(matrix,0,sizeof(matrix));
	rep(i,N) rep(j,N) {
		if(bd[i][j]==0) {
			rep(k,N) set(i,j,k);
		} else {
			set(i,j,bd[i][j]-1);
		}
	}
}

struct Node {
	int left,right,up,down,x,y;
	Node() {}
	Node(int l,int r,int u,int d,int _x,int _y) {
		left = l; right = r;
		up = u; down = d;
		x = _x; y = _y;
	}
	void set(int l,int r,int u,int d,int _x,int _y) {
		left = l; right = r;
		up = u; down = d;
		x = _x; y = _y;
	}
};

Node nodes[4*N*N*N*N*N + 4*N*N + 1];
int  num = 0;

vector<int> col_head,col_cnt;
vector<vector<int> > board, id;

void show() {
	int n = 4;
	vector<vector<int> > bd(n,vector<int>(n,0) );
	int p,p2,p3;
	p = 0;
	p2 = nodes[p].right;
	while(p2 != p) {
		p3 = nodes[p2].down;
		while(p3 != p2) {
			bd[nodes[p3].x][nodes[p3].y] = 1;
			p3 = nodes[p3].down;
		}
		p2 = nodes[p2].right;
	}

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) 
			 cout << bd[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

void remove(int col) {
	int p,p2,p3;
	p = col_head[col];
	nodes[nodes[p].right].left = nodes[p].left;
	nodes[nodes[p].left].right = nodes[p].right;
	p2 = nodes[p].down;
	while(p2 != p) {
		p3 = nodes[p2].right;
		while(p3 != p2) {
			nodes[nodes[p3].down].up = nodes[p3].up;
			nodes[nodes[p3].up].down = nodes[p3].down;
			col_cnt[nodes[p3].y] --;
			p3 = nodes[p3].right;
		}
		p2 = nodes[p2].down;
	}
}

void resume(int col) {
	int p,p2,p3;
	p = col_head[col];
	nodes[nodes[p].right].left = p;
	nodes[nodes[p].left].right = p;
	p2 = nodes[p].down;
	while( p2 != p ) {
		p3 = nodes[p2].right;
		while(p3 != p2) {
			nodes[nodes[p3].down].up = p3;
			nodes[nodes[p3].up].down = p3;
			col_cnt[nodes[p3].y] ++;
			p3 = nodes[p3].right;
		}
		p2 = nodes[p2].down;
	}
}

int ans[N*N];

int findMinColCnt() {
	int p = nodes[0].right;
	int res = p;
	while(p != 0) {
		if(col_cnt[nodes[p].y] < col_cnt[nodes[res].y]) res = p;
		p = nodes[p].right;
	}
	return res;
}

bool dance(int depth) {
	int p,p2,p3;
	p = nodes[0].right;
	if(p == 0) return true;

	p = findMinColCnt();

	p2 = nodes[p].down;
	if(p2 == p) return false;

	remove(nodes[p].y);
	while(p2 != p) {
		ans[ depth ] = nodes[p2].x;

		p3 = nodes[p2].right;
		while(p3 != p2) {
			remove(nodes[p3].y);
			p3 = nodes[p3].right;
		}

		if( dance(depth + 1) ) return true;

		p3 = nodes[p2].left;
		while(p3 != p2) {
			resume(nodes[p3].y);
			p3 = nodes[p3].left;
		}

		p2 = nodes[p2].down;
	}
	resume(nodes[p].y);
	return false;
}

void dancing() {
	int n,m;
	n = N*N*N;
	m = 4*N*N;
	board.assign(n,vector<int>(m,0));

	rep(i,n) rep(j,m) board[i][j] = matrix[i][j];

	num = 0;
	int head = num++;
	nodes[head].set(head,head,head,head,0,0);

	col_head.assign(m,0);
	col_cnt.assign(m,0);

	// heads
	int pre = head;
	for(int i = 0; i < m; i++) {
		col_head[i] = num++;
		int p = col_head[i];
		nodes[p].up = nodes[p].down = p;
		nodes[p].x  = 0; nodes[p].y = i;
		nodes[p].right = nodes[pre].right;
		nodes[p].left  = pre;
		nodes[nodes[pre].right].left = p;
		nodes[pre].right = p;
		pre = p;
	}

	// init nodes
	id = board;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) if(board[i][j] == 1) {
			id[i][j] = num;
			nodes[num].set(num,num,num,num,i,j);
			num ++;
		}
	}
	
	// conn cols
	int p;
	for(int j = 0; j < m ; j++) {
		pre = col_head[j];
		for(int i = 0; i < n; i++) if(board[i][j]==1) {
			col_cnt[j] ++;
			p = id[i][j];
			nodes[p].down = nodes[pre].down;
			nodes[p].up   = pre;
			nodes[nodes[pre].down].up = p;
			nodes[pre].down = p;
			pre = p;
		}
	}

	// conn rows
	for(int i = 0; i < n; i++) {
		pre = -1;
		for(int j = 0; j < m; j++) if(board[i][j]==1) {
			if(pre < 0) pre = id[i][j];
			else {
				p = id[i][j];
				nodes[p].right = nodes[pre].right;
				nodes[p].left  = pre;
				nodes[nodes[pre].right].left = p;
				nodes[pre].right = p;
				pre = p;
			}
		}
	}
	
	if(dance(0)) {
		// cout << "Yes" << endl;
		rep(id,N*N) {
			int i,j,k;
			i = ans[id];
			k = i % N; i /= N;
			j = i % N; i /= N;
			
			bd[i][j] = k+1;
		}
		rep(i,N) {
			rep(j,N) cout << bd[i][j] << " ";
			cout << endl;
		}
	} else {
		cout << "No" << endl;
	}
}

void go() {
	rep(i,N) rep(j,N) cin >> bd[i][j];
	create();
	dancing();
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(false); cin.tie(0);
	int T;
	cin >> T;
	rep(t,T) go();
	return 0;
}

