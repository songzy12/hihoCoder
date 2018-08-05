#include<iostream>
#include<algorithm>
#include<map>
#include<cstdlib>
// C++ set is ordered.
// otherwise use unordered_set 
using namespace std;

const int maxn = 100000;
pair<int,int> dock[maxn+5];

int n;
	
int solve() {
	int cur = 1;
	bool found = false;
	
	map<int, int> buf;
	map<int, bool> buf_head;
	
	for (int i = n - 1; i >= 0; --i) {
		if (buf.find(dock[i].second) == buf.end())
			buf[dock[i].second] = i; 
		// NOTE: 我们检查所有 B 面是需要的 cur 的纸牌，不能只看当前是不是遇到过
		// 不能只看当前是不是遇到过 A 面重复的情况，
		// 只有在所有的 A 面都不重复的情况下才会去翻最后一张 B 面
		// test case: (2,1) (2,1) (3,1)
	}
	
	bool spare = false;
	for (int i = 0; i + 1 < n; ++i) { // NOTE: here i + 1 < n
		if (dock[i].first == dock[i+1].first) {
			buf_head[dock[i].second] = true;
			buf_head[dock[i+1].second] = true;
			spare = true;
			// NOTE: 一定要翻一张牌，如果有两张牌 A 面一样，随便翻一张
		}
	}
	for (int i = 0; i < n; ++i)  // NOTE: here i < n
		if (dock[i].first == dock[i].second)
			spare = true;
		// NOTE: 一定要翻一张牌，如果有一张牌 AB 一样，随便翻一下
	
	int i = 0;
	int tail = n;
	while(i < tail) {
		//cout<<dock[i].first<<" "<<dock[i].second<<" "<<cur<<endl;
		if (dock[i].first == cur) {
			cur++;			
		}
		else {
			if (found) {
				return cur;				
			}
			if (buf_head[cur]) {
				// 如果有重复的 A 面恰好 B 面是 cur
				found = true;
				cur++;
				continue;
			}
			else if (buf.find(cur) != buf.end() && buf[cur] > i) {
				// NOTE: here we need buf[cur] > i
				// 不存在某个重复的 A 面的 B 面恰好是 cur
				// 这里需要我们找到的这张牌还没有被看过
				// case: (1,4), (2,4), (3,4), (5,3)
				found = true;
				tail = buf[cur]; 
				// NOTE: (2,1), (3,1)
				cur++;
				continue; // NOTE: since here i cannot change
			} else {
				return cur;
			}
		}
		
		while (i + 1 < tail && dock[i].first == dock[i + 1].first)  {
			//buf_head[dock[i].second] = true;
			//buf_head[dock[i+1].second] = true;
			i++;
		}
		i++;
	}
	if (found || spare || tail < n)
		return cur;
	return cur - 1; // NOTE: must turn one around
}

int main() {
	freopen("in.txt", "r", stdin); // NOTE: remember to delete this
	cin>>n;
	for (int i = 0; i < n; ++i)
		cin>>dock[i].first;
	for (int i = 0; i < n; ++i)
		cin>>dock[i].second;
	sort(dock, dock+n);
	cout<<solve()<<endl;
	return 0;
}

// 如今看来最笨的办法反而是最简单的：枚举要被翻过来的那张牌，计算每一个结果。