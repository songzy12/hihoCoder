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

const int MAXN = 1000;
int secret[MAXN];

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    int N;
    cin>>N;
    for (int i = 0; i < N; ++i)
        cin>>secret[i];
    int i = N - 1;
    while (i > 0 && secret[i - 1] - secret[i] < 0) 
        i --;
    // i == 0 or secret[i - 1] - secret[i] >= 0
    if (!i)
        cout<<secret[0]<<endl;
    else {
        for (int j = 0; j < i; ++j)
            cout<<secret[j]<<" ";
        cout<<endl;
    }
	return 0;
}