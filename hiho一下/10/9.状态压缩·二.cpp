#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
ll memo[1005][1<<5][1<<5];

int n, m;
ll solve(int r, int bs0, int bs1) {
	// filling the rth row, current row is bs0, next row is bs1
	if (r == n) return (bs0 == 0 && bs1 == 0);
	// boundary condition
	if (memo[r][bs0][bs1] != -1) return memo[r][bs0][bs1];
	if (bs0 == (1<<m)-1) return solve(r+1, bs1, 0);
	// if current row is full, then next row
	int id = -1;
	for (int i = 0; i < m; i++) {
		if ((bs0 & (1<<i)) == 0) {
			id = i;
			break;
		}
	}
	// id is the first zero position counting from back
	memo[r][bs0][bs1] = solve(r, bs0 | (1<<id), bs1 | (1<<id));
	// put it vertically, the corresponding position of next row must be empty, since we only put cake in this row
	if ( id < m-1 && (bs0 & (1<<(id+1))) == 0 ) {
	// put it horizontally
		memo[r][bs0][bs1] += solve(r, bs0 | (3<<id), bs1);
		memo[r][bs0][bs1] %= mod;
	}
	return memo[r][bs0][bs1];
}

int main() {
	cin >> n >> m;
	
	memset(memo, -1, sizeof memo);
	cout << solve(0, 0, 0) << endl; // 0th row, current and next row is both empty, number of different methods
	return 0;
}