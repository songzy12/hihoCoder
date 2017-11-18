// http://hihocoder.com/contest/hiho95/problem/1
#include <iostream>
using namespace std;

void extend_gcd(long long A, long long B, long long &x, long long &y) {
    // A * x + B * y = gcd(A, B)
    // B * x' + (A % B) * y' = gcd(B, A % B)
    if (A % B == 0) {
        x = 0;
        y = 1;
        return;
    }

    long long tempX, tempY;
    extend_gcd(B, A % B, tempX, tempY);
    x = tempY;
    y = tempX - (A / B) * tempY;
}

long long gcd(long long A, long long B) {
    if (B == 0)
        return A;
    return gcd(B, A % B);
}

long long solve(long long s1, long long s2, long long v1, long long v2, long long m) {
    long long A = v1 - v2;
    long long B = m;
    long long C = s2 - s1;

    if (A < 0)
        A += m;
    long long D = gcd(A, B);
    if (C % D)
        return -1;

    A /= D;
    B /= D;
    C /= D;
    long long x, y;
    extend_gcd(A, B, x, y);
    x = (x * C) % B;
    while (x < 0)
        x += B;
    return x;
}

int main() {
    long long s1, s2, v1, v2, m;
    cin>>s1>>s2>>v1>>v2>>m;
    cout<<solve(s1,s2,v1,v2,m)<<endl;
    return 0;
}
