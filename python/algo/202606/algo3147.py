from cmath import inf
from typing import List

# 七、其他线性 DP - 7.1 一维 DP
class Solution:
    def maximumEnergy(self, energy: List[int], k: int) -> int:
        ans, n = -inf, len(energy)
        
        for i in range(n):
            if i + k >= n: ans = max(ans, energy[i]) 
            else: energy[i+k] = max(energy[i+k], energy[i+k] + energy[i])
    
        return ans