#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.2 队列 - 设计
class Router {
private:
    int limit;
    queue<tuple<int, int, int>> que;
    unordered_set<string> h;        // 使用 string 作为 key
    unordered_map<int, vector<int>> det;

public:
    Router(int memoryLimit) {
        this->limit = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        string key = format("{:06}", source) + format("{:06}", destination) + format("{:010}", timestamp);

        if (h.count(key)) return false;
        if (que.size() == limit) forwardPacket();
        
        que.push({source, destination, timestamp});
        h.insert(key);
        det[destination].push_back(timestamp);
        return true;
    } 
    
    vector<int> forwardPacket() {
        if (que.empty()) return {};
        auto [src, dst, ts] = que.front();
        que.pop();
        h.erase(format("{:06}", src) + format("{:06}", dst) + format("{:010}", ts));
        det[dst].erase(det[dst].begin());
        return {src, dst, ts};
    }

    
    int getCount(int destination, int startTime, int endTime) {
        auto& vec = det[destination];
        int left = ranges::lower_bound(vec, startTime) - vec.begin();
        int right = ranges::upper_bound(vec, endTime) - vec.begin();
        return right-left;
    }
};

// 自定义 hash for tuple
struct TupleHash {
    template<typename T>
    static void hash_combine(size_t& seed, const T& v) {
        // 参考 boost::hash_combine
        seed ^= hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    size_t operator()(const tuple<int, int, int>& t) const {
        auto& [a, b, c] = t;
        size_t seed = 0;
        hash_combine(seed, a);
        hash_combine(seed, b);
        hash_combine(seed, c);
        return seed;
    }
};

class Router {
private:
    int limit;
    queue<tuple<int, int, int>> que;
    // 自定义 tuple opreator，使用 tuple 作为 key，性能提升
    unordered_set<tuple<int, int, int>, TupleHash> h;   
    unordered_map<int, vector<int>> det;

public:
    Router(int memoryLimit) {
        this->limit = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {

        if (h.count({source, destination, timestamp})) return false;
        if (que.size() == limit) forwardPacket();
        
        que.push({source, destination, timestamp});
        h.insert({source, destination, timestamp});
        det[destination].push_back(timestamp);
        return true;
    } 
    
    vector<int> forwardPacket() {
        if (que.empty()) return {};
        auto [src, dst, ts] = que.front();
        que.pop();
        h.erase({src, dst, ts});
        det[dst].erase(det[dst].begin());
        return {src, dst, ts};
    }

    
    int getCount(int destination, int startTime, int endTime) {
        auto& vec = det[destination];
        int left = ranges::lower_bound(vec, startTime) - vec.begin();
        int right = ranges::upper_bound(vec, endTime) - vec.begin();
        return right-left;
    }
};

/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */