#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 7.2  并查集 - 进阶
class UnionFind {
    vector<int> fa;
public:
    int cc;         // 连通块个数
    UnionFind(int n): fa(n), cc(n) {
        ranges::iota(fa, 0);
    }

    int find(int x) {
        if (fa[x] != x) {
            fa[x] = find(fa[x]);
        }
        return fa[x];
    }

    void merge(int from, int to) {
        int x = find(from), y = find(to);
        if (x != y) {
            fa[x] = y; cc--;
        }
    }
};

class Solution {
public:
    vector<vector<int>> matrixRankTransform(vector<vector<int>>& matrix) {
        // 如下AI自动生成，我是有大致的思路，但是代码实现上有瓶颈
        if (matrix.empty() || matrix[0].empty()) {
            return {};
        }

        int m = matrix.size();
        int n = matrix[0].size();

        // Collect all elements with their positions
        vector<tuple<int, int, int>> elements;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                elements.emplace_back(matrix[i][j], i, j);
            }
        }

        // Sort elements by value
        sort(elements.begin(), elements.end());

        // Initialize result matrix
        vector<vector<int>> answer(m, vector<int>(n));
        vector<int> rowMaxRank(m, 0);     // Current maximum rank for each row
        vector<int> colMaxRank(n, 0);     // Current maximum rank for each column

        int idx = 0;
        const int totalElements = static_cast<int>(elements.size());

        while (idx < totalElements) {
            int currentVal = get<0>(elements[idx]);

            // Step 1: Group all elements with same value
            vector<pair<int, int>> group;   // 相同元素分组
            while (idx < totalElements && get<0>(elements[idx]) == currentVal) {
                auto& elem = elements[idx];
                group.emplace_back(get<1>(elem), get<2>(elem));
                idx++;
            }

            // Step 2: Use Union-Find to connect rows and columns
            UnionFind uf(m + n);    // 每个值建立并查集，同行同列的值相同的元素的秩相同，！！没想到！！
            for (auto& coord : group) {
                int i = coord.first;
                int j = coord.second;
                uf.merge(i, m + j);  // Rows are 0..m-1, cols are m..m+n-1
            }

            // Step 3: Store coordinates by connected components
            unordered_map<int, vector<pair<int, int>>> componentDict;
            for (auto& coord : group) {
                int i = coord.first;
                int root = uf.find(i);
                componentDict[root].push_back({i, coord.second});
            }

            // Step 4: Assign ranks to each component
            for (auto& entry : componentDict) {
                auto& component = entry.second;
                int maxCurrentRank = 0;

                // Find the maximum existing rank in this component's rows and columns
                for (auto& coord : component) {
                    int i = coord.first;
                    int j = coord.second;
                    maxCurrentRank = max(maxCurrentRank, 
                                        max(rowMaxRank[i], colMaxRank[j]));
                }

                int newRank = maxCurrentRank + 1;

                // Update the answer and track the new maximums
                for (auto& coord : component) {
                    int i = coord.first;
                    int j = coord.second;
                    answer[i][j] = newRank;
                    rowMaxRank[i] = newRank;
                    colMaxRank[j] = newRank;
                }
            }
        }

        return answer;
    }
};