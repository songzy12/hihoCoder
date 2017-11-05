#include<iostream>
#include<stack>
#include<cstdio>
using namespace std;

const int maxn = 100000;
int A[maxn+5];
int B[maxn+5];

int main() {
    int n;
    cin>>n;
    for (int i = 0; i < n; ++i)
        cin>>A[i];
    
    stack<pair<int, int> > s;
    for (int i = 0; i < n; ++i) {
        if (s.empty() || s.top().first >= A[i])
            s.push({A[i], i});
        else {
            while (!s.empty() && s.top().first < A[i]) {
                B[s.top().second] = i - s.top().second;
                s.pop();
            }
            s.push({A[i], i});
        }
    }
    while (!s.empty()) {
        B[s.top().second] = -1;
        s.pop();
    }
    for (int i = 0; i < n; ++i)
        printf("%d\n", B[i]);
    return 0;
}