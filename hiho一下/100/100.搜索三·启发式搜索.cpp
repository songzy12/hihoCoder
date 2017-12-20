// http://hihocoder.com/contest/hiho100/problem/1

// 康托展开

// X = a[1]*(n-1)!+a[2]*(n-2)!+...+a[i]*(n-i)!+...+a[n-1]*1!+a[n]*0!
// 其中a[i]表示在num[i+1..n]中比num[i]小的数的数量

// min X = 0
// max X = (n-1) * (n-1)! + ... + 0 * 0! = n! - 1

// all possible values are n * (n-1) * ... * 1 = n!

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

using namespace std;

const int n = 9;
int fac[n];

void init(){
	fac[0] = 1;
	for (int i = 1; i < n; ++i)
		fac[i] = i * fac[i-1];
}

int Cantor(int num[], int n) {
	int x = 0;
	for (int i = 0; i < n; ++i) {
		int tp = 0;
		for (int j = i+1; j < n; ++j)
			if (num[j] < num[i])
				tp++;
		x = x + tp * fac[n - 1 - i];
	}
	
	return x;
}

void unCantor(int x, int num[], int n) {
	int a[9];
	bool used[9];
	memset(used, false, sizeof used);

	for (int i = 0; i < n; ++i) {
		a[i] = x / fac[n-i-1];
		x = x % fac[n-i-1];
		int cnt = 0;
		for (int j = 0; j < n; ++j) {
			if (!used[j]) {
				cnt++;
				if (cnt == a[i] + 1) {
					num[i] = j + 1;
					used[j] = true;
					break;
				}
			}
		}
	}
}

// 启发式搜索

struct state{
	int status;
	vector<int> neighborStatus;
	int g, f, h;

	bool operator<(const state& rhs) const
    {
        if(f == rhs.f) 
			return g > rhs.g;
		return f > rhs.f; // notice the direction of >
    }
};

void printf_status(int status) {
	int temp[n];
	unCantor(status, temp, n);
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (temp[3*i+j] == 9)
				printf("  ");
			else
				printf("%d ", temp[3*i+j]);
		}
		printf("\n");
	}
	printf("\n");
}

vector<int> compute_neighbors(int status) {
	int temp[n];
	unCantor(status, temp, n);

	vector<int> res;
	int i, j;
	bool flag = false;
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			// TODO:
            if (temp[3*i+j] == 9) {
                flag = true;
				break;
			}
		}
        if (flag)
            break;
	}

    // i, j is 9
	int dir[][2] = {-1, 0, 1, 0, 0, -1, 0, 1};
	for (int k = 0; k < 4; ++k) {
		int dx = dir[k][0];
		int dy = dir[k][1];
		if (i+dx < 0 || i+dx > 2 || j+dy < 0 || j+dy > 2)
			continue;
    	swap(temp[3*i+j], temp[3*(i+dx)+j+dy]);
    	int status_ = Cantor(temp, n);
		res.push_back(status_);

		swap(temp[3*i+j], temp[3*(i+dx)+j+dy]);
	}
	return res;
}

void goal(int k, int &x, int &y) {
	x = k / 3;
	y = k % 3;
}

int evaluate(int status) {
	int temp[n];
	unCantor(status, temp, n);
	
	int res = 0;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int k = temp[i*3+j] - 1;
			
			// TODO:
			if (k == 8)
				continue;
			int x, y;
			goal(k, x, y);
			res += abs(x - i) + abs(y - j);
		}
	}
	return res;
}

int solve(int num[], int n) {
	state start;
	start.status = Cantor(num, n);
	start.g = 0;
	start.h = evaluate(start.status);
	start.f = start.g + start.h;

	int end_[n];
	for (int i = 0; i < n; ++i)
		end_[i] = i + 1;
	int end = Cantor(end_, n);

	priority_queue<state> min_f;
	map<int, state> openlist;
	map<int, bool> closelist;

	min_f.push(start);
	openlist[start.status] = start;

	while(!openlist.empty()) {
		int cur = min_f.top().status;
		min_f.pop();

		state u = (openlist[cur]);
		openlist.erase(cur);

        closelist[cur] = true;

		//printf("Cantor: %d, cur: %d, g: %d\n", u.status, cur, u.g);
		//printf_status(cur);
		
		if (cur == end)
            return u.g;

		vector<int>::iterator neighbor;

		vector<int> neighbors = compute_neighbors(cur);;
		for (neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor) {
			int v = *neighbor;
			if (closelist.find(v) != closelist.end()){
				continue;
			} else {		
				//printf("neighbor: %d\n", v);	
				if (openlist.find(v) != openlist.end()) {
					if (((openlist[v])).f > ((openlist[v])).h + u.g + 1) {
						((openlist[v])).f = ((openlist[v])).h + u.g + 1;
						min_f.push((openlist[v]));
					}
				} else {
					state v_; // 居然每次生成的 state 的位置是一样的！！！
					v_.status = v;
					v_.g = u.g + 1;
					v_.h = evaluate(v_.status);
					v_.f = v_.g + v_.h;
					//printf("g: %d, h: %d\n", v_.g, v_.h);
					openlist[v] = v_;					
					min_f.push(v_); // 但是这样 push 的时候大概是复制了一份吧
				}
			}
		}
	}
	return -1;
}

int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);

	init();

	int t;
	cin>>t;
	while(t--) {
		int num[n];
		for (int i = 0; i < n; ++i) {
			cin>>num[i];
			if (num[i] == 0)
				num[i] = n;
		}
				
		//printf("Cantor: %d, f: %d\n", Cantor(num, n), evaluate(Cantor(num, n)));
		int result = solve(num, n);
		if (result == -1)
			cout<<"No Solution!"<<endl;
		else 
			cout<<result<<endl;
	}
	return 0;
}

// C++ 的指针是个大坑！！！！