/* event_vec[0].reserve(2 * Q); 
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cassert>
using namespace std;

struct event {
    int t; // start time
    int n; // lane
    int x; // type

    event() {}
    event(int _t, int _n, int _x) :
            t(_t), n(_n), x(_x) {}

    bool operator < (const event& other) const {
        if (t == other.t) {
            return x < other.x;
        } else {
            return t < other.t;
        }
    }
};

int main()
{
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
    int TASKS;
    cin >> TASKS;
    while (TASKS--) {
        int T, L, R, N, Q;
        scanf("%d %d %d %d %d", &T, &L, &R, &N, &Q);
        vector<event> event_vec[2];
        event_vec[0].reserve(2 * Q); // 1, -1 for direction 0
        event_vec[1].reserve(2 * Q);

        for (int i = 0; i < Q; i++) {
            int t, l, n, d;
            scanf("%d %d %d %d", &t, &l, &n, &d);
            if (L < l) {
                event_vec[d].push_back(event(t, n, 1));
                event_vec[d].push_back(event(t + l - L, n, -1));
            } else if (L == l) {
                event_vec[d].push_back(event(t - 1, n, 1));
                event_vec[d].push_back(event(t + 1, n, -1));
            } else {
                event_vec[d].push_back(event(t + l - L, n, 1));
                event_vec[d].push_back(event(t, n, -1));
            }
            event_vec[1-d].push_back(event(t - L, n, 1));
            event_vec[1-d].push_back(event(t + l, n, -1));
        }
        sort(event_vec[0].begin(), event_vec[0].end());
        sort(event_vec[1].begin(), event_vec[1].end());

        int time = T;
        int dir = 0;
        int event_idx[2] = {0, 0}; // the index of next event
        int lane[2][N]; // lane[0][i]: for direction 0 and lane i, whether it is free to go
        memset(lane, 0, sizeof(int) * N * 2);

        while (R) {
            bool found = false;
            while (event_idx[dir] < 2 * Q) {
                event e = event_vec[dir][event_idx[dir]];
                if (e.t < time) {
                    lane[dir][e.n] += e.x;
                    event_idx[dir]++;
                } else {
					// e.t >= time
                    for (int i = 0; i < N; i++) {
                        if (lane[dir][i] == 0) {
                            found = true;
                            time += L;
                            break;
                        }
                    }
                    if (found) {
                        break;
                    } else {
						// all lanes are occupied
                        time = e.t; // move time to e.t, then continue to check
                        lane[dir][e.n] += e.x;
                        event_idx[dir]++;
                    }
                }
            } // only found or done will cause a break
            if (!found) {
                time += L;
            }
            dir = 1 - dir;
            R--;
        }
        cout << time << endl;
    }
}