#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <vector>
#include <cstdio>
#include <climits>
#include <cmath>
#include <cstring>

using namespace std;

string line;

void deal(string line) {
	int i = 0, len = line.size();
	while (i < len && line[i] == ' ') i++; // remove starting space.
	int state = 0; // 0 for start of sentence.	
	while (i < len) {
		switch(state) {
			case 0: 
				if (line[i] == ' ') {
					while (i < len && line[i+1] == ' ') i++;	
					if (line[i+1] == ',' || line[i+1] == '.') {
						i++;
						break;
					}
				}	
				else 
					state = 1;
				if (line[i] >= 'a' && line[i] <= 'z') {
					line[i] += 'A' - 'a';
				}				
				cout<<line[i++];				
				break;
			case 1:
				if (line[i] >= 'A' && line[i] <= 'Z')
					line[i] -= 'A' - 'a';
				else if (line[i] == '.')
					state = 0;
				else if (line[i] == ' '){
					while (i < len && line[i+1] == ' ') i++;
					if (line[i+1] == ',' || line[i+1] == '.') {
						i++;
						break;
					}
				}
				cout<<line[i++];
				break;
		}
	}
	cout<<endl;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	ios::sync_with_stdio(false);
	while(getline(cin, line))
		deal(line);	
	return 0;
}