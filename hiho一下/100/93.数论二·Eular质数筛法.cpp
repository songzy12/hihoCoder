// http://hihocoder.com/contest/hiho93

#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 1000000;

bool isPrime[maxn+5];
int primes[maxn+5];

int solve(int n) {
    int cnt = 0;
    memset(isPrime, true, sizeof isPrime);
    for (int i = 2; i <= n; ++i) {
        if (isPrime[i])
            primes[cnt++] = i;
        // we will always do the sieve no matter i is prime or not.
        for (int j = 0; j < cnt; ++j) {
            if (primes[j] * i > n)
                break;
            isPrime[primes[j] * i] = false;
            if (i % primes[j] == 0)
                // to ensure each composite number only sieved once
                // suppose T = M * p1 = N * p2, where p1 < p2 and prime
                // then N < M and N % p1 == 0
                // so that we will not sieve T when enumerating N
                break;
        }
    }
    return cnt;
}

int main() {
    int n;
    cin>>n;
    cout<<solve(n)<<endl;
}
