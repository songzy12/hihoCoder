#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;
const int maxn = 110;
int t;
char input[maxn], ans[maxn], tempAns[maxn], 
	data[maxn][maxn], tempData[maxn][maxn];
bool used[10], notZero[26];
int inputLen, maxNumLen, maxNumNum,
	len[maxn], 
	letter[26], 
	op[maxn];
bool flag[26];
int cnt[26];
int use[26];

void fillAns() {
	int number = 0;
	for (; number < 10; ++number) if (!used[number]) {
		break;
	}
	int i = 0, j = 0;
	for (; i < inputLen; ++i) {
        // leave the operators alone
		if (input[i] == '+' || input[i] == '=') tempAns[j++] = input[i];
        // fill in the assigned letters
		else if (letter[input[i] - 'A'] > -1) tempAns[j++] = '0' + letter[input[i] - 'A'];
        // try all the possibilities
		else {
			if (notZero[input[i] - 'A'] && number == 0) {
				int nn = number + 1;
				for (; nn < 10; ++nn) if (!used[nn]) {
					break;
				}
				if (nn == 10) return;

				tempAns[j++] = '0' + nn;
				used[nn] = true;
				letter[input[i] - 'A'] = nn;
			}
			else {
				tempAns[j++] = '0' + number;
				used[number] = true;
				letter[input[i] - 'A'] = number;
				for (; number < 10; ++number) if (!used[number]) {
					break;
				}
			}
		}
	}
	tempAns[inputLen] = '\0';
	if (ans[0] == '#') strcpy(ans, tempAns);
    // since out method is not ordered by letters
	else if (strcmp(ans, tempAns) > 0) strcpy(ans, tempAns);
	else;
}

void dfs(int i, int j, int s) {
	//用(i,j)来表示当前枚举到了右起第i位，上起第j个字母。
	//s是前面的进位
    
    // all the columns and rows are checked 
	if (i == maxNumLen) {
        if (s == 0) fillAns();

		return;
	}
    
    // for the i th column, all the rows are checked 
	if (j == maxNumNum) {
		if (s % 10 == 0) 
			dfs(i + 1, 0, s / 10);
		
		return;
	}

	char ch = data[j][i];
    // '\0' ?
	if (ch == '#' || ch == '\0') {
		dfs(i, j + 1, s);
		return;
	}

    
	if (letter[ch - 'A'] > -1) 
        // if ch has been assigned
		dfs(i, j + 1, s + letter[ch - 'A'] * op[j]);
	else {
		int st = 0;
		if (notZero[ch - 'A']) st = 1;
        // try all the possibilities
		for (int x = st; x < 10; ++x) if (!used[x]) {
			used[x] = true;
			letter[ch - 'A'] = x;
			
            dfs(i, j + 1, s + x * op[j]);
			
            used[x] = false;
			letter[ch - 'A'] = -1;
		}
	}
}

bool firstCheck() {
	//bool flag[26];
	memset(flag, 0, sizeof(flag));
	for (int i = 0; i < inputLen; ++i) {
		flag[input[i] - 'A'] = true;
	}
	int rt = 0;
	for (int i = 0; i < 26; ++i) {
		if (flag[i]) ++rt;
	}
	
	return rt <= 10;
}

void gen_data_and_len() {
    // l: current length of number
    // ff: current operator of number
	int ff = 1, l = 0;
    // len[num], op[num], tampData[num]: 
    // the length, operator, temp data of num
	maxNumLen = 0, maxNumNum = 0;
	for (int i = 0; i < inputLen; ++i) {
        // only +, =, letter
		if (input[i] == '=') {
			len[maxNumNum] = l;
			op[maxNumNum++] = ff;
			maxNumLen = max(maxNumLen, l);

			ff = -1;
			l = 0;
		}
		else if (input[i] == '+') {
			len[maxNumNum] = l;
			op[maxNumNum ++] = ff;
			maxNumLen = max(maxNumLen, l);
			l = 0;
		}
		else{
			tempData[maxNumNum][l++] = input[i];
		}
	}
	len[maxNumNum] = l;
	op[maxNumNum++] = ff;
	maxNumLen = max(maxNumLen, l);

	//gen data
	for (int i = 0; i < maxNumNum; ++i) {
        // check nonzero letter
		if(len[i] > 1) notZero[tempData[i][0] - 'A'] = true;
        // reverse tempData to get data
		for (int j = len[i] - 1; j > -1; --j) {
			data[i][j] = tempData[i][len[i] - 1 - j];
		}
		for (int j = len[i]; j < maxNumLen; ++j) {
			data[i][j] = '#';
		}
	}

	//unused letter
	for (int j = 0; j < maxNumLen; ++j) {
		//bool flag[26];
		//int cnt[26];
		//int use[26];
		memset(flag, 0, sizeof(flag));
        memset(cnt, 0, sizeof(cnt));
		memset(use, 0, sizeof(use));
        // cnt: number of letter on the left side
        // use: number of letter on the right side
        // flag: shortcut to judge if a letter has shown up
		int st = 0;
		while (op[st] > 0) {
			if (j < len[st]) {
				flag[data[st][j] - 'A'] = true;
				cnt[data[st][j] - 'A']++;
			}
			++st;
		}
        // eliminate the same letter on both sides with '#'
		for (; st < maxNumNum; ++st) {
			if (j < len[st] && flag[data[st][j] - 'A']) {
				if (cnt[data[st][j] - 'A'] > 0) {
					cnt[data[st][j] - 'A']--;
					use[data[st][j] - 'A']++;
					data[st][j] = '#';
				}
			}
		}
		st = 0;
		while (op[st] > 0) {
			if (j < len[st] && use[data[st][j] - 'A'] > 0) {
				use[data[st][j] - 'A']--;
				data[st][j] = '#';
			}
			++st;
		}
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif	
    scanf("%d", &t);
	while (t--) {
		scanf("%s", &input);
        inputLen = strlen(input);
        // number of letters can't exceed 26
		if (!firstCheck()) {
			puts("No Solution");
			continue;
		}
		ans[0] = '#';
		memset(letter, -1, sizeof(letter));
		memset(data, '#', sizeof(data));
		memset(tempData, '#', sizeof(tempData));
		memset(notZero, 0, sizeof(notZero));
		memset(used, 0, sizeof(used));
		memset(len, 0, sizeof(len));
		memset(op, 0, sizeof(op));

		gen_data_and_len();
		dfs(0, 0, 0);

		if (ans[0] == '#') {
			puts("No Solution");
		}
		else {
			printf("%s\n", ans);
		}
	}
	return 0;
}