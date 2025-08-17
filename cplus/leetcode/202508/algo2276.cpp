#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 8.5 动态开点线段树
class CountIntervals {
private:
    unordered_map<int, int> tree; // lazy 支持区间更新优化    
public:
    CountIntervals() {
        
    }
    // 动态开点线段树 - 模板 - 区间计数 区间更新 
    void add(int left, int right) {
        auto update = [&] (this auto&& update, int l, int r, int start, int end, int p) -> void {
            if (l <= start && end <= r) {
                tree[p] = end - start + 1;  return; //lazy[p] = 1;
            }
            
            if (tree[p] == end - start + 1) return;

            int m = start + ((end - start) >> 1);

            if (l <= m) update(l, r, start, m, p*2+1);
            if (r > m) update(l, r, m + 1, end, p*2+2);
            
            tree[p] = tree[p*2+1] + tree[p*2+2];
        };        
        update(left, right, 0, 1e9, 0); // [0, 1e9])
    }
    
    int count() {
        return tree[0];
    }
};