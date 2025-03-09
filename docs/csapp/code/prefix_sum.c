#include <stdio.h>

// computes prefix sum of vector a
void psum1(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i=1; i<n; i++)
        p[i] = p[i-1] + a[i];
}

void psum2(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i=1; i<n-1; i+=2) {
        float mid_val = p[i-1] + a[i];
        p[i] = mid_val;
        p[i+1] = mid_val + a[i+1];
    }

    if (i < n) p[i] = p[i-1] + a[i];
}

int main() {
    float a1[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float p1[10];
    psum1(a1, p1, 10);
    // Output the result
    for (int i=0; i<10; i++) printf("%f,", p1[i]);
    printf("\n");

    float a2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    float p2[10];
    psum2(a2, p2, 10);
    // Output the result
    for (int i=0; i<10; i++) printf("%f,", p2[i]);
    printf("\n");    
}