#include <bits/stdc++.h>
using namespace std;

struct Node {
    int cover;
    int length;
    int max_length;
};

class Solution {
private:
    // For segment solution
    vector<Node> tree;
    vector<int> x_bound;
    
public:
    void init (int s, int t, int p) {
        tree[p].cover = tree[p].length = 0;
        if (s == t) {
            tree[p].max_length = x_bound[s] - x_bound[s-1];
            return;
        }
        int m = s + ((t - s) >> 1);

        if (s <= m) init(s, m, p*2+1);
        if (t > m) init(m + 1, t, p*2+2);
        tree[p].max_length = tree[p*2+1].max_length + tree[p*2+2].max_length;
    };


    void update (int l, int r, int diff, int s, int t, int p) {
        if (l <= s && t <= r) {
            tree[p].cover += diff;
            maintain(s, t, p);
            return;
        }
        int m = s + ((t - s) >> 1);

        if (l <= m) update(l, r, diff, s, m, p*2+1);
        if (r > m)  update(l, r, diff, m+1, t, p*2+2);
        maintain(s, t, p);
    };

    void maintain(int s, int t, int p) {
        if (tree[p].cover > 0) tree[p].length = tree[p].max_length;
        else if (s == t) tree[p].length = 0;
        else tree[p].length = tree[p*2+1].length + tree[p*2+2].length;
    }

    

    double separateSquares(vector<vector<int>>& squares) {

        int n = squares.size();
        for (auto& rect : squares) {
            x_bound.push_back(rect[0]);             // 左边界 
            x_bound.push_back(rect[0]+rect[2]);     // 右边界
        }
        sort(x_bound.begin(), x_bound.end());
        // unique 将相邻重复元素移动到 vector 末尾，删除重复元素
        x_bound.erase(unique(x_bound.begin(), x_bound.end()), x_bound.end());
        
        // ? 不区分上下边界
        int m = x_bound.size();
        tree.resize(4 * m + 1);
        init(1, m-1, 0);

        vector<tuple<int, int, int>> sweep;     // 扫描线
        for (int i = 0; i < n; ++i) {
            sweep.emplace_back(squares[i][1], i, 1); // 上边界
            sweep.emplace_back(squares[i][1] + squares[i][2], i, -1); // 下边界
        }
        sort(sweep.begin(), sweep.end());
        long tot_area = 0; vector<long long> areas; vector<pair<int, int>> w_h;
        for (int i=0; i<sweep.size(); ++i) {
            int j = i;  // j 为 最大的与 i 的 x 坐标相同的
            while (j+1 < sweep.size() && get<0>(sweep[i]) == get<0>(sweep[j + 1]))
                ++j;
            if (j + 1 == sweep.size()) break;

            for (int k=i; k<=j; ++k) {
                auto&& [_, idx, diff] = sweep[k];
                int left = squares[idx][0], right = squares[idx][0] + squares[idx][2];
                auto l = lower_bound(x_bound.begin(), x_bound.end(), left) - x_bound.begin() + 1;
                auto r = lower_bound(x_bound.begin(), x_bound.end(), right) - x_bound.begin();
                update(l, r, diff, 1, m-1, 0);
            }
            areas.emplace_back(tot_area); w_h.emplace_back(tree[0].length, get<0>(sweep[j]));
            tot_area += 1LL * tree[0].length * (get<0>(sweep[j+1])-get<0>(sweep[j]));
            i = j;      // 跳过相同的 x 坐标
        }
        
        int i = lower_bound(areas.begin(), areas.end(), (tot_area+1)/2) - areas.begin() - 1;
        long long area = areas[i], width = w_h[i].first, height = w_h[i].second;

        return height + (tot_area - area * 2) / (width * 2.0);
    }
};
int main() {
    vector<vector<int>> squares = {{27,28,9},{22,28,2}};
    cout << Solution().separateSquares(squares) << endl;
}