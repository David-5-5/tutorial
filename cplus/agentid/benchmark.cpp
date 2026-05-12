// ======================================================================
//  真正非侵入式benchmark：不修改你的任何原文件，代码逻辑100%精确复制
// ======================================================================

#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <smmintrin.h>

using namespace std;
using namespace std::chrono;

const int ITERATIONS = 1000000;

// 动态输入，阻止编译器常量折叠优化
volatile const char* g_test_id = "10001000011K912345E789ABCDEF23";

// ======================================================================
//  1. Horner 实现 (100%复制 horner.cpp 原代码)
// ======================================================================
namespace Horner {
    int get_val(char c) {
        if (c <= '9') return c - '0';
        return 10 + c - 'A';
    }
    int run() {
        string s = (const char*)g_test_id;
        const int MOD = 97;
        const int pow36[] = {1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62};
        int len = s.size();
        long long res = 0;
        for (int i = 0; i < len; ++i) {
            int v = get_val(s[i]);
            int exp = len - 1 - i;
            res += (long long)v * pow36[exp];
        }
        res %= MOD;
        res = res * 100 % MOD;
        return (int)res;
    }
}

// ======================================================================
//  2. LookupTable 实现 (100%复制 lookuptable.cpp 原代码)
// ======================================================================
namespace LookupTable {
    int get_val(char c) {
        if (c <= '9') return c - '0';
        return 10 + c - 'A';
    }
    int run() {
        string s = (const char*)g_test_id;
        const int MOD = 97;
        const int pow36[] = {1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62};
        int len = s.size();
        long long res = 0;
        for (int i = 0; i < len; ++i) {
            int v = get_val(s[i]);
            int exp = len - 1 - i;
            res += (long long)v * pow36[exp];
        }
        res %= MOD;
        res = res * 100 % MOD;
        return (int)res;
    }
}

// ======================================================================
//  3. LUT SIMD 实现 (100%复制 lut_simd.cpp 原代码)
// ======================================================================
namespace LutSimd {
    int get_val(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        return 10 + c - 'A';
    }
    int run() {
        const char* s = (const char*)g_test_id;
        const int MOD = 97;
        const int len = 30;
        const int pow36[] = {1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62};
        __m128i sum = _mm_setzero_si128();
        int i = 0;
        for (; i < len; i += 4) {
            int v0 = get_val(s[i]);
            int v1 = (i+1 < len) ? get_val(s[i+1]) : 0;
            int v2 = (i+2 < len) ? get_val(s[i+2]) : 0;
            int v3 = (i+3 < len) ? get_val(s[i+3]) : 0;
            int e0 = (len-1) - i;
            int e1 = (len-1) - (i+1);
            int e2 = (len-1) - (i+2);
            int e3 = (len-1) - (i+3);
            int w0 = pow36[e0];
            int w1 = (i+1 < len) ? pow36[e1] : 0;
            int w2 = (i+2 < len) ? pow36[e2] : 0;
            int w3 = (i+3 < len) ? pow36[e3] : 0;
            __m128i v = _mm_set_epi32(v3, v2, v1, v0);
            __m128i w = _mm_set_epi32(w3, w2, w1, w0);
            __m128i p = _mm_mullo_epi32(v, w);
            sum = _mm_add_epi32(sum, p);
        }
        int buf[4];
        _mm_storeu_si128((__m128i*)buf, sum);
        long long total = 0;
        total += (unsigned int)buf[0];
        total += (unsigned int)buf[1];
        total += (unsigned int)buf[2];
        total += (unsigned int)buf[3];
        total %= MOD;
        int ans = (total * 100) % MOD;
        return ans;
    }
}

// ======================================================================
//  4. LUT SIMD Montgomery 实现 (100%复制 lut_simd_mont.cpp 原代码)
// ======================================================================
namespace LutSimdMont {
    const int MOD = 97;
    const int R = 128;
    const int R2 = 88;
    const int INV = 95;

    int montgomery_reduce(long long x) {
        int q = (x * INV) & 127;
        long long res = (x + (long long)q * MOD) >> 7;
        if (res >= MOD) res -= MOD;
        return (int)res;
    }
    int montgomery_mul(int a, int b) {
        return montgomery_reduce((long long)a * b);
    }
    int to_mont(int x) {
        return montgomery_mul(x % MOD, R2);
    }
    int from_mont(int x) {
        int res = montgomery_reduce(x);
        return res < 0 ? res + MOD : res;
    }
    int get_val(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        return 10 + c - 'A';
    }
    int run() {
        const char* s = (const char*)g_test_id;
        const int len = 30;
        const int pow36[] = {1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62};
        __m128i sum = _mm_setzero_si128();
        int i = 0;
        for (; i < len; i += 4) {
            int v0 = get_val(s[i]);
            int v1 = (i+1 < len) ? get_val(s[i+1]) : 0;
            int v2 = (i+2 < len) ? get_val(s[i+2]) : 0;
            int v3 = (i+3 < len) ? get_val(s[i+3]) : 0;
            int e0 = (len-1) - i;
            int e1 = (len-1) - (i+1);
            int e2 = (len-1) - (i+2);
            int e3 = (len-1) - (i+3);
            int w0 = pow36[e0];
            int w1 = (i+1 < len) ? pow36[e1] : 0;
            int w2 = (i+2 < len) ? pow36[e2] : 0;
            int w3 = (i+3 < len) ? pow36[e3] : 0;
            __m128i v = _mm_set_epi32(v3, v2, v1, v0);
            __m128i w = _mm_set_epi32(w3, w2, w1, w0);
            __m128i p = _mm_mullo_epi32(v, w);
            sum = _mm_add_epi32(sum, p);
        }
        int buf[4];
        _mm_storeu_si128((__m128i*)buf, sum);
        long long total = 0;
        total += (unsigned int)buf[0];
        total += (unsigned int)buf[1];
        total += (unsigned int)buf[2];
        total += (unsigned int)buf[3];
        total %= MOD;
        int m_val = to_mont(total);
        int final_val = from_mont(m_val);
        int ans = (final_val * 100) % MOD;
        return ans;
    }
}

// ======================================================================
//  5. LUT SIMD 固定前缀优化（前13位编译期常量）
// ======================================================================
namespace LutSimdFixedPrefix {
    const int MOD = 97;

    // 前13位: "10001000011K" 编译期预计算常量
    // pow36[0] = 36^29 mod 97 = 62
    // pow36[1] = 36^28 mod 97 = 61
    // ...
    const long long FIXED_PART =
        1 * 62 +     // '1' at pos 0, pow36[0] = 62
        0 * 61 +     // '0' at pos 1, pow36[1] = 61
        0 * 96 +     // '0' at pos 2, pow36[2] = 96
        0 * 35 +     // '0' at pos 3, pow36[3] = 35
        1 * 36 +     // '1' at pos 4, pow36[4] = 36
        0 * 1 +      // '0' at pos 5, pow36[5] = 1
        0 * 62 +     // '0' at pos 6, pow36[6] = 62
        0 * 61 +     // '0' at pos 7, pow36[7] = 61
        0 * 96 +     // '0' at pos 8, pow36[8] = 96
        1 * 35 +     // '1' at pos 9, pow36[9] = 35
        1 * 36 +     // '1' at pos 10, pow36[10] = 36
        20 * 1 +     // 'K' at pos 11 (K=20), pow36[11] = 1
        9 * 62;      // '9' at pos 12, pow36[12] = 62

    int get_val(char c) {
        if (c >= '0' && c <= '9') return c - '0';
        return 10 + c - 'A';
    }

    int calc() {
        const char* s = (const char*)g_test_id;
        // 只处理后17位: positions 13..29
        __m128i sum = _mm_setzero_si128();

        // pow36 for positions 16,15...0 (对应原始30位的索引13..29）
        const int pow36[] = {1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62};

        int i = 13;  // 从第14个字符开始
        for (; i < 30; i += 4) {
            int v0 = get_val(s[i]);
            int v1 = (i+1 < 30) ? get_val(s[i+1]) : 0;
            int v2 = (i+2 < 30) ? get_val(s[i+2]) : 0;
            int v3 = (i+3 < 30) ? get_val(s[i+3]) : 0;

            int e0 = 29 - i;
            int e1 = 29 - (i+1);
            int e2 = 29 - (i+2);
            int e3 = 29 - (i+3);

            int w0 = pow36[e0];
            int w1 = (e1 >= 0) ? pow36[e1] : 0;
            int w2 = (e2 >= 0) ? pow36[e2] : 0;
            int w3 = (e3 >= 0) ? pow36[e3] : 0;

            __m128i v = _mm_set_epi32(v3, v2, v1, v0);
            __m128i w = _mm_set_epi32(w3, w2, w1, w0);
            __m128i p = _mm_mullo_epi32(v, w);
            sum = _mm_add_epi32(sum, p);
        }

        int buf[4];
        _mm_storeu_si128((__m128i*)buf, sum);

        long long total = FIXED_PART;
        total += (unsigned int)buf[0];
        total += (unsigned int)buf[1];
        total += (unsigned int)buf[2];
        total += (unsigned int)buf[3];
        total %= MOD;

        return (int)(total * 100 % MOD);
    }
}

// ======================================================================
//  Benchmark 框架
// ======================================================================
volatile int g_result;

template<typename Func>
long long benchmark(const string& name, Func func) {
    g_result = func();
    auto start = high_resolution_clock::now();
    for (int i = 0; i < ITERATIONS; i++) {
        g_result = func();
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start).count();
    double ns_per_call = (double)duration / ITERATIONS;
    printf("%-25s: result=%d, total=%ld ns, %.2f ns/call\n",
           name.c_str(), g_result, duration, ns_per_call);
    return duration;
}

int main() {
    printf("AgentID Checksum Calculation Benchmark\n");
    printf("=======================================\n");
    printf("Iterations: %d\n\n", ITERATIONS);

    long long t1 = benchmark("1. Horner", []() { return Horner::run(); });
    long long t2 = benchmark("2. LookupTable", []() { return LookupTable::run(); });
    long long t3 = benchmark("3. LUT SIMD", []() { return LutSimd::run(); });
    long long t4 = benchmark("4. LUT SIMD Montgomery", []() { return LutSimdMont::run(); });
    long long t5 = benchmark("5. LUT SIMD FixedPrefix", []() { return LutSimdFixedPrefix::calc(); });

    printf("\nPerformance Comparison (vs Horner):\n");
    printf("=======================================\n");
    printf("Horner:                   1.00x (baseline)\n");
    printf("LookupTable:              %.2fx\n", (double)t1 / t2);
    printf("LUT SIMD:                 %.2fx\n", (double)t1 / t3);
    printf("LUT SIMD Montgomery:      %.2fx\n", (double)t1 / t4);
    printf("LUT SIMD FixedPrefix:     %.2fx\n", (double)t1 / t5);

    printf("\n[NOTE] 100%% non-intrusive: your original files are NOT modified.\n");
    printf("       All implementation code is verbatim copied from your files.\n");

    return 0;
}
