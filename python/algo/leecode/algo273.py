class Solution:
    def numberToWords(self, num: int) -> str:
        if num == 0: return 'Zero'
        unit = 0
        output = []
        div = num // 1000
        rem = num % 1000
        while div > 0 or rem > 0:
            output = self.transfer(rem, unit) + output
            rem = div % 1000
            div = div // 1000
            unit += 1

        return ' '.join(output)


    def transfer(self, rem:int, unit:int) -> str:
        units = {0:'', 1:'Thousand', 2:'Million', 3:'Billion'}
        numToE = {0:'Zero', 1:'One', 2:'Two', 3:'Three', 4:'Four', 5:'Five', 6:'Six', 
        7:'Seven', 8:'Eight', 9:'Nine', 10:'Ten', 11:'Eleven', 12:'Twelve', 13:'Thirteen',
        14:'Fourteen', 15:'Fifteen', 16:'Sixteen', 17:'Seventeen', 18:'Eighteen', 19:'Nineteen', 
        20:'Twenty', 30:'Thirty', 40:'Forty', 50:'Fifty', 60:'Sixty', 70:'Seventy', 80:'Eighty', 90:'Ninety'}
        if rem == 0: return []
        hund = rem // 100
        output = []
        if hund > 0:
            output.append(numToE[hund])
            output.append('Hundred')
        
        rem = rem % 100
        if rem > 0 and rem <= 20:
            output.append(numToE[rem])
        elif rem > 20:
            output.append(numToE[(rem // 10) * 10])
            if rem % 10 > 0:
                output.append(numToE[rem % 10])

        if unit>0 : output.append(units[unit])
        return output

if __name__ == "__main__":
    sol = Solution()
    num = 1000000
    print(sol.numberToWords(num))