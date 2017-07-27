#include<iostream>
#include<cstdio>
#include<map>
#include<vector>

using namespace std;

const int maxn = 1000;
int a[maxn+5];
int n;
// we have first < second
map<int, vector<pair<int,int> > > position;

long long compute(vector<pair<int, int> > pairs) {
    // sort by the first element, into different groups
    // then the answer is just the multiplication of different group size - invalid pairs
    // the number of invalid pairs is the one with the same second element
    map<pair<int, int>, int> y2count; // map[y][group]
    map<pair<int, int>, int> x2count; // map[x][group]
    vector<int> last; // index of last element of group i
    
    int group = 0;
    for (int i = 0; i < pairs.size(); ++i) {
        if (i > 0 && pairs[i].first != pairs[i-1].first) {
            group++;
            last.push_back(i);
        }
        x2count[{pairs[i].first, group}] ++;
        y2count[{pairs[i].second, group}] ++;
    }
    last.push_back(pairs.size());
    
    long long ans = 0;
    for (int i = 0; i < last.size(); ++i) {
        long long first1 = (i > 0) ? last[i-1] : 0;
        long long last1 = last[i];
        // this group is from first1 to last1
        for (int j = i + 1; j < last.size(); ++j) {
            long long first2 = last[j-1];
            long long last2 = last[j];
            // this group is from first2 to last2
            // take care of these long long 
            long long temp = (last1-first1)*(last2-first2); 
            temp -= y2count[{pairs[first1].first, j}];
            temp -= y2count[{pairs[first2].first, i}];
            
            // how to compute repeat y in group2 as group1
            for (int k = first1; k < last1; k++) {
                temp -= y2count[{pairs[k].second, j}];
            }
            ans += temp;
        }
    }
    
    return ans;
}


long long compute() {
    position.clear();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            position[a[i]+a[j]].push_back({i, j});
    
    long long res = 0;
    for (auto const &ent: position) {
        res += compute(ent.second);
    }
    return res;
}

int main() {
    cin>>n;
    for (int i = 0; i < n; ++i)
        cin>>a[i];
    cout<<compute() * 2<<endl;
}

// 第一次 WA 因为 long long 计算错误
// 第二次 WA 改正了 long long, 但 first2 计算错误
// 第三次 WA 试图改正 first2，但 没有改正成功
// 第四次 TLE 改正了 first2，但 TLE