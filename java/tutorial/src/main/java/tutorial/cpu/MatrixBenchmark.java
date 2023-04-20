package tutorial.cpu;

import java.io.IOException;
import java.util.Random;

import org.openjdk.jmh.annotations.Benchmark;
import org.openjdk.jmh.annotations.BenchmarkMode;
import org.openjdk.jmh.annotations.Fork;
import org.openjdk.jmh.annotations.Measurement;
import org.openjdk.jmh.annotations.Mode;
import org.openjdk.jmh.annotations.Setup;
import org.openjdk.jmh.annotations.Scope;
import org.openjdk.jmh.annotations.State;
import org.openjdk.jmh.annotations.Warmup;

@Fork(2)
@BenchmarkMode(Mode.Throughput)
//@BenchmarkMode(Mode.AverageTime)
@State(Scope.Benchmark)
// 预热3次
@Warmup(iterations = 3, time = 1)
// 循环 10 次
@Measurement(iterations = 10, time = 1)
public class MatrixBenchmark {
    private static int[][] A = new int[1000][1000];
    private static int[][] B = new int[1000][1000];


    @Setup
    public void setUp() {
        Random random = new Random();
        for (int i=0; i<1000; i++) {
            for (int j=0; j<1000; j++) {
                A[i][j] = random.nextInt();
                B[i][j] = random.nextInt();
            }
        }
    }

    public static void main(String[] args) throws IOException {
        org.openjdk.jmh.Main.main(args);
    }

    @Benchmark
    public void testMultipleA() {
        Matrix.multipleA(A, B);
    }
    
    @Benchmark
    public void testMultipleB() {
        Matrix.multipleB(A, B);
    }

    @Benchmark
    public void testMultipleC() {
        Matrix.multipleC(A, B);
    }
}

