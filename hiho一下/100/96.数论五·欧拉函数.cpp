// http://hihocoder.com/contest/hiho96/problem/1

// \phi(n): 1, ..., n-1 中与 n 互素的数的个数
// suppose p is prime
// if p | n: \phi(n * p) = \phi(n) * p
// if p \not | n: \phi(n * p) = \phi(n) * (p-1)

// if p is prime
// \phi(p^k) = (p^k-1) - (p^{k-1} - 1) = p^{k-1} (p - 1)

// if p, q co-prime
// \phi(p * q) = \phi(p) * \phi(q)
// gcd(m, p*q) = 1 <=> gcd(m, p) = 1 && gcd(m, q) = 1

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 5e6;

bool isPrime[maxn+5];
int primeList[maxn+5];
int phi[maxn+5];
int primeCount = 0;

void solve(int r) {
    for (int i = 2; i <= r; ++i) {
        if (isPrime[i]) {
            primeCount++;
            primeList[primeCount] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= primeCount; ++j) {
            if (i * primeList[j] > r)
                break;
            isPrime[i * primeList[j]] = false;
            if (i % primeList[j] == 0) {
                phi[i * primeList[j]] = phi[i] * primeList[j];
                break;
            } else {
                phi[i * primeList[j]] = phi[i] * (primeList[j] - 1);
            }
        }
    }
}

int main() {
    int l, r;
    cin>>l>>r;
    memset(isPrime, true, sizeof isPrime);
    solve(r);
    int ans = l;
    for (int i = l; i <= r; ++i) {
        //printf("phi[%d]: %d\n", i, phi[i]);
        if (phi[i] < phi[ans])
            ans = i;
    }
    cout<<ans<<endl;
    return 0;
}
