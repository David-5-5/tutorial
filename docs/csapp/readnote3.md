[toc]

# 优化程序性能

_你能获得的对程序最大的加速比就是当你第一次让它工作起来的时候_ -- Jonh K. Ousterhout

编写高效程序需要几类程序：
1. 选择一组合适的算法和数据结构
2. 编写出编译器能够有效优化以转换成高效可执行代码的源代码
3. 针对处理运算量特别大的计算，将一个任务分成多个部分，可以在多核和多处理器的某种组合上并行的计算

对于第 2 点，理解优化编译器的能力和局限性是很重要的。

即使最好的编译器也受到 __妨害优化的因素__ (optimization blocker) 的阻碍，妨碍优化的因素就是程序行为中那些严重依赖于执行环境的方面。程序员必须编写容易优化的代码，以帮助编译器。


## 优化编译器的能力和局限性
编译器必须对程序只使用 __安全__ 优化，也就是说在 C 语言标准保证之下，优化后得到的程序和未优化的版本有一样的行为。

第一个妨害优化的因素：两个指针可能指向同一个存储器位置的情况称为 __存储器别名使用__ (memory aliasing).
```C++
x = 1000; y = 3000;
*q = y;         /* 3000 */
*p = x;         /* 1000 */
t1 = *q;        /* 1000 or 3000*/
```
`t1` 的计算值依赖于指针 `p` 和 `q` 是否指向存储器的同一个位置，如果不是，`t1` 就等于3000, 如果是，`t1` 就等于1000。


第二个妨碍优化的因素是函数调用
```C
int f();

int func1() {
    return f() + f() + f() + f()
}

int func2() {
    return 4 * f()
}
```
最初看上去两个过程计算都有相同的结果，但是 `func2()` 调用 `f` 1 次，而 `func1()` 调用 `f` 4 次。以 `func1()` 作为源时，会很想产生 `func2()` 风格的代码。 考虑下面 `f` 的代码：
```C
int counter = 0;
int f() {
    return counter ++;
}
```
大多数编译器不会试图判断一个函数是否没有副作用，因此任意函数都可能是优化的候选者。相反，编译器会假释糟糕的情况，并保持所有的函数调用不变。


## 表示程序性能
引入度量标准 _每元素的周期数_ (Cycles Per Element, CPE)，作为一种表示程序性能并改进代码的方法。用时钟周期来表示，度量值表示的是执行了多少条指令，而不是时钟运行的有多快。许多过程含有在一组元素上迭代的循环。例如 psum1 和 psum2 计算的都是一个长度为 n 的向量的前置和。
```C++
void psum1(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i=1; i < n; i++) 
        p[i] = p[i-1] + a[i];
}

void psum2(float a[], float p[], long int n) {
    long int i;
    p[0] = a[0];
    for (i=1; i < n-1; i+=2) {
        float mid_val = p[i-1] + a[i]
        p[i] = mid_val;
        p[i+1] = mid_val + a[i+1];
    }
    /* For even n, finish remaining elements */
    if (i<n)
        p[i] = p[i-1] + a[i];
}
```
函数 psum1 每次迭代计算结果向量中的一个元素。第二个函数使用 _循环展开_ (loop unrolling) 的技术，每次迭代计算两个元素。本章后面会探讨循环展开的好处。这个过程所需要的时间可以用一个常数加上一个与被处理元素个数成正比的因子来描述。例如我们发现 psum1 和 psum2 的运行时间分别近似于 `496+10.0n` 和 `500+6.5n`。这两个等是表明对代码计时和初始化过程、准备循环以及完成过程中的开销为 496～500 个时钟周期加上每个元素 6.5 或 10.0 周期的线性因子。这项中的系数称为 _每元素的周期数_ 的有效数。



## 程序示例
定义了结构体 `vec_rec` 及其指针类型 `vec_ptr`；以及结构体的方法 `new_vec`, `get_vec_element`, `combine1`。

> 代码 code/vec.h code/vec.c


## 消除循环的低效率
修改了代码示例 `combine2`, 改进循环的测试效率。通过把对 vec_length 的调用移出循环测试。这个优化是一类常见的优化的例子，称为 _代码移动_ (code motion)。这类优化包括识别要执行多次但是计算结果不会改变的计算。

> 代码 code/vec.h code/vec.c

优化编译器会试着进行代码移动。但对于会改变在哪里调用函数或调用多少次变换，编译器通常会非常小心。它们不能可靠的发现一个函数是否有副作用。为了改进代码，程序员必须经常帮助编译器显式的进行代码移动。


> vector.size() 可否在循环中使用
>> https://www.geeksforgeeks.org/vector-size-in-cpp-stl/
>> Does the size() method affect vector performance?
>> No, calling size() does not affect the performance as it operates in O(1) time.
>
> 编译器在循环中调用 vector.size() 是否有优化？ 是否会频繁的进行方法调用的入栈出栈操作？

lower代码举例，`stelen` 方法的时间复杂度为 O(n).
> 代码 code/chapter5-lower.cpp

这个示例说明编程时一个常见的说明，一个看上去无足重轻的代码片段有隐藏的渐进低效率 (asymptotic inefficiency)


## 减少过程调用
过程调用会带来相当大的开销，而且妨碍大多数形式的程序优化。从 `combine2` 中可以看出，每次循环都会调用 `get_vec_element` 来获取下一个向量元素。

作为替代，为抽象类型增加一个函数 `get_vec_start`。这个函数返回数组的起始地址，然后就优化成 `combine3` 的过程，其中循环中没有函数调用嗯。一个纯粹主义者会说这种变换严重影响了程序的模块性。

> `combine3` 方法在代码 code/vec.c


## 消除不必要的存储器引用
`combine3` 的代码将合并运算计算的值累积在指针 `dest` 指定的位置。通过循环产生的汇编代码，可以看出这个属性。
```
// combine3: data_t = float , OP = *
// i in %rdx, data in %rax, des in %rbp
.L498                               loop:
moves (%rbp), %xmm0                     Read product from dest
mulss (%rax, %rdx, 4), %xmm0            Multiply product by data[i]
movss %xmm0, (%rbp)                     Store product at dest
addq  $1, %rdx                          Increment 1
cmpq  %rdx, %r12                        Compare i:limit
jq    .L498                             if >, goto loop
```

这样的读写很浪费，每次迭代开始时从 dest 读出的值就是上次迭代最后写入的值。我们能够消除这样无用的存储器读写，优化的 `combine4` 引入一个临时变量 acc，它在循环中用来累积计算出来的值。只有在循环结束时才存放在 dest 中。`combine4` 的汇编代码如下：
```
// combine4: data_t = float , OP = *
// i in %rdx, data in %rax, limit in %rbp, acc in %xmm0
.L498                               loop:
mulss (%rax, %rdx, 4), %xmm0            Multiply acc by data[i]
addq  $1, %rdx                          Increment 1
cmpq  %rdx, %r12                        Compare i:limit
jq    .L498                             if >, goto loop
```

> `combine4` 方法在代码 code/vec.c 中

使用命令行选项 "-O2" 的 GCC 来编译 `combine3` 时，得到的代码 CPE 性能远好于使用 "-O1" 时，检查编译器产生的汇编代码如下：
```
// combine3: data_t = float , OP = *, compiled -O2
// i in %rdx, data in %rax, limit in %rbp, dest at %rx12
.L560                                loop:
mulss (%rax, %rdx, 4), %xmm0            Multiply product by data[i]
addq  $1, %rdx                          Increment 1
cmpq  %rdx, %rbp                        Compare i:limit
movss %xmm0, (%r12)                     Store product at dest
jq    .L498                             if >, goto loop
```


