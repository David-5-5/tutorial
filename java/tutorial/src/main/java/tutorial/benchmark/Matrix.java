package tutorial.benchmark;

public class Matrix {

    public static long[][] multipleA(int[][] A, int[][] B) {
        int rank = A.length;
        long[][] result = new long[rank][rank];

        for (int i=0; i<rank; i++){
            for (int j=0; j<rank; j++){
                long sum = 0;
                for (int k=0; k<rank; k++){
                    sum += A[i][k] * B[k][j];
                }
                result[i][j] = sum;
            }
        }
        return result;
    }

    public static long[][] multipleB(int[][] A, int[][] B) {
        int rank = A.length;
        long[][] result = new long[rank][rank];

        for (int j=0; j<rank; j++){
            for (int k=0; k<rank; k++){
                long rB = B[k][j];
                for (int i=0; i<rank; i++) {
                    result[i][j] += A[i][k] * rB;
                }
            }
        }
        return result;
    }

    public static long[][] multipleC(int[][] A, int[][] B) {
        int rank = A.length;
        long[][] result = new long[rank][rank];

        for (int k=0; k<rank; k++){
            for (int i=0; i<rank; i++) {
                long rA = A[i][k];
                for (int j=0; j<rank; j++) {
                    result[i][j] += B[k][j] * rA;
                }
            }
        }
        return result;
    }
}
