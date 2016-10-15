#include <iostream>     // std::cout
#include <algorithm>    // std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>       // std::vector
using namespace std;
int main () {
    int N;
    cin>>N;
    vector<int> heap;
    while(N--) {
        char type;
        cin>>type;
        if (type == 'A') {
            int W;
            cin>>W;
            heap.push_back(W);
            push_heap(heap.begin(), heap.end());
        } else {
            pop_heap(heap.begin(), heap.end());
            int ans = heap.back();
            heap.pop_back();
            cout<<ans<<endl;
        }
    }
    return 0;
}