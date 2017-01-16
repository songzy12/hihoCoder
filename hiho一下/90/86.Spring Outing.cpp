#include <iostream>
using namespace std;
const int N = 1000;
int n,k,vot[N][N];

int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	cin >> n >> k;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j <= k; j++) {
			int x; cin >> x;
			vot[i][x] = j; // for i, x is the j th best choice
		}
	}
	
	int res = 0;
    // backward deduction
	for(int j = k; j >= 1; j--) {
		int v = 0;
		for(int i = 0; i < n; i++) {
			if(vot[i][j] <= vot[i][res]) 
                v++;
		}
		
		if(v * 2 > n) {
			res = j;
		}
	}
	
	if(res==0) cout << "otaku" <<endl;
	else cout << res << endl;
	
	return 0;
}
