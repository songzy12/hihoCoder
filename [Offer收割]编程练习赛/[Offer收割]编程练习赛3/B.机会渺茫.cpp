#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<cstdio>
#include<climits>
#include<cmath>
#include<cstring>

using namespace std;

const int MAXN = 1e6;

long long pn[MAXN];
int dn[MAXN];
long long pm[MAXN];
int dm[MAXN];

int get_prime(long long n, long long * pn, int *dn) {
    int i = 0, temp = sqrt(n);
    for (int j = 2; j <= temp; ++j) {
        if (n % j == 0) {
            int d = 0;
            while (n % j == 0) {
                n /= j;
                d ++;
            }
            pn[i] = j;
            dn[i++] = d;
        }
    }
    if (n > 1) {
        pn[i] = n;
        dn[i++] = 1;
    }
    return i;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    long long N, M;
    cin>>N>>M;
    
    int cn = get_prime(N, pn, dn);
    int cm = get_prime(M, pm, dm);
    
    int A = 1;
    int i = 0, j = 0;
    while (i < cn && j < cm) {
        if (pn[i] == pm[j]) {
            A *= max(dn[i], dm[j]) + 1;
            i ++;
            j ++;
        } else if (pn[i] < pm[j]) {
            A *= dn[i] + 1;
            i ++;
        } else {
            A *= dm[j] + 1;
            j ++;
        }
    }
    while (i < cn) {
        A *= dn[i] + 1;
        i ++;
    } 
    while (j < cm) {
        A *= dm[j] + 1;
        j ++;
    }
    
    cout<<A<<" "<<1<<endl;
	return 0;
}