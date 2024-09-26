package tutorial.algo.leetcode;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

// 双周赛 125
public class Solution3067 {
    private int signalSpeed;
    List<int[]>[] g;

    private int dfs(int u, int fa, int w) {
        int res = w % signalSpeed== 0 ? 1 : 0 ;

        for (int[] v : g[u]) {
            if (v[0] != fa)
                res += dfs(v[0], u, w + v[1]);
        }

        return res;
    }

    public int[] countPairsOfConnectableServers(int[][] edges, int signalSpeed) {
        int n = edges.length + 1;
        this.signalSpeed = signalSpeed;
        g = new ArrayList[n];
        Arrays.setAll(g, e -> new ArrayList<>());
        for (int[] e : edges) {
            int x = e[0];
            int y = e[1];
            int wt = e[2];
            g[x].add(new int[]{y, wt});
            g[y].add(new int[]{x, wt});
        }

        int [] ans = new int[n];
        for (int u = 0; u < n; u++ ) {
            int prev = 0; // previous count of children
            for (int[] v : g[u]) {
                int cnt = dfs(v[0], u, v[1]);
                ans[u] += prev * cnt;
                prev += cnt;
            }
        }

        return ans;

    }

    public static void main(String[] args ) {
        int[][] nums = new int[][]{{0,1,1},{1,2,5},{2,3,13},{3,4,9},{4,5,2}};
        int[] ans  = new Solution3067().countPairsOfConnectableServers(nums, 1);
        for (int a : ans) System.out.print(a + ",");
        System.out.println("");
    }
}
