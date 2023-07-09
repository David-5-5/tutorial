# Python3 program for the above approach

# Function to check whether there exists a Hamiltonian Path or not
def exist_use_dp(adj, N):
    dp = [[False for i in range(1 << N)]
                 for j in range(N)]

    # Set all dp[i][(1 << i)] to true
    for i in range(N):
        dp[i][1 << i] = True

    # Iterate over each subset of nodes
    for i in range(1 << N):
        for j in range(N):

            # If the jth nodes is included in the current subset
            if ((i & (1 << j)) != 0):

                # Find K, neighbour of j
                # also present in the
                # current subset
                for k in range(N):
                    if ((i & (1 << k)) != 0 and
                             adj[k][j] == 1 and
                                     j != k 
                            and dp[k][i ^ (1 << j)]):
                        # Update dp[j][i] to true
                        dp[j][i] = True
                        break
    
    # Traverse the vertices
    for i in range(N):
 
        # Hamiltonian Path exists
        if (dp[i][(1 << N) - 1]):
            return True
 
    # Otherwise, return false
    return False


def dfs_use_dp(adj, N):
    def dfs(i, visited):
        if visited == (1 << N) - 1:
            return True

        for j in range(N):
            if i != j and adj[i][j] == 1 and visited & 1 << j == 0:
                return dfs(j, visited | 1 << j)

        return False

    for i in range(N):
        if dfs(i, 1 << i):
            return True
    return False

def dfs_use_dp_withcount(adj, N):
    def dfs(i, visited):
        if visited == (1 << N) - 1:
            return 1
        
        count = 0
        for j in range(N):
            if i != j and adj[i][j] == 1 and visited & 1 << j == 0:
                count += dfs(j, visited | 1 << j)
        return count

    count = 0 
    for i in range(N):
        count += dfs(i, 1 << i)

    return count


# Driver Code
adj = [ [ 0, 1, 1, 1, 0 ] ,
        [ 1, 0, 1, 0, 1 ],
        [ 1, 1, 0, 1, 1 ],
        [ 1, 0, 1, 0, 0 ],
        [ 0, 1, 1, 0, 0 ] ]

adj = [[0, 1, 0, 0], [1, 0, 1, 1], [0, 1, 0, 0], [0, 1, 0, 0]]
N = len(adj)

if (exist_use_dp(adj, N)):
    print("YES")
else:
    print("NO")

if (dfs_use_dp(adj, N)):
    print("YES")
else:
    print("NO")

print(dfs_use_dp_withcount(adj, N))
# This code is contributed by maheshwaripiyush9