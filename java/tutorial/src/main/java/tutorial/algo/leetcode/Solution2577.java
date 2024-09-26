package tutorial.algo.leetcode;

import java.util.ArrayList;

public class Solution2577 {
    private final static int[][] DIRS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    private int[][] grid, vis;

    public boolean check(int endTime) {
        // BFS
        int m = grid.length, n = grid[0].length;
        ArrayList<int[]> q = new ArrayList<>();
        q.add(new int[]{m-1,n-1});
        vis[m-1][n-1] = endTime;
        int t = endTime - 1;
        while (q.size()>0) {
            ArrayList<int[]> tmp = q;
            q = new ArrayList<>();
            
            for (int[] pos : tmp) {
                for (int[] d: DIRS) {
                    int x = pos[0] + d[0], y = pos[1] + d[1];
                    if (0<=x && x<m && 0<=y && y < n && vis[x][y]!=endTime && grid[x][y]<=t) {
                        if (x == 0 && y == 0)return true;
                        vis[x][y] = endTime;
                        q.add(new int[]{x, y});
                    }
                }
            }
            t--;
        }

        return false;
    }

    public int minimumTime(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        if (grid[0][1]>1 && grid[1][0]>1) return -1;

        this.grid = grid;
        vis = new int[m][n];

        // 二分查找开区间
        int left = Math.max(m+n-2, grid[m-1][n-1]) - 1;
        int right =  (int) 1e5 + m + n;

        while (left+1 < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            }else{
                left = mid;
            }
        }
        return right + (right + m + n) % 2;
    }    
}
