# Learning Python

[TOC]

## Built-in Functions
内置函数
> <https://docs.python.org/3/library/functions.html>

### enumerate(iterable, start=0)
Return an enumerate object. iterable must be a sequence, an iterator, or some other object which supports iteration. The __next__() method of the iterator returned by enumerate() returns a tuple containing a count (from start which defaults to 0) and the values obtained from iterating over iterable.
返回枚举对象。Iterable 必须是序列、迭代器或其他支持迭代的对象。enumerate（） 返回的迭代器的 __next__（） 方法返回一个元组，其中包含一个计数（从 start 开始，默认值为 0）和通过迭代 iterable 获得的值。

```python
seasons = ['Spring', 'Summer', 'Fall', 'Winter']
list(enumerate(seasons))
# [(0, 'Spring'), (1, 'Summer'), (2, 'Fall'), (3, 'Winter')]
list(enumerate(seasons, start=1))
# [(1, 'Spring'), (2, 'Summer'), (3, 'Fall'), (4, 'Winter')]
```

### map() function

语法：map(fun, iter)
参数：
fun： 是一个函数，map 将给定可迭代元素中的每个元素传递给该函数。
iter： 要映射的可迭代元素。

```python
g = [[1,2,3],[4,5],[6,7,8,9]]
d = list(map(len,g))
```
The result of d is [3, 2, 4]



## 重载 Overloading

### 运算符重载 operator overloading

#### 二元运算符

|  运算符 |              重载方法             | 说明          |
| :--: | :---------------------------: | ----------- |
|   +  |    \_\_add\_\_(self, other)   |             |
|   –  |    \_\_sub\_\_(self, other)   |             |
|  \*  |    \_\_mul\_\_(self, other)   |             |
|   /  |  \_\_truediv\_\_(self, other) | 浮点数除法       |
|  //  | \_\_floordiv\_\_(self, other) | 针对浮点数除法向下取整 |
|   %  |    \_\_mod\_\_(self, other)   |             |
| \*\* |    \_\_pow\_\_(self, other)   |             |
|  >>  |  \_\_rshift\_\_(self, other)  |             |
|  <<  |  \_\_lshift\_\_(self, other)  |             |
|   &  |    \_\_and\_\_(self, other)   |             |
|  \|  |    \_\_or\_\_(self, other)    |             |
|   ^  |    \_\_xor\_\_(self, other)   |             |

#### 比较运算符

| 运算符 |           重载方法          | 说明 |
| :-: | :---------------------: | -- |
|  <  | \_\_lt\_\_(self, other) |    |
|  >  | \_\_gt\_\_(self, other) |    |
|  <= | \_\_le\_\_(self, other) |    |
|  >= | \_\_ge\_\_(self, other) |    |
|  == | \_\_eq\_\_(self, other) |    |
|  != | \_\_ne\_\_(self, other) |    |

#### 赋值运算符

|  运算符  |              重载方法              | 说明 |
| :---: | :----------------------------: | -- |
|   -=  |    \_\_isub\_\_(self, other)   |    |
|   +=  |    \_\_iadd\_\_(self, other)   |    |
|  \*=  |    \_\_imul\_\_(self, other)   |    |
|   /=  |    \_\_idiv\_\_(self, other)   |    |
|  //=  | \_\_ifloordiv\_\_(self, other) |    |
|   %=  |    \_\_imod\_\_(self, other)   |    |
| \*\*= |    \_\_ipow\_\_(self, other)   |    |
|  >>=  |  \_\_irshift\_\_(self, other)  |    |
|  <<=  |  \_\_ilshift\_\_(self, other)  |    |
|   &=  |    \_\_iand\_\_(self, other)   |    |
|  \|=  |    \_\_ior\_\_(self, other)    |    |
|   ^=  |    \_\_ixor\_\_(self, other)   |    |

#### 一元运算符

| 运算符 |        重载方法        | 说明                |
| :-: | :----------------: | ----------------- |
|  –  |  \_\_neg\_\_(self) | 负的 negative       |
|  +  |  \_\_pos\_\_(self) | 正的 positive       |
|  \~ | `__invert__(self)` | 按位取反 \~a = -(a+1) |

#### 右操作符

对于像 +、-、\*、/ 这样的算术计算，我们需要 2 个操作数来执行运算符功能。我们必须将运算符符号绑定到左/右操作数。

```python
class Foo(object):
      
    def __init__(self, val):
        self.val = val
          
    def __mul__(self, other):
        return Foo(self.val * other.val)
  
    def __str__(self):
        return "Foo [% s]" % self.val
  
class Bar(object):
      
    def __init__(self, val):
        self.val = val
  
    def __str__(self):
        return "Bar [% s]" % self.val
  
# Driver Code
f = Foo(5)
b = Bar(6)
print(f * b)
```

上述表达式`f * b`，其中 f 是类 Foo 的一个实例. 为了执行该`__mul__`方法, 运算符查看左操作数 (x) 的类是否存在 `__mul__` 即, 运算符 (\*) 将检查类 Foo 是否存在`__mul__` 方法, 如果它有`__mul__`方法, 它会调用`(Foo())f.__mul__(b)`. 否则, 它会抛出 ` TypeError: unsupported operands` 错误消息.

如果我们将乘法反转为 `b * f`, 它会再次引发问题 , 因为它会查看没有任何 `__mul__` 方法的左操作数的类 `(Bar()). b.__mul__(f)` 将引发问题, 因为 b 的类 Bar() 没有 `__mul__` 方法.

`__mul__`和之间的细微差别 `__rmul__` 是，运算符 `__mul__` 在左操作数中查找 `__rmul__` 在右操作数中查找。

```python
class Foo(object):
      
    def __init__(self, val):
        self.val = val
  
    def __str__(self):
        return "Foo [% s]" % self.val
  
  
class Bar(object):
      
    def __init__(self, val):
        self.val = val
  
    def __rmul__(self, other):
        return Bar(self.val * other.val)
  
    def __mul__(self, other):
        return self.__rmul__(other)
  
    def __str__(self):
        return "Bar [% s]" % self.val
  
  
# Driver Code
f = Foo(5)
b = Bar(6)
  
print(b * f)
print(f * b)
```

在Foo类中增加 `__rmul__` 方法，这样`f * b` 及 `b * f` 都可以正确执行.

### 内置函数重载




## pycache

如果曾经运行过Python脚本，可能已经注意到在项目目录中创建了一个特殊的文件夹。这个名为\_\_pycache\_\_的文件夹乍一看可能很神秘，但它在Python 如何执行脚本方面起着至关重要的作用。

Python是一种解释型语言，这意味着它将源代码转换为计算机可以理解和执行的格式。此转换过程可能需要一些时间，尤其是对于较大的脚本。为了加快此过程，Python 将转换后的代码以.pyc文件的形式保存到\_\_pycache\_\_文件夹中。这些文件是字节码的一种形式，Python 可以比原始源代码更快地执行。

## 特殊变量和方法 Special Variables and methods

### 特殊变量 pecial Variables

### 特殊方法 pecial Methods

## 列表

### 列表表达式

#### 基本用法



```python
# 生成全为1的数量为5的列表
dp = [1]*5

[1,1,1,1,1]

# 生成全为1, n=5的二维列表
dp = [[1]*5]*5

[[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1]]

# 使用列表表达式，生成全为1, n=5的二维列表
dp = [[1]*5 for _ in range(5)]

[[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1],
[1,1,1,1,1]]

# 使用列表表达式，生成全为值等于行号的二维列表
dp = [[i] * 5 for i in range(1,6)]

[[1, 1, 1, 1, 1],
[2, 2, 2, 2, 2],
[3, 3, 3, 3, 3], 
[4, 4, 4, 4, 4], 
[5, 5, 5, 5, 5]]


# 使用列表表达式生成对角线为T，其余为F的二维列表
dp = [[i==j for i in range(5)] for j in range(5)]

[[True, False, False, False, False], 
[False, True, False, False, False], 
[False, False, True, False, False],
[False, False, False, True, False], 
[False, False, False, False, True]]


# 使用列表表达式生成单位矩阵
dp = [[1 if i==j else 0 for i in range(5)] for j in range(5)]

[[1, 0, 0, 0, 0], 
[0, 1, 0, 0, 0],
[0, 0, 1, 0, 0], 
[0, 0, 0, 1, 0], 
[0, 0, 0, 0, 1]]

```

#### 差异比较

```python
dp = [[1]*4] * 5
print(dp)
[[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1]]

dp[1][2] = 2
print(dp)
[[1, 1, 2, 1], 
[1, 1, 2, 1], 
[1, 1, 2, 1], 
[1, 1, 2, 1], 
[1, 1, 2, 1]]
```

第三列都修改为2
原因在于`[1]*4`生成的`[1, 1, 1, 1]`后，  每行都共享相同的内存空间
即`dp[i][*]`指向同一个变量

```python
dp = [[1] * 4 for _ in range(5)] 
print(dp)
[[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1]]

dp[1][2] = 2
print(dp)
[[1, 1, 1, 1], 
[1, 1, 2, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1], 
[1, 1, 1, 1]]
```

这样每个`dp[i][j]`都是独立的变量

### 列表max

```python
dp = [[i*j for i in range(1, 5)] for j in range(1, 6)]
print(dp)
[[1, 2, 3, 4], 
[2, 4, 6, 8], 
[3, 6, 9, 12], 
[4, 8, 12, 16], 
[5, 10, 15, 20]]

print(max(max(dp)))
print(max(max(row) for row in dp))
```

在这样递增的二维列表中，两个方法的返回值是一样的

```python
import random
dp = [[random.randint(1,999) for _ in range(4)] for _ in range(5)]
print(dp)

print(max(max(dp)))
print(max(max(row) for row in dp))
```

但是上述随机生成的二维列表中，发现仅`max(max(row) for row in dp)`能真正找到二维列表中的最大值

max(max(max(row) for row in matrix) for matrix in dp)

三维的情况如下：

```python
import random
dp = [[[random.randint(1,999) for _ in range(4)] for _ in range(5)] for _ in range(3)]
print(dp)

print(max(max(max(dp))))
print(max(max(max(row) for row in matrix) for matrix in dp))
```

二维的情况，某列的最小值

```python
import random
f = [[random.randint(1,100) for _ in range(4)] for _ in range(5)]
m = len(f)
n = len(f[0])
ans = min(f[t][n - 1] for t in range(m))
```



### 统计数字的二进制0，1个数

```python
bin(1234).count('0')
bin(1234).count("1")
```

### 二分查找

python标准库下bisect 下函数

1.  bisect.bisect(a, x, lo=0, hi=len(a))
2.  bisect.bisect\_right(a, x, lo=0, hi=len(a))
3.  bisect.bisect\_left(a, x, lo=0, hi=len(a))
4.  bisect.insort(a, x, lo=0, hi=len(a))
5.  bisect.insort\_right(a, x, lo=0, hi=len(a))
6.  bisect.insort\_left(a, x, lo=0, hi=len(a))

SortedDict

```python
# 待补充
```

> Java 二分查找
>
> > java.util.Arrays.binarySearch(...)
> > java.util.Collections.binarySearch(List\<T> ...)


## itertools
The module standardizes a core set of fast, memory efficient tools that are useful by themselves or in combination. Together, they form an “iterator algebra” making it possible to construct specialized tools succinctly and efficiently in pure Python.
该模块标准化了一组快速、内存高效的核心工具，这些工具可以单独使用或组合使用。它们共同构成了一个“迭代器代数”，使得在纯 Python 中简洁高效地构建专用工具成为可能。


### pairwise()
Return successive overlapping pairs taken from the input iterable.
返回从输入可迭代对象中获取的连续重叠对。

The number of 2-tuples in the output iterator will be one fewer than the number of inputs. It will be empty if the input iterable has fewer than two values. 输出迭代器中的 2 元组数将比输入数少 1。如果输入可迭代对象的值少于两个，则它将为空。

``` python
pairwise('ABCDEFG') 
# AB BC CD DE EF FG
```


## Vscode相关

### 1、变量引用

示例文件study\_note\_1.py的内容如下：

```py

class Session(object):
   """
   A simple example class
   """
   sess = "comm session"

class Table(object):
   def __init__(
      self,
      session: Session,
      name: str
   ):
      self._name = name
      self._session = session
   
   def name(self):
      return self._name;

   def session(self):
      return self._session.sess;


table1 = Table(Session(), "first_table");
print(table1.name());
print(table1.session());

```

其执行结果为：

```shell
$ python3 study_note_1.py
first_table
comm session
```

修改上述文件，改变`Table`和`Session`的定义顺序，先定义`Session`，如study\_note\_2.py的内容如下：

```py
class Table(object):
   def __init__(
      self,
      session: Session,
      name: str
   ):
      self._name = name
      self._session = session
   
   def name(self):
      return self._name;

   def session(self):
      return self._session.sess;

class Session(object):
   """
   A simple example class
   """
   sess = "comm session"


table1 = Table(Session(), "first_table");
print(table1.name());
print(table1.session());

```

其执行结果为：

```shell
$ python3 study_note_2.py 
Traceback (most recent call last):
  File "RefClass.py", line 2, in <module>
    class Table(object):
  File "RefClass.py", line 5, in Table
    session: Session,
NameError: name 'Session' is not defined
```

修改study\_note\_2.py文件，将文件中`session: Session,` 修改为`session: "Session",`后再次执行，其结果为：

```shell
$ python3 study_note_2.py 
first_table
comm session
```

### 2、Python Enviroment Setting in vscode

vscode的python相关环境变量的设置，在[vscode官方的文档](https://code.visualstudio.com/docs/python/environments)涉及python环境变量，例如`PYTHONPATH`，关键信息描述如下:

By default, the Python extension looks for and loads a file named .env in the current workspace folder, then applies those definitions.

Environment variable definitions files can be used for scenarios such as debugging and tool execution (including linters, formatters, IntelliSense, and testing tools), but aren't applied to the terminal.

The PYTHONPATH environment variable specifies additional locations where the Python interpreter should look for modules. In VS Code, PYTHONPATH can be set through the terminal settings (terminal.integrated.env.\*) and/or within an .env file.

google中文翻译：
默认情况下，Python 扩展在当前工作空间文件夹中查找并加载一个名为 .env 的文件，然后应用这些定义。

环境变量定义文件可用于调试和工具执行（包括 linter、格式化程序、IntelliSense 和测试工具）等场景，但不适用于终端。

PYTHONPATH 环境变量指定 Python 解释器应在其中查找模块的其他位置。 在 VS Code 中，可以通过终端设置 (terminal.integrated.env.\*) 和/或在 .env 文件中设置 PYTHONPATH。

简单说，当运行一个py文件时，使用在terminal中执行`python ***.py`命令，python引用到的其他文件(`PYTHONPATH`)或使用的其他环境变量的设置，需要通过terminal.integrated.env.\*设置；而debug一个py文件时，使用到的环境变量可以在.env文件中进行设置

设置方法

*   terminal.integrated.env
    1.  在vscode中，选择setting，搜索terminal.integrated
    2.  选择使用的Env，包括linux、windows等，点击`Edit in setting.json`
    3.  在打开的setting.json文件中，进行编辑：
        ```json
        "terminal.integrated.env.linux": {
           "PYTHONPATH": "${workspaceFolder}/python:${env:PYTHONPATH}",
           "PROJECT_BASE": "${workspaceFolder}"
        },
        ```

*   运行python文件(菜单命令：Run Python File)时环境变量设置，使用`.env`文件
    1.  在项目的根目录下添加.env，若以存在则忽略
    2.  在.env中添加环境变量
        ```shell
        PYTHONPATH=${workspaceFolder}/python
        PROJECT_BASE=./
        ```

*   Debug python文件(菜单命令：Debug Python File)时变量设置
    ???

*   Debug python文件时，配置并使用`launch.json`文件,在`Run and Debug`窗口中执行配置文件中`Python: Current File`
    1.  例如设置`FATE_PROJECT_BASE`环境变量
    2.  在Debug窗口中，增加`launch.json`配置文件，或在文件中增加配置信息
        ```json
        {
             // Use IntelliSense to learn about possible attributes.
             // Hover to view descriptions of existing attributes.
             // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
             "version": "0.2.0",
             "configurations": [
                 {
                     "name": "Python: Current File",
                     "type": "python",
                     "request": "launch",
                     "program": "${file}",
                     "console": "integratedTerminal",
                     "justMyCode": true,
                     "env": {"FATE_PROJECT_BASE": "${workspaceFolder}/"}
         
                 },
                 {
                     "name": "Python: Attach using Process Id",
                     "type": "python",
                     "request": "attach",
                     "connect": {
                         "host": "127.0.0.1",
                         "port": 5678
                     }
                 }
             ]
         }
        ```
        在launch请求类型中增加环境变量`FATE_PROJECT_BASE`，执行当前python文件中，读取配置的环境变量

## Python Installation and configure

> <https://computingforgeeks.com/how-to-install-python-3-on-centos/>
> <https://computingforgeeks.com/install-python-3-on-centos-rhel-7/>

### 1, Python shell ^\[\[a ↑ ↓

操作系统：Centos 7
Python版本：3.8.16
问题：在pythom shell中使用↑ ↓ 键，出现^\[\[a字符，而无法选择历史命令
解决方案：

*   安装的系统软件， yum instll readline
*   安装python库， 使用**pip3 install gnureadline**， 而不是~~pip3 install readline~~

# Reference

## Python Type check

[Python 类型检查（指南）](https://realpython.com/python-type-checking/#duck-types-and-protocols)

[中文翻译](https://zhuanlan.zhihu.com/p/141504225)