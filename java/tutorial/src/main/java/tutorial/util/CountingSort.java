package tutorial.util;

import java.util.Arrays;
import java.util.Random;

public class CountingSort {
    public static void sort(int[] arr, int limit) {
        int[] counts = new int[limit];
        for (int val : arr) {
            counts[val] += 1;
        }

        int inx = 0;
        for (int i = 0; i<limit; i++){
            for (int j=0; j < counts[i]; j++) {
                arr[inx + j]  = i;
            }
            inx += counts[i];
        }
    }


    public static void main(String[] args)
    {
        int n = 1 << 10;
        int[] arr1 = new int[n];
        int[] arr2 = new int[n];
        Random random = new Random();
        int limit = 100;
        for (int i=0; i<n; i++) {
            int val = random.nextInt(limit);
            arr1[i] = val;
            arr2[i] = val;
        }
        sort(arr1, limit);
        Arrays.sort(arr2);
        for (int i = 0; i<n; i++){
            if (arr1[i] != arr2[i])
                System.out.println("Counting sort is wrong");
        }

        n = 1 << 25;
        arr1 = new int[n];
        arr2 = new int[n];
        limit = 20000;
        for (int i=0; i<n; i++) {
            int val = random.nextInt(limit);
            arr1[i] = val;
            arr2[i] = val;
        }

        //System.out.println("Given Array is");
        //printArray(arr, n);
        Long begin = System.currentTimeMillis();
        sort(arr1, limit);
        System.out.println("Execute timSort: " + (System.currentTimeMillis() - begin));
        
        begin = System.currentTimeMillis();
        Arrays.sort(arr2);
        System.out.println("Execute Array.sort " + (System.currentTimeMillis() - begin));
    }

}
