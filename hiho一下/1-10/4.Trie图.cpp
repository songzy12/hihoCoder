#include<iostream>
#include<cstring>
#include<string>
#include<queue>
using namespace std;

// DFA: Deterministic Finite Automata
// AC automation: Aho-Corasick automation#include<iostream>

struct Trie{
	int flag;
	struct Trie *next[26];
	struct Trie *suffix;
	Trie(){
		flag=0;
		for(int i=0; i<26; ++i)
			next[i]=NULL;
		suffix=NULL;
	}
};

void build(Trie *root, string &s){
	Trie *cur=root;
	int len=s.length();
	for(int i=0;i<len;++i){
		int id=s[i]-'a';
		if(!cur->next[id])
            cur->next[id]=new Trie;
		cur=cur->next[id];
	}
	cur->flag=1;
}


int main(){
	int n;
	cin>>n;
	string s;
	Trie *root=new Trie;
	while(n--){
		cin>>s;
		build(root,s);
	}
	
	root->suffix=root; // 后缀
	queue<Trie*> qt;
	for(int i=0;i<26;++i){
		if(!root->next[i])
			root->next[i]=root;
		else{
			root->next[i]->suffix=root;
			qt.push(root->next[i]);
		}
	}
	
	Trie *cur, *suf;
	while(!qt.empty()){
		cur=qt.front();
		qt.pop();
		suf=cur->suffix;
		for(int i=0;i<26;++i){
			if(!cur->next[i]){
			// all shorter suffix has been decided
				cur->next[i]=suf->next[i]; 
			}else{
			// decide suffix of next if next is not null
			// suffix of next of current is next of suffix of current
				cur->next[i]->suffix=suf->next[i];
				qt.push(cur->next[i]);
			}
		}
	}
	
	cin>>s;
	int len=s.length(),flag=0;
	cur=root;
	for(int i=0;i<len;++i){
		int id=s[i]-'a';
		cur=cur->next[id];
		if(cur->flag) {
			cout<<"YES"<<endl;
			flag=1;break;
		}
	}
	if(!flag) cout<<"NO"<<endl;
	return 0;
}