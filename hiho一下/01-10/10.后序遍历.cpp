#include<iostream>
using namespace std;
string preorder, inorder;
void rebuild(int i1, int j1, int i2, int j2){
	if(j1 - i1 == 0)
		return;
	if(j1 - i1 == 1){
		cout<<preorder[i1];
		return;
	}
	int len = 0;
	while(inorder[i2+len] != preorder[i1])
		len ++;
	rebuild(i1+1, i1+1+len, i2, i2+len);
	rebuild(i1+1+len, j1, i2+len+1, j2);
	cout<<preorder[i1];
}
int main(){
	cin>>preorder>>inorder;
	rebuild(0, preorder.size(), 0, inorder.size());
	return 0;
}