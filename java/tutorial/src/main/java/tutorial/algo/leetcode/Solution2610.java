package tutorial.algo.leetcode;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;

public class Solution2610 {
    public List<List<Integer>> findMatrix(int[] nums) {
        HashMap<Integer, Integer> cnt = new HashMap<>();
        for (int x:nums) cnt.merge(x, 1, Integer::sum);

        List<List<Integer>> ans = new ArrayList<>();
        while (!cnt.isEmpty()) {
            List<Integer> row = new ArrayList<>();
            for (Iterator<Entry<Integer, Integer>> it = cnt.entrySet().iterator(); it.hasNext(); ) {
                Entry<Integer, Integer> item = it.next();
                row.add(item.getKey());
                if (item.getValue()>1)
                    item.setValue(item.getValue()-1);
                else
                    it.remove();
            }
            ans.add(row);
        }

        return ans;
    }

    public List<List<Integer>> findMatrix2(int[] nums) {
        HashMap<Integer, Integer> cnt = new HashMap<>();
        for (int x:nums) cnt.merge(x, 1, Integer::sum);

        List<List<Integer>> ans = new ArrayList<>();
        while (!cnt.isEmpty()) {
            List<Integer> row = new ArrayList<>();
            for (Integer k : cnt.keySet()) {
                row.add(k);
            }
            ans.add(row);

            for (Integer k :row) {
                if (cnt.get(k) > 1) cnt.put(k, cnt.get(k)-1);
                else cnt.remove(k);
            }
        }

        return ans;
    }    
}
