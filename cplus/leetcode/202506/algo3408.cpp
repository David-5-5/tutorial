#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 5.6 堆 - 懒删除堆
class TaskManager {
private:
    unordered_map<int, pair<int, int>> tasks;
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<>> pq;
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto t: tasks) {
            add(t[0], t[1], t[2]);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        tasks[taskId] = {userId, priority};
        pq.emplace(priority, taskId);        
    }
    
    void edit(int taskId, int newPriority) {
        tasks[taskId].second = newPriority;
        pq.emplace(newPriority, taskId);
    }
    
    void rmv(int taskId) {
        tasks.erase(taskId);
    }
    
    int execTop() {
        while (pq.size() && (!tasks.count(pq.top().second) || tasks[pq.top().second].second != pq.top().first))
            pq.pop();       // Invalidate task, task deleted or priority of task changed
        if (pq.size()) {
            int taskId = pq.top().second, userId = tasks[taskId].first;
            pq.pop(); tasks.erase(taskId);
            return userId;
        } else return -1;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */