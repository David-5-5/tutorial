#!/usr/bin/env python3
import time
import subprocess
import os

ITERATIONS = 100000  # Python慢，减少迭代次数
TEST_ID = "10001000011K912345E789ABCDEF23"

# pow36 table
pow36 = [1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62,1,36,35,96,61,62]

def get_val(c):
    if c <= '9':
        return ord(c) - ord('0')
    return 10 + ord(c) - ord('A')

def check_id_pure_python(s):
    """纯Python Horner算法实现"""
    total = 0
    for c in s:
        v = get_val(c)
        total = (total * 36 + v) % 97
    return (total * 100) % 97

def check_id_int_convert(s):
    """利用Python大整数转换 (int(s, 36))"""
    return (int(s, 36) * 100) % 97

def benchmark_py(name, func, s, iterations):
    # warmup
    result = func(s)
    start = time.perf_counter_ns()
    for _ in range(iterations):
        func(s)
    end = time.perf_counter_ns()
    duration = end - start
    ns_per_call = duration / iterations
    print(f"{name:25}: result={result}, total={duration} ns, {ns_per_call:.2f} ns/call")
    return ns_per_call, result

def main():
    os.chdir(os.path.dirname(os.path.abspath(__file__)))

    print("AgentID Checksum Calculation Benchmark - Python vs C++")
    print("=" * 70)
    print(f"Test ID: {TEST_ID}")
    print()

    print("Python Benchmarks (100k iterations):")
    print("-" * 70)
    ns_pure_py, _ = benchmark_py("1. Pure Python Horner", check_id_pure_python, TEST_ID, 100000)
    ns_int_conv, _ = benchmark_py("2. Python int(s, 36)", check_id_int_convert, TEST_ID, 100000)
    print()

    print("Running C++ benchmarks (1M iterations)...")
    print("-" * 70)
    result = subprocess.run(['./benchmark'], capture_output=True, text=True)
    lines = result.stdout.split('\n')

    # Extract C++ results
    cpp_times = {}
    for line in lines:
        if line.startswith(('1. ', '2. ', '3. ', '4. ', '5. ')):
            print(line)
            # "1. Horner                : result=45, total=89172919 ns, 89.17 ns/call"
            parts = line.split(',')
            name = parts[0].split(':')[0].strip()
            ns_str = parts[-1].strip().split(' ')[0]
            ns = float(ns_str)
            cpp_times[name] = ns

    print()
    print("=" * 70)
    print("Performance Comparison (vs Pure Python):")
    print("=" * 70)
    print(f"Pure Python (lookup):      {ns_pure_py:.2f} ns,   1.00x (baseline)")
    print(f"Python int(s, 36):         {ns_int_conv:.2f} ns,   {ns_pure_py/ns_int_conv:.2f}x")
    print()

    baseline = ns_pure_py
    order = ["1. Horner", "2. LookupTable", "3. LUT SIMD", "4. LUT SIMD Montgomery", "5. LUT SIMD FixedPrefix"]
    for name in order:
        if name in cpp_times:
            ns = cpp_times[name]
            speedup = baseline / ns
            print(f"{name:25}: {ns:8.2f} ns,   {speedup:6.2f}x {'🔥' if speedup > 100 else ''}")

    best = min(cpp_times.values())
    print()
    print(f"🏆  Best C++ SIMD FixedPrefix is {baseline/best:.0f}x faster than pure Python!")

if __name__ == "__main__":
    main()
