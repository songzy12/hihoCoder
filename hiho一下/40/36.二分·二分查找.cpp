#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<list>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
using namespace std;

const int MAXN = 1000000;
int a[MAXN + 5];

int solve(int left, int right, int target, int offset) {
    if (left >= right) {
        if (a[left] != target)
            return -1;
        else
            return offset + 1;
    } 
    int mid = a[left];
    int i = left, j = right;
    while (i < j) {
        while (i < j && a[j] >= mid) {
            j --;
        }
        if (i < j) {
            a[i] = a[j];
            i ++;
        }
        while (i < j && a[i] <= mid) {
            i ++;
        }
        if (i < j) {
            a[j] = a[i];
            j--;
        }
    }
    a[i] = mid;
    
    /*for (int k = left; k <= right; ++k )
        cout<<a[k]<<" ";
    cout<<endl;*/
    
    
    if (mid == target) {
        return offset + i - left + 1;
    } else if (mid < target) {
        return solve(i + 1, right, target, offset + i - left + 1);
    } else {
        return solve(left, i - 1, target, offset);
    }
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	int N, K;
    cin>>N>>K;
    for (int i = 0; i < N; ++i) 
        cin>>a[i];
    cout<<solve(0, N - 1, K, 0)<<endl;
	return 0;
}