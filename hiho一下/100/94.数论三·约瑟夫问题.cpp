// http://hihocoder.com/contest/hiho94/problem/1

// after delete the first one, there only left k - 1
// else, we remove N / K as a group,
// then discuss based on where the final position is

#include<iostream>

using namespace std;

int josephus(int n, int k) {
    if (n == 1)
        return 0;
    if (n < k) {
        int ret = 0;
        for (int i = 2; i <= n; ++i)
            ret = (ret + k) % i; // here
        return ret;
    }
    int ret = josephus(n - n / k, k);
    if (ret < n % k) {
        // ret in the tail part
        return ret + n - (n % k);
    }
    // ret in the head part
    return ret - (n % k) + (ret - (n % k)) / (k -1);
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        int n, k;
        cin>>n>>k;
        cout<<josephus(n, k)<<endl;
    }
    return 0;
}
