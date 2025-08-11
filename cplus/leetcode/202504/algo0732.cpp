#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 -  2.1 一维差分
class MyCalendarThree {
    map<int, int> diff;

    // for dynamic segment tree
    // ID begin at 0:
    // left_child_id  = parent_id * 2 + 1
    // right_child_id = parent_id * 2 + 2
    unordered_map<int, int> tree, lazy; // lazy 支持区间更新优化       
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        // 参考题解 同 731, 真是会者不难，难者不会!!!
        diff[startTime] ++;
        diff[endTime] --;
        
        int cnt = 0;
        for (auto& [_, c] : diff) {
            cnt += c;
        }

        return cnt;        
    }


    bool book2(int startTime, int endTime) {
        // 参考题解 用差分数组结合区间统计
        auto pushdown = [&](int start, int end, int p) -> void {
            if (start == end || !lazy.count(p) || lazy[p] == 0) return;
            tree[p * 2 + 1] += lazy[p]; lazy[p * 2 + 1] += lazy[p];
            tree[p * 2 + 2] += lazy[p]; lazy[p * 2 + 2] += lazy[p];
            lazy[p] = 0;
        };

        auto update = [&] (this auto&& update, int l, int r, int val, int start, int end, int p) -> void {
            if (l <= start && end <= r) {
                tree[p] += val; lazy[p] += val; return;
            }
            
            if (lazy[p]) pushdown(start, end, p);

            int m = start + ((end - start) >> 1);

            if (l <= m)
                update(l, r, val, start, m, p*2+1);
            if (r > m)
                update(l, r, val, m + 1, end, p*2+2);
            
            tree[p] = max(tree[p*2+1], tree[p*2+2]);
        };

        auto query = [&] (this auto&& query, int l, int r, int start, int end, int p) -> int {
            
            if (!tree.count(p) || end < l || start > r) return 0;
            if (l <= start && end <= r) {
                return tree[p];
            }

            if (lazy[p]) pushdown(start, end, p);

            int m = (start + end) >> 1;
            int res = 0;
            if (l <= m) res = max(res, query(l, r, start, m, p*2+1));
            if (r > m) res = max(res, query(l, r, m+1, end, p*2+2));
            return res;
        };
        // 动态开点线段树 - 模板 - 区间最大值 区间更新 懒标记
        int start = 0, end = 1e9;
        // if (query(startTime, endTime-1, start, end, 0) > k-2) return false;
        update(startTime, endTime-1, 1, start, end, 0);
        return query(start, end, start, end, 0);
    }
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(startTime,endTime);
 */