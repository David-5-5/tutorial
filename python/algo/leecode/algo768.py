class Solution:
    def maxChunksToSorted(self, arr) -> int:
        # the element of stack is two-value-list [lower, upper]
        # represent a range
        # 数组中的每个元素都是一个区间，lower == upper
        #
        # 要求分段后每段的排序后连接与原数组排序结果相同
        # 则存在
        # stack[i][upper] <= stack[i+1][lower]
        # 即 stack[i][1] <= stack[i+1][0]
        stack = []
        n = len(arr)
        for i in range(n):
            cur = [arr[i], arr[i]]
            while stack and stack[-1][1] > cur[0]: # 与期望条件相反
                # 若不符合上述条件，即将进栈的cur的lower小于栈顶的upper
                # 则合并两个区间
                val = stack.pop(-1)
                cur[0] = min(cur[0], val[0])
                cur[1] = max(cur[1], val[1])
            
            stack.append(cur)
        
        return len(stack)

if __name__ == "__main__":
    sol = Solution()
    arr = [2,1,3,4,4]
    print(sol.maxChunksToSorted(arr))