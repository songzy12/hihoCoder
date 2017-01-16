#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 1000;
const int INF = 0x3fffffff;

int n, cost[MAXN], map[MAXN][MAXN];
bool use[MAXN];

int prim(){
	int i, j, ans = 0;
	for(i = 0; i < n; ++i){
		cost[i] = map[0][i];
	}
	use[0] = true; // add 0 to the tree
	for(i = 1; i < n; ++i){
		int minn = INF, minj;
		for(j = 1; j < n; ++j){
			if(!use[j] && cost[j] < minn){
				minn = cost[j];
				minj = j;
			}
		}
		use[minj] = true; // add minj to the tree
		ans += minn;
		for(j = 1; j < n; ++j){
			if(!use[j] && map[minj][j] < cost[j]){
                // update cost[j] to be min distance from node j to the tree
				cost[j] = map[minj][j]; 
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			scanf("%d", &map[i][j]);
		}
	}
	printf("%d\n", prim());
	return 0;
}