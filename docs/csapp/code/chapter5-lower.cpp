#include <bits/stdc++.h>
using namespace std;


void lower1(char *s) {
    for (int i = 0; i<strlen(s); i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] -= ('A' - 'a');
}


void lower2(char *s) {
    int len = strlen(s);
    for (int i = 0; i<len; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] -= ('A' - 'a');    
}

/**
 * Sample implementation of library function strlen
 * Compute length of string
 */
size_t strlen(const char *s) {
    int lenght = 0;
    while (*s != '\0') {
        s++;
        lenght ++;
    }
    return lenght;
}

int main() {
    char t[] = "Hello World"; // Writable
    // char *s = "HelloWorld";  // Readonly, modify literal would occurs Segmentation Fault.
    lower1(t);
    printf("<%s>\n", t);

    char s[] = "Hello World"; // Writable
    lower2(s);
    printf("<%s>\n", s);
}
