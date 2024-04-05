package tutorial.util;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class TypeAdd {
    public static void main(String[] args) {
        int n = 1 << 26;
        List<Integer> arr1 = new ArrayList<>();
        List<Double> arr2 = new ArrayList<>();

        Random random = new Random();

        for (int i = 0; i < n; i++) {
            arr1.add(random.nextInt());
            arr2.add(random.nextDouble());
        }

        // System.out.println("Given Array is");
        // printArray(arr, n);
        Long begin = System.currentTimeMillis();
        long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr1.get(i);
        }
        System.out.println("Integer sum is " + sum);
        System.out.println("Integer Add" + (System.currentTimeMillis() - begin));

        begin = System.currentTimeMillis();
        double sum2 = 0;
        for (int i = 0; i < n; i++) {
            sum2 += arr2.get(i);
        }
        System.out.println("Double sum is " + sum2);
        System.out.println("Double add " + (System.currentTimeMillis() - begin));

    }
}
