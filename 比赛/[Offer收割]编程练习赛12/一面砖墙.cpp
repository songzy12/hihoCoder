#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    map<long long, int> m;
    int n;
    cin>>n;
    long long max_width = 0;
    for (int i = 0; i < n; ++i) {
        long long width = 0;
        int c;
        cin>>c;
        for (int j = 0; j < c; ++j) {
            long long w;
            cin>>w;
            width += w;
            m[width] += 1;
        }
        max_width = max(width, max_width);
    }
    int cut = 0;
    for (auto const &ent: m) {
        if (ent.first != max_width)
            cut = max(cut, ent.second);
    }
    cout<<n-cut<<endl;
    return 0;
}