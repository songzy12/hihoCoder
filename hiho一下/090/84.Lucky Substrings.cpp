#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool f[110];
bool letter[30];

int main() {

    //freopen("input.txt", "r", stdin);

    f[1] = f[2] = f[3] = f[5] = f[8] = f[13] = f[21] = f[34] = f[55] = f[89] = true;
    char s[110];
    scanf("%s", s);
    vector<string> ans;
    int num = 0;
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        memset(letter, 0, sizeof(letter));
        num = 0;
        for (int j = i; j < len; ++j) {
            if (!letter[s[j] - 'a']) {
                letter[s[j] - 'a'] = true;
                ++num;
            }

            if (f[num])
                ans.push_back(string(s + i, s + j + 1));
        }
    }
    sort(ans.begin(), ans.end());
    printf("%s\n", ans[0].c_str());
    for (int i = 1; i < ans.size(); ++i)
        if (ans[i] != ans[i-1])
            printf("%s\n", ans[i].c_str());
    return 0;
}
