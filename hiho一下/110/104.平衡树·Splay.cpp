// http://hihocoder.com/contest/hiho104/problem/1

// Zig, Zig-Zig, Zig-Zag 操作

// splay(x, y)，表示对x节点进行调整，使得x是y的儿子节点
// 在执行这个操作的时候，需要保证y节点一定是x节点祖先。

/* 
insert(key):
	node = bst_insert(key) // 同普通的BST插入, node为当前插入的新节点
	splay(node, NULL)
	
find(key):
	node = bst_find(key) // 同普通的BST查找, node为查找到的节点
	splay(node, NULL) 
*/
	
/* 
因为要删除[a,b]，那么我就要想办法把[a,b]的数旋转到一个子树上，再将这个子树删掉就行了。
方法和删除一个数相同，我首先将a的前一个数prev和b的后一个数next找出来。
同样将prev旋转至根，再将next旋转为prev的儿子。
那么此时next的左子树一定就是所有[a,b]之间的数了！
*/

// 不再有随机性