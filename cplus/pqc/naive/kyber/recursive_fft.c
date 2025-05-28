#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define PI 3.14159265358979323846

// 递归FFT函数
void recursive_fft(complex double *a, complex double *y, int n) {
    if (n == 1) {
        y[0] = a[0];
        return;
    }
    
    complex double *a_even = (complex double *)malloc(n/2 * sizeof(complex double));
    complex double *a_odd = (complex double *)malloc(n/2 * sizeof(complex double));
    complex double *y_even = (complex double *)malloc(n/2 * sizeof(complex double));
    complex double *y_odd = (complex double *)malloc(n/2 * sizeof(complex double));
    
    // 分离偶数和奇数索引元素
    for (int i = 0; i < n/2; i++) {
        a_even[i] = a[2*i];
        a_odd[i] = a[2*i + 1];
    }
    
    // 递归计算偶数和奇数部分的FFT
    recursive_fft(a_even, y_even, n/2);
    recursive_fft(a_odd, y_odd, n/2);
    
    // 合并结果
    for (int k = 0; k < n/2; k++) {
        complex double omega = cexp(2.0 * I * PI * k / n);
        y[k] = y_even[k] + omega * y_odd[k];
        y[k + n/2] = y_even[k] - omega * y_odd[k];
    }
    
    free(a_even);
    free(a_odd);
    free(y_even);
    free(y_odd);
}


int main() {
    // 测试数据
    int n = 8;
    complex double a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    complex double *y = (complex double *)malloc(n * sizeof(complex double));
    
    // 计算FFT
    recursive_fft(a, y, n);
    
    // 输出结果
    printf("FFT结果:\n");
    for (int i = 0; i < n; i++) {
        printf("y[%d] = %.4f + %.4fi\n", i, creal(y[i]), cimag(y[i]));
    }
    
    free(y);
    return 0;
}
