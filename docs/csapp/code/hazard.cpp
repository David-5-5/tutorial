#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <climits>
#include <algorithm>

// 定义数组长度（可修改，建议≥1000万以体现时间差异）
#define ARR_SIZE 200000

// 方法1：无哨兵，循环内判断边界（触发CPU流水线控制冒险）
long long calcMaxSumWithoutSentinel(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    long long max_sum = LLONG_MIN;

    for (int i = 0; i < n; ++i) {
        long long curr_sum = arr[i]; // 先加自身
        // 分支判断：i-1是否越界（触发流水线控制冒险）
        if (i - 1 >= 0) {
            curr_sum += arr[i-1];
        }
        // 分支判断：i+1是否越界（触发流水线控制冒险）
        if (i + 1 < n) {
            curr_sum += arr[i+1];
        }
        max_sum = std::max(max_sum, curr_sum);
    }
    return max_sum;
}

// 方法2：有哨兵，无边界判断（避免CPU流水线控制冒险）
long long calcMaxSumWithSentinel(const std::vector<int>& arr) {
    int n = arr.size();
    if (n == 0) return 0;
    // // 构造哨兵数组：前加1个0，后加1个0（仅需处理i-1和i+1）
    // std::vector<int> sentinel_arr(n + 2, 0);
    // // 原数组拷贝到哨兵数组的[1, n]位置
    // std::copy(arr.begin(), arr.end(), sentinel_arr.begin() + 1);

    long long max_sum = LLONG_MIN;
    // 遍历原数组对应的哨兵位置（i从1到n），无需任何分支判断
    for (int i = 1; i < n-1; ++i) {
        // 固定求和：i-1 + i + i+1（哨兵保证不越界）
        long long curr_sum = arr[i-1] + arr[i] + arr[i+1];
        max_sum = std::max(max_sum, curr_sum);
    }
    long long val = std::max(1LL * arr[0] + arr[1], 1LL * arr[n-2]+arr[n-1]);
    return std::max(max_sum, val);
}

// 生成指定长度的随机数组（值范围：-1000~1000，避免溢出）
std::vector<int> generateRandomArray(int size) {
    std::vector<int> arr(size);
    // 初始化随机数生成器（高性能、高随机性）
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(-1000, 1000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dist(rng);
    }
    return arr;
}

int main() {
    // 1. 生成超大随机数组
    const int array_size = ARR_SIZE;
    std::cout << "生成数组长度：" << array_size << std::endl;
    std::vector<int> arr = generateRandomArray(array_size);



    // 2. 执行方法1：无哨兵（含分支），统计时间
    auto start1 = std::chrono::high_resolution_clock::now();
    long long res1 = calcMaxSumWithoutSentinel(arr);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration1 = end1 - start1;

    // 3. 执行方法2：有哨兵（无分支），统计时间
    auto start2 = std::chrono::high_resolution_clock::now();
    long long res2 = calcMaxSumWithSentinel(arr);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration2 = end2 - start2;

    // 4. 输出结果（验证计算结果一致，排除逻辑错误）
    std::cout << "===== 计算结果验证 =====" << std::endl;
    std::cout << "无哨兵方法结果：" << res1 << std::endl;
    std::cout << "有哨兵方法结果：" << res2 << std::endl;
    if (res1 == res2) {
        std::cout << "结果一致，逻辑正确！" << std::endl;
    } else {
        std::cout << "结果不一致，逻辑错误！" << std::endl;
    }

    // 5. 输出性能对比
    std::cout << "===== 性能对比（毫秒） =====" << std::endl;
    std::cout << "无哨兵方法执行时间：" << duration1.count() << " ms" << std::endl;
    std::cout << "有哨兵方法执行时间：" << duration2.count() << " ms" << std::endl;
    std::cout << "性能提升比例：" << (duration1.count() - duration2.count()) / duration1.count() * 100 << "%" << std::endl;

    return 0;
}