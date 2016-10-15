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

void get_factor(int num, vector<int> & factor) {
    for (int i = 1; i <= num; ++i) {
        if (num % i == 0)
            factor.push_back(i);
    }
}

int main(){
	ios::sync_with_stdio(false);
	int p, q;
    cin>>p>>q;
    vector<int> factor_p;
    vector<int> factor_q;
    get_factor(p, factor_p);
    get_factor(q, factor_q);
    for (size_t i = 0; i < factor_p.size(); ++i)
        for (size_t j = 0; j < factor_q.size(); ++j)
            cout<<factor_p[i]<<" "<<factor_q[j]<<endl;
	return 0;
}