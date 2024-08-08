# include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    for (int i=0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(x));
}

int main() {
    int i = 12345;
    float f = 12345.0;
    
    show_int(i);
    show_float(f);
    show_pointer(&i);

    int val = 0x87654321;
    byte_pointer p = (byte_pointer) &val;
    show_bytes(p, 1);
    show_bytes(p, 2);
    show_bytes(p, 3);
    show_bytes(p, 4);
}