#include<iostream>
#include<algorithm>
#include<list>
#include<map>
#include<vector>
#include<cstdio>
#include<climits>
#include<cmath>
#include<cstring>

using namespace std;

const int MAXN = 1000;
int N, M, S, T;
int A[MAXN + 5];

int compute(int current_score, int current_level, int current_total, int current_correct) {
    if (current_level == N)
        return current_correct;
    
    if (current_total == M)
        return -1;
    
    if (current_score > A[current_level])
        return compute(0, current_level + 1, current_total, current_correct);
    
    int a = compute(current_score + S, current_level, current_total + 1, current_correct + 1);
    int b = compute(current_score + T, current_level, current_total + 1, current_correct);
    if (a == -1)
        return b;
    if (b == -1)
        return a;
    return min(a, b);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    int Q;
    while (Q--) {        
        cin>>N>>M>>S>>T;
        for (int i = 0; i < N; ++i)
            cin>>A[i];
        int ans = compute(0, 0, 0, 0);
        if (ans == -1)
            cout<<"No"<<endl;
        else 
            cout<<ans<<endl;
    }    
	return 0;
}