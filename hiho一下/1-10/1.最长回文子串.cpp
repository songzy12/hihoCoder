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
const int MAXL = 1e6;
int p[2*MAXL+3];
char ss[2*MAXL+3];
char s[MAXL];
int main(){	
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	int t;
	scanf("%d", &t);
	ss[0] = '^';
	ss[1] = '#';
	while(t--){
		scanf("%s", s);
		int n = 2;
		//Manacher Algorithm
		for(int i=0; s[i]; ++i){
			ss[n++] = s[i]; //multiplication to addition
			ss[n++] = '#'; // centre at '#', length is even
		}
		// ss[n]  = '$'; // since ss[n] = '\0';
		int mx = 0, ans = 0, id;
		for(int i=1; i<n; i++){
			if(mx > i)
				p[i] = min(p[2*id-i], mx-i); // caution!
			else
				p[i] = 1;
			while(ss[i+p[i]] == ss[i-p[i]])
				p[i] ++;
			if(p[i]+i > mx){
				mx = p[i]+i;
				id = i;
			}
			ans = max(ans, p[i]-1); // even or odd, both p[i]-1
		}
		printf("%d\n", ans);
	}
}
/*
int main(){
	int n;
	cin>>n;
	while(n--){
		string s;
		cin>>s;
		int ans = 1;
		for(int i=0; i<s.size(); ++i){
			int temp = 1;
			int j;
			for(j=1; i+j < s.size() && i-j >= 0; ++j){
				if(s[i+j] != s[i-j])
					break;
			}
			temp += 2*(j-1);
			ans = max(temp, ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}*/