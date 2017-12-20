#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;

const int maxn = 250;
int n, m;
long long k;
long long a[maxn+5][maxn+5];
long long pre[maxn+5][maxn+5]; // sum of columns

int main() {
    cin>>n>>m>>k;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin>>a[i][j];
    
    for (int i = 0; i < n; ++i)
        pre[i][0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            pre[i][j+1] = pre[i][j] + a[i][j];
        
    int ans = 0;
    for (int width = 1; width <= m; ++width) {
        for (int index = 0; index - 1 + width < m; ++index) {
            int head = 0, tail = 0;
            long long temp = 0;
            long long _temp = pre[tail][index+width] - pre[tail][index];
            while (head < n) {
                while (_temp <= k && tail < n) {
                    temp = _temp;
                    tail++;
                    _temp = temp + pre[tail][index+width] - pre[tail][index];
                }
                ans = max(ans, (tail-head)*width);
                temp -= pre[head][index+width] - pre[head][index];
                head ++;
                if (tail == n)
                    break;
            }
        }
    }
    cout<<ans<<endl;
}