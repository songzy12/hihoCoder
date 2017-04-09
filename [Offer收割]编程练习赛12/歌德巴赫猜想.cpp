#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 1000000;

bool isPrime[maxn+5];

int main() {
    int n;
    cin>>n;
    memset(isPrime, true, sizeof isPrime);
    
    for (int i = 2; i <= maxn+5; ++i) {
        if (!isPrime[i])
            continue;
        for (int j = 2; i * j < maxn+5; j++)
            isPrime[i*j] = false;
    }
    
    for (int i = 2; i <= maxn / 2 && n - i >= 2; ++i) {
        if (isPrime[i] && isPrime[n-i]) {
            cout<<i<<" "<<n-i<<endl;
            break;
        }
    }
    return 0;
}