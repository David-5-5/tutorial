from typing import Counter


class Solution:
    def originalDigits(self, s: str) -> str:
        cnt = Counter(s)
        
        d2e = {0:'zero', 1:'one', 2:'two', 3:'three', 4:'four', 5:'five', 6:'six', 7:'seven', 8:'eight', 9:'nine'}

        digits = [0] * 10
        if cnt['z']: # d = 0
            d = 0
            digits[d] = cnt['z']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['w']: # d = 2
            d = 2
            digits[d] = cnt['w']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['u']: # d = 4
            d = 4
            digits[d] = cnt['u']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['x']: # d = 6
            d = 6
            digits[d] = cnt['x']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['g']: # d = 8
            d = 8
            digits[d] = cnt['g']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['f']: # d = 5
            d = 5
            digits[d] = cnt['f']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['v']: # d = 7
            d = 7
            digits[d] = cnt['v']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['r']: # d = 3
            d = 3
            digits[d] = cnt['r']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['o']: # d = 1
            d = 1
            digits[d] = cnt['o']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]

        if cnt['i']: # d = 9
            d = 9
            digits[d] = cnt['i']
            for ch in d2e[d]:
                cnt[ch] -= digits[d]


        return "".join([str(d) * cnt for d, cnt in enumerate(digits)])