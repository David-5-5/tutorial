package tutorial.util.stream;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Set;
import java.util.stream.Collectors;

public class ListFilterSort {

    public static void executeInSquential(List<Integer> list) {
        Set<Integer> collect = list.stream()
            .filter(e -> e > 2)
            .sorted()
            //.map(e -> e * 2)
            .collect(Collectors.toSet());
        
        System.out.print(collect.size());
    }

    public static void executeInParral(List<Integer> list) {
        Set<Integer> collect = list.stream()
            .parallel()
            .filter(e -> e > 2)
            .sorted()
            //.map(e -> e * 2)
            .collect(Collectors.toSet());
        
        System.out.print(collect.size());
    }

    public static void main(String[] args) {
        List<Integer> list = new ArrayList<>();
        int n = 19999999;
        Random random = new Random();
        Long begin = System.currentTimeMillis();
        for (int i=0; i<n; i++) {
            list.add(random.nextInt());
        }
        System.out.println("Prepare data duration is " + (System.currentTimeMillis() - begin));

        begin = System.currentTimeMillis();
        executeInSquential(list);
        System.out.println("In squence duraiton is " + (System.currentTimeMillis() - begin));

        begin = System.currentTimeMillis();
        executeInParral(list);
        System.out.println("In pararel duraiton is " + (System.currentTimeMillis() - begin));
    }   
}