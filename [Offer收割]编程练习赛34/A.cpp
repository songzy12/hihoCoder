#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000;
int a[maxn+5];

int main() {
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i)
        cin>>a[i];
    sort(a, a+n);
    long long ans = 0;
    for (int i = 1; i < n; ++i)
        ans += a[i] - a[0];
    cout<<ans<<endl;
    return 0;
}