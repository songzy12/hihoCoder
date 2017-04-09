#include<iostream>
using namespace std;

string convert(string t) {
    string ans = "";
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] >= 'a' && t[i] <= 'z')
            ans += t[i];
        else if (t[i] == '_') {
            ans += 'A' + t[i+1] - 'a';
            i += 1;
        } else if (t[i] >= 'A' && t[i] <= 'Z') {
            ans += '_';
            ans += 'a' + t[i] - 'A';
        }
    }
    return ans;
}

int main() {
    int n;
    cin>>n;
    while (n--) {
        string t;
        cin>>t;
        cout<<convert(t)<<endl;
    }
    return 0;
}