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

int compute(int i, int n) {
    if (n == 0)
        return 0;
    
    if (i % 4 == 0)
        return compute(i / 4, n - 1);
    if (i % 4 == 1)
        return compute(i / 4 + 1, n - 1);
    // new born at current session
    return n;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    int T;
    cin>>T;
    while (T--) {
        int i, n;
        cin>>i>>n;
        cout<<compute(i, n)<<endl;
    }
    
	return 0;
}