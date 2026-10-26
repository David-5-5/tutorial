# 2D Max Pooling 手写实现学习笔记

## 0. 先确认你已经会的部分

你已经能理解交叉熵这道题：

```python
target_logits = logits[torch.arange(N, device=logits.device), true_labels]
loss[:] = (torch.log(torch.sum(torch.exp(logits), dim=1)) - target_logits).mean()
```

这里面用到的三个核心动作，本笔记全程复用：

1. **按维度规约**：`sum(dim=1)` 沿第 1 维把一行压成一个数
2. **高级索引**：`logits[arange(N), labels]` 按行对齐取元素
3. **广播逐元素运算**：两个张量形状对齐后直接 `+ - * /`

max pooling 没有引入新数学，只是把"对一行取 sum"换成"对一个窗口取 max"。难点只在于：**如何把所有窗口一次性取出来**。

---

## 1. 问题与约定

### 1.1 输入输出形状

池化前：

```
x: [N, C, H, W]
```

- `N`：batch，一批多少张图
- `C`：通道数，每张图几个特征层
- `H, W`：高度、宽度

池化后：

```
y: [N, C, H_out, W_out]
```

公式：

$$H_{out} = \lfloor (H + 2p - k) / s \rfloor + 1$$
$$W_{out} = \lfloor (W + 2p - k) / s \rfloor + 1$$

其中 `k` = kernel_size，`s` = stride，`p` = padding。

### 1.2 单样本单通道看本质

先把 `N=1, C=1` 固定住，只看一个 `H × W` 矩阵。池化就是：在矩阵上滑动 `k × k` 窗口，每个窗口只留最大值。

以题目示例 1 为例（`k=2, s=2, p=0`）：

```
x:
1 2 3 4
5 6 7 8
9 2 4 3
1 6 5 8
```

四个窗口：

```
窗口 (0,0) → 取 max(1,2,5,6)  = 6
窗口 (0,1) → 取 max(3,4,7,8)  = 8
窗口 (1,0) → 取 max(9,2,1,6)  = 9
窗口 (1,1) → 取 max(4,3,5,8)  = 8

y:
6 8
9 8
```

### 1.3 一个输出位置对应一个窗口

对输出位置 `(h, w)`，输入窗口的左上角：

$$h_0 = h \cdot s - p$$
$$w_0 = w \cdot s - p$$

窗口覆盖：

```
x[:, :, h_0 : h_0 + k, w_0 : w_0 + k]
```

---

## 2. 方案一：Python 手写循环（理解逻辑用，不能 AC）

### 2.1 思路

按输出位置逐个遍历，切出窗口，取 `max`，写回 `y`。这是最贴近公式的写法，用来理解"一个输出位置对应一个窗口"。

### 2.2 代码

```python
import torch
import torch.nn.functional as F

def solve_loop(input: torch.Tensor, output: torch.Tensor,
               kernel_size: int, stride: int, padding: int,
               N: int, C: int, H: int, W: int):
    x = input.reshape(N, C, H, W)

    # 先补 padding，max 场景补 -1e30（近似 -inf），不能补 0
    x = F.pad(x, (padding, padding, padding, padding),
              mode="constant", value=-1e30)

    H_out = (H + 2 * padding - kernel_size) // stride + 1
    W_out = (W + 2 * padding - kernel_size) // stride + 1

    # 初始化 y，先填 -1e30，保证窗口内全负时取到真实值
    y = torch.full((N, C, H_out, W_out), -1e30,
                   device=x.device, dtype=x.dtype)

    # 四层循环：batch、channel、输出行、输出列
    for n in range(N):
        for c in range(C):
            for h in range(H_out):
                for w in range(W_out):
                    h0 = h * stride
                    w0 = w * stride
                    window = x[n, c, h0:h0 + kernel_size,
                               w0:w0 + kernel_size]
                    y[n, c, h, w] = window.max()

    output[:] = y.reshape(-1)
```

### 2.3 逐行讲解

**补 padding**

```python
x = F.pad(x, (padding, padding, padding, padding),
          mode="constant", value=-1e30)
```

`F.pad` 的参数顺序是 `(左, 右, 上, 下)`，这里四个参数相等表示四周各补 `padding`。补的值选 `-1e30` 而不是 0：max 取大值，若补 0，当窗口真实值全为负数时，结果会错误地变成 0。

**输出尺寸**

```python
H_out = (H + 2 * padding - kernel_size) // stride + 1
W_out = (W + 2 * padding - kernel_size) // stride + 1
```

补零后输入变成 `H + 2p`，窗口起点从 0 开始，每次跳 `stride`，最后一个窗口起点为 `(H_out - 1) * s`，终点不超出补零后的高度。

**初始化 y**

```python
y = torch.full((N, C, H_out, W_out), -1e30,
               device=x.device, dtype=x.dtype)
```

和补 padding 同一个道理：用足够小的值初始化，后续 `max` 才能正确覆盖。

**切片取窗口**

```python
window = x[n, c, h0:h0 + kernel_size, w0:w0 + kernel_size]
```

- `n, c`：定位到第几张图、哪个通道
- `h0:h0+k`：窗口在行方向的范围
- `w0:w0+k`：窗口在列方向的范围

`window` 的形状是 `[k, k]`，`window.max()` 返回标量。

### 2.4 为什么超时

四重循环每一层都在 Python 里执行，每切一个小窗口就启动一次 GPU 小操作。GPU 擅长一次处理大块张量，频繁调用小内核导致大部分时间耗在 Python 调度上，而不是计算上。

这道题性能测试规模 `N=4, k=3, s=2`，H、W 上限 1024，窗口数量可以达到几十万，Python 循环逐条处理必然超时。

---

## 3. 预备知识：维度规约与展开

### 3.1 `max(dim=?)` 和 `sum(dim=?)` 是同族操作

交叉熵里你已经用过：

```python
torch.sum(logits, dim=1)   # 沿第 1 维求和，每行压成一个标量
```

max 完全同构：

```python
window.max(dim=-1).values  # 沿最后一维取最大值
```

注意 `max` 返回两个东西：

```python
values, indices = window.max(dim=-1)
```

- `values`：最大值本身
- `indices`：最大值所在位置（池化用不到，取 `.values` 即可）

### 3.2 规约前后形状变化

```python
# a.shape = [2, 3, 4, 5]
a.max(dim=-1).values.shape  # [2, 3, 4]，最后一维被消掉
a.max(dim=2).values.shape   # [2, 3, 5]，第 2 维被消掉
```

和 `sum(dim=?)` 规则一致：被规约的那一维从形状里消失。

### 3.3 `unfold` 做什么

`unfold(dimension, size, step)` 沿指定维度滑动窗口，把窗口内容展开成新的一维。

先看一维例子：

```python
x = torch.tensor([1.0, 2.0, 3.0, 4.0, 5.0])
x.unfold(0, size=2, step=1)
```

结果：

```
tensor([[1., 2.],
        [2., 3.],
        [3., 4.],
        [4., 5.]])
```

形状从 `[5]` 变成 `[4, 2]`：

- 第 0 维：窗口个数
- 新的最后一维：窗口内元素

`size=2` 是窗口长度，`step=1` 是滑动步长。

### 3.4 二维连续 unfold

对 `[N, C, H, W]` 连续调两次：

```python
windows = x.unfold(2, kernel_size, stride).unfold(3, kernel_size, stride)
```

形状变化：

```
x:          [N, C, H, W]
unfold(2):  [N, C, H_out, W, k]
unfold(3):  [N, C, H_out, W_out, k, k]
```

最后两维 `k, k` 就是窗口本身；前面四维对应 batch、通道、输出行、输出列。

### 3.5 用一个小矩阵确认

```python
x = torch.arange(1, 10, dtype=torch.float32).reshape(1, 1, 3, 3)
# x:
# [[1, 2, 3],
#  [4, 5, 6],
#  [7, 8, 9]]

windows = x.unfold(2, 2, 1).unfold(3, 2, 1)
# windows.shape = [1, 1, 2, 2, 2, 2]
```

`windows[0, 0, 0, 0]` 就是左上角窗口：

```
[[1., 2.],
 [4., 5.]]
```

`windows[0, 0, 0, 1]` 是右上窗口：

```
[[2., 3.],
 [5., 6.]]
```

四个输出位置和四个窗口一一对应，和 2.2 节手写循环切出的内容完全相同。

---

## 4. 方案二：unfold + 两次 max（AC 方案）

### 4.1 思路

1. 补 padding
2. 两次 `unfold` 把所有窗口拼成 `[N, C, H_out, W_out, k, k]`
3. 先沿最后一维（窗口列方向）取 max，再沿新的最后一维（窗口行方向）取 max
4. 得到 `[N, C, H_out, W_out]`，展平写入 output

### 4.2 代码

```python
import torch
import torch.nn.functional as F

def solve_unfold(input: torch.Tensor, output: torch.Tensor,
                kernel_size: int, stride: int, padding: int,
                N: int, C: int, H: int, W: int):
    x = input.reshape(N, C, H, W)
    x = F.pad(x, (padding, padding, padding, padding),
              mode="constant", value=-1e30)

    H_out = (H + 2 * padding - kernel_size) // stride + 1
    W_out = (W + 2 * padding - kernel_size) // stride + 1

    # [N, C, H_out, W_out, k, k]
    windows = x.unfold(2, kernel_size, stride) \
               .unfold(3, kernel_size, stride)

    # 先取窗口列方向 max，再取窗口行方向 max
    y = windows.max(dim=-1).values.max(dim=-1).values

    output[:] = y.reshape(-1)
```

### 4.3 形状跟踪表

| 步骤 | 形状 | 说明 |
|------|------|------|
| `x = input.reshape(...)` | `[N, C, H, W]` | 还原标准布局 |
| `F.pad(...)` | `[N, C, H+2p, W+2p]` | 四周补 `-1e30` |
| `unfold(2, k, s)` | `[N, C, H_out, W+2p, k]` | 行方向展开窗口 |
| `unfold(3, k, s)` | `[N, C, H_out, W_out, k, k]` | 列方向展开窗口 |
| `max(dim=-1)` | `[N, C, H_out, W_out, k]` | 每行内取最大值 |
| `max(dim=-1)` | `[N, C, H_out, W_out]` | 列方向再取最大值 |
| `reshape(-1)` | `[N*C*H_out*W_out]` | 对齐一维 output |

### 4.4 两次 max 的必要性

窗口是二维 `[k, k]`，`max` 一次只能消一维。

```
窗口 [k, k]
  → max(dim=-1) 消掉列维，得到 [k]：每一行的最大值
  → max(dim=-1) 消掉行维，得到标量：整个窗口的最大值
```

和手写循环里 `window.max()` 一次性取全部元素最大值等价，只是分两步做。

### 4.5 为什么不需要 Python 循环

`unfold` 在 GPU 上一次性构造所有窗口张量；两次 `max` 也是对整块张量做规约，中间没有 Python 层循环。窗口数量再大，内核启动次数保持常数。

---

## 5. 方案三：移位 + 逐元素 maximum（不依赖 unfold 的备选）

### 5.1 思路

不展开窗口，而是固定输出网格，把输入按核内偏移位置平移，每个偏移位置取一次 `maximum`。

核内偏移记为 `(di, dj)`，范围 `0 ≤ di, dj < k`。输出位置 `(h, w)` 对应的输入元素在：

$$x[:, :, h \cdot s + di, w \cdot s + dj]$$

所有偏移位置的最大值合并起来就是窗口最大值。

### 5.2 代码

```python
import torch
import torch.nn.functional as F

def solve_shift(input: torch.Tensor, output: torch.Tensor,
                kernel_size: int, stride: int, padding: int,
                N: int, C: int, H: int, W: int):
    x = input.reshape(N, C, H, W)
    x = F.pad(x, (padding, padding, padding, padding),
              mode="constant", value=-1e30)

    H_out = (H + 2 * padding - kernel_size) // stride + 1
    W_out = (W + 2 * padding - kernel_size) // stride + 1

    y = torch.full((N, C, H_out, W_out), -1e30,
                   device=x.device, dtype=x.dtype)

    # 循环只遍历核大小 k × k，不随 N、H、W 增长
    for di in range(kernel_size):
        for dj in range(kernel_size):
            # 切片步长取 stride，对应输出网格
            patch = x[:, :, di:H_out * stride + di:stride,
                      dj:W_out * stride + dj:stride]
            y = torch.maximum(y, patch)

    output[:] = y.reshape(-1)
```

### 5.3 讲解

**偏移切片**

```python
patch = x[:, :, di:H_out * stride + di:stride,
          dj:W_out * stride + dj:stride]
```

- `di` 是核内行偏移，`dj` 是核内列偏移
- 切片从 `di` 开始，步长 `stride`，终点取 `H_out * stride + di`，刚好覆盖所有输出位置
- `patch` 形状和 `y` 一致：`[N, C, H_out, W_out]`

**逐元素取大**

```python
y = torch.maximum(y, patch)
```

`maximum` 是广播逐元素比较，和 `+ - * /` 同类。每遍历一个核内位置，`y` 就保留到目前为止的最大值。

**循环次数可控**

外层两层循环只遍历 `k × k`，约束中 `k ≤ 16`，最多 256 次；内层切片和 `maximum` 都是整块 GPU 操作。这和方案一的四重空间循环有本质区别：循环次数不随输入尺寸增长。

### 5.3 三种方案对比

| 方案 | Python 循环 | 依赖算子 | 适用场景 |
|------|------------|----------|----------|
| 手写四重循环 | `N × C × H_out × W_out` | 无 | 只用于理解逻辑，不能 AC |
| unfold + max | 无 | `unfold`、`max` | 通用向量化写法，本题 AC |
| 移位 + maximum | `k × k`（常数） | `maximum`、切片步长 | 平台拦截 `unfold` 时兜底 |

---

## 6. 常见问题对照

### 6.1 补零为什么不用 0

max 保留大值。若窗口内真实值全为负，补 0 会让结果错误变成 0。max 池化语义上补的是 `-inf`，代码中用 `-1e30` 近似。

### 6.2 输出尺寸公式什么时候用 `ceil`

默认模式下输出尺寸用 `floor`，题目示例 1、2 都符合这个公式。若平台开 `ceil_mode=True`，公式改为向上取整；本题约束未提及，按 `floor` 实现即可。

### 6.3 输出为什么要 `reshape(-1)`

LeetGPU 平台传入的 `output` 通常是一维展平张量，池化结果 `[N, C, H_out, W_out]` 需要展平后写入；若题目 `output` 本身是四维，去掉 `reshape(-1)` 直接赋值。

### 6.4 交叉熵的思路能否套到池化上

交叉熵核心动作是"沿类别维规约"，池化是"沿窗口两维规约"。换一道窗口类题目（平均池化、窗口求和、层归一化窗口统计），先 `unfold` 出窗口，再换成 `mean`、`sum`、`std` 即可，框架不变。

---

## 7. 动手自测清单

1. 把 2.2 节手写循环在小矩阵 `3×3, k=2, s=1, p=0` 上跑通，手算预期结果对照。
2. 把 4.2 节 unfold 方案加一行 `print(windows.shape)`，确认形状和 4.3 节表格一致。
3. 故意把补零值改成 `0`，构造全负输入观察错误结果，理解为什么 max 要补 `-inf`。
4. 把 4.2 节两次 `max` 改成一次，观察形状和结果错误，理解二维窗口为什么要规约两次。
