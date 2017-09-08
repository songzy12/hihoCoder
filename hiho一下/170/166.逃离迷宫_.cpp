#include<iostream>
#include<cstring>
#include<queue>
#include<map>

using namespace std;

const int maxk = 5;
const int maxn = 100;
const int maxm = 100;

string grid[maxn];

int K;
int N, M, a, b, c, d;

pair<int, int> pos_key[maxk];

struct State {
    int _x, _y;
    bool has_key[maxk];

    State(int x, int y) {
        _x = x;
        _y = y;
        memset(has_key, false, sizeof has_key);
    }
    
    bool operator <(const State &rhs) const
    {
        if (_x != rhs._x)
            return _x < rhs._x;
        if (_y != rhs._y)
            return _y < rhs._y;
        for (int i = 0; i < K; ++i)
            if (has_key[i] != rhs.has_key[i])
                return has_key[i] < rhs.has_key[i];
        // do not return false or true here
    }
};

map<State, bool> repeat;

void update_key(State &s) { // note the & here
    for (int i = 0; i < K; ++i) {
        if (s.has_key[i])
            continue;
        if (s._x == pos_key[i].first && s._y == pos_key[i].second) {
            s.has_key[i] = true;
        }
    }
    return;
}

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int solve() {
    queue< pair<State,int> > q;
    State p = State(a, b);
    repeat[p] = true;
    q.push(make_pair(State(a, b), 0));
    while (!q.empty()) {
        State s = q.front().first; 
        int step = q.front().second;
        q.pop();
        if (s._x == c && s._y == d)
            return step;
        for (int i = 0; i < 4; ++i) {
            if (s._x + dx[i] < 0 || s._x + dx[i] >= N || s._y + dy[i] < 0 || s._y + dy[i] >= M) 
                continue;
            int _x = s._x + dx[i];
            int _y = s._y + dy[i];
            if (grid[_x][_y] == '#')
                continue;
            if (grid[_x][_y] != '.' && !s.has_key[grid[_x][_y] - 'A'])
                continue;
            State p = State(_x, _y);
            memcpy(p.has_key, s.has_key, sizeof s.has_key);
            update_key(p);
            if (repeat[p])
                continue;
            q.push(make_pair(p, step + 1));
            repeat[p] = true;
        }
    }
    return -1; // remember this
}

int main() {
    cin>>N>>M>>K>>a>>b>>c>>d;
    for (int i = 0; i < N; ++i)
        cin>>grid[i];
    for (int i = 0; i < K; ++i) {
        cin>>pos_key[i].first>>pos_key[i].second;
    }
    cout<<solve()<<endl;
    return 0;
}
