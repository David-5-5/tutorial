#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 链表 - 1.10 综合应用
class MyLinkedList {
private:
    int size = 0;
    ListNode *head = new ListNode(0);    
public:
    MyLinkedList() {
    }
    
    int get(int index) {
        if (index < 0 || index >= size) return -1;
        auto cur = head;
        for (int i=0; i<=index; ++i) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        // head->next = new ListNode(val, head->next);
        // size ++;
        addAtIndex(0, val);
    }
    
    void addAtTail(int val) {
        // auto cur = head;
        // while (cur->next) {
        //     cur = cur->next;
        // }
        // cur->next = new ListNode(val);
        // size ++;
        addAtIndex(size,val);
    }

    
    void addAtIndex(int index, int val) {
        if (index > size) return;
        auto cur = head;
        for (int i=0; i<index; ++i) {
            cur = cur->next;
        }
        cur->next = new ListNode(val, cur->next);
        size ++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) return;
        auto cur = head;
        for (int i=0; i<index; ++i) {
            cur = cur->next;
        }
        cur->next = cur->next->next;
        size --;
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */