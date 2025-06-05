#include <bits/stdc++.h>
using namespace std;

// 常用数据结构 - 4.2 队列 - 设计
class MyCircularQueue {
private:
    int capacity, head=0, tail=0;
    vector<int> que;

public:
    MyCircularQueue(int k) {
        this->capacity = k;
        que.assign(k, -1);
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        que[tail] = value;
        tail = (tail + 1) % capacity;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        que[head] = -1;
        head = (head + 1) % capacity;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return que[head];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return que[(tail-1+capacity)%capacity];
    }
    
    bool isEmpty() {
        return tail == head && que[head] == -1;
    }
    
    bool isFull() {
        return tail == head && que[head] != -1;
    }
};



/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */