#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

const int MAXN = 100000;
int A[MAXN + 5];
int N;
int ans1[MAXN + 5], ans2[MAXN + 5];

void solve() {
    bool valid1 = true, valid2 = true;
    ans1[0] = ans2[0] = 0;
    
    ans1[1] = 0;
    for (int i = 1; i <= N; ++i) {
        ans1[i + 1] = A[i] - ans1[i-1] - ans1[i];
        if (ans1[i + 1] != 0 && ans1[i + 1] != 1) {
            valid1 = false;
            break;
        }
    }
    if (ans1[N + 1] != 0)
        valid1 = false;
    
    ans2[1] = 1;
    for (int i = 1; i <= N; ++i) {
        ans2[i + 1] = A[i] - ans2[i-1] - ans2[i];
        if (ans2[i + 1] != 0 && ans2[i + 1] != 1) {
            valid2 = false;
            break;
        }
    }
    if (ans2[N + 1] != 0)
        valid2 = false;
    
    /*for (int i = 0; i <= N + 1; i ++)
        cout<<ans1[i]<<" ";
    cout<<(valid1?"valid":"invalid")<<endl;
    for (int i = 0; i <= N + 1; i ++)
        cout<<ans2[i]<<" ";
    cout<<(valid2?"valid":"invalid")<<endl;*/
    
    vector<int> res1;
    vector<int> res0;
    if (valid1 == false) {
        for (int i = 1; i <= N; ++i) {
            if (ans2[i] == 0)
                res0.push_back(i);
            else
                res1.push_back(i);
        }
    } else if (valid2 == false) {
        for (int i = 1; i <= N; ++i) {
            if (ans1[i] == 0)
                res0.push_back(i);
            else
                res1.push_back(i);
        }
    } else {
        for (int i = 1; i <= N; ++i) {
            if (ans1[i] == 0 && ans2[i] == 0)
                res0.push_back(i);
            else if (ans1[i] == 1 && ans2[i] == 1)
                res1.push_back(i);
        }
    }
    cout<<res1.size()<<" ";
    for (size_t i = 0; i < res1.size(); ++i)
        cout<<res1[i]<<" ";
    cout<<endl;
    cout<<res0.size()<<" ";
    for (size_t i = 0; i < res0.size(); ++i)
        cout<<res0[i]<<" ";
    cout<<endl;
}

int main(){
	ios::sync_with_stdio(false);
	int Task;
    cin>>Task;
    while (Task--) {
        cin>>N;
        for (int i = 1; i <= N; ++i) {
            cin>>A[i];
        }
        solve();
    }
	return 0;
}