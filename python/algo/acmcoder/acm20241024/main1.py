# def solution():
#     m, n = [int(i) for i in input().split()]
#     print(f"m={m} n={n}")

# while True:
#     try:
#         solution()
#     except:
#         break
#     # except Exception as err:
#     #     print(err)
#     #     break


n =  int(input().strip())
nums = []
for _ in range(n):
    p, r = [int(i) for i in input().split()]
    nums.append((r*10+p))


ans = []
for i, _  in sorted(enumerate(nums), key=lambda p:p[1], reverse=True):
    ans.append(str(i+1))

print(" ".join(ans))

