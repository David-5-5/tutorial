#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.4 堆 - 第 K 小/大
class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        // 自行解答
        int n = arr.size();
        priority_queue<tuple<double, int, int>, vector<tuple<double, int, int>>, greater<>> pq;

        // 初始化，将nums[0]/nums[i] i=[1,n) 加入队列 nums[0]/nums[n-1] 肯定是最小值
        for (int i=1; i<n; ++i) pq.emplace(1.0*arr[0]/arr[i], 0, i);    
        
        for (int i=0; i<k-1; ++i) {
            auto [_, u, v] = pq.top(); pq.pop();
            // 将 arr[u+1]/arr[v] 作为候选入优先队列
            pq.emplace(1.0*arr[u+1]/arr[v], u+1, v);
        }

        return {arr[get<1>(pq.top())], arr[get<2>(pq.top())]};  

    }
};