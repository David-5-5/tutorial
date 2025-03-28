/* Code to generate zetas and zetas_inv used in the number-theoretic transform:*/
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h> 

// refer to https://zhuanlan.zhihu.com/p/566394562
// 蒙哥马利算法中, it is R, A * R % q - > A', 将 A 变换到蒙哥马利域上，即 A'
#define MONT -1044      // 2^16 mod q, R(mod N) 模 N 下的 R
#define KYBER_Q 3329    // N
#define QINV -3327      // q^-1 mod 2^16   // 对应 Montgomery 算法中的 k' = -N^-1 mod R

#define KYBER_ROOT_OF_UNITY 17  // 17 ^128 = -1 mod 3329; 256-th root of unity; 
                                // zeta^128 = -1, thus (X^256 + 1) = (X^256 - zeta^128),
                                // and X^k + zeta^r = X^k - zeta^(r+128)

static const uint8_t tree[128] = {  // prepared for bit reverse
  0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
  4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
  2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
  6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126,
  1, 65, 33, 97, 17, 81, 49, 113, 9, 73, 41, 105, 25, 89, 57, 121,
  5, 69, 37, 101, 21, 85, 53, 117, 13, 77, 45, 109, 29, 93, 61, 125,
  3, 67, 35, 99, 19, 83, 51, 115, 11, 75, 43, 107, 27, 91, 59, 123,
  7, 71, 39, 103, 23, 87, 55, 119, 15, 79, 47, 111, 31, 95, 63, 127
};


/*************************************************
* Name:        montgomery_reduce
*
* Description: Montgomery reduction; given a 32-bit integer a, computes
*              16-bit integer congruent to a * R^-1 mod q, where R=2^16
*
* Arguments:   - int32_t a: input integer to be reduced;
*                           has to be in {-q2^15,...,q2^15-1}
*
* Returns:     integer in {-q+1,...,q-1} congruent to a * R^-1 modulo q.
**************************************************/
int16_t montgomery_reduce(int32_t a)
{
  int16_t t;

  t = (int16_t)a*QINV;
  t = (a - (int32_t)t*KYBER_Q) >> 16;
  return t;
}

/*************************************************
* Name:        barrett_reduce
*
* Description: Barrett reduction; given a 16-bit integer a, computes
*              centered representative congruent to a mod q in {-(q-1)/2,...,(q-1)/2}
*
* Arguments:   - int16_t a: input integer to be reduced
*
* Returns:     integer in {-(q-1)/2,...,(q-1)/2} congruent to a modulo q.
**************************************************/
int16_t barrett_reduce(int16_t a) {
  int16_t t;
  const int16_t v = ((1<<26) + KYBER_Q/2)/KYBER_Q;

  t  = ((int32_t)v*a + (1<<25)) >> 26;
  t *= KYBER_Q;
  return a - t;
}

static int16_t fqmul(int16_t a, int16_t b) {  // Finite Field Multiplication
  return montgomery_reduce((int32_t)a*b); // 蒙哥马利模乘
}

const int16_t zetas[128] = {
  -1044,  -758,  -359, -1517,  1493,  1422,   287,   202,
   -171,   622,  1577,   182,   962, -1202, -1474,  1468,
    573, -1325,   264,   383,  -829,  1458, -1602,  -130,
   -681,  1017,   732,   608, -1542,   411,  -205, -1571,
   1223,   652,  -552,  1015, -1293,  1491,  -282, -1544,
    516,    -8,  -320,  -666, -1618, -1162,   126,  1469,
   -853,   -90,  -271,   830,   107, -1421,  -247,  -951,
   -398,   961, -1508,  -725,   448, -1065,   677, -1275,
  -1103,   430,   555,   843, -1251,   871,  1550,   105,
    422,   587,   177,  -235,  -291,  -460,  1574,  1653,
   -246,   778,  1159,  -147,  -777,  1483,  -602,  1119,
  -1590,   644,  -872,   349,   418,   329,  -156,   -75,
    817,  1097,   603,   610,  1322, -1285, -1465,   384,
  -1215,  -136,  1218, -1335,  -874,   220, -1187, -1659,
  -1185, -1530, -1278,   794, -1510,  -854,  -870,   478,
   -108,  -308,   996,   991,   958, -1460,  1522,  1628
};

// the zeta for test the generation methods
int16_t _zetas[128];

// bit reverse
void _br(int16_t* tmp) {
  for(int i=0;i<128;i++) {
    _zetas[i] = tmp[tree[i]];  // bit reverse
    if(_zetas[i] > KYBER_Q/2)
      _zetas[i] -= KYBER_Q;
    if(_zetas[i] < -KYBER_Q/2)
      _zetas[i] += KYBER_Q;
  }
}

void init_ntt() {
  unsigned int i;
  int16_t tmp[128];
  
  tmp[0] = MONT;        // in montgomery field
  for(i=1;i<128;i++)
    // equals to tmp[i-1] * KYBER_ROOT_OF_UNITY % KYBER_Q;
    tmp[i] = fqmul(tmp[i-1],MONT*KYBER_ROOT_OF_UNITY % KYBER_Q);

  _br(tmp);

}


void init_ntt_naive() {
  unsigned int i;
  int16_t tmp[128];
  
  tmp[0] = MONT;        // in montgomery field
  // tmp[0] = 1;           // direct multiple of modulo
  for(i=1;i<128;i++)
    // 
    tmp[i] = tmp[i-1] * KYBER_ROOT_OF_UNITY % KYBER_Q;

  _br(tmp);
}

/*************************************************
* Name:        ntt
*
* Description: Inplace number-theoretic transform (NTT) in Rq.
*              input is in standard order, output is in bitreversed order
*
* Arguments:   - int16_t r[256]: pointer to input/output vector of elements of Zq
**************************************************/
void ntt(int16_t r[256]) {
  unsigned int len, start, j, k;
  int16_t t, zeta;

  k = 1;
  for(len = 128; len >= 2; len >>= 1) {
    for(start = 0; start < 256; start = j + len) {
      zeta = zetas[k++];
      for(j = start; j < start + len; j++) {
        t = fqmul(zeta, r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;
      }
    }
  }
}


void invntt(int16_t r[256]) {
  unsigned int start, len, j, k;
  int16_t t, zeta;
  const int16_t f = 1441; // mont^2/128

  k = 127;
  for(len = 2; len <= 128; len <<= 1) {
    for(start = 0; start < 256; start = j + len) {
      zeta = zetas[k--];
      for(j = start; j < start + len; j++) {
        t = r[j];
        r[j] = barrett_reduce(t + r[j + len]); // 巴雷特约减
        r[j + len] = r[j + len] - t;
        r[j + len] = fqmul(zeta, r[j + len]);
      }
    }
  }

  for(j = 0; j < 256; j++)
    r[j] = fqmul(r[j], f);
}



int main() {

  init_ntt_naive();
  for (int i=0; i<128; i++) {
    printf("%d, ", _zetas[i]);      // _zeats by generating
    if ((i+1)%8==0) printf("\n");
  }
  printf("\n");

  init_ntt();
  for (int i=0; i<128; i++) {
    printf("%d, ", _zetas[i]);      // _zeats by generating
    if ((i+1)%8==0) printf("\n");
  }


  // for (int i=0; i<128; i++) {
  //   // printf("0x%04x, ", (uint16_t)zetas[i]);
  //   printf("0x%" PRIx16 ", ", (uint16_t)zetas[i]);
  // }

  // int16_t b = MONT*KYBER_ROOT_OF_UNITY % KYBER_Q;
  // printf("MONT*KYBER_ROOT_OF_UNITY mod KYBER_Q = %d\n", b);

  // int32_t c = (int32_t)MONT * b;

  // printf("result of a*b = %d\n", c);

  // printf("c mod 3329 = %d\n", c % KYBER_Q);
  // printf("montgomery_reduce(c)= %d\n", montgomery_reduce(c));

  int ring1[256], ring2[256];
  
  memset(ring1, 0, sizeof(ring1));
  memset(ring2, 0, sizeof(ring2));
  

}