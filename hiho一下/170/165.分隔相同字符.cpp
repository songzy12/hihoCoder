#include<iostream>
using namespace std;

int cnt[26];
int total;
char last;

bool is_valid(int total) {
    for (int i = 0; i < 26; ++i) {
        
        if (cnt[i] > (total + 1) / 2) {
            return false;
        }
    }
    return true;
}

char next_valid() {
    for (int i = 0; i < 26; ++i) {
        if (!cnt[i])
            continue;
        if (i == last)
            continue;
        cnt[i]--;
        if (!is_valid(total-1)) {
            cnt[i]++;
            continue;
        }
        total--;
        last = i;
        return i + 'a';
    }
    return ' ';
}

string solve() {
    string ans;
    while (total) {
        char c = next_valid();
        if (c == ' ')
            return "INVALID";
        ans.push_back(c);
    }
    return ans;
}

int main() {
    string s;
    cin>>s;
    for (int i = 0; i < s.size(); ++i) {
        cnt[s[i]-'a']++;
    }
    last = -1;
    total = s.size();
    cout<<solve()<<endl;
}

// consider this: abbbc
// we need to check whether the left is valid for each step
// the if and only if cnt[i] <= (total + 1) / 2, it is vaild