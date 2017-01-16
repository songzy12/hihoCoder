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

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	
    string str;
    getline(cin, str);
    
    vector<string> stack;
    map<string, int> count;
    
    int prev = 0, temp = 0;
    int len = str.length();    
    for (int i = 0; i < len; ++i) {
        if (str[i] == '<') {
            if (!stack.empty())
                count[stack.back()] += temp;
            prev = i + 1;
            temp = 0;
        } else if (str[i] == '>') {
            string tag = str.substr(prev, i - prev);
            if (tag[0] == '/') {
                stack.pop_back();
            } else {
                stack.push_back(tag);
            }
            prev = i + 1;
            temp = 0;
        } else if (str[i] != ' ') {
            // str[i] may be ' '
            temp ++;
        }
    }
    printf("%d %d %d", count["red"], count["yellow"], count["blue"]);
	return 0;
}