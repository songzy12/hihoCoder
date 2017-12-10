// http://hihocoder.com/contest/hiho97/problem/1

// x mod m_1 = r_1
// x mod m_2 = r_2

// x = k_1 m_1 + r_1
// x = k_2 m_2 + r_2

// k_1 m_1 - k_2 m_2 = r_2 - r_1

// Ax + By = C => extend gcd

// x = k_1 m_1 + r_1
// X = k lcm(m_1, m_2) + x

// This is the same form as x = k_1 m_1 + r_1

#include<iostream>
#include<cstdio>
using namespace std;

void extend_gcd(long long A, long long B, long long &x, long long &y) {
    // printf("A: %lld, B: %lld\n", A, B);
    if (B == 0) {
        x = 1;
        y = 0;
        return;
    }

    long long tempX, tempY;
    extend_gcd(B, A % B, tempX, tempY);
    x = tempY;
    y = tempX - (A / B) * tempY;
    return;
}

long long gcd(long long n, long long m) {
    if (!m)
        return n;
    return gcd(m, n % m);
}

bool flag = true;

void compute(long long &M, long long &R, long long m, long long r) {
    long long x, y;
    long long D = gcd(M, m);
    if ((r - R) % D) {
        flag = false;
        return;
    }

    long long a = M / D;
    long long b = m / D;
    long long c = (r - R) / D;

    extend_gcd(a, b, x, y);
    x = ((x * c) % b + b) % b; // overflow

    R = x * M + R;
    M = M * b; // overflow
    R = ((R % M) + M) % M;
}

int main() {
    int n;
    cin>>n;
    long long M, R, m, r;
    cin>>M>>R;
    n--;
    while (n--) {
        cin>>m>>r;
        // printf("M: %lld R: %lld\n", M, R);
        if (flag)
            compute(M, R, m, r);
    }
    if (!flag)
        cout<<-1<<endl;
    else
        cout<<R<<endl;
    return 0;
}
