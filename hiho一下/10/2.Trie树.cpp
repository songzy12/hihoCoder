#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
#include<cstring>
#include<map>
#include<iomanip>
#define x first
#define y second
#define pii pair<int, int>
#define DEBUG
using namespace std;

class Trie{
public:
	Trie(){
		end = false;
		T = 0;
		for(int i=0; i<26; ++i)
			alpha[i] = NULL; // initialize to NULL
	}
	
	bool end;
	int T;
	Trie* alpha[26];
};

int main(){
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	Trie* root = new Trie();
	int n;
	cin>>n;
	string s;
	while(n--){
		cin>>s;
		Trie* temp = root;
		for(int i=0; i<s.size(); ++i){
			if(!temp->alpha[s[i]-'a'])
				temp->alpha[s[i]-'a'] = new Trie();
			temp = temp->alpha[s[i]-'a'];
			temp->T++;
		}
		temp->end = true;
	}
	cin>>n;
	while(n--){
		cin>>s;
		Trie* temp = root;
		bool found = true;
		for(int i=0; i<s.size(); ++i){
			if(!temp->alpha[s[i]-'a']){
				found = false;
				break;
			}
			temp = temp->alpha[s[i]-'a'];
		}
		cout<<(found ? temp->T : 0)<<endl;
	}
	return 0;
}