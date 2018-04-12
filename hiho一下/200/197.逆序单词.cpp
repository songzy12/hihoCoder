#include<iostream>
#include<map>
using namespace std;

string reversed(string s) {
	string res = "";
	for (int i = s.length()-1; i >= 0; i--)
		res += s[i];
	return res;
}

int main() {
	int n;
	cin>>n;
	int cnt = 0;
	map<string, bool> m;
	while(n--) {
		string s;
		cin>>s;
		if (m.find(reversed(s)) == m.end()) {
			m[s] = true;
		} else {
			cnt++;
		}
	}
	cout<<cnt<<endl;
	return 0;
}