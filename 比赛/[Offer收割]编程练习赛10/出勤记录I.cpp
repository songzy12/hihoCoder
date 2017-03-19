#include<iostream>
#include<cstdio>
using namespace std;

bool solve(string s){
    bool flag_a = false;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'A') {
            if (flag_a)
                return false;
            flag_a = true;
        }
        if (i - 2 >= 0 && s[i] == 'L' && s[i-1] == 'L' && s[i-2] == 'L')
            return false;
    }
    return true;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int T;
    cin>>T;
    while(T--){
        string s;
        cin>>s;
        cout<<(solve(s)?"YES":"NO")<<endl;
    }
}