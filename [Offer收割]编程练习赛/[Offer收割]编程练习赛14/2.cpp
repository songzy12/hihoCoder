#include<iostream>
#include<cstring>

using namespace std;

const int maxn = 1000;
double p[maxn+5];

double m[maxn+5][maxn+5];
int N, M;

double dp(int base, int left) {
    if (m[base][left] != -1) {
        return m[base][left];
    }
    if (base == N) {
        return m[base][left] = (left == 0) ? 1 : 0;
    }
    
    m[base][left] = p[base] * dp(base+1,left-1) + (1-p[base]) * dp(base+1, left);
    return m[base][left];
}

int main() {
    cin>>N>>M;
    for (int i = 0; i <= N; ++i)
        for (int j = 0; j <= N; ++j)
            m[i][j] = -1;
    for (int i = 0; i < N; ++i)
        cin>>p[i];
    cout<<dp(0, M)<<endl;
    return 0;
}
