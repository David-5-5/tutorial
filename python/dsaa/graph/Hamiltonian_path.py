# Python3 program for the above approach
 
# Function to check whether there exists a Hamiltonian Path or not
def Hamiltonian_path(adj, N):
     
    dp = [[False for i in range(1 << N)]
                 for j in range(N)]
 
    # Set all dp[i][(1 << i)] to true
    for i in range(N):
        dp[i][1 << i] = True
 
    # Iterate over each subset of nodes
    for i in range(1 << N):
        for j in range(N):
 
            # If the jth nodes is included
            # in the current subset
            if ((i & (1 << j)) != 0):
 
                # Find K, neighbour of j
                # also present in the
                # current subset
                for k in range(N):
                    if ((i & (1 << k)) != 0 and
                             adj[k][j] == 1 and
                                     j != k and
                            dp[k][i ^ (1 << j)]):
                         
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
 
# Driver Code
adj = [ [ 0, 1, 1, 1, 0 ] ,
        [ 1, 0, 1, 0, 1 ],
        [ 1, 1, 0, 1, 1 ],
        [ 1, 0, 1, 0, 0 ] ]
 
N = len(adj)
 
if (Hamiltonian_path(adj, N)):
    print("YES")
else:
    print("NO")
 
# This code is contributed by maheshwaripiyush9