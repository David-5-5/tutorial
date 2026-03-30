# Ray 源码分析：从 @ray.remote 装饰器到 C++ 核心调度全过程

## 目录

1. [从一个最简单的案例开始](#一从一个最简单的案例开始)
2. [Python 层：@ray.remote 装饰器做了什么](#二python层rayremote-装饰器做了什么)
3. [Cython 桥接层：Python 到 C++ 的转换](#三cython-桥接层python-到-c-的转换)
4. [C++ 核心层：CoreWorker 任务构造](#四c-核心层coreworker-任务构造)
5. [调度层：Raylet 如何完成资源调度](#五调度层raylet-如何完成资源调度)
6. [执行层：任务在 Worker 进程中执行](#六执行层任务在-worker-进程中执行)
7. [总结：整个调用链路梳理](#七总结整个调用链路梳理)

---

## 一、从一个最简单的案例开始

让我们从用户最直观的用法开始，一步步追踪代码的走向：

```python
import ray

# 初始化Ray集群
ray.init()

# 使用@ray.remote装饰器标记远程函数
@ray.remote
def add(a, b):
    return a + b

# 远程调用，返回ObjectRef
obj_ref = add.remote(1, 2)

# 获取结果
result = ray.get(obj_ref)
print(result)  # 输出: 3
```

这短短几行代码，背后涉及了 Python 装饰器处理 → Cython 类型转换 → C++ 任务构造 → GCS 元数据存储 → Raylet 调度 → Worker 进程执行 → 结果写回对象存储 这一整套流程。

---

## 二、Python 层：@ray.remote 装饰器做了什么

### 2.1 装饰器入口：`ray.remote` 的定义

`@ray.remote` 装饰器定义在 [`ray/_private/worker.py`](file:///home/luming/workspace/ray-project/ray/python/ray/_private/worker.py) 中：

```python
def remote(*args, **kwargs):
    if len(args) == 1 and len(kwargs) == 0:
        # 直接装饰函数：@ray.remote
        return _make_remote(args[0], {})
    # 带参数装饰器：@ray.remote(num_gpus=1)，返回偏函数
    assert len(args) == 0 and len(kwargs) > 0
    return functools.partial(_make_remote, options=kwargs)
```

### 2.2 `_make_remote`：区分函数还是类

```python
def _make_remote(function_or_class, options):
    if inspect.isfunction(function_or_class) or is_cython(function_or_class):
        ray_option_utils.validate_task_options(options, in_options=False)
        return ray.remote_function.RemoteFunction(
            Language.PYTHON,
            function_or_class,
            None,
            options,
        )

    if inspect.isclass(function_or_class):
        ray_option_utils.validate_actor_options(options, in_options=False)
        return ray.actor._make_actor(function_or_class, options)

    raise TypeError(...)
```

**关键点：**
- 对于普通函数，包装成 `RemoteFunction` 对象
- 对于类，包装成 `ActorClass` 对象（本文专注函数调用）

### 2.3 `RemoteFunction`：保存元信息，等待调用

`RemoteFunction` 定义在 [`ray/remote_function.py`](file:///home/luming/workspace/ray-project/ray/python/ray/remote_function.py)：

```python
class RemoteFunction:
    def __init__(self, language, function, function_descriptor, task_options):
        self._default_options = task_options
        # 保存函数信息
        self._language = language
        self._function = function
        self._function_name = function.__module__ + "." + function.__name__
        self._function_descriptor = function_descriptor
        ...
        # 覆盖remote方法的签名和文档
        @wraps(function)
        def _remote_proxy(*args, **kwargs):
            return self._remote(
                serialized_runtime_env_info=self._serialized_base_runtime_env_info,
                args=args, kwargs=kwargs, **self._default_options)
        self.remote = _remote_proxy
```

当用户调用 `add.remote(1, 2)` 时，实际上调用的是 `_remote_proxy → _remote()`。

### 2.4 `_remote()`：提交任务前的准备工作

在 `RemoteFunction._remote()` 中，主要做了这些事情：

1. **检查是否连接**：`worker.check_connected()`
2. **导出函数**：如果是第一次在当前集群调用这个函数，序列化函数并导出到 GCS
   ```python
   self._function_descriptor = PythonFunctionDescriptor.from_function(
       self._function, self._uuid)
   self._pickled_function = pickle_dumps(self._function, ...)
   worker.function_actor_manager.export(self)
   ```
3. **处理参数**：扁平化参数，提取签名信息
4. **整理资源请求**：从 options 中提取 `num_cpus`/`num_gpus`/自定义资源，生成资源字典
5. **处理调度策略**：支持默认调度、Spread 调度、Placement Group 调度等
6. **调用核心worker提交**：最终调用 `worker.core_worker.submit_task(...)`

---

## 三、Cython 桥接层：Python 到 C++ 的转换

`worker.core_worker` 实际上是 Cython 扩展模块 `ray._raylet` 中定义的 `CoreWorker` 类。`submit_task` 定义在 [`_raylet.pyx`](file:///home/luming/workspace/ray-project/ray/python/ray/_raylet.pyx)：

```cython
def submit_task(self,
                Language language,
                FunctionDescriptor function_descriptor,
                args,
                c_string name,
                int num_returns,
                resources,
                int max_retries,
                c_bool retry_exceptions,
                retry_exception_allowlist,
                scheduling_strategy,
                c_string debugger_breakpoint,
                c_string serialized_runtime_env_info,
                int64_t generator_backpressure_num_objects,
                c_bool enable_task_events,
                labels,
                label_selector):
    # 1. Python字典 -> C++ unordered_map 转换资源
    cdef unordered_map[c_string, double] c_resources
    prepare_resources(resources, &c_resources)

    # 2. 转换调度策略
    cdef CSchedulingStrategy c_scheduling_strategy
    self.python_scheduling_strategy_to_c(scheduling_strategy, &c_scheduling_strategy)

    # 3. 转换函数描述符
    cdef CRayFunction ray_function = CRayFunction(
        language.lang, function_descriptor.descriptor)

    # 4. 转换任务参数，处理对象引用
    cdef c_vector[unique_ptr[CTaskArg]] args_vector
    prepare_args_and_increment_put_refs(...)

    # 5. 创建任务选项
    cdef CTaskOptions task_options = CTaskOptions(
        name, num_returns, c_resources, ...)

    # 6. **释放GIL，调用C++核心**
    with nogil:
        return_refs = CCoreWorkerProcess.GetCoreWorker().SubmitTask(
            ray_function, args_vector, task_options,
            max_retries, retry_exceptions, c_scheduling_strategy, ...)

    # 7. 转换C++返回值为Python对象返回
    return VectorToObjectRefs(return_refs, ...)
```

**核心作用：**
- 负责 Python 数据类型到 C++ 数据结构的转换
- 释放 Python GIL，让 C++ 可以真正并发执行
- 调用 C++ `CoreWorker::SubmitTask`，返回结果给 Python 层

---

## 四、C++ 核心层：CoreWorker 任务构造

`CCoreWorkerProcess::GetCoreWorker()` 返回单例 `CoreWorker`，调用其 `SubmitTask` 方法，定义在 [`core_worker.cc`](file:///home/luming/workspace/ray-project/ray/src/ray/core_worker/core_worker.cc)：

```cpp
std::vector<rpc::ObjectReference> CoreWorker::SubmitTask(
    const RayFunction &function,
    const std::vector<std::unique_ptr<TaskArg>> &args,
    const TaskOptions &task_options,
    int max_retries,
    bool retry_exceptions,
    const rpc::SchedulingStrategy &scheduling_strategy,
    ...) {

  // 1. 生成任务ID：TaskID::ForNormalTask
  const auto task_id = TaskID::ForNormalTask(
      worker_context_->GetCurrentJobID(),
      worker_context_->GetCurrentInternalTaskId(),
      next_task_index);

  // 2. 添加Placement Group约束（如果有的话）
  auto constrained_resources =
      AddPlacementGroupConstraint(task_options.resources, scheduling_strategy);

  // 3. 构建任务规格TaskSpecification
  TaskSpecBuilder builder;
  BuildCommonTaskSpec(
      builder,
      worker_context_->GetCurrentJobID(),
      task_id,
      task_name,
      ... /* 填充所有字段：函数描述、参数、资源、标签等 */);
  builder.SetNormalTaskSpec(max_retries, retry_exceptions, ...);
  TaskSpecification task_spec = std::move(builder).ConsumeAndBuild();

  // 4. 如果是本地模式，本地直接执行；否则交给任务管理器异步提交
  if (options_.is_local_mode) {
    returned_refs = ExecuteTaskLocalMode(task_spec);
  } else {
    returned_refs = task_manager_->AddPendingTask(
        task_spec.CallerAddress(), task_spec, CurrentCallSite(), max_retries);

    // 异步提交任务到raylet，通过事件循环处理
    io_service_.post(
        [this, task_spec = std::move(task_spec)]() mutable {
          normal_task_submitter_->SubmitTask(std::move(task_spec));
        },
        "CoreWorker.SubmitTask");
  }

  // 返回对象引用给Python层，用户可以用ray.get获取结果
  return returned_refs;
}
```

**这里已经构造好了完整的任务描述：**
- 任务ID、JobID
- 函数描述符（包含序列化后的Python函数）
- 资源要求（CPU/GPU/自定义资源）
- 参数（可以是内联参数或对象引用）
- 调度策略
- 重试配置等

---

## 五、调度层：Raylet 如何完成资源调度

### 5.1 任务怎么到达 Raylet？

`normal_task_submitter_->SubmitTask` 通过 gRPC 将任务提交给本地 Raylet（运行在同一个节点上）。

Raylet 是 Ray 的节点守护进程，用 C++ 实现，主要负责：
- 节点资源管理
- 任务调度
- 启动/停止 Worker 进程

### 5.2 资源调度流程

Raylet 的调度逻辑主要在：
- **`raylet/node_manager.cc`**：节点管理器，处理心跳、任务提交、启动Worker
- **`raylet/scheduling/cluster_resource_scheduler.cc`**：集群资源调度器，决定任务分配到哪个节点
- **`raylet/scheduling/cluster_resource_manager.cc`**：集群资源管理器，维护各节点资源状态

调度的大体流程：

1. **接收任务**：Raylet 的 NodeManager 接收到来自 CoreWorker 的任务提交请求
2. **资源检查**：`ClusterResourceScheduler` 检查当前节点（或其他节点）是否有足够空闲资源满足任务要求
   ```cpp
   // 检查资源是否满足，这是调度决策的核心
   bool ClusterResourceScheduler::HasAvailableResources(
       const ResourceRequest &resource_request,
       string *node_will_be_schedulded_on) {
     // ... 尝试找到一个有足够空闲资源的节点 ...
   }
   ```
3. **分配资源**：找到满足资源的节点后，标记资源为已占用
4. **租约机制**：Ray 使用 "lease" 机制，将任务的执行租约授予该节点
5. **等待Worker**：如果节点上没有空闲的Python Worker进程，Raylet会启动一个新的Worker
6. **下发任务**：通过gRPC将任务规格发送给选定的Worker进程

### 5.3 调度策略

Ray 支持几种调度策略：

| 策略 | 说明 |
|-----|------|
| DEFAULT | 默认策略，优先Pack任务（让任务紧凑排列） |
| SPREAD | 尽量Spread分布，适合需要隔离的场景 |
| PlacementGroup | 基于放置组的亲和性调度，保证一组任务放在一起 |
| NodeAffinity | 指定必须调度到某个节点 |

---

## 六、执行层：任务在 Worker 进程中执行

当任务被调度到某个Worker后：

1. **Worker接收任务**：Worker进程中的 CoreWorker 通过 gRPC 收到任务
2. **反序列化**：取出任务规格，反序列化出Python函数和参数
3. **执行函数**：在Python解释器中执行用户函数
   ```python
   # Worker进程执行任务的大体逻辑
   result = function(*args, **kwargs)
   ```
4. **结果写入对象存储**：将执行结果写入Ray的共享内存对象存储（Plasma）
5. **返回引用**：结果对象的引用通过Gossip传播给调用者
6. **调用者获取结果**：`ray.get()` 通过对象引用从本地或远端对象存储取出结果

---

## 七、总结：整个调用链路梳理

让我们从头到尾串一遍调用路径：

```
用户代码
  ↓
@ray.remote 装饰Python函数
  → _make_remote → 创建 RemoteFunction 对象
  ↓
add.remote(1, 2) 触发调用
  → RemoteFunction._remote()
  → 序列化函数（如果第一次调用）
  → worker.core_worker.submit_task()
  ↓
Cython 桥接层 (_raylet.pyx)
  → Python类型 → C++类型转换
  → 释放GIL
  → CCoreWorkerProcess::GetCoreWorker().SubmitTask()
  ↓
C++ CoreWorker (core_worker.cc)
  → 生成TaskID
  → 构建TaskSpecification
  → task_manager->AddPendingTask()
  → 异步提交给Raylet
  ↓
Raylet 调度 (raylet/)
  → NodeManager 接收任务
  → ClusterResourceScheduler 检查资源
  → 分配资源，获取Worker
  → 通过gRPC下发任务给Worker进程
  ↓
Worker 执行
  → CoreWorker 接收任务
  → 反序列化函数和参数
  → Python解释器执行用户函数
  → 结果写入对象存储
  ↓
返回结果给调用者
  → 结果对象引用返回给调用方
  → ray.get() 从对象存储取出结果
  → 用户拿到最终计算结果
```

## 八、关键设计点

| 层级 | 职责 | 关键文件 |
|-----|------|---------|
| Python API | 用户接口、参数整理、函数序列化 | `remote_function.py`, `worker.py` |
| Cython 桥接 | 类型转换、跨语言调用 | `_raylet.pyx` |
| CoreWorker | 任务构造、任务管理 | `core_worker.cc`, `task_manager.cc` |
| Raylet | 资源调度、Worker管理 | `node_manager.cc`, `cluster_resource_scheduler.cc` |
| Worker | 实际执行用户代码 | Python 解释器 + 任务执行循环 |

**亮点设计：**

1. **分层架构**：Python层负责接口和易用性，C++层负责核心调度和性能
2. **惰性序列化**：函数只在第一次调用时序列化，避免重复工作
3. **租约调度**：分布式调度使用租约机制，减少锁竞争
4. **共享内存对象存储**：结果存在共享内存，多进程零拷贝读取

---

## 附录：关键文件索引

| 文件路径 | 作用 |
|---------|------|
| `python/ray/_private/worker.py` | `@ray.remote` 入口定义 |
| `python/ray/remote_function.py` | `RemoteFunction` 类实现 |
| `python/ray/_raylet.pyx` | Cython桥接，连接Python和C++核心 |
| `src/ray/core_worker/core_worker.cc` | C++ CoreWorker实现，SubmitTask入口 |
| `src/ray/raylet/node_manager.cc` | Raylet节点管理 |
| `src/ray/raylet/scheduling/cluster_resource_scheduler.cc` | 资源调度核心逻辑 |
