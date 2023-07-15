package tutorial.benchmark;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;


@BenchmarkMode(Mode.AverageTime)
@State(Scope.Benchmark)
@Warmup(iterations = 1, time = 1)
@Measurement(iterations = 1, time = 1)
public class BufferedBenchmark {
    public static String fileName = "/home/luming/Downloads/spring-boot-main.zip";

    public int count(InputStream in, int expect) throws IOException {
        int count = 0;
        int buf = in.read();
        while (buf != -1) {
            if (buf == expect)
                count ++;
            buf = in.read();
        }
        return count;

    }


    public static void main(String[] args) throws IOException {
        org.openjdk.jmh.Main.main(args);
        // BufferedBenchmark bench = new BufferedBenchmark();
        // bench.testCountWithoutBuffered();
        // bench.testCountWithBuffered();

    } 

    @Benchmark
    public void testCountWithBuffered() throws FileNotFoundException, IOException {
        try (BufferedInputStream bis = new BufferedInputStream(new FileInputStream(fileName))) {
            int result = count(bis, 50);
            System.out.print(result);
        }
    }
    
    @Benchmark
    public void testCountWithoutBuffered() throws FileNotFoundException, IOException {
        try (FileInputStream fis = new FileInputStream(fileName)) {
            int result = count(fis, 50);
            System.out.print(result);
        }
    }
    

}
