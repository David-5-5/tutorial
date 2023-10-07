# 欧拉判别准则 判断n是否为p的二次剩余
# x^2 = n mod p
def testResidual(n,p):
    if pow(n,(p-1)//2)%p == p-1:
        return False
    else:
        return True

# Cipolla算法
# 解方程 x^2 = n mod p 中的x
# 因为是二次方程 所有有两个解
def Cipolla(n,p):
    # 如果n不是p的二次剩余 报错
    if testResidual(n,p) == False:
        raise Exception('No solution')

    # 随机取w^2
    import random
    while True:
        a = random.choice(range(1,(p-1)//2+1)) # [1,(p-1)//2]区间内任取a 这里取半个Fp区间是因为a^2是关于(p-1)//2对称的
        w_2 = (pow(a,2)-n)%p
        if testResidual(w_2,p) == False: # 找到一个w^2 是一个二次非剩余
            break
    
    # 定义Fp2这个域 在class里实现他的运算法则
    class omega_field:

        def __init__(self,a,b):
            self.a = a%p
            self.b = b%p

        # 乘法运算
        def mul(self,another):
            x = self.a*another.a + self.b*another.b*w_2
            y = self.b*another.a + self.a*another.b
            return omega_field(x,y)

        # 乘方运算
        # 快速幂运算
        # 常规循环累乘方的复杂度是O(n) 快速幂运算则是O(logn)
        # 把指数进行了二进制分解 循环次数等于二进制的位数
        def pow(self,n):
            ans = omega_field(1,0)
            t = self
            while(n):
                if n&1:
                    ans = omega_field.mul(ans,t)
                t = omega_field.mul(t,t)
                n >>= 1
            return ans
        
        # get method
        def get(self):
            return self.a,self.b
    
    x = omega_field.pow(omega_field(a,1),(p+1)//2).get()

    # x.b理论上讲一定为0 这里保险起见加一个报错
    if x[1] != 0:
        raise Exception('Please contact the coder, something goes wrong')
    else:
        x = x[0]
    return x,p-x

# 中国余数定理
# pairs是(n,c) n是模数 c是余数
def CRT(pairs):

    def inv(a,b,c):
        import gmpy2
        return (gmpy2.invert(a,c)*b)%c

    x = 0
    m = 1

    for i in pairs:
        m *= i[0]

    for i in pairs:
        x += m//i[0] * inv(m//i[0],i[1],i[0])

    return x%m

# Rabin解密 
# Rabin是公钥为(e=2,n)情况下的RSA
# 返回全部4个可能结果 输出结果为二进制
# c-密文 p,q-为n的质因数分解
def Rabin(c,p,q):

    r = Cipolla(c,p) # r^2 = c mod p
    s = Cipolla(c,q) # s^2 = c mod q

    # 联立上面两个等式
    # 解中国余数定理
    x = []
    n = p*q
    x.append(CRT([(p,r[0]),(q,s[0])]))
    x.append(n-x[0])
    x.append(CRT([(p,r[1]),(q,s[0])]))
    x.append(n-x[2])
    
    for i in x:
        #二进制输出
        print(bin(i)[2:])


if __name__ == '__main__':

    p = 10663
    q = 49123
    c = 162853095
    Rabin(c,p,q)