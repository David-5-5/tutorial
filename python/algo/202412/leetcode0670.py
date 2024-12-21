class Solution:
    def maximumSwap(self, num: int) -> int:
        # 自行解答，后缀最大值, 两次遍历
        # 官方题解 暴力 O(n^2)
        # 其他题解 一次遍历
        sl = list(str(num))
        suf_mx = [-1] * len(sl)
        suf_mx[-1] = len(sl)-1
        
        # print(suf_mx)
        for i in range(len(sl)-2,-1,-1):
            if sl[i] > sl[suf_mx[i+1]]: # 如果有相同的最大值，交换后面的值
                suf_mx[i] = i
            else: suf_mx[i] = suf_mx[i+1]
        
        for i in range(len(sl)-1):
            if sl[i] < sl[suf_mx[i+1]]:
                sl[i], sl[suf_mx[i+1]] = sl[suf_mx[i+1]], sl[i]
                break
        
        return int("".join(sl))
