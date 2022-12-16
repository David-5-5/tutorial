package tutorial.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;

public class ListFilterSort {

    public static void execute(List<Integer> list) {

        list.removeIf(i -> (i > 2));
        Collections.sort(list);

        System.out.print(list.size());
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
        execute(list);
        System.out.println("In squence duraiton is " + (System.currentTimeMillis() - begin));

    }   

}
