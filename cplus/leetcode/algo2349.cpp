#include <bits/stdc++.h>
using namespace std;

// 力扣 双周赛 83
// 平衡树 set
class NumberContainers {

    unordered_map<int, int> i2n;
    unordered_map<int, set<int>> n2i;
public:
    NumberContainers() {
    }
    
    void change(int index, int number) {
        auto it = i2n.find(index);
        if (it != i2n.end()) {
            n2i[it->second].erase(index);
            it->second = number; // 直接在迭代器上修改
        } else i2n[index] = number;
        
        n2i[number].insert(index);
        // i2n[index] = number;
    }
    
    int find(int number) {
        auto it = n2i.find(number);
        if (it == n2i.end() || it->second.empty()) return -1;
        return *it->second.begin(); // begin() 是一个指针，取指向的值加 *
    }
};

// 懒惰堆
class NumberContainers2 {
    unordered_map<int, int> i2n;
    unordered_map<int, priority_queue<int, vector<int>, greater<int>>> n2i;
public:

    void change(int index, int number) {
        i2n[index] = number;
        n2i[number].push(index);
    }
    
    int find(int number) {
        while (!n2i[number].empty() and i2n[n2i[number].top()] != number)
            n2i[number].pop();
        return n2i[number].empty() ? -1 : n2i[number].top();
    }
};


/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */