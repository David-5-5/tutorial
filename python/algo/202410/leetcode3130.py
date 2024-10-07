from math import perm


class Solution:
    def numberOfStableArrays(self, zero: int, one: int, limit: int) -> int:
        MOD = 1_000_000_007
        sum_p = perm(zero + one) // perm(zero) // perm(one)

        if zero > limit:
            sum_p -= perm(zero + one - limit) // perm(zero-limit) // perm(one)
        
        if one > limit:
            sum_p -= perm(zero + one - limit) // perm(zero) // perm(one-limit)
        
        if zero > limit and one > limit:
            sum_p += perm(zero + one - 2 * limit) // perm(zero-limit)  // perm(one-limit)


        return sum_p % MOD