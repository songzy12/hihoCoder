// https://hihocoder.com/contest/hiho183/problem/1

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<set>

using namespace std;

const int maxx = 1000;

int map(int x, int y) {
	return maxx * x + y;
}

bool grid[maxx][maxx];
int father[maxx * maxx];

void init() {
	memset(grid, false, sizeof grid);
	for (int i = 0; i < maxx * maxx; ++i) {
		father[i] = i;
	}
}

int find(int x) {
	if (father[x] != x) {
		father[x] = find(father[x]);
	}
	return father[x];
}

void merge(int x, int y) {
	int fx = find(x);
	int fy = find(y);
	if (fx < fy) {
		father[fy] = fx;
	} else {
		father[fx] = fy;
	}
	return;
}

int amount = 0;

void solve(int x, int y) {
	amount ++;
	grid[x][y] = true;
	int d[][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
	
	for (int i = 0; i < 4; ++i) {
		int x_ = x + d[i][0];
		int y_ = y + d[i][1];
		
		if (x_ < 0 || x_ >= 1000 || y_ < 0 || y_ >= 1000)
			continue;
		if (!grid[x_][y_])
			continue;
		if (find(map(x, y)) != find(map(x_, y_))) {
			//printf("(%d, %d): %d, (%d, %d): %d\n", x, y, find(map(x, y)), x_, y_, find(map(x_, y_)));
			amount--;
			merge(map(x, y), map(x_, y_));
		}
	}
	// set<int> ids;
	// ids.insert(find(map(x_, y_)));
	// amount -= ids.size();
	// NOTE:  this may also work,
	// but after you do merge()
	// the next find() will return a different result as the first find()
	// thus find(a) may be in the same group as find(b) originally
	// but it appears different with a merge(a, c) in between.
	cout<<amount<<endl;
}

int main() {
	
	freopen("in.txt", "r", stdin);
	init();
	
	int n;
	cin>>n;
	
	while(n--) {
		int x, y;
		cin>>x>>y;
		solve(x, y);		
	}
	return 0;
}