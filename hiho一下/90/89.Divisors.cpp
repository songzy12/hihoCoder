#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <cstdio>
#include <climits>
#include <cmath>
#include <cstring>

using namespace std;

int primes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43}; // no 21!

long long maxDivisors = 1;
long long result = 1;
long long n;

void dfs(int index, long long now, long long divisors, int lastNi) {
    // cout<<primes[index]<<" "<<now<<" "<<divisors<<" "<<lastNi<<endl;
    if (divisors > maxDivisors || 
        divisors == maxDivisors && now < result) {
        maxDivisors = divisors;
        result = now;
    }
    int i = 1;
    int prime = primes[index];
    long long temp = prime;
    while (now * temp <= n && i <= lastNi) {
        dfs(index + 1, now * temp, divisors * (i + 1), i);
        i ++;
        temp *= prime;
    }
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);

    cin>>n;
    dfs(0, 1, 1, 63);
    cout<<result<<endl;
    
	return 0;
}