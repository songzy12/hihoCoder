#include<iostream>
using namespace std;

const int maxn = 100000;
long long a[maxn+5];
long long max0, max1;

int main() {
    int T;
    cin>>T;
    max0 = 0, max1 = 0;
    while (T--) {
        int N;
        cin>>N;
        for (int i = 0; i < N; ++i) {
            cin>>a[i];
            if (a[i] >= max0) {
                max1 = max0;
                max0 = a[i];
            } else if (a[i] >= max1) {
                max1 = a[i];
            } 
        }
        cout<<max0*max1*(max1&max0)<<endl;
    }
}