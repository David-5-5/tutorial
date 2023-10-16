from sortedcontainers import SortedDict
class ListNode:
    def __init__(self, key=0, val=0, freq=1, prev=None, next=None):
        self.key = key
        self.val = val
        self.prev = prev
        self.next = next
        # ListNode has two type, 1: value node 
        # 2, Endpiont node, inclcude head, tail for each freq,
        # For endpoint, the freq should always be -1.
        self.freq = freq

class LFUCache:

    def __init__(self, capacity: int): 
        self.capacity = capacity
        # store the key/value
        # key is int and 
        # value is ListNode which wrap the value of int
        self.cache = SortedDict()
        # store the freq of each 
        # key is freq
        # value is head and tail of double queue
        self.freqs = SortedDict()

    def get(self, key: int) -> int:
        if key not in self.cache.keys():
            return -1
        cur = self.cache[key]
        self._updateFreq(cur)
        return cur.val

    def put(self, key: int, value: int) -> None:
        if key not in self.cache.keys():
            if len(self.cache) == self.capacity :
                self._remove()
            self._newInstance(key, value)
        else:
            cur = self.cache[key]
            cur.val = value
            self._updateFreq(cur)

    def _newInstance(self, key: int, value: int) :
        node = ListNode(key, value)
        self._insertFreq(node)

        self.cache[key] = node
    
    def _updateFreq(self, node: ListNode) :
        # remove from origial freqs
        if node.prev.freq == -1 and node.next.freq == -1:
            del self.freqs[node.freq]
        else:
            prev,next = node.prev, node.next
            prev.next = next
            next.prev = prev
        
        # insert into next freq
        node.freq += 1
        self._insertFreq(node)

    def _insertFreq(self, node: ListNode):
        if node.freq not in self.freqs.keys():
            head = ListNode(0, 0, -1)
            tail = ListNode(0, 0, -1)
            head.next = tail
            tail.prev = head
            self.freqs[node.freq] = (head, tail)        
        # insert node after head
        next = self.freqs[node.freq][0].next

        node.prev = self.freqs[node.freq][0]
        self.freqs[node.freq][0].next = node
        next.prev = node
        node.next = next
        
    def _remove(self): 
        # values[0] is head, values[1] is tail
        _, values = self.freqs.peekitem(0)
        node = values[1].prev

        # The freq only include one node, delele freq key directory
        if values[1].prev.prev.freq == -1:
            self.freqs.popitem(0)
        else:
            node.prev.next = values[1]
            values[1].prev = node.prev
        
        del self.cache[node.key]

if __name__ == "__main__":
    lfu = LFUCache(2)

    lfu.put(1,1)
    lfu.put(2,2)
    print(lfu.get(1))
    lfu.put(3,3)
    print(lfu.get(2))
    print(lfu.get(3))
    lfu.put(4,4)
    print(lfu.get(1))
    print(lfu.get(3))
    print(lfu.get(4))
