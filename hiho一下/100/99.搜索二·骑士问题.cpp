// http://hihocoder.com/contest/hiho99/problem/1

// 先检查了所有一步的状态
// 然后检查所有两步的状态

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;


bool check(int status) {
    return ((status & 0x3f) == ((status >> 6) & 0x3f)) && (((status >> 6) & 0x3f) == ((status >> 12) & 0x3f));
}

int step[1<<18]; // 1<<n == 2**n
bool visited[1<<18];

int convert(string p) {
    int a = p[0] - 'A';
    int b = p[1] - '1'; // 注意题目中的坐标范围是 '1'-'8'
    return (a << 3) | b;
}

int merge(int s[3]) {
    return (s[0] << 12) | (s[1] << 6) | s[2];
}

int dir[][2] = {-2, 1, -2, -1, -1, 2, -1, -2, 2, 1, 2, -1, 1, 2, 1, -2};

int apply(int s, int j) {
    int a = s>>3 & 0x7;
    int b = s & 0x7;
    a += dir[j][0];
    b += dir[j][1];
    if (a < 0 || a >= 8 || b < 0 || b >= 8)
        return -1;
    return a << 3 | b;
}

void print_status(int s) {
    cout<<((s>>3)&7)<<" "<<(s&7)<<endl;
    cout<<((s>>9)&7)<<" "<<((s>>6)&7)<<endl;
    cout<<((s>>15)&7)<<" "<<((s>>12)&7)<<endl;
    return ;
}

int next_status(int s, int i, int j) {
    int s_[3];
    s_[0] = s>>12 & 0x3f;
    s_[1] = s>>6 & 0x3f;
    s_[2] = s & 0x3f;
    s_[i] = apply(s_[i], j);
    if (s_[i] == -1)
        return -1;
    return merge(s_);
}

int solve(string p[3]) {
    int s[3];
    for (int i = 0; i < 3; ++i) {
        s[i] = convert(p[i]);        
    }
    int status = merge(s);
    queue<int> q;
    q.push(status);
    visited[status] = true;
    step[status] = 0;
    if (check(status))
        return 0;
    while (q.size()) {
        status = q.front();
        q.pop();
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 8; ++j) {
                int status_ = next_status(status, i, j);
                if (visited[status_])
                    continue;
                if (status_ == -1)
                    continue;
                if (check(status_))
                    return step[status] + 1;
                visited[status_] = true;
                step[status_] = step[status] + 1;
                q.push(status_);
            }
    }
}


int main() {
    int t;
    cin>>t;
    while(t--) {
        memset(visited, false, sizeof visited);
        memset(step, 0, sizeof step);
        string p[3];
        for (int i = 0; i < 3; ++i)
            cin>>p[i];
        cout<<solve(p)<<endl;
    }
    return 0;
}