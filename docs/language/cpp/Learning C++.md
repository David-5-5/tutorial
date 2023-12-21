# Learing C++

[toc]


## C++ Fundemental

### Type

#### std::size_t
`std::size_t`是`sizeof`运算符结果的无符号整数类型, 也是`sizeof`运算符和对齐运算符（自 C++11 起）. `std::size_t`可以存储理论上可能的任何类型的对象（包括数组）的最大大小. 大小不能用`std::size_t`表示的类型格式不正确. 在许多平台上（具有分段寻址的系统除外）, `std::size_t`可以安全地存储任何非成员指针的值，在这种情况下，它与 `std::uintptr_t` 同义。

`std::size_t`通常用于数组索引和循环计数。使用其他类型（如无符号 int）进行数组索引的程序可能会失败，例如，当索引超过 64 位系统时，UINT_MAX 或依赖于 32 位模块化算术。

在索引C++容器（如 `std::string`、`std::vector` 等）时，相应的类型是此类容器提供的成员 `typedef size_type`。它通常被定义为 `std::size_t` 的同义词。



> https://en.cppreference.com/w/cpp/types/size_t

### Variable assignment and initialization

#### Variable Assignment

After a variable has been defined, you can give it a value (in a separate statement) using the = operator. This process is called assignment, and the = operator is called the assignment operator.


```cpp
int width; // define an integer variable named width
width = 5; // assignment of value 5 into variable width

// variable width now has value 5
```


#### Variable Initialization

One downside of assignment is that it requires at least two statements: one to define the variable, and one to assign the value.
赋值的一个缺点是它至少需要两个语句：一个用于定义变量，另一个用于赋值。

These two steps can be combined. When a variable is defined, you can also provide an initial value for the variable at the same time. This is called initialization. The value used to initialize a variable is called an initializer.
这两个步骤可以结合起来。定义变量时，还可以同时为变量提供初始值。这称为初始化。用于初始化变量的值称为初始值设定项。

Initialization in C++ is surprisingly complex, so we’ll present a simplified view here.
C++ 中的初始化非常复杂，因此我们将在这里提供一个简化的视图。


There are 6 basic ways to initialize variables in C++:
```c++
int a;         // no initializer (default initialization)
int b = 5;     // initializer after equals sign (copy initialization)
int c( 6 );    // initializer in parenthesis (direct initialization)

// List initialization methods (C++11) (preferred)
int d { 7 };   // initializer in braces (direct list initialization)
int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
int f {};      // initializer is empty braces (value initialization)
```


##### Default Initialization
When no initialization value is provided (such as for variable a above), this is called default initialization. In most cases, default initialization leaves a variable with an indeterminate value.
当未提供初始化值时（例如上面的变量 a），这称为默认初始化。在大多数情况下，默认初始化会使变量具有不确定的值。

##### Copy Initialization

When an initializer is provided after an equals sign, this is called copy initialization. This form of initialization was inherited from C.
当在等号后提供初始值设定项时，这称为复制初始化。这种初始化形式继承自 C。
```c++
int width = 5; // copy initialization of value 5 into variable width
```
Much like copy assignment, this copies the value on the right-hand side of the equals into the variable being created on the left-hand side. In the above snippet, variable width will be initialized with value 5.
与复制赋值非常相似，这会将等号右侧的值复制到左侧创建的变量中。在上面的代码段中，变量 width 将使用值 5 进行初始化。


Copy initialization had fallen out of favor in modern C++ due to being less efficient than other forms of initialization for some complex types. However, `C++17` remedied the bulk of these issues, and copy initialization is now finding new advocates. You will also find it used in older code (especially code ported from C), or by developers who simply think it looks more natural and is easier to read.
复制初始化在现代 C++ 中已经失宠，因为对于某些复杂类型，复制初始化的效率低于其他形式的初始化。然而，C++17 解决了大部分这些问题，复制初始化现在正在寻找新的倡导者。您还会发现它在较旧的代码（尤其是从 C 移植的代码）中使用，或者被那些只是认为它看起来更自然、更易于阅读的开发人员使用。


Copy initialization is also used whenever values are implicitly copied or converted, such as when passing arguments to a function by value, returning from a function by value, or catching exceptions by value.
每当隐式复制或转换值时，例如按值将参数传递给函数、按值从函数返回或按值捕获异常时，也会使用复制初始化。

##### Direct Initialization

When an initializer is provided inside parenthesis, this is called direct initialization.
当在括号内提供初始值设定项时，这称为直接初始化。
```c++
int width( 5 ); // direct initialization of value 5 into variable width
```

Direct initialization was initially introduced to allow for more efficient initialization of complex objects (those with class types, which we’ll cover in a future chapter). Just like copy initialization, direct initialization had fallen out of favor in modern C++, largely due to being superseded by list initialization. However, we now know that list initialization has a few quirks of its own, and so direct initialization is once again finding use in certain cases.
直接初始化最初是为了允许更有效地初始化复杂对象（那些具有类类型的对象，我们将在以后的章节中介绍）。就像复制初始化一样，直接初始化在现代 C++ 中已经失宠，主要是由于被列表初始化所取代。但是，我们现在知道列表初始化有其自身的一些怪癖，因此在某些情况下，直接初始化再次被使用。

Direct initialization is also used when values are explicitly cast to another type.
当值显式转换为另一种类型时，也使用直接初始化。

One of the reasons direct initialization had fallen out of favor is because it makes it hard to differentiate variables from functions. For example:
直接初始化失宠的原因之一是因为它很难区分变量和函数。例如：
```c++
int x();  // forward declaration of function x
int x(0); // definition of variable x with initializer 0
```


##### List Initialization
The modern way to initialize objects in C++ is to use a form of initialization that makes use of curly braces. This is called list initialization (or uniform initialization or brace initialization).
在 C++ 中初始化对象的现代方法是使用使用大括号的初始化形式。这称为列表初始化（或统一初始化或大括号初始化）。

List initialization comes in three forms:
```c++
int width { 5 };    // direct list initialization of value 5 into variable width
int height = { 6 }; // copy list initialization of value 6 into variable height
int depth {};       // value initialization (see next section)
```
Prior to the introduction of list initialization, some types of initialization required using copy initialization, and other types of initialization required using direct initialization. List initialization was introduced to provide a more consistent initialization syntax (which is why it is sometimes called “uniform initialization”) that works in most cases.Additionally, list initialization provides a way to initialize objects with a list of values (which is why it is called “list initialization”). 
在引入列表初始化之前，某些类型的初始化需要使用复制初始化，而其他类型的初始化需要使用直接初始化。引入列表初始化是为了提供一种更一致的初始化语法（这就是为什么它有时被称为“统一初始化”），在大多数情况下都有效。此外，列表初始化提供了一种使用值列表初始化对象的方法（这就是它被称为“列表初始化”的原因）。

List initialization has an added benefit: it disallows “narrowing conversions”. This means that if you try to brace initialize a variable using a value that the variable can not safely hold, the compiler will produce an error. 列表初始化还有一个额外的好处：它不允许“缩小转换范围”。这意味着，如果尝试使用变量无法安全保存的值来大括号初始化变量，编译器将产生错误。
For example:
```c++
int width { 4.5 }; // error: a number with a fractional value can't fit into an int
```
In the above snippet, we’re trying to assign a number (4.5) that has a fractional part (the .5 part) to an integer variable (which can only hold numbers without fractional parts).
在上面的代码片段中，我们尝试将一个具有小数部分（.5 部分）的数字 （4.5） 分配给一个整数变量（它只能保存没有小数部分的数字）。

Copy and direct initialization would simply drop the fractional part, resulting in the initialization of value 4 into variable width (your compiler may produce a warning about this, since losing data is rarely desired). However, with list initialization, the compiler will generate an error instead, forcing you to remedy this issue before proceeding.
复制和直接初始化只会删除小数部分，从而导致值 4 初始化为可变宽度（编译器可能会对此产生警告，因为很少希望丢失数据）。但是，在列表初始化时，编译器将生成错误，迫使您在继续操作之前解决此问题。



## GCC Command Options

### Attribute Syntax


`__attribute__` 是一个用于在声明时指定一些特性的编译器指令，可以让我们进行更多的错误检查以及高级优化工作。关于__attribute__具体解释，查了一下GNU C关于它的描述，摘录如下
> The syntax with which `__attribute__` may be used, and the constructs to which attribute specifiers bind, for the C language. Some details may vary for C++ and Objective-C. Because of infelicities in the grammar for attributes, some forms described here may not be successfully parsed in all cases.
对于 C 语言，可以使用 `__attribute__` 的语法，以及属性说明符绑定到的构造。对于 C++ 和 Objective-C，某些细节可能会有所不同。由于属性语法的缺陷，此处描述的某些形式可能无法在所有情况下都成功解析。


`__attribute__`语法格式为：
`__attribute__ ((attribute-list))`
> attribute list is a possibly empty comma-separated sequence of attributes

`__attribute__`可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。

举例:
```cpp
__attribute__ ((visibility ("default")))
__attribute__((no_sanitize_undefined))
__attribute__((unused))
__attribute__((__always_inline__))
```



