#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 100000;

pair<int,int> job[maxn*2];

int main() {
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        int s, t;
        cin>>s>>t;
        job[2*i] = {s, 1};
        job[2*i+1] = {t, 0}; // let t be front of s
    }
    sort(job, job+2*n);
    int count = 0;
    int ans = 0;
    for (int i = 0; i < n*2; ++i) {
        if (job[i].second == 1) {
            count++;
        } else {
            ans = max(ans, count);
            count--;
        }
    }
    cout<<ans<<endl;
    return 0;
}