#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.7 堆 - 对顶堆（滑动窗口第 K 小/大）
class SORTracker {
private:
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;   // 排名靠后的，最好的在堆顶
    priority_queue<pair<int, string>> sel;                                        // 排名靠前的，最差的在堆顶
public:
    SORTracker() {        
    }
    
    void add(string name, int score) {
        sel.emplace(-score, name);      // 先都加入排名考前的，
        pq.push(sel.top()); sel.pop();  // 将排名考前的最后一名，加入排名靠后
    }
    
    string get() {
        sel.emplace(pq.top()); pq.pop();    // 排名靠前的增加一个元素
        return sel.top().second;            // 将排名靠前的最后一个出队列
    }
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */