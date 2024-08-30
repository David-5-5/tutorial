// 在命令行执行下列语句：
// gcc -S sum.c
// 就能得到 C 语言编译器产生的汇编代码 sum.s
// gcc -c sum.c 产生目标代码文件 sum.o，它是二进制表示
// 要查看目标代码的内容，最有价值的是反汇编器。根据目标代码产生一种类似于汇编代码的格式
// 执行 objdump -d sum.o
int accum = 0;

int sum(int x, int y) {
    int t = x + y;
    accum += t;
    return t;
}