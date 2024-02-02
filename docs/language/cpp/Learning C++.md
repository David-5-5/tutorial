# Learing C++remove_extent

[toc]

## Metaprogramming library

### std::remove_extent

```cpp
template< class T > struct remove_extent; // (since C++11)
template< class T > using remove_extent_t = typename remove_extent<T>::type; //	(since C++14)
```
如果 T 是某种类型 X 的数组，则提供等于 X 的成员 typedef 类型，否则 type 为 T。

为 std::remove_extent 添加专用化的程序的行为未定义。



## Utility library
C++ 包括各种实用程序库, 这些库提供从位计数到部分函数应用程序的功能。这些库大致可分为两组：
- 语言支持库, 提供与语言功能密切交互的类和函数, 并支持通用语言习语。
- 通用库。


### Type Support Support

#### std::size_t
`std::size_t`是`sizeof`运算符结果的无符号整数类型, 也是`sizeof`运算符和对齐运算符(自 C++11 起). `std::size_t`可以存储理论上可能的任何类型的对象(包括数组)的最大大小. 大小不能用`std::size_t`表示的类型格式不正确. 在许多平台上(具有分段寻址的系统除外), `std::size_t`可以安全地存储任何非成员指针的值, 在这种情况下, 它与 `std::uintptr_t` 同义。

`std::size_t`通常用于数组索引和循环计数。使用其他类型(如无符号 int)进行数组索引的程序可能会失败, 例如, 当索引超过 64 位系统时, UINT_MAX 或依赖于 32 位模块化算术。

在索引C++容器(如 `std::string`、`std::vector` 等)时, 相应的类型是此类容器提供的成员 `typedef size_type`。它通常被定义为 `std::size_t` 的同义词。

> https://en.cppreference.com/w/cpp/types/size_t


### 动态内存管理 Dynamic memory management 


#### std::shared_ptr

`std::shared_ptr`是一个智能指针，它通过指针保留对象的共享所有权。多个`shared_ptr`对象可能拥有同一个对象。当发生以下任一情况时，对象将被销毁并解除其内存分配：
- 拥有该对象的最后剩余`shared_ptr`被销毁;
- 拥有该对象的最后剩余`shared_ptr`通过 `operator=` 或 `reset()` 分配另一个指针。

使用 `delete-expression` 或在构造过程中提供给 `shared_ptr` 的自定义删除器销毁对象。

`shared_ptr`可以共享对象的所有权，同时存储指向另一个对象的指针。此功能可用于在拥有成员对象所属对象时指向成员对象。存储的指针是由 get()、取消引用和比较运算符访问的指针。托管指针是当使用计数达到零时传递给删除程序的指针。

`shared_ptr`也可能不拥有任何对象，在这种情况下，它被称为空(如果使用别名构造函数创建空shared_ptr，则空可能具有非 null 存储的指针)。

`shared_ptr`的所有specializations都满足 `CopyConstructible`、`CopyAssignable` 和 `LessThanComparable` 的要求，并且可以在上下文中转换为 bool。

所有成员函数(包括复制构造函数和复制赋值)都可以由不同`shared_ptr`实例上的多个线程调用，而无需额外同步，即使这些实例是同一对象的副本并共享所有权。如果多个执行线程在不同步的情况下访问同一个`shared_ptr`实例，并且其中任何一个访问都使用了 `shared_ptr` 的非常量成员函数，则将发生数据争用;原子函数的`shared_ptr`重载可用于防止数据争用。


##### std::make_shared, std::make_shared_for_overwrite

```cpp
// (1)	(since C++11) (T is not array)
template< class T, class... Args >
shared_ptr<T> make_shared( Args&&... args );

// (2)	(since C++20) (T is U[])
template< class T >
shared_ptr<T> make_shared( std::size_t N );

// (3)	(since C++20) (T is U[N])
template< class T >
shared_ptr<T> make_shared();
// (4)	(since C++20) (T is U[])
template< class T >
shared_ptr<T> make_shared( std::size_t N, const std::remove_extent_t<T>& u );

// (5)	(since C++20) (T is U[N])
template< class T >
shared_ptr<T> make_shared( const std::remove_extent_t<T>& u );

// (6)	(since C++20) (T is not U[])
template< class T >
shared_ptr<T> make_shared_for_overwrite();

// (7)	(since C++20) (T is U[])
template< class T >
shared_ptr<T> make_shared_for_overwrite( std::size_t N );
```
说明：
- (1) 构造一个 T 类型的对象，并使用 args 作为 T 构造函数的参数列表将其包装在 `std::shared_ptr` 中。对象的构造方式类似于表达式 ::new (pv) T(std::forward<Args>(args)...)，其中 pv 是指向适合保存 T 类型对象的存储的内部 void* 指针。存储通常大于 `sizeof(T)`，以便对共享指针的控制块和 T 对象使用一个分配。此函数调用的 `std::shared_ptr` 构造函数允许使用指向 T 类型的新构造对象的指针进行`shared_from_this`。
仅当 T 不是数组类型时，此重载才参与重载解析。(从 C++20 开始)

- (2,3) 与 (1) 相同，但构造的对象是一个可能的多维数组，其 std::remove_all_extents_t 类型的非数组元素<T>被值初始化，就像通过 placement-new 表达式 ::new(pv) std::remove_all_extents_t<T>() 一样。重载 (2) 沿第一维创建一个大小为 N 的数组。数组元素按其地址的升序初始化，当其生存期结束时，将按其原始构造的相反顺序销毁。

- (4,5) 与 (2,3) 相同，但每个元素都是从默认值 u 初始化的。如果 U 不是数组类型，则与 (1) 中相同的 placement-new 表达式执行此操作;否则，这就像使用与(1)中相同的placement-new表达式将数组的每个非数组元素初始化为U中的相应元素来执行(可能是多维的)数组。重载 (4) 沿第一维创建一个大小为 N 的数组。数组元素按其地址的升序初始化，当其生存期结束时，将按其原始构造的相反顺序销毁。

- (6) 如果 T 不是数组类型，则与 (1) 和 (3) 如果 T 为 U[N] 相同，只是创建的对象是默认初始化的。

- (7)与 (2) 相同，只是单个数组元素是默认初始化的。


##### std::enable_shared_from_this

定义:
```cpp
template< class T > class enable_shared_from_this;
```

`std::enable_shared_from_this` 允许当前由名为 pt 的 `std::shared_ptr` 管理的对象 t 安全地生成其他 `std::shared_ptr` 实例 pt1、pt2、...所有 T 与 PT 共享所有权。

公开继承自 `std::enable_shared_from_this<T>` 为类型 T 提供成员函数`shared_from_this`。如果 T 类型的对象 t 由名为 pt 的 `std::shared_ptr` 管理，<T>则调用 T::shared_from_this 将返回一个新的 std::shared_ptr，该 std::<T> 与 pt 共享 t 的所有权。



#### std::unique_ptr

std::unique_ptr 是一个智能指针，它通过指针拥有和管理另一个对象，并在unique_ptr超出范围时释放该对象。

当发生以下任一情况时，将使用关联的删除程序释放对象：
- 管理unique_ptr对象被销毁。
- 通过 operator= 或 reset() 为管理 unique_ptr 对象分配另一个指针。

通过调用 get_deleter()(ptr)，使用可能由用户提供的删除程序来释放对象。默认删除程序使用 delete 运算符，该运算符会销毁对象并解除分配内存。

unique_ptr也可以不拥有任何对象，在这种情况下，它被称为空。

std::unique_ptr 有两个版本：
- 管理单个对象(例如，使用 new 分配)。
- 管理动态分配的对象数组(例如，使用 new[] 分配)。




## C++ Language

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
赋值的一个缺点是它至少需要两个语句：一个用于定义变量, 另一个用于赋值。

These two steps can be combined. When a variable is defined, you can also provide an initial value for the variable at the same time. This is called initialization. The value used to initialize a variable is called an initializer.
这两个步骤可以结合起来。定义变量时, 还可以同时为变量提供初始值。这称为初始化。用于初始化变量的值称为初始值设定项。

Initialization in C++ is surprisingly complex, so we’ll present a simplified view here.
C++ 中的初始化非常复杂, 因此我们将在这里提供一个简化的视图。


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
当未提供初始化值时(例如上面的变量 a), 这称为默认初始化。在大多数情况下, 默认初始化会使变量具有不确定的值。

##### Copy Initialization

When an initializer is provided after an equals sign, this is called copy initialization. This form of initialization was inherited from C.
当在等号后提供初始值设定项时, 这称为复制初始化。这种初始化形式继承自 C。
```c++
int width = 5; // copy initialization of value 5 into variable width
```
Much like copy assignment, this copies the value on the right-hand side of the equals into the variable being created on the left-hand side. In the above snippet, variable width will be initialized with value 5.
与复制赋值非常相似, 这会将等号右侧的值复制到左侧创建的变量中。在上面的代码段中, 变量 width 将使用值 5 进行初始化。


Copy initialization had fallen out of favor in modern C++ due to being less efficient than other forms of initialization for some complex types. However, `C++17` remedied the bulk of these issues, and copy initialization is now finding new advocates. You will also find it used in older code (especially code ported from C), or by developers who simply think it looks more natural and is easier to read.
复制初始化在现代 C++ 中已经失宠, 因为对于某些复杂类型, 复制初始化的效率低于其他形式的初始化。然而, C++17 解决了大部分这些问题, 复制初始化现在正在寻找新的倡导者。您还会发现它在较旧的代码(尤其是从 C 移植的代码)中使用, 或者被那些只是认为它看起来更自然、更易于阅读的开发人员使用。


Copy initialization is also used whenever values are implicitly copied or converted, such as when passing arguments to a function by value, returning from a function by value, or catching exceptions by value.
每当隐式复制或转换值时, 例如按值将参数传递给函数、按值从函数返回或按值捕获异常时, 也会使用复制初始化。

##### Direct Initialization

When an initializer is provided inside parenthesis, this is called direct initialization.
当在括号内提供初始值设定项时, 这称为直接初始化。
```c++
int width( 5 ); // direct initialization of value 5 into variable width
```

Direct initialization was initially introduced to allow for more efficient initialization of complex objects (those with class types, which we’ll cover in a future chapter). Just like copy initialization, direct initialization had fallen out of favor in modern C++, largely due to being superseded by list initialization. However, we now know that list initialization has a few quirks of its own, and so direct initialization is once again finding use in certain cases.
直接初始化最初是为了允许更有效地初始化复杂对象(那些具有类类型的对象, 我们将在以后的章节中介绍)。就像复制初始化一样, 直接初始化在现代 C++ 中已经失宠, 主要是由于被列表初始化所取代。但是, 我们现在知道列表初始化有其自身的一些怪癖, 因此在某些情况下, 直接初始化再次被使用。

Direct initialization is also used when values are explicitly cast to another type.
当值显式转换为另一种类型时, 也使用直接初始化。

One of the reasons direct initialization had fallen out of favor is because it makes it hard to differentiate variables from functions. For example:
直接初始化失宠的原因之一是因为它很难区分变量和函数。例如：
```c++
int x();  // forward declaration of function x
int x(0); // definition of variable x with initializer 0
```


##### List Initialization
The modern way to initialize objects in C++ is to use a form of initialization that makes use of curly braces. This is called list initialization (or uniform initialization or brace initialization).
在 C++ 中初始化对象的现代方法是使用使用大括号的初始化形式。这称为列表初始化(或统一初始化或大括号初始化)。

List initialization comes in three forms:
```c++
int width { 5 };    // direct list initialization of value 5 into variable width
int height = { 6 }; // copy list initialization of value 6 into variable height
int depth {};       // value initialization (see next section)
```
Prior to the introduction of list initialization, some types of initialization required using copy initialization, and other types of initialization required using direct initialization. List initialization was introduced to provide a more consistent initialization syntax (which is why it is sometimes called “uniform initialization”) that works in most cases.Additionally, list initialization provides a way to initialize objects with a list of values (which is why it is called “list initialization”). 
在引入列表初始化之前, 某些类型的初始化需要使用复制初始化, 而其他类型的初始化需要使用直接初始化。引入列表初始化是为了提供一种更一致的初始化语法(这就是为什么它有时被称为“统一初始化”), 在大多数情况下都有效。此外, 列表初始化提供了一种使用值列表初始化对象的方法(这就是它被称为“列表初始化”的原因)。

List initialization has an added benefit: it disallows “narrowing conversions”. This means that if you try to brace initialize a variable using a value that the variable can not safely hold, the compiler will produce an error. 列表初始化还有一个额外的好处：它不允许“缩小转换范围”。这意味着, 如果尝试使用变量无法安全保存的值来大括号初始化变量, 编译器将产生错误。
For example:
```c++
int width { 4.5 }; // error: a number with a fractional value can't fit into an int
```
In the above snippet, we’re trying to assign a number (4.5) that has a fractional part (the .5 part) to an integer variable (which can only hold numbers without fractional parts).
在上面的代码片段中, 我们尝试将一个具有小数部分(.5 部分)的数字 (4.5) 分配给一个整数变量(它只能保存没有小数部分的数字)。

Copy and direct initialization would simply drop the fractional part, resulting in the initialization of value 4 into variable width (your compiler may produce a warning about this, since losing data is rarely desired). However, with list initialization, the compiler will generate an error instead, forcing you to remedy this issue before proceeding.
复制和直接初始化只会删除小数部分, 从而导致值 4 初始化为可变宽度(编译器可能会对此产生警告, 因为很少希望丢失数据)。但是, 在列表初始化时, 编译器将生成错误, 迫使您在继续操作之前解决此问题。


### Expressions
表达式是一系列运算符及其操作数, 用于指定计算。

表达评估可能产生结果(例如, 评估2 + 2产生结果4), 并可能产生副作用(例如std::printf(“%d”,  4)打印字符'4'在标准输出上)。
每个 C++ 表达式都具有两个独立的属性：类型和值类别。

- 值类别(lvalue、rvalue、glvalue、prvalue、xvalue)按值对表达式进行分类(自 C++11 起)
- 参数和子表达式的计算顺序指定获得中间结果的顺序

#### Constant expressions
Defines an expression that can be evaluated at compile time.定义可在编译时计算的表达式。

Such expressions can be used as non-type template arguments, array sizes, and in other contexts that require constant expressions, e.g. 此类表达式可用作非类型模板参数、数组大小以及其他需要常量表达式的上下文，例如

##### Core constant expressions
A core constant expression is any expression whose evaluation would not evaluate any one of the following核心常量表达式是不会计算以下任何一项的任何表达式:
1. the this pointer, except in a constexpr function that is being evaluated as part of the expression this 指针，但作为表达式的一部分计算的 constexpr 函数除外
2. a control flow that passes through a declaration of a variable with static or thread-local storage duration, and unusable in constant expressions 一个控制流，它通过具有静态或线程本地存储持续时间的变量的声明，在常量表达式中不可用
3. a function call expression that calls a function (or a constructor) that is not declared constexpr 调用未声明 constexpr 的函数（或构造函数）的函数调用表达式
   ```cpp
   constexpr int n = std::numeric_limits<int>::max(); // OK: max() is constexpr
   constexpr int m = std::time(nullptr); // Error: std::time() is not constexpr
   ```
4. a function call to a constexpr function which is declared, but not defined 对已声明但未定义的 constexpr 函数的函数调用
5. a function call to a constexpr function/constructor template instantiation where the instantiation fails to satisfy constexpr function/constructor requirements. 对 constexpr 函数/构造函数模板实例化的函数调用，其中实例化无法满足 constexpr 函数/构造函数要求。
6. a function call to a constexpr virtual function, invoked on an object not usable in constant expressions and whose lifetime began outside this expression. 对 constexpr 虚函数的函数调用，在常量表达式中不可用的对象上调用，并且其生存期在此表达式之外开始。
7. an expression that would exceed the implementation-defined limits 将超出实现定义的限制的表达式
8. an expression whose evaluation leads to any form of core language undefined behavior (including signed integer overflow, division by zero, pointer arithmetic outside array bounds, etc). 一个表达式，其计算结果会导致任何形式的核心语言未定义行为（包括有符号整数溢出、除以零、指针算术、数组边界外等）。
9. (until C++17) a lambda expression
10. an lvalue-to-rvalue implicit conversion unless applied to a non-volatile literal-type glvalue that 左值到右值的隐式转换，除非应用于非易失性文本类型 glvalue
    - designates an object that is usable in constant expressions, 指定可在常量表达式中使用的对象
    - refers to a non-volatile object whose lifetime began within the evaluation of this expression 指非易失性对象，其生存期在此表达式的计算中开始
11. an lvalue-to-rvalue implicit conversion or modification applied to a non-active member of a union or its subobject (even if it shares a common initial sequence with the active member) 应用于联合的非活动成员或其子对象的左值到右值的隐式转换或修改（即使它与活动成员共享一个通用的初始序列）
12. an lvalue-to-rvalue implicit conversion on an object whose value is indeterminate 值不确定的对象的左值到右值的隐式转换
13. an invocation of implicit copy/move constructor/assignment for a union whose active member is mutable (if any), with lifetime beginning outside the evaluation of this expression 对活动成员可变（如果有）的联合的隐式复制/移动构造函数/赋值的调用，其生存期从此表达式的计算范围开始
14. (until C++20) an assignment expression that would change the active member of a union 将更改联合的活动成员的赋值表达式
15. an id-expression referring to a variable or a data member of reference type, unless the reference is usable in constant expressions or its lifetime began within the evaluation of this expression 引用变量或引用类型的数据成员的 id-expression，除非引用在常量表达式中可用，或者其生存期在此表达式的计算中开始
16. conversion from pointer to void to a pointer-to-object type T* unless the pointer points to an object whose type is similar to T(since C++26) 从指针到 void 到指向对象类型的 T* 的转换，除非指针指向类型类似于 T 的对象
17. (until C++20) dynamic_cast
18. reinterpret_cast
19. (until C++20) pseudo-destructor call
20. (until C++14) an increment or a decrement operator 递增或递减运算符
21. (since C++14) modification of an object, unless the object has non-volatile literal type and its lifetime began within the evaluation of the expression 修改对象，除非该对象具有非易失性文本类型，并且其生存期从表达式的计算开始
22. (since C++20) a destructor call or pseudo destructor call for an object whose lifetime did not begin within the evaluation of this expression 析构函数调用或伪析构函数调用对象，其生存期未在此表达式的计算中开始 
23. (until C++20) a typeid expression applied to a glvalue of polymorphic type 应用于多态类型的 glvalue 的 TypeID 表达式
24. a new-expression or a call to std::allocator<T>::allocate, unless the selected allocation function is a replaceable global allocation function and the allocated storage is deallocated within the evaluation of this expression(since C++20) new-expression 或对 std::Allocator<T>::Allocate 的调用，除非所选分配函数是可替换的全局分配函数，并且分配的存储在此表达式的计算中被释放
25. a delete-expression or a call to std::allocator<T>::deallocate, unless it deallocates a region of storage allocated within the evaluation of this expression(since C++20) delete-expression 或对 std::allocator<T>::deallocate 的调用，除非它释放了在此表达式的计算中分配的存储区域
26. (since C++20) Coroutines: an await-expression or a yield-expression 协程：await-expression 或 yield-expression
27. (since C++20) a three-way comparison when the result is unspecified 结果未指定时的三向比较
28. an equality or relational operator whose result is unspecified 结果未指定的相等运算符或关系运算符
29. (until C++14) an assignment or a compound assignment operator 赋值或复合赋值运算符
30. a throw expression
31. an asm-declaration
32. an invocation of the va_arg macro 对 va_arg 宏的调用
33. a goto statement
34. a dynamic_cast or typeid expression that would throw an exception 会引发异常的 dynamic_cast 或 typeid 表达式
35. inside a lambda-expression, a reference to this or to a variable defined outside that lambda, if that reference would be an odr-use 在 lambda 表达式中，对 this 或对在该 lambda 外部定义的变量的引用（如果该引用是 odr-use）
    ```cpp
    void g()
    {
      const int n = 0;
 
      constexpr int j = *&n; // OK: outside of a lambda-expression
 
      [=]
      {
        constexpr int i = n;   // OK: 'n' is not odr-used and not captured here.
        constexpr int j = *&n; // Ill-formed: '&n' would be an odr-use of 'n'.
      };
    }
    ```
Even if an expression E does not evaluate anything stated above, it is unspecified whether E is a core constant expression if evaluating E would evalute any of the following 即使表达式 E 不计算上述任何内容，如果计算 E 将计算以下任何一项，则无法指定 E 是否为核心常量表达式：
- An operation with undefined behavior in the standard library. 标准库中具有未定义行为的操作
- An invocation of the va_start macro. 调用 va_start 宏
- A call to a function that was previously declared with the [[noreturn]] attribute, and that call returns to its caller. 对以前使用 [[noreturn]] 属性声明的函数的调用，该调用返回到其调用方。
- An assumption [[assume(expr)]]; such that if expr evaluated where the assumption appears, the result is not true, while E is not disqualified from being a core constant expression (i.e., the hypothetical evaluation of expr would evaluate any item of the previous list).假设 [[assume（expr）]];这样，如果 expr 在假设出现的地方求值，则结果不成立，而 E 不会被取消作为核心常数表达式的资格（即，expr 的假设求值将求值前一个列表中的任何项目）。


##### Constant expression
A constant expression is either
- an lvalue(until C++14)a glvalue(since C++14) core constant expression that refers to
  - an object with static storage duration that is not a temporary, or 具有非临时静态存储持续时间的对象，或者
  - an object with static storage duration that is a temporary, but whose value satisfies the constraints for prvalues below, or 具有静态存储持续时间的对象，该对象是临时的，但其值满足以下 prvalues 的约束，或者
  - a non-immediate(since C++20) function 非即时函数
- a prvalue core constant expression whose value satisfies the following constraints 一个 PRvalue 核心常量表达式，其值满足以下约束:
  - if the value is an object of class type, each non-static data member of reference type refers to an entity that satisfies the constraints for lvalues(until C++14)glvalues(since C++14) above 如果该值是类类型的对象，则引用类型的每个非静态数据成员都引用满足lvalues、glvalues约束的实体
  - if the value is of pointer type, it holds
    - address of an object with static storage duration 具有静态存储持续时间的对象的地址
    - address past the end of an object with static storage duration 具有静态存储持续时间的对象末尾的地址
    - address of a non-immediate(since C++20) function 非即时函数的地址
    - a null pointer value
  - if the value is of pointer-to-member-function type, it does not designate an immediate function 如果该值是指向成员函数类型的指针，则它不指定即时函数
  - if the value is an object of class or array type, each subobject satisfies these constraints for valuesif the value is an object of class or array type, each subobject satisfies these constraints for values 如果值是类或数组类型的对象，则每个子对象都满足值的这些约束如果值是类或数组类型的对象，则每个子对象都满足这些值约束


###### Integral constant expression
Integral constant expression is an expression of integral or unscoped enumeration type implicitly converted to a prvalue, where the converted expression is a core constant expression. If an expression of class type is used where an integral constant expression is expected, the expression is contextually implicitly converted to an integral or unscoped enumeration type. 整型常量表达式是隐式转换为 prvalue 的整型或无作用域枚举类型的表达式，其中转换后的表达式是核心常量表达式。如果在需要整数常量表达式的地方使用类类型的表达式，则该表达式将在上下文中隐式转换为整数或无作用域枚举类型。

The following contexts require an integral constant expression:
- array bounds 数组边界
- the dimensions in new-expressions other than the first 除第一个表达式外的 new-expression 中的维度
- bit-field lengths 位场长度
- enumeration initializers when the underlying type is not fixed 基础类型不固定时的枚举初始值设定项
- alignments. 路线


###### Converted constant expression
A converted constant expression of type T is an expression implicitly converted to type T, where the converted expression is a constant expression, and the implicit conversion sequence contains only 
T 类型的转换常量表达式是隐式转换为 T 类型的表达式，其中转换后的表达式是常量表达式，隐式转换序列仅包含:
- constexpr user-defined conversions (so a class can be used where integral type is expected) constexpr 用户定义的转换（因此可以在需要整型类型的地方使用类）
- lvalue-to-rvalue conversions 左值到右值的转换
- integral promotions
- non-narrowing integral conversions 非缩小积分转换
- array-to-pointer conversions 数组到指针的转换
- function-to-pointer conversions 函数到指针的转换
- function pointer conversions (pointer to noexcept function to pointer to function) 函数指针转换（指向 noexcept 的指针到指向函数的指针）
- qualification conversions
- null pointer conversions from std::nullptr_t
- null member pointer conversions from std::nullptr_t
- And if any reference binding takes place, it is direct binding (not one that constructs a temporary object) 如果发生任何引用绑定，则它是直接绑定（而不是构造临时对象的绑定）


###### Historical categories
Categories of constant expressions listed below are no longer used in the standard since C++14 标准中不再使用下面列出的常量表达式类别:

- A literal constant expression is a prvalue core constant expression of non-pointer literal type (after conversions as required by context). A literal constant expression of array or class type requires that each subobject is initialized with a constant expression. 文本常量表达式是非指针文本类型的 prvalue 核心常量表达式（根据上下文要求进行转换后）。数组或类类型的文本常量表达式要求使用常量表达式初始化每个子对象。
- A reference constant expression is an lvalue core constant expression that designates an object with static storage duration or a function. 引用常量表达式是一个左值核心常量表达式，用于指定具有静态存储持续时间的对象或函数。
- An address constant expression is a prvalue core constant expression (after conversions required by context) of type std::nullptr_t or of a pointer type, which points to an object with static storage duration, one past the end of an array with static storage duration, to a function, or is a null pointer. 地址常量表达式是 std：：nullptr_t 类型或指针类型的 prvalue 核心常量表达式（在上下文所需的转换之后），它指向具有静态存储持续时间的对象、超过具有静态存储持续时间的数组末尾的对象、指向函数或空指针。


##### Constant subexpression

##### Usable in constant expressions

##### Manifestly constant-evaluated expressions

##### Functions and variables needed for constant evaluation



#### const_cast 转换
在具有不同 cv 资格的类型之间进行转换。
语法
```cpp
const_cast<target-type expression>()		
```
只有以下转换可以使用const_cast完成。
- 对于两个相似的类型和 , 如果类型为T1的值 prvalue 可以转换为T2, 考虑到两种类型的限定分解qualification-decompositions,  对所有i, 每个 P1_i 与 P2_i 相同. 结果引用原始实体。
  ```cpp
  typedef int *A[3];              // array of 3 pointer to int
  typedef const int *const CA[3]; // array of 3 const pointer to const int
 
  CA &&r = A{}; // OK, reference binds to temporary array object
 
  // after qualification conversion to type CA
  A &&r1 = const_cast<A>(CA{});   // error: temporary array decayed to pointer
  A &&r2 = const_cast<A&&>(CA{}); // OK
  ```
- 对于两个对象类型 T1 和 T2，如果可以使用 const cast<T2*> 将指向 T1 的指针显式转换为类型“指向 T2 的指针”，则还可以进行以下转换: 
  - 可以使用 const_cast<T2&> 将 T1 类型的左值显式转换为 T2 类型的左值。
  - 可以使用 const_cast<T2&&> 将类型的 glvalue 显式转换为类型的 xvalue。
  - 如果 T1 是Class 类型，则可以使用 const_cast<T2&&> 将 T1 类型的 prvalue 显式转换为 T2 类型的 xvalue。
- 空指针值可以转换为 target-type 的空指针值。空成员指针值可以转换为 target-type 的空成员指针值。


与所有强制转换表达式一样，结果是：
- 如果目标类型是左值引用类型或对函数类型的右值引用，则为左值;
- 如果 target-type 是对对象类型的右值引用，则为 xvalue;
- 否则为 prvalue。

##### 抛弃恒常性 Casting away constness
<span id="Casting_away_constness"></span>
对于两种不同的类型 T1 和 T2，如果存在 T2 形式的限定分解，则从 T1 到 T2 的转换会抛弃恒定性cv2_0 P2_0 cv2_1 P2_1......cv2_n-1 P2_n-1 cv2_n U2“，并且没有将 T1 转换为”cv2_0 P1_0 cv2_1 P1_1 ...cv2_n-1 P1_n-1 cv2_n U1“(相同的 cv 分量、不同的 P 分量和 U 分量)。

如果从 T1* 类型的 prvalue 转换为 T2* 类型的转换会丢弃恒定性，则引用const_casts(item (2)) 也将会降低恒定性。

只有const_cast才能用来抛弃恒常性。

“抛弃恒常性”意味着“抛弃波动性”，因为资格转换也不能抛弃波动性。



#### static_cast 转换
使用隐式转换和用户定义的转换组合在类型之间进行转换。

语法
```cpp
static_cast<target-type>(expression)		
```

只有以下转换可以用`static_cast`完成, 除非这种转换会[抛弃恒常性casting away constness](#Casting_away_constness)(或波动性)
- 如果 target-type 是对某个完整类 D 的引用，而 expression 是其非虚拟基 B 的左值，或者 target-type 是指向某个完整类 D 的指针，而 expression 是指向其非虚拟基 B 的 prvalue 指针，则 static_cast 执行下转换。(如果 B 不明确、不可访问或虚拟碱基(或虚拟碱基的碱基)为 D，则此下沉格式不正确。
这种向下转换不会进行运行时检查以确保对象的运行时类型实际上是 D，并且只有在通过其他方式(例如实现静态多态性时)保证此前提条件时才能安全使用。安全的下沉可以用`dynamic_cast`来完成。如果对象表达式引用或指向实际上是 D 类型对象的基类子对象，则结果引用 D 类型的封闭对象。 否则，行为未定义：
    ```cpp
    struct B {};
    struct D : B { B b; };

    D d;
    B& br1 = d;
    B& br2 = d.b;

    static_cast<D&>(br1); // OK: lvalue denoting the original d object
    static_cast<D&>(br2); // UB: the b subobject is not a base class subobject
    ```

- 如果 target-type 是右值引用类型，则`static_cast`将 glvalue、Class prvalue 或数组 prvalue(直到 C++17)的值转换为引用与表达式相同的对象的 xvalue(自 C++17 起)或其基本子对象(取决于目标类型)。如果目标类型是表达式类型的不可访问或不明确的基，则程序格式不正确。如果表达式是位字段左值，则首先将其转换为基础类型的 prvalue。这种类型的static_cast用于在 std::move 中实现移动语义。

- 如果存在从 expression 到 target-type 的隐式转换序列，或者如果从 expression 直接初始化对象或引用 target-type 类型的重载解析会找到至少一个可行的函数，则 `static_cast<target-type>(expression)` 返回虚构变量 Temp 初始化，就像通过目标类型 Temp(expression );一样初始化，这可能涉及隐式转换， 对 target-type 构造函数的调用或对用户定义的转换运算符的调用。对于非引用目标类型，static_cast prvalue 表达式的结果对象是直接初始化的对象。(自 C++17 起)

- 如果 target-type 是 void 类型(可能是 cv 限定的)，static_cast在计算 expression 的值后将其丢弃。

- 如果存在从目标类型到表达式类型的标准转换序列，其中不包括左值到右值lvalue-to-rvalue、数组到指针array-to-pointer、函数到指针function-to-pointer、空指针null pointer、空成员指针null member pointer、函数指针function pointer(自 C++17 起)或布尔转换，则static_cast可以执行该隐式转换的逆转换。

- 如果表达式到目标类型的转换涉及左值到右值、数组到指针或函数到指针的转换，则可以通过 `static_cast`显式执行。

- 作用域枚举类型可以转换为整数或浮点类型。
  - 当目标类型为 bool(可能是 cv 限定)时，如果原始值为零，则结果为 false，而所有其他值为 true。对于其余整型，如果枚举可以由目标类型表示，则结果为枚举的值，否则未指定。(直到 C++20)
  - 结果与从枚举的基础类型到目标类型的隐式转换相同。

- 整数或枚举类型的值可以转换为任何完整的枚举类型。
  - 如果基础类型不是固定的，则当 expression 的值超出范围时，行为是未定义的(该范围是足够大以容纳目标枚举的所有枚举器的最小位域的所有可能值)。
  - 如果基础类型是固定的，则结果与先将原始值转换为枚举的基础类型，然后再转换为枚举类型相同。
- 浮点类型的值也可以转换为任何完整的枚举类型。
  - 结果与先将原始值转换为枚举的基础类型，然后再转换为枚举类型相同。

- 浮点类型的 prvalue 可以显式转换为任何其他浮点类型。
  - 如果源值可以精确地表示在目标类型中，则它不会更改。
  - 如果源值介于目标类型的两个可表示值之间，则结果是这两个值之一(这是实现定义的，尽管如果支持 IEEE 算术，则舍入默认为最接近值)。
  - 否则，行为是未定义的。

- 指向某个完整类 D 的成员的指针可以向上转换为指向其明确、可访问的基类 B 的成员的指针。此static_cast不进行任何检查以确保成员实际存在于指向对象的运行时类型中：如果 B 不包含原始成员，并且不是包含原始成员的类的基类，则行为未定义。

- 指向 void 的指针类型的 prvalue(可能是 cv 限定的)可以转换为指向任何对象类型 T 的指针。
  - 如果原始指针值表示内存中某个字节的地址，该地址不满足 T 的对齐要求，则未指定生成的指针值。
  - 否则，如果原始指针值指向对象 a，并且存在一个类型类似于 T 的对象 b，该对象可与 a 进行指针互换，则结果是指向 b 的指针。
  - 否则，指针值保持不变。

与所有强制转换表达式一样，结果是：
- 如果目标类型是左值引用类型或对函数类型的右值引用，则为左值(自 C++11 起);
- 如果 target-type 是对对象类型的右值引用，则为 xvalue; (从 C++11 开始)
- 否则为 pr值。


### Declarations

#### constexpr specifier
specifies that the value of a variable or function can appear in constant expressions. 指定变量或函数的值可以出现在常量表达式中

The constexpr specifier declares that it is possible to evaluate the value of the function or variable at compile time. Such variables and functions can then be used where only compile time constant expressions are allowed (provided that appropriate function arguments are given). constexpr 说明符声明可以在编译时计算函数或变量的值。然后，可以在仅允许编译时常量表达式的情况下使用此类变量和函数（前提是给定适当的函数参数）。

A constexpr specifier used in an object declaration or non-static member function(until C++14) implies const. A constexpr specifier used in a function or static data member(since C++17) declaration implies inline. If any declaration of a function or function template has a constexpr specifier, then every declaration must contain that specifier. 对象声明或非静态成员函数中使用的 constexpr 说明符（直到 C++14）表示 const。函数或静态数据成员（自 C++17 起）声明中使用的 constexpr 说明符意味着内联。如果函数或函数模板的任何声明都具有 constexpr 说明符，则每个声明都必须包含该说明符。


##### constexpr variable
A constexpr variable must satisfy the following requirements:
- its type must be a LiteralType
- it must be immediately initialized
- the full-expression of its initialization, including all implicit conversions, constructors calls, etc, must be a constant expression 其初始化的完整表达式，包括所有隐式转换、构造函数调用等，必须是常量表达式
- it must have constant destruction, i.e. either:
  - it is not of class type nor (possibly multi-dimensional) array thereof, or 它不是类类型，也不是（可能是多维的）数组，或者
  - it is of class type or (possibly multi-dimensional) array thereof, that class type has a constexpr destructor, and for a hypothetical expression e whose only effect is to destroy the object, e would be a core constant expression if the lifetime of the object and its non-mutable subobjects (but not its mutable subobjects) were considered to start within e. 它是类类型或（可能是多维的）数组，该类类型具有 constexpr 析构函数，对于唯一作用是销毁对象的假设表达式 e，如果对象及其不可变子对象（但不是其可变子对象）的生存期被认为是在 e 内开始的，则 e 将是一个核心常量表达式。

If a constexpr variable is not translation-unit-local, it should not be initialized to point to, or refer to, or have a (possibly recursive) subobject that points to or refers to, a translation-unit-local entity that is usable in constant expressions. Such initialization is disallowed in a module interface unit (outside its private-module-fragment, if any) or a module partition, and is deprecated in any other context. 如果 constexpr 变量不是 translation-unit-local，则不应将其初始化为指向或引用，或具有指向或引用可在常量表达式中使用的翻译单元本地实体的（可能是递归的）子对象。在模块接口单元（在其 private-module-fragment 之外，如果有）或模块分区中不允许进行此类初始化，并且在任何其他上下文中均不推荐使用。


##### constexpr function
A constexpr function must satisfy the following requirements:
- it must not be virtual
- it must not be a function-try-block
- it must not be a coroutine
- for constructor and destructor(since C++20), the class must have no virtual base classes 对于构造函数和析构函数，该类必须没有虚拟基类
- its return value (if any) and each of its parameters must be of a LiteralType 其返回值（如果有）及其每个参数都必须为 LiteralType
- there exists at least one set of argument values such that an invocation of the function could be an evaluated subexpression of a core constant expression (for constructors, use in a constant initializer is sufficient). No diagnostic is required for a violation of this bullet. 至少存在一组参数值，因此函数的调用可以是核心常量表达式的计算子表达式（对于构造函数，在常量初始值设定项中使用就足够了）。违反此项目符号不需要诊断。
- the function body must be either deleted or defaulted or contain only the following 函数体必须被删除或默认，或者仅包含以下内容:
  - null statements (plain semicolons)
  - static_assert declarations
  - typedef declarations and alias declarations that do not define classes or enumerations
  - using declarations
  - using directives
  - if the function is not a constructor, exactly one return statement
- the function body must not contain:
  - a goto statement
  - a statement with a label other than case and default
  - a try-block
  - an asm declaration
  - a definition of a variable for which no initialization is performed
  - a definition of a variable of non-literal type
  - a definition of a variable of static or thread storage duration


##### constexpr constructor


##### constexpr destructor



### Classes

#### static members
Inside a class definition, the keyword static declares members that are not bound to class instances. Outside a class definition, it has a different meaning: see storage duration. 在类定义中，关键字 static 声明未绑定到类实例的成员。在类定义之外，它具有不同的含义：请参阅存储持续时间。

##### Syntax
A declaration for a static member is a member declaration whose declaration specifiers contain the keyword static. The keyword static usually appears before other specifiers (which is why the syntax is often informally described as static data-member or static member-function), but may appear anywhere in the specifier sequence. 静态成员的声明是其声明说明符包含关键字 static 的成员声明。关键字 static 通常出现在其他说明符之前（这就是为什么语法通常被非正式地描述为静态数据成员或静态成员函数），但也可能出现在说明符序列中的任何位置。

The name of any static data member and static member function must be different from the name of the containing class. 任何静态数据成员和静态成员函数的名称必须与包含类的名称不同。

##### Explanation

Static members of a class are not associated with the objects of the class: they are independent variables with static or thread(since C++11) storage duration or regular functions. 类的静态成员不与类的对象相关联：它们是具有静态或线程（自 C++11 以来）存储持续时间或常规函数的独立变量。

The static keyword is only used with the declaration of a static member, inside the class definition, but not with the definition of that static member static 关键字仅用于类定义中静态成员的声明，而不用于该静态成员的定义:
```cpp
class X { static int n; }; // declaration (uses 'static')
int X::n = 1;              // definition (does not use 'static')
```

The declaration inside the class body is not a definition and may declare the member to be of incomplete type (other than void), including the type in which the member is declared: 类体中的声明不是一个定义，可以将成员声明为不完整类型（无效除外），包括声明成员的类型：

However, if the declaration uses constexpr or inline(since C++17) specifier, the member must be declared to have complete type. 但是，如果声明使用 constexpr 或 inline（自 C++17 起）说明符，则必须将成员声明为具有完整类型。



## Containers

### std::vector

#### 构造函数

从各种数据源构造新容器, 可以选择使用用户提供的分配器分配, 部分构造函数
```cpp
explicit vector( size_type count,
                 const T& value = T(),
                 const Allocator& alloc = Allocator() );

constexpr vector( size_type count,
                  const T& value,
                  const Allocator& alloc = Allocator() );                 
```


##### Parameters
- alloc
  allocator to use for all memory allocations of this container
  用于此容器的所有内存分配的分配器

- count
  the size of the container
- value
  the value to initialize elements of the container with
- first,last
  the range [first, last) to copy the elements from
- other
  another container to be used as source to initialize the elements of the container with
  另一个容器用作源, 用于初始化容器的元素
- init
  initializer list to initialize the elements of the container with
- rg
  A container compatible range, that is, an input_range whose elements are convertible to T
  容器兼容范围, 即其元素可转换为 T 的input_range

`std::vector`构造举例
```cpp
std::vector<int> b{3}; // creates a 1-element vector holding {3}
std::vector<int> d(3); // creates a 3-element vector holding {0, 0, 0}
 
std::vector<int> p{1, 2}; // creates a 2-element vector holding {1, 2}
std::vector<int> q(1, 2); // creates a 1-element vector holding {2}
```

> https://en.cppreference.com/w/cpp/container/vector/vector

#### 成员函数

##### at

```cpp
reference at( size_type pos );
const_reference at( size_type pos ) const;
```

示例
```cpp
std::vector<int> data = {1, 2, 4, 5, 5, 6};

// Set element 1
data.at(1) = 88;

// Read element 2
std::cout << "Element at index 2 has value " << data.at(2) << '\n';
```


##### emplace_back
```cpp
template< class... Args > void emplace_back( Args&&... args );
template< class... Args > reference emplace_back( Args&&... args );
template< class... Args > constexpr reference emplace_back( Args&&... args );
```
将新元素追加到容器的末尾。元素是通过 `std::allocator_traits::construct` 构造的，它通常使用 placement-new 在容器提供的位置就地构造元素。参数 `args...` 作为 `std::forward<Args>(args)....` 转发到构造函数。

如果在操作后，新的 `size()` 大于旧的 `capacity()`，则会发生重新分配，在这种情况下，所有迭代器(包括 `end()` 迭代器)和对元素的所有引用都将失效。否则，只有 `end()`  迭代器无效。

参数:
- `args` 转发给元素构造函数的参数
- 类型要求 `T`(容器的元素类型)必须满足 `MoveInsertable` 和 `EmplaceConstructible` 的要求。
- 返回值(无)

使用 `emplace_back` 方法的优点是避免产生不必要的临时变量，避免不必要的临时对象的产生，举个例子：
```cpp
struct Foo {
    Foo(int n, double x);
};

std::vector<Foo> v;
v.emplace(someIterator, 42, 3.1416);     ///< 没有临时变量产生
v.insert(someIterator, Foo(42, 3.1416)); ///< 需要产生一个临时变量
v.insert(someIterator, {42, 3.1416});    ///< 需要产生一个临时变量
```


## GCC Command Options

### Attribute Syntax
`__attribute__` 是一个用于在声明时指定一些特性的编译器指令, 可以让我们进行更多的错误检查以及高级优化工作。关于__attribute__具体解释, 查了一下GNU C关于它的描述, 摘录如下
> The syntax with which `__attribute__` may be used, and the constructs to which attribute specifiers bind, for the C language. Some details may vary for C++ and Objective-C. Because of infelicities in the grammar for attributes, some forms described here may not be successfully parsed in all cases.
对于 C 语言, 可以使用 `__attribute__` 的语法, 以及属性说明符绑定到的构造。对于 C++ 和 Objective-C, 某些细节可能会有所不同。由于属性语法的缺陷, 此处描述的某些形式可能无法在所有情况下都成功解析。


`__attribute__`语法格式为：
`__attribute__ ((attribute-list))`
> attribute list is a possibly empty comma-separated sequence of attributes

`__attribute__`可以设置函数属性(Function Attribute)、变量属性(Variable Attribute)和类型属性(Type Attribute)。

举例:
```cpp
__attribute__ ((visibility ("default")))
__attribute__((no_sanitize_undefined))
__attribute__((unused))
__attribute__((__always_inline__))
```

