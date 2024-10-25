
n =  int(input().strip())

for _ in range(n):
    trs = int(input().strip())

    pipe = [int(i) for i in input().split()]
    
    st = []

    for i in range(1, trs+1):
        while st and st[-1] == pipe[0]:
            st.pop(-1)
            pipe.pop(0)
        st.append(i)
    ans = False
    if len(st) == 0 and len(pipe) == 0: ans = True
    elif len(st) != len(pipe):
        ans = False
    elif st and pipe and st == pipe[::-1]:
        ans = True

    print("YES") if ans else print("NO")

