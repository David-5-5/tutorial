from typing import List
class Solution:
    def secondGreaterElement(self, nums: List[int]) -> List[int]:
        ''' 如果使用一个栈，当栈非空且栈顶元素小于当前元素，则找到当前元素的更大元素
        要求找到下一个更大元素, 则使用两个栈, st1中放入等待更大元素的数值下标,
        st2, 中放入 st1 中找到已找到更大元素，等待下一个更大元素的数值下标
        '''
        n = len(nums)
        st1, st2 = [], []
        ans = [-1] * n
        for i in range(n):
            # 若 st2 栈顶元素小于 nums[i]， 表示当前元素是该元素的下一个更大元素
            while st2 and nums[st2[-1]] < nums[i]:
                ans[st2[-1]] = nums[i]
                st2.pop(-1)
            # 在 st1 栈顶比较是否小于当前元素， 小于表示已找到更大元素，并移入 st2
            # 移入 st2 保证 数组下标值的单调递减
            pos = len(st1) - 1
            while pos >= 0 and nums[st1[pos]] < nums[i]:
                pos -= 1
            st2 += st1[pos+1:]
            del st1[pos+1:]
            st1.append(i)
        return ans

if __name__ == "__main__":
    sol = Solution()
    nums = [2,4,0,9,6]
    print(sol.secondGreaterElement(nums))