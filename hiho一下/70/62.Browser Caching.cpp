#include<iostream>
#include<cstdio>
#include<map>
using namespace std;

const int maxn = 20000;
string a[maxn + 5];

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    int n, m;
    cin>>n>>m;
    
    map<string, int> lastVisit;
    for (int i = 1; i <= n; ++i)
        cin>>a[i];
    
    int s = 1, cacheCnt = 1; // since default is 0
    lastVisit[a[1]] = 1;
    cout<<"Internet"<<endl;
    
    for (int i = 2; i <= n; ++i) {
        if (lastVisit[a[i]] >= s && lastVisit[a[i]] < i) {
            cout<<"Cache"<<endl;
        } else {
            cacheCnt ++;
            if (cacheCnt > m) {
                s++; // no need to remove from cache
            } 
            cout<<"Internet"<<endl;
        }
        lastVisit[a[i]] = i;
        while (lastVisit[a[s]] != s)
            s ++;        
    }
    return 0;
}