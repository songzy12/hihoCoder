// http://hihocoder.com/contest/hiho92

#include <iostream>
#include <cstdio>
using namespace std;

// Fermat: a^{p-1} = 1 (mod p)
// Miller-Rabin: if p is odd prime, then x^2 = 1 (mod p) => x = 1 or x = p-1
// if p-1 % 2 == 0, let u = (p-1)/2, then a^u = 1 or a^u = p-1

long long A[] = {2,3,5,7,11,13,17,19,23,29,31,37};

long long n;

long long mod_mul(long long a, long long b, long long n) {
    long long res = 0;
    while (b) {
        if(b & 1)
            res = (res + a) % n;
        a = (a + a) % n;
        b >>= 1;
    }
    return res;
}

long long mod_exp(long long a, long long b, long long n) {
    long long res = 1;
    while(b) {
        if(b & 1)
            res = mod_mul(res, a, n);
        a = mod_mul(a, a, n);
        b >>= 1;
    }
    return res;
}

bool Miller_Rabin(long long n) {
  if (n <= 2)
    return n == 2;
  if (n % 2 == 0)
    return false;

    long long u = n - 1;
    while (u % 2 == 0)
        u /= 2;
    long long temp = u;

  for (int i = 0; i < 12; ++i) {
    if (A[i] >= n)
        break;
    long long a = A[i] % n;
    u = temp;
    long long x = mod_exp(a, u, n);
    while (u < n) {
        long long y = mod_mul(x, x, n);
        if (y == 1 && (x % n) != 1 && (x % n) != n - 1)
                return false;
        x = y;
        u *= 2;
    }
    if (x != 1)
        return false;
  }
  return true;
}

int main() {
    int t;
    cin>>t;
    while (t--) {
        cin>>n;
        cout<<(Miller_Rabin(n) ? "Yes" : "No")<<endl;
    }
}

// Carmichael数（都是合数）
// 409709791834013701 是个质数
// Montgomery算法
