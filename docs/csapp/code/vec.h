/**
 * Create abstract data type for vector
 */

typedef int data_t;

typedef struct{
    long int len;
    data_t *data;
} vec_rec, *vec_ptr;


# define INDET 0
# define OP +

// # define INDET 1
// # define OP *

