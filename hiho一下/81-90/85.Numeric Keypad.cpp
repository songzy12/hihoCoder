#include <iostream>
#include <string>

using namespace std;

const int N = 10;
int go[N][N] = {
{1, 0,0,0, 0,0,0, 0,0,0},

{1, 1,1,1, 1,1,1, 1,1,1},
{1, 0,1,1, 0,1,1, 0,1,1},
{0, 0,0,1, 0,0,1, 0,0,1},

{1, 0,0,0, 1,1,1, 1,1,1},
{1, 0,0,0, 0,1,1, 0,1,1},
{0, 0,0,0, 0,0,1, 0,0,1},

{1, 0,0,0, 0,0,0, 1,1,1},
{1, 0,0,0, 0,0,0, 0,1,1},
{0, 0,0,0, 0,0,0, 0,0,1}};

bool dfs(string &res,string &K,int dep,int last,bool below) {
	// cout << res << endl;
	int len = res.length();
	if(dep >= len) {
		return true;
	}
	if(below) {
		int mi = 0;
		for(int i = 9; i >=0; i--) 
            // find the largest reachable number 
            if(go[last][i]) {
                mi = i;
                break;
            }
        // set all the rest to this number
		for(int i = dep; i < len; i++) 
            res[i] = mi+'0';
		return true;
	}
	for(int i = 9; i >= 0; i--) if(i <= K[dep] && go[last][i]) {
		res[dep] = i+'0';
		if(dfs(res,K,dep+1,i,i<K[dep])) 
            return true;
	}
	return false;
}

int main() {
	int T;
	cin >> T;
	for(;T--;) {
		string K,res;
		cin >> K;
		res = K;
		for(int i = 0; i < K.length(); i++) K[i] -= '0';
		for(int i = 0; i < K.length(); i++) res[i] = '#';
		dfs(res,K,0,1,false);
		// for(int i = 0; i < K.length(); i++) res[i] += '0';
		cout << res << endl;
	}
	return 0;
}
