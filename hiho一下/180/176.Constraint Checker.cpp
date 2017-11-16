#include <iostream>
#include <cstdio>
#include <map>

using namespace std;

const int maxn = 20;
map<char, int> m;
int n;
string c[maxn];

int get(string s, int &i) {
    int temp = 0;
    while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
        temp = temp * 10 + (s[i] - '0');
        i++;
    }
    if (temp != 0)
        return temp;
    return m[s[i++]];
}

bool check_one(string s) {
    int i = 0;
    int a = get(s, i);
    int b;
    while (i < s.size()) {\
        if (s[i] == '<' && i + 1 < s.size() && s[i+1] == '=') {
            i += 2;
            b = get(s, i);
            if (a > b)
                return false;
            a = b;
        } else if (s[i] == '<') {
            i += 1;
            b = get(s, i);
            if (a >= b)
                return false;
            a = b;
        }
    }
    return true;
}

bool check() {
    for (int i = 0; i < n; ++i) {
        if (!check_one(c[i]))
            return false;
    }
    return true;
}

int main()
{
    cin>>n;
    for (int i = 0; i < n; ++i)
        cin>>c[i];
    int t;
    cin>>t;
    char k;
    int v;
    cin>>k>>v;
    m[k] = v;
    while(cin>>k>>v) {
        if (m.find(k) != m.end()) {
            cout<<(check()?"Yes":"No")<<endl;
            m.clear();
        }
        m[k] = v;
    }
    cout<<(check()?"Yes":"No")<<endl;
    return 0;
}
