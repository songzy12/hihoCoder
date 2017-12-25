#include<iostream>
#include<map>
#include<set>
using namespace std;

int main() {
	map<string, int> purchase;
	int n;
	cin>>n;
	for (int i = 0; i < n; ++i) {
		set<string> prods;
		int m;
		cin>>m;
		for (int j = 0; j < m; ++j) {
			string id, date, price;
			cin>>id>>date>>price;
			prods.insert(id + price);
		}
		for (auto & prod: prods) {
			purchase[prod]++;
		}
	}
	
	for (auto &kv: purchase) {
		if (kv.second == n) {
			cout<<kv.first.substr(0,9)<<endl;
		}
	}
	return 0;
}