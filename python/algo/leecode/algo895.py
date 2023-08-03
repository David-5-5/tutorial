from sortedcontainers import SortedDict
class FreqStack:

    def __init__(self):
        # key is frequency, value is list of value
        # A val should be in each key's list from
        # 1 .. current frequnce
        self.freq_stack = SortedDict()
        # key is val, value is current freq
        # push the stack, the freq increase 1
        # and pop the stack, the freq decrease 1
        self.val_freq = {}

    def push(self, val: int) -> None:
        freq = 0
        if val in self.val_freq.keys():
            self.val_freq[val] += 1
        else:
            self.val_freq[val] = 1
        
        freq = self.val_freq[val]

        if freq not in self.freq_stack.keys():
            self.freq_stack[freq] = [val]
        else:
            self.freq_stack[freq].append(val)

    def pop(self) -> int:
        maxfreq = max(self.freq_stack.keys())
        ret = self.freq_stack[maxfreq].pop(-1)
        if len(self.freq_stack[maxfreq]) == 0:
            del self.freq_stack[maxfreq]
        
        self.val_freq[ret] -= 1
        return ret

# Your FreqStack object will be instantiated and called as such:
# obj = FreqStack()
# obj.push(val)
# param_2 = obj.pop()