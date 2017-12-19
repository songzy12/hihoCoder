#include<iostream>
#include<cstdio>
using namespace std;

void solve(int n, int depth, int h, int m) {
    if (depth == 5) {
        if (h > 23)
            return;
    } 
    if (depth == 11) {
        if (m > 59)
            return;
        if (n != 0)
            return;
        printf("%02d:%02d\n", h, m);
        return;
    }
    
    if (depth < 5) {
        solve(n, depth+1, h<<1, m);
        if (n > 0)
            solve(n-1, depth+1, (h<<1)+1, m);
    } else {
        solve(n, depth+1, h, m<<1);
        if (n > 0)
            solve(n-1, depth+1, h, (m<<1)+1);
    }
}

int main() {
	int n;
	cin>>n;
	solve(n, 0, 0, 0);
	return 0;
}