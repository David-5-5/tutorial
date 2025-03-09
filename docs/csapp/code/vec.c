#include <bits/stdc++.h>
#include "vec.h"

// Create vector of specified length
vec_ptr new_vec(long int len) {
    // Allocate header structure
    vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));

    if (!result) return NULL; // Couldn't allocate storage

    result->len = len;
    /* Allocate array*/
    if (len>0) {
        data_t *data = (data_t *) calloc(len, sizeof(data_t));
        if (!data) {
            free((void*) result);
            return NULL; // Couldn't allocate storage
        }
        result->data = data;
    } else result->data = NULL;

    return result;
}


/**
 * Retrieve vector element and store at dest.
 * Return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long int index, data_t *dest) {
    if (index < 0 || index >= v->len) {
        return 0;
    }
    *dest = v->data[index];
    return 1;
}

// return length of vector
long int vec_length(vec_ptr v) {
    return v->len;
}

void combine1(vec_ptr v, data_t *dest) {
    *dest = INDET;
    for (long int i = 0; i< vec_length(v); i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}


void combine2(vec_ptr v, data_t *dest) {
    long int length = vec_length(v);

    *dest = INDET;
    for (long int i = 0; i< length; i++) {
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}


data_t *get_vec_start(vec_ptr v) {
    return v->data;
}

void combine3(vec_ptr v, data_t *dest) {
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = INDET;
    for (long int i = 0; i< length; i++) {
        data_t val;
        *dest = *dest OP data[i];
    }
}

/**
 * Accumulate result in local variable
 */
void combine4(vec_ptr v, data_t *dest) {
    long int length = vec_length(v);
    data_t *data = get_vec_start(v);

    data_t acc = INDET;
    for (long int i = 0; i< length; i++) {
        data_t val;
        acc = acc OP data[i];
    }
    *dest = acc;
}

/**
 * Accumulate result in local variable
 */
void combine5(vec_ptr v, data_t *dest) {
    long int i;
    long int length = vec_length(v);
    long int limit = length - 1;
    data_t *data = get_vec_start(v);
    data_t acc = INDET;

    // Combine 2 elements at a time
    for (int i=0; i < limit; i+=2) {
        acc = (acc OP data[i]) OP data[i+1];
    }

    for (; i<length; i++) {
        acc = acc OP data[i];
    }
    *dest = acc;

}


int main() {
    vec_ptr v = new_vec(100);
    data_t* result;
    for (int i=0; i<100; i+=2) {
        v->data[i] = i;
    }

    combine1(v, result);
    printf("result of combine1: %d\n", *result);

    combine2(v, result);
    printf("result of combine2: %d\n", *result);

    combine3(v, result);
    printf("result of combine3: %d\n", *result);

    combine4(v, result);
    printf("result of combine4: %d\n", *result);

    combine5(v, result);
    printf("result of combine5: %d\n", *result);
}