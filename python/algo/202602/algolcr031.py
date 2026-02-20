# 同 146 LRU 缓存
class ListNode:
    def __init__(self, key=0, val=0, prev=None, next=None):
        self.key = key
        self.val = val
        self.prev = prev
        self.next = next
        
class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.head = ListNode()
        self.tail = ListNode()
        self.head.next = self.tail
        self.tail.prev = self.head
        
    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        self.move_after_head(self.cache[key])
        return self.cache[key].val
    
    def put(self, key: int, value: int) -> None:
        if key in self.cache:
            self.move_after_head(self.cache[key])
            self.cache[key].val = value
        else:
            node = ListNode(key, value)
            self.add_node(node)
            self.cache[key] = node
        if (len(self.cache) > self.capacity):
            self.remove()
         
    def move_after_head(self, node: ListNode):
        node.prev.next = node.next
        node.next.prev = node.prev
        self.add_node(node)
    
    def add_node(self, node: ListNode):
        node.prev = self.head
        node.next = self.head.next
        self.head.next = node
        node.next.prev = node

    def remove(self):
        self.cache.pop(self.tail.prev.key)
        self.tail.prev = self.tail.prev.prev
        self.tail.prev.next = self.tail
