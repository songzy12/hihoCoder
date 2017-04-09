#include <iostream>
#include <algorithm>
using namespace std;

bool solve(int L, int F, int D) {
    return __gcd(L,D) >= F;
}

int main() {
    int T;
    cin>>T;
    while(T--) {
        int L, F, D;
        cin>>L>>F>>D;
        cout<<(solve(L, F, D)?"YES":"NO")<<endl;
    }
}

// n 步之后脚后跟所在位置 n * D mod L
// 希望对于所有的 n, 有 n * D mod L < L - F

// 可踩位置为有限个，故必定重复
// [L / gcd(L, D)] * D mod L = 0

// 可踩位置均匀，故相邻位置间距 gcd(L,D)

// 距离线最近的距离为 gcd(L,D)，只需判断 gcd(L,D) >= F ? true : false;