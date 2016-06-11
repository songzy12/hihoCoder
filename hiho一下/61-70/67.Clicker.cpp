#include <iostream>
#include <cstring>
#include <utility>
using namespace std;

const int MAXN = 35;
const int MAXM = 20005;
int c[MAXN][150];
int v[MAXN];
int f[MAXM];

int n, m;

int main(){
    memset(f, 0, sizeof(f));
    ios::sync_with_stdio(false);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> v[i] >> c[i][1];
        int j = 1, tmp = (int)(1.07 * c[i][1]);
        while(true){
            c[i][j + 1] = c[i][j] + tmp; // cost for hero of level j+1
            if(c[i][j + 1] > m)
                break;
            tmp = (int)(1.07 * tmp);
            j++;
        }
        // f[j]: optimal weight when take first i groups with cost j.
        for(j = m; j >= 1; j--){
            for(int k = 1; c[i][k] <= j; k++){
                // need the value of f[j - c[i][k]] of last level
                f[j] = max(f[j], f[j - c[i][k]] + v[i] * k);
            }
        }
    }
    int ret = 0;
    for(int j = 1; j <= m; j++){
        ret = max(ret, f[j]);
    }
    cout << ret << endl;
    return 0;
}

/*0-1 knap sack problem:
n object, cost c[i], weight w[i]. total cost <= V, optimal weight
f[i][v] means after first i objects, with cost <= v, optimal weight
f[i][v] = max(f[i-1][v], f[i-1][v-c[i]] + w[i])
*/
/*group knap sack problem:
n object, cost c[i], weight w[i], k group, total cost <= V, optimal weight
f[i][v] means after first i groups, with cost <= v, optimal weight
f[i][v] = max(f[i-1][v], f[i-1][v-c[t]] + w[t]), where t \in group i.
*/
/*generalized knap sack problem:
n object, cost changable, w[i]=f_i(c[i]). total cost <= V, optimal weight
*/