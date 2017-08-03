#include<iostream>
#include<cstring>
using namespace std;

string s;

int mult() {
    int left = 0;
    for (int i = s.size()-1; i >= 2; --i) {
        left += 2*(s[i] - '0');
        s[i] = '0' + (left % 10);
        left /= 10;
    }
    return left;
}

string solve() {
    // if s can be represented as powers of 2
    // then it can be represented by len(s) bits of 2
    
    // if s can be represented as powers of 2
    // then its n-th bit can be obtained by s * (2^n)  
    string ans = "0.";
    for (int i = 2; i < s.size(); ++i) {
        ans.push_back('0'+mult());
    }
    for (int i = 2; i < s.size(); ++i) {
        if (s[i] != '0')
            return "NO";
    }
    return ans;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        cin>>s;
        cout<<solve()<<endl;
    }
}