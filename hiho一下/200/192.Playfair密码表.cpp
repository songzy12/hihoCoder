// http://hihocoder.com/contest/hiho192/problem/1
#include<iostream>
#include<cstring>
using namespace std;

int main() {
	string s;
	cin>>s;
	char grid[5][5];
	bool used[26];
	memset(used, false, sizeof used);
	int cnt = 0;
	used['J'-'A'] = true;
	for (int i = 0; i < s.size(); ++i) {
		if (used[s[i] - 'A'])
			continue;
		used[s[i] - 'A'] = true;
		grid[cnt / 5][cnt % 5] = s[i];
		cnt += 1;
	}
	for (int i = 0; i < 26; ++i) {
		if (used[i])
			continue;
		used[i] = true;
		grid[cnt / 5][cnt % 5] = i + 'A';
		cnt += 1;
	}
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			cout<<grid[i][j];
		cout<<endl;
	}
	return 0;
}