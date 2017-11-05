#include<iostream>
#include<algorithm>
#include<vector>
#include<cstdio>
#include<map>
#include<string>
#include<sstream>
using namespace std;

map<int, bool> m;

bool check(int n) {
    if (m.find(n) != m.end())
        return m[n];
    ostringstream ss;
    ss << n;
    string s = ss.str();
    
    int i = 0;
    int j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return m[n] = false;
        i ++;
        j --;
    }
    return m[n] = true;
}

int main() {
    int a, b;
    cin>>a>>b;
    int n1 = 0, n2 = 0;
    long long ans = 0;
    int count = 0;
    for (int i = a; i <= b; ++i) {
        // printf("i: %d, check: %d\n", i, check(i));
        if (check(i)) {
            count ++;
        }
        if (count % 2 == 0)
            n2 ++;
        else
            n1 ++;        
    }
    
    //printf("n1: %d, n2: %d, count: %d\n\n", n1, n2, count);
    
    for (int i = a; i <= b; ++i) {
        // from i to b;
        // printf("i: %d, n1: %d, n2: %d, ans: %d\n", i, n1, n2, ans);
        
        ans += n2;
        if (check(i)) 
            n1 --;
        else 
            n2 --;
        
        if (check(i)) {
            count--;
            swap(n1, n2);
        } 
    }
    cout<<ans<<endl;
    return 0;
}

// 预处理所有的回文整数
// 这样就不需要挨个遍历
// 而是在回文整数之间成段遍历