#include <bits/stdc++.h>
using namespace std;

template<typename T>
class FenwickTree {
    vector<T> arr;
public:
    FenwickTree(int n) : arr(n+1) { }

    void update(int i, T val) {
        while (i < arr.size()) {
            arr[i] += val;
            i += i & -i;
        }
    }

    T pre(int i)  {
        T ans = 0;
        while (i>0) {
            ans += arr[i];
            i -= i & -i;    // i &= i - 1
        }
        return ans;
    }
};

class StreamRank {
private:
    FenwickTree<int> ft;
public:
    StreamRank():ft(50001){
    }
    
    void track(int x) {
        ft.update(x+1, 1);  // x 值域开始为 1
    }
    
    int getRankOfNumber(int x) {
        return ft.pre(x+1);
    }
};
/**
 * Your StreamRank object will be instantiated and called as such:
 * StreamRank* obj = new StreamRank();
 * obj->track(x);
 * int param_2 = obj->getRankOfNumber(x);
 */