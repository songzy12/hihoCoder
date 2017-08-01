#include<iostream>
#include<cmath>
using namespace std;

// (a + (a+t-1)) * t / 2 = n
// a = (2*n-t*(t-1)) / (2*t)
// a > 0 => t < \sqrt(2*n) + 1

int solve(int n) {
    int t = sqrt(2*n);
    while (t > 1) {
        if ((2*n-t*(t-1)) % (2*t) == 0)
            return t;
        t --;
    }
    return t;
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        int n;
        cin>>n;
        cout<<solve(n)<<endl;
    }    
}