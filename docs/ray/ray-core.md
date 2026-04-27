# Ray Core 核心流程分析

本文档按核心文件和调用链组织 Ray 核心流程分析，通过交叉引用建立完整的知识体系。

---

[toc]

---

## 1. ray start 集群启动流程

### 1.1 入口层：scripts.py

**位置**: 第 679-1180 行

`ray start` 命令支持 **Head 节点** 和 **Worker 节点** 两种模式，共用同一个 `start()` 函数（约 500 行代码），通过 `--head` 参数分支执行不同逻辑。

#### 1.1.1 CLI 参数设计

40+ 个参数按功能分类：

| 参数类别 | 关键参数 | 作用 |
|---------|---------|------|
| **节点标识** | `--head`, `--address`, `--port` | Head/Worker 模式选择 |
| **资源配置** | `--num-cpus`, `--num-gpus`, `--memory`, `--resources` | 节点资源声明 |
| **网络端口** | `--object-manager-port`, `--node-manager-port`, `--min-worker-port` | 各组件端口绑定 |
| **Dashboard** | `--include-dashboard`, `--dashboard-port` | Dashboard 配置 |
| **存储配置** | `--plasma-directory`, `--object-spilling-directory` | 对象存储配置 |
| **高级配置** | `--system-config`, `--temp-dir`, `--block` | 系统级配置 |
| **标签** | `--labels`, `--labels-file` | 节点标签（调度用） |

#### 1.1.2 执行流程总览

```
ray start [--head]
    ↓
[ 通用阶段 ] - Head 和 Worker 都执行
    ├── 1. 参数解析与验证
    ├── 2. 资源和标签解析
    └── 3. 构建 RayParams 对象
    ↓
[ 分支阶段 ] - 根据 --head 分流
    ├─→ Head 节点流程 ──┐
    │                   │
    └─→ Worker 节点流程 ┘
    ↓
[ 收尾阶段 ]
    ├── 写入 gcs_address 到临时目录
    └── --block 模式：进入无限循环监控
```

#### 1.1.3 通用阶段详解

**参数解析与验证**

```python
# 双重标签解析：字符串 + YAML 文件
labels_from_file = parse_node_labels_from_yaml_file(labels_file)
labels_from_string = parse_node_labels_string(labels)  # key1=val1,key2=val2
labels_dict = {**labels_from_file, **labels_from_string}  # 字符串优先级更高

# 资源隔离配置
resource_isolation_config = ResourceIsolationConfig(...)
```

**RayParams 对象构建**

**关联文件**: `python/ray/_private/parameter.py`

RayParams 是**所有配置的唯一容器**，包含 30+ 个基础配置字段、资源隔离配置、Dashboard 配置、系统级配置。

**扩展点：RAY_START_HOOK**

```python
if ray_constants.RAY_START_HOOK in os.environ:
    load_class(os.environ[ray_constants.RAY_START_HOOK])(ray_params, head)
```

允许在真正启动前注入自定义逻辑（测试、监控、审计等）。

#### 1.1.4 Head 节点流程 (`--head`)

```
ray start --head --port=6379
    ↓
1. 设置 GCS 端口（默认 6379）
    ↓
2. ✅ 冲突检测：检查默认地址是否已在运行
    ↓
3. 创建 Node 实例 (head=True)
    ↓
4. 打印 Dashboard 地址和使用说明
    ↓
5. 写入 gcs_address 到临时文件
    ↓
6. --block 模式：进入监控循环
```

**关键设计：冲突检测**：通过临时目录中的 bootstrap 地址与默认地址比较，防止重复启动。

#### 1.1.5 Worker 节点流程

```
ray start --address=head-node:6379
    ↓
1. ✅ 必须指定 --address，否则直接 abort
    ↓
2. ✅ Head-only 参数检查（禁止 Worker 指定 --port 等）
    ↓
3. 规范化 GCS 地址
    ↓
4. 获取本机 IP 地址（连接到 GCS 后自动探测）
    ↓
5. 创建 Node 实例 (head=False) → 见 [1.2 进程编排层](#12-进程编排层nodepy)
    ↓
6. 版本检查：确保 Worker 与 Head 版本一致
    ↓
7. 写入 gcs_address 到临时文件
    ↓
8. --block 模式：进入监控循环
```

**关键设计：Worker 自动 IP 探测**：Worker 需要连接到 GCS 后才能确定自己应该使用哪个网卡。

#### 1.1.6 --block 模式详解

指定 `--block` 时，进程进入无限循环监控子进程状态：

```python
while True:
    time.sleep(1)
    deceased = node.dead_processes()  # 见 [1.2.4 进程统一管理机制](#124-进程统一管理机制)
    
    # 检查异常退出的进程
    expected_return_codes = [0, SIGTERM, -SIGTERM, 128+SIGTERM]
    unexpected_deceased = [p for p in deceased if p.returncode not in expected_return_codes]
    
    if unexpected_deceased:
        cli_logger.error("Some Ray processes died unexpectedly...")
```

**作用**:
- 生产环境推荐使用，防止进程退出导致集群节点离线
- 监控所有子进程（raylet、gcs_server 等）
- 异常退出时及时报警

---

### 1.2 进程编排层：node.py

**调用入口**: `scripts.py` 第 112/146 行创建 Node 实例

Node 类是**进程编排器**，负责所有子进程的生命周期管理，所有 C++ 进程均通过此类间接调用 `services.py` 启动。

#### 1.2.1 Node 类核心职责

| 职责 | 说明 |
|------|------|
| **进程启动** | Head 专属服务、Raylet、Agent 等 |
| **进程监控** | 检测子进程异常退出 |
| **配置同步** | Worker 从 GCS 拉取系统配置 |
| **生命周期** | 集群启动、关闭、清理 |

**关键方法矩阵**:

| 方法 | Head | Worker | 作用 |
|------|------|--------|------|
| `__init__()` | ✅ | ✅ | 初始化，调用下面两个方法 |
| `start_head_processes()` | ✅ | ❌ | GCS、Monitor、API Server |
| `start_ray_processes()` | ✅ | ✅ | Raylet、Agent、Log Monitor |
| `dead_processes()` | ✅ | ✅ | 获取已死亡的子进程 |
| `kill_all_processes()` | ✅ | ✅ | 杀死所有子进程 |
| `check_version_info()` | ❌ | ✅ | Worker 版本校验 |

---

#### 1.2.2 start_head_processes() 详解

**位置**: 第 1344 行

Head 节点专属，启动 GCS 及相关服务。

```python
def start_head_processes(self):
    self.start_gcs_server()              # 见 [1.2.2.1 Node.start_gcs_server()]
    self._write_cluster_info_to_kv()     # 写入元数据到 KV
    
    if not self._ray_params.no_monitor:
        self.start_monitor()             # 自动扩缩容监控
    
    if self._ray_params.ray_client_server_port:
        self.start_ray_client_server()   # 客户端连接服务
    
    self.start_api_server()              # Dashboard + REST API
```

**启动顺序原则**:
1. **GCS Server 必须第一个启动**，其他所有服务都依赖 GCS 进行通信和状态存储
2. 启动顺序严格按照依赖关系排列

##### 1.2.2.1 Node.start_gcs_server()

**位置**: 第 1113 行

Head 节点启动 GCS Server 的包装方法：

```python
def start_gcs_server(self):
    # 前置断言：确保只启动一次
    gcs_server_port = self._ray_params.gcs_server_port
    assert gcs_server_port > 0
    assert self._gcs_address is None, "GCS server is already running."
    
    # 1. 日志文件命名（唯一化）
    stdout_log_fname, stderr_log_fname = self.get_log_file_names(
        "gcs_server", unique=True, create_out=True, create_err=True
    )
    
    # 2. 调用 services.start_gcs_server() 启动 C++ 进程 → 见 [1.3.2]
    process_info = ray._private.services.start_gcs_server(
        self.redis_address,
        log_dir=self._logs_dir,
        stdout_filepath=stdout_log_fname,
        stderr_filepath=stderr_log_fname,
        session_name=self.session_name,
        ...,  # 12 个参数
    )
    
    # 3. 注册进程到 all_processes 字典 → 见 [1.2.4]
    assert ray_constants.PROCESS_TYPE_GCS_SERVER not in self.all_processes
    self.all_processes[ray_constants.PROCESS_TYPE_GCS_SERVER] = [process_info]
    
    # 4. 保存 GCS 地址供其他组件使用
    self._gcs_address = build_address(self._node_ip_address, gcs_server_port)
```

**关键设计要点**:

| 设计点 | 说明 |
|--------|------|
| **前置断言** | 防止重复启动 GCS，确保单例 |
| **日志唯一化** | `unique=True` 确保每次启动生成不同的日志文件 |
| **Fate Share 机制** | `kernel_fate_share` 确保父进程退出时 GCS 自动清理 → 见 [1.3.4] |
| **进程注册** | 所有进程注册到 `all_processes` 字典统一管理 → 见 [1.2.4] |

---

#### 1.2.3 start_ray_processes() 详解

**位置**: 第 1373 行

**调用方**: Head 和 Worker 节点 `__init__` 时都调用此方法

```python
def start_ray_processes(self):
    # [Worker 节点专属] 先从 GCS 拉取系统配置
    if not self.head:
        gcs_options = ray._raylet.GcsClientOptions.create(...)
        global_state = ray._private.state.GlobalState()
        global_state._initialize_global_state(gcs_options)
        new_config = global_state.get_system_config()
        
        # 配置一致性校验：本地配置必须是 GCS 配置的子集
        assert self._config.items() <= new_config.items(), (...)
        self._config = new_config
    
    # 1. 资源规格与硬件使用记录
    resource_and_label_spec = self.get_resource_and_label_spec()
    
    # 2. 确定 Plasma 对象存储配置
    plasma_directory, fallback_directory, object_store_memory = \
        services.determine_plasma_store_config(...)
    
    # 3. 资源隔离：将对象存储内存计入系统保留内存
    if self.resource_isolation_config.is_enabled():
        self.resource_isolation_config.add_object_store_memory(object_store_memory)
    
    # 4. 启动 Log Monitor（可选，用于日志聚合）
    if self._ray_params.include_log_monitor:
        self.start_log_monitor()
    
    # 5. 启动 Raylet（核心！本地调度器和对象存储）→ 见 [1.2.3.1]
    self.start_raylet(plasma_directory, fallback_directory, object_store_memory)
```

**关键设计：Worker 配置同步机制**

Worker 节点必须从 GCS 拉取系统配置，确保整个集群配置一致：
- 使用 `GlobalState` 客户端连接 GCS
- 拉取后进行子集校验，确保本地配置没有冲突
- 冲突时直接抛出异常，防止启动不一致的节点

##### 1.2.3.1 Node.start_raylet()

**位置**: 第 1147 行

Node 类中参数最多的方法之一，负责启动 Raylet 进程，分为 4 个阶段：

```python
def start_raylet(
    self,
    plasma_directory: str,
    fallback_directory: str,
    object_store_memory: int,
    use_valgrind: bool = False,
    use_profiler: bool = False,
):
    # 阶段 1：日志文件准备 - 为 Raylet 及内部 Agent 分别准备日志
    raylet_stdout_filepath, raylet_stderr_filepath = \
        self.get_log_file_names(PROCESS_TYPE_RAYLET, unique=True, ...)
    dashboard_agent_stdout_filepath, dashboard_agent_stderr_filepath = \
        self.get_log_file_names(PROCESS_TYPE_DASHBOARD_AGENT, ...)
    runtime_env_agent_stdout_filepath, runtime_env_agent_stderr_filepath = \
        self.get_log_file_names(PROCESS_TYPE_RUNTIME_ENV_AGENT, ...)
    
    # 阶段 2：资源隔离配置 - 收集系统进程 PID 用于 Cgroup
    self.resource_isolation_config.add_system_pids(
        self._get_system_processes_for_resource_isolation()
    )
    
    # 阶段 3：调用 services.start_raylet() 启动 C++ 进程 → 见 [1.3.3]
    process_info = ray._private.services.start_raylet(
        self.redis_address, self.gcs_address, self._node_id,  # 地址与标识
        self._node_ip_address, self._ray_params.node_manager_port,
        self._raylet_socket_name, self._plasma_store_socket_name,  # Socket 通信
        ...,  # 共 30+ 个参数
    )
    
    # 阶段 4：进程注册 → 见 [1.2.4]
    assert ray_constants.PROCESS_TYPE_RAYLET not in self.all_processes
    self.all_processes[ray_constants.PROCESS_TYPE_RAYLET] = [process_info]
```

---

#### 1.2.4 进程统一管理机制

Node 类通过 `all_processes` 字典统一管理所有子进程：

```python
# 字典结构
self.all_processes = {
    PROCESS_TYPE_GCS_SERVER: [process_info],      # Head 专属
    PROCESS_TYPE_RAYLET: [process_info],           # 所有节点
    PROCESS_TYPE_DASHBOARD: [process_info],        # Head 专属
    PROCESS_TYPE_MONITOR: [process_info],          # Head 专属
    PROCESS_TYPE_LOG_MONITOR: [process_info],      # 可选
    # ... 其他进程类型
}
```

**统一接口**:
- `dead_processes()`：从此字典查询异常退出的进程 → 被 `scripts.py` 的 --block 模式调用
- `kill_all_processes()`：从此字典获取所有进程并杀死 → 被 `ray stop` 命令调用

---

### 1.3 进程启动层：services.py

**调用入口**: `node.py` 中所有 `start_xxx()` 方法最终都调用此文件

底层进程启动函数的集合，提供所有 C++ 进程的 Python 包装。

#### 1.3.1 可执行文件路径映射

**位置**: 第 52-56 行

这些路径对应 Bazel 编译输出，打包在 Python wheel 中：

```python
RAYLET_EXECUTABLE = os.path.join(
    RAY_PATH, "core", "src", "ray", "raylet", "raylet" + EXE_SUFFIX
)
GCS_SERVER_EXECUTABLE = os.path.join(
    RAY_PATH, "core", "src", "ray", "gcs", "gcs_server" + EXE_SUFFIX
)
```

---

#### 1.3.2 start_gcs_server() 详解

**位置**: 第 1452 行

**调用方**: `Node.start_gcs_server()` → 见 [1.2.2.1]

```python
def start_gcs_server(
    redis_address: str, log_dir: str, ..., gcs_server_port: Optional[int] = None,
):
    # 构建命令行参数
    command = [
        GCS_SERVER_EXECUTABLE,
        f"--log_dir={log_dir}",
        f"--config_list={serialize_config(config)}",  # 序列化系统配置
        f"--gcs_server_port={gcs_server_port}",
        f"--node-ip-address={node_ip_address}",
        f"--session-name={session_name}",
        f"--ray-commit={ray.__commit__}",  # Git commit hash，版本校验
    ]
    
    # Redis 相关参数（可选外部 Redis）
    if redis_address:
        command += [f"--redis_address={redis_ip_address}", f"--redis_port={redis_port}"]
    
    # 调用通用进程启动器 → 见 [1.3.4]
    process_info = start_ray_process(
        command, ray_constants.PROCESS_TYPE_GCS_SERVER, ...
    )
    return process_info
```

---

#### 1.3.3 start_raylet() 详解

**位置**: 第 1536 行

**调用方**: `Node.start_raylet()` → 见 [1.2.3.1]

**函数签名**（30+ 个参数）：

```python
def start_raylet(
    redis_address: str, gcs_address: str, node_id: str, node_ip_address: str,
    node_manager_port: int, raylet_name: str, plasma_store_name: str,
    cluster_id: str, worker_path: str, setup_worker_path: str,
    temp_dir: str, session_dir: str, resource_dir: str, log_dir: str,
    resource_and_label_spec, plasma_directory: str, fallback_directory: str,
    object_store_memory: int, session_name: str, is_head_node: bool,
    resource_isolation_config: ResourceIsolationConfig,
    min_worker_port: Optional[int] = None, max_worker_port: Optional[int] = None,
    # ... 共 30+ 个参数
):
    # 内部调用 start_ray_process() → 见 [1.3.4]
```

**设计特点**:
- 参数数量极多（30+），反映了 Raylet 的复杂性
- 包含资源隔离、端口管理、路径配置等所有底层细节
- 所有配置最终通过命令行参数传递给 C++ 进程

---

#### 1.3.4 通用进程启动器：start_ray_process()

所有 C++ 进程都通过此函数启动，统一处理：

```python
def start_ray_process(
    command: List[str], process_type: str,
    stdout_file=None, stderr_file=None, fate_share=None,
):
    # 1. 环境变量设置
    # 2. 进程创建 subprocess.Popen
    # 3. Fate Share 机制（父进程死亡时子进程自动死亡）
    # 4. 返回 ProcessInfo 对象
```

**核心机制：Fate Share**

Ray 的核心设计，确保父进程退出时所有子进程自动清理，防止孤儿进程。此参数由 `node.py` 传入的 `kernel_fate_share` 控制 → 见 [1.2.2.1]。

---

### 1.4 C++ 核心组件层

启动入口：`services.py` 中通过可执行文件路径调用 C++ 二进制

#### 1.4.1 GCS Server 架构

**关键文件**: `src/ray/gcs/gcs_server.h`

GCS（Global Control Store）是 Ray 的全局状态管理中心，所有元数据都存储在这里。

**核心组件**

```cpp
class GcsServer {
private:
    // 元数据管理
    std::unique_ptr<GcsNodeManager> gcs_node_manager_;
    std::unique_ptr<GcsActorManager> gcs_actor_manager_;   // 核心！
    std::unique_ptr<GcsJobManager> gcs_job_manager_;
    std::unique_ptr<GcsWorkerManager> gcs_worker_manager_;
    std::unique_ptr<GcsPlacementGroupManager> gcs_placement_group_manager_;
    std::unique_ptr<GcsTaskManager> gcs_task_manager_;
    
    // 资源与调度
    std::unique_ptr<GcsResourceManager> gcs_resource_manager_;
    std::unique_ptr<ClusterResourceScheduler> cluster_resource_scheduler_;
    std::unique_ptr<ClusterLeaseManager> cluster_lease_manager_;
    
    // KV 存储与通信
    std::unique_ptr<GcsKVManager> gcs_kv_manager_;
    std::unique_ptr<rpc::GrpcServer> rpc_server_;
};
```

**启动完整流程**

```
GcsServer::Start()
  ↓
1. 初始化存储后端（Redis / 内存）
  ↓
2. 初始化各 Manager（按依赖顺序）
  ├── GcsNodeManager
  ├── GcsResourceManager
  ├── GcsActorManager    ← Actor 生命周期管理 → 见 [2.2]
  ├── GcsJobManager
  ├── GcsTaskManager
  └── GcsKVManager
  ↓
3. 注册所有 gRPC 服务 handler
  ↓
4. 启动 gRPC Server 监听（默认端口 6379）
  ↓
5. 启动后台定时任务（节点健康检查等）
```

---

#### 1.4.2 Raylet 内部架构

**关键文件**: `src/ray/raylet/raylet.h`

Raylet 是每个节点上的本地调度器，负责：
- 本地资源管理
- Worker 进程池管理
- 任务调度
- 对象管理

**核心组件**

| 组件 | 作用 | 关键文件 |
|------|------|---------|
| `NodeManager` | 节点资源管理、任务调度、Worker 生命周期 | `node_manager.h` |
| `WorkerPool` | Worker 进程池，管理空闲/忙碌的 Worker | `worker_pool.h` |
| `ClusterResourceScheduler` | 全局资源视图、节点选择 | `cluster_resource_scheduler.h` |
| `LocalResourceManager` | 本地资源核算 | `local_resource_manager.h` |
| `ObjectManager` | 对象传输、拉取/推送 | `object_manager.h` |
| `AgentManager` | Dashboard Agent 管理 | `agent_manager.h` |

**Worker 进程类型**

| 类型 | 作用 | 数量 |
|------|------|------|
| Python Worker | 执行普通任务/Actor | 动态增减 |
| Java Worker | 执行 Java 任务 | 动态增减 |
| CoreWorker | C++ 核心层（每个进程 1 个） | 每个进程 1 个 |
| Driver | 用户主进程（Python/Java） | 每个 Job 1 个 |

---

## 2. ray remote 任务提交与执行

### 2.1 @ray.remote 完整流程

**关键文件**: `python/ray/_private/worker.py` (第 3552 行)

详细追踪 `@ray.remote` 装饰器从 Python 函数定义到任务提交、调度、执行、返回结果的完整调用链。

#### 2.1.1 阶段一：Python 语法层 - 装饰器

```python
@PublicAPI
def remote(*args, **kwargs) -> Union[RemoteFunction, ActorClass]:
    # 当用 @ray.remote 装饰一个函数或类时
    # 如果是函数 → 创建 RemoteFunction 对象
    # 如果是类 → 创建 ActorClass 对象
```

#### 2.1.2 阶段二：任务提交 - 调用 `.remote()`

```
函数.remote(args)
    ↓
1. 检查 worker 连接状态
    ↓
2. 函数序列化与导出（第一次调用时）
    ├── 创建函数描述符
    ├── 序列化函数（cloudpickle）
    └── 导出函数到 GCS
    ↓
3. 调用 core_worker.submit_task（C++ 边界）
```

#### 2.1.3 阶段三：C++ 层任务提交

**关键文件**: `src/ray/core_worker/task_submission/normal_task_submitter.h`

```cpp
class NormalTaskSubmitter {
public:
    void SubmitTask(TaskSpecification task_spec);
private:
    DependencyResolver resolver_;                  // 依赖解析器
    TaskManagerInterface &task_manager_;           // 任务管理器
    std::shared_ptr<RayletClientInterface> local_raylet_client_;
};
```

**提交流程**:
```
SubmitTask(task_spec)
  ↓
1. 任务加入待提交队列
  ↓
2. DependencyResolver 解析对象依赖
  ↓
3. 等待依赖就绪
  ↓
4. 向 Raylet 请求 worker 租约（RequestLease RPC）
  ↓
5. 获得租约后，远程调用目标 worker 执行任务
```

#### 2.1.4 阶段四：调度层 - Raylet 调度

```
RequestLease RPC → Raylet
  ↓
1. ClusterResourceScheduler 检查资源可用性
  ↓
2. 找到可用节点后，检查是否有匹配的 worker 进程
  ↓
3. 若没有现成 worker：启动新的 Python 进程
  ↓
4. 返回租约（包含目标 worker 的地址）
```

#### 2.1.5 完整流程架构图

```
用户代码 Python 进程 (Driver)
┌─────────────────────────────────────────────────────────┐
│  @ray.remote                                            │
│      ↓ (装饰阶段)                                        │
│  RemoteFunction 实例                                     │
│      ↓ (调用 .remote())                                  │
│  _remote() 方法                                           │
│      ↓ (函数序列化 + export)                              │
│  worker.core_worker.submit_task()                        │
└────────────────────────┬────────────────────────────────┘
                         │ C++ 边界
┌────────────────────────▼────────────────────────────────┐
│  C++ CoreWorker (Driver)                                │
│      ↓ NormalTaskSubmitter::SubmitTask                  │
│  1. 依赖解析                                             │
│  2. 向 Raylet 请求租约 (RequestLease)                   │
└────────────────────────┬────────────────────────────────┘
                         │ gRPC
┌────────────────────────▼────────────────────────────────┐
│  Raylet (本地节点调度器)                                 │
│      ↓ ClusterResourceScheduler                         │
│  1. 资源匹配与节点选择                                    │
│  2. 启动/复用 Worker 进程                                 │
│  3. 返回租约（目标 Worker 地址）                          │
└────────────────────────┬────────────────────────────────┘
                         │ gRPC
┌────────────────────────▼────────────────────────────────┐
│  Worker 进程 (Python + C++)                             │
│  ┌─────────────────────────────────────────────────┐   │
│  │  C++ CoreWorker                                 │   │
│  │    ↓ TaskReceiver::HandleTasks                  │   │
│  │  1. 反序列化任务参数                              │   │
│  │  2. 调用 Python 执行器                            │   │
│  └──────────────────┬──────────────────────────────┘   │
│                     │ Python 边界                        │
│  ┌──────────────────▼──────────────────────────────┐   │
│  │  Python Worker                                   │   │
│  │    ↓ 反序列化函数和参数                            │   │
│  │    ↓ 执行用户函数                                  │   │
│  │    ↓ 序列化结果                                   │   │
│  └──────────────────┬──────────────────────────────┘   │
│                     │ 写入对象存储                        │
└────────────────────────▼────────────────────────────────┘
                         │
┌────────────────────────▼────────────────────────────────┐
│  Object Store (Plasma) - 共享内存对象存储               │
└─────────────────────────────────────────────────────────┘
```

---

### 2.2 Actor 创建完整流程

**概述**: Actor 是 Ray 的有状态计算抽象，创建流程涉及多个组件协同。

**调用链追踪**:

```
用户代码: @ray.remote class MyActor: pass
  ↓
1. Python 层: ActorClass 实例化 (python/ray/actor.py)
  ↓
2. 调用 .remote() 创建 Actor
  ↓
3. CoreWorker::CreateActor（C++ 边界）
  ↓
4. 向 GCS 发送 RegisterActorRequest → 见 [1.4.1 GCS Server]
  ↓
5. GcsActorManager 调度 Actor 到合适节点
  ├── 检查资源需求
  ├── 选择合适的 Raylet
  └── 记录 Actor 状态（PENDING → SCHEDULED）
  ↓
6. 目标 Raylet 创建 Worker 进程 → 见 [1.4.2 Raylet]
  ↓
7. Worker 进程中初始化 Actor
  ├── 反序列化 Actor 类
  ├── 执行 __init__ 方法
  └── 向 GCS 报告 Actor READY
  ↓
8. 返回 ActorHandle 给用户
```

**关键状态转换**:

```
PENDING (等待调度)
    ↓
SCHEDULED (已分配节点)
    ↓
CREATING (Worker 正在创建中)
    ↓
READY (可接收任务)
    ↓
DEAD (已死亡/退出)
```

---

## 3. 对象存储（Plasma）与外部存储集成

### 3.1 Plasma 对象存储基础架构

**关键文件**: `src/ray/object_manager/plasma/store.h`

Plasma 是 Ray 的**共享内存对象存储**，实现了高性能的跨进程数据共享：

```cpp
class PlasmaStore {
public:
    // 核心 API
    Status CreateObject(const ObjectID &object_id, int64_t data_size, int64_t metadata_size);
    Status SealObject(const ObjectID &object_id);    // 标记对象为只读
    Status DeleteObject(const ObjectID &object_id);
    
private:
    // 内存管理
    std::unique_ptr<Allocator> allocator_;           // 内存分配器
    std::unordered_map<ObjectID, PlasmaObject> objects_;
    
    // 客户端管理
    std::vector<std::unique_ptr<Client>> clients_;
    
    // 事件循环
    std::unique_ptr<epoll_event> events_;
};
```

#### 核心设计特点

| 特性 | 说明 |
|------|------|
| **共享内存** | 使用 `/dev/shm` 或 `mmap` 文件，跨进程零拷贝访问 |
| **不可变对象** | 对象一旦 Seal 就不可修改，确保安全并发 |
| **引用计数** | 每个对象被多少 Worker 引用，用于自动 Eviction |
| **内存映射** | 大对象通过 mmap 映射，避免物理内存复制 |

---

### 3.2 对象传输与本地/远程复制机制

**关键文件**: `src/ray/object_manager/object_manager.h`

ObjectManager 负责节点间对象的高效传输：

```cpp
class ObjectManager {
public:
    // Pull 流程 - 从远程节点获取对象
    uint64_t Pull(const std::vector<rpc::ObjectReference> &object_refs, ...);
    
    // Push 流程 - 将本地对象推送到远程节点
    void Push(const ObjectID &object_id, const NodeID &node_id);
    
private:
    PullManager pull_manager_;       // 拉取请求管理
    PushManager push_manager_;       // 推送请求管理
    ObjectBufferPool buffer_pool_;   // 对象缓冲池
    std::unique_ptr<ObjectStoreRunner> object_store_internal_;
};
```

#### 小对象 vs 大对象策略

```
┌─────────────────────────────────────────────────────────┐
│              对象传输策略选择                            │
├─────────────────────────────────────────────────────────┤
│                                                         │
│  小对象 (< chunk_size)                                 │
│    ├─ 直接序列化传输                                    │
│    └─ 完整复制到目标节点 Plasma                         │
│                                                         │
│  大对象 (> chunk_size)                                 │
│    ├─ 分 chunk 传输 (默认 1MB)                         │
│    ├─ 边接收边写入 Plasma                               │
│    └─ 接收完所有 chunk 后 Seal                         │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

**chunk 传输实现** (`object_manager.h:315-339`):
- 使用 `ChunkObjectReader` 分块读取对象
- 每个 chunk 独立发送 gRPC 请求
- 接收端使用 `ObjectBufferPool` 管理写入缓冲

---

### 3.3 对象溢出（Spilling）机制详解

**关键文件**: `python/ray/_private/external_storage.py`

当 Plasma 内存不足时，Ray 会将冷对象**溢出**到外部存储。

#### 溢出触发条件

| 触发条件 | 说明 |
|---------|------|
| **内存不足** | Plasma 使用率达到阈值（默认 90%） |
| **对象不可用** | 所有本地引用已释放 |
| **LRU 选择** | 选择最近最少使用的对象 |

#### 完整溢出/恢复流程

```
溢出流程 (Plasma → 外部存储):
──────────────────────────────────
1. Raylet 检测到 Plasma 内存压力
   ↓
2. ObjectManager 选择可溢出对象（仅 pinned by raylet）
   ↓
3. 调用 spill_objects() 回调 → Python 层
   ├── 获取对象从 Plasma（零拷贝）
   ├── 序列化到外部存储文件
   └── 记录 URL 到 GCS
   ↓
4. 删除 Plasma 中的对象，释放内存

恢复流程 (外部存储 → Plasma):
──────────────────────────────────
1. Worker 访问被溢出的对象
   ↓
2. CoreWorker 检测对象不在 Plasma
   ↓
3. 向 GCS 查询 spilled URL
   ↓
4. 调用 restore_spilled_objects()
   ├── 从外部存储读取
   ├── 写回 Plasma 共享内存
   └── 继续任务执行
```

---

### 3.4 ExternalStorage 抽象与实现

**关键文件**: `python/ray/_private/external_storage.py:72`

```python
class ExternalStorage(metaclass=abc.ABCMeta):
    """外部存储抽象基类"""
    
    @abc.abstractmethod
    def spill_objects(self, object_refs, owner_addresses) -> List[str]:
        """将对象溢出到外部存储，返回 URL 列表"""
        
    @abc.abstractmethod
    def restore_spilled_objects(self, object_refs, url_list) -> int:
        """从外部存储恢复对象"""
        
    @abc.abstractmethod
    def delete_spilled_objects(self, urls: List[str]):
        """删除已溢出的对象"""
```

#### 内置实现

| 实现类 | 后端 | 特点 |
|--------|------|------|
| `FileSystemStorage` | 本地磁盘 | 默认实现，多目录轮询，最高性能 |
| `ExternalStorageSmartOpenImpl` | S3/GCS/... | 使用 `smart_open` 库，支持云端存储 |
| `NullStorage` | 无 | 禁用溢出（开发/测试） |

#### FileSystemStorage 实现细节

```python
# 多目录轮询 - 支持挂载多个磁盘
self._directory_paths = ["/disk1/ray_spill", "/disk2/ray_spill"]
self._current_directory_index = 0  # Round-Robin 选择

# 对象融合优化 - 多个小对象写入同一文件
def _write_multiple_objects(self, f, object_refs, ...):
    """将多个对象融合到一个文件，减少小文件开销"""
    # Header 格式: [data_size][metadata_size][owner_len][data...]
```

---

### 3.5 外部数据源集成：Ray Data Datasource

**关键文件**: `python/ray/data/_internal/datasource/sql_datasource.py`

对于**计算对象就是分布式存储数据**的场景（Hadoop、数据库、数据湖），Ray Data 提供了 Datasource 抽象，实现零拷贝读取。

#### SQLDatasource 并行读取架构

```python
class SQLDatasource(Datasource):
    """支持分片并行读取的 DB API2 数据源"""
    
    def supports_sharding(self, parallelism: int) -> bool:
        """检测数据库是否支持 MOD/ABS/CONCAT 分片操作"""
        
    def get_read_tasks(self, parallelism: int) -> List[ReadTask]:
        """将 SQL 查询拆分为多个并行 ReadTask"""
```

#### 分片并行读取流程

```
┌─────────────────────────────────────────────────────────────┐
│                    SQL 数据库                                 │
│  ┌──────┐  ┌──────┐  ┌──────┐  ┌──────┐                    │
│  │Shard0│  │Shard1│  │Shard2│  │Shard3│  ← MOD(哈希(shard_key))│
│  └───┬──┘  └───┬──┘  └───┬──┘  └───┬──┘                    │
└──────┼──────────┼──────────┼──────────┼──────────────────────┘
       │          │          │          │
       ▼          ▼          ▼          ▼
    ReadTask   ReadTask   ReadTask   ReadTask
    (Worker 0)  (Worker 1)  (Worker 2)  (Worker 3)
       │          │          │          │
       └──────────┴─────┬────┴──────────┘
                         │
                         ▼
                    Ray Dataset
                    (Blocks in Plasma)
```

**分片 SQL 生成**:
```sql
SELECT * FROM (
    {用户原始 SQL}
) as T 
WHERE MOD(ABS(MD5(shard_key)), {parallelism}) = {task_id}
```

---

### 3.6 绕过对象复制的三种策略

用户问题：**能否避免在 Ray 中进行高代价的对象复制？**

答案：**可以，Ray 提供了三层策略**：

| 策略层级 | 方案 | 适用场景 | 性能 |
|---------|------|---------|------|
| **存储层** | **零拷贝共享内存** | 单机多进程 | 🟢 最高 |
| **溢出层** | **远端直接读取** | 对象在其他节点 | 🟡 中 |
| **数据源层** | **Datasource 并行读取** | 外部系统（Hadoop/DB） | 🔵 原生 |

#### 策略一：Plasma 零拷贝（单机）

**工作原理**:
- 对象存储在 `/dev/shm` 共享内存
- Worker 进程通过 mmap 直接映射，**无物理内存复制**
- 小对象通过 Value Semantics 复制，大对象始终共享内存

**关键优化点**:
```cpp
// CoreWorker::Get() - 检测是否为本地 Plasma 对象
if (object.IsPlasmaBuffer()) {
    // 直接返回共享内存指针，零拷贝
    return buffer;
}
```

#### 策略二：分布式对象直接读取

**避免全量 Pull**:
```
传统方式 (Pull 全量):
    Worker A → 对象传输 → Worker B
    (高网络开销)

优化方式 (本地引用):
    Worker B → 检测对象在 Worker A
    Worker B → 向 Worker A 远程执行计算
    (仅传输任务，不传输数据)
```

**Ray 调度亲和性**:
- `ray.get()` 时，调度器会优先将任务调度到**对象所在节点**
- 减少网络传输，计算移动而不是数据移动

#### 策略三：外部数据源原生集成

**推荐架构**（针对 Hadoop/数据库场景）：

```
┌───────────────────────────────────────────────────────────────┐
│                    外部存储系统 (HDFS/S3/DB)                   │
│  ┌────────┐  ┌────────┐  ┌────────┐  ┌────────┐              │
│  │ Block 0│  │ Block 1│  │ Block 2│  │ Block N│  数据分片     │
│  └───┬────┘  └───┬────┘  └───┬────┘  └───┬────┘              │
└──────┼───────────┼───────────┼───────────┼───────────────────┘
       │           │           │           │
       └───────────┼───────────┼───────────┘
                   │
       ┌───────────▼───────────┐
       │   Ray Data Datasource │  ← 自定义 Datasource
       └───────────┬───────────┘
                   │
       ┌───────────▼───────────┐
       │  并行 ReadTasks       │  ← 每个 Task 只读取所属分片
       └───────────┬───────────┘
                   │
       ┌───────────▼───────────┐
       │  计算 Task (map_batches) │ ← 计算在数据所在节点执行
       └───────────────────────┘
```

**关键实现**:
1. **自定义 Datasource**：继承 `Datasource` 类，实现分片逻辑
2. **计算亲和性**：通过 `NodeAffinityScheduleStrategy` 调度
3. **零序列化**：直接在 Reader 中进行 Arrow 格式转换

---

### 3.7 自定义外部存储开发指南

如需接入自定义外部存储（如 HDFS、Redis、自定义缓存等），可实现 `ExternalStorage` 接口：

```python
class MyCustomStorage(ExternalStorage):
    def spill_objects(self, object_refs, owner_addresses) -> List[str]:
        """实现自定义溢出逻辑"""
        pass
        
    def restore_spilled_objects(self, object_refs, url_list) -> int:
        """实现自定义恢复逻辑"""
        pass
```

典型场景：
- **内存数据库溢出**：Redis、Memcached
- **分布式文件系统**：HDFS、MinIO
- **对象存储服务**：阿里云 OSS、腾讯云 COS、AWS S3

---

## 4. 核心架构洞察

---

### 4.1 Python 进程与 C++ 进程的交互边界

Ray 的核心设计哲学是：**Python 作为控制面，C++ 作为数据面**。

#### 4.1.1 通信机制分层

```
用户 Python 进程 (Driver/Worker)
    │
    ├─► [Cython 边界层] _raylet.pyx
    │       │
    │       ▼
    │   GcsClient / CoreWorkerClient (C++ 对象)
    │       │
    │       ▼
    │   gRPC 调用 (TCP 端口)
    │       │
    │       ▼
    └──► C++ 服务进程
            ├─ GCS Server (6379 端口)
            ├─ Raylet (node_manager_port)
            └─ Object Manager (object_manager_port)
```

**关键设计：所有跨进程通信都通过 gRPC**
- Python 从不直接访问 C++ 内部内存
- 所有交互都是明确的 RPC 调用
- 这也是 Ray 能无缝支持多语言（Java、C++）的根本原因

---

### 4.2 GCS Server 的资源管理与控制边界

#### 4.2.1 完全独立的进程生命周期

| 特性 | 说明 |
|------|------|
| **独立性** | 独立 OS 进程，PID 与 Driver 不同 |
| **内存** | 独立地址空间，自己管理堆内存 |
| **线程** | 内部有 gRPC 线程池、IO 事件循环、后台定时任务 |
| **日志** | 独立写入 `gcs_server.out` |
| **退出** | 可独立崩溃/重启，不影响正在运行的任务 |

#### 4.2.2 Python 对 GCS 的控制权限矩阵

| 操作 | Python 能控制 | 实现方式 |
|------|--------------|---------|
| 启动/停止 | ✅ 完全控制 | `subprocess.Popen()` + `kill()` |
| 发送 RPC 请求 | ✅ 完全控制 | 通过 `GcsClient` 包装 |
| 直接访问内部内存 | ❌ 不能 | 进程地址空间隔离 |
| 中断内部线程 | ❌ 不能 | 只能通过 RPC 优雅关闭 |
| 热更新配置 | ❌ 不能 | 必须重启进程 |

---

### 4.3 `ray.remote` 任务传递的本质

#### 4.3.1 传递的不是指针，而是"完整的计算描述"

这是 Ray 最核心的设计洞察：

```
用户以为在"传递函数调用"：
    my_func.remote(1, 2)

实际在"传递序列化的计算描述"：
┌──────────────────────────────────────────┐
│  TaskSpecification (序列化消息)          │
├──────────────────────────────────────────┤
│ 1. 函数描述 (cloudpickle 序列化)         │
│    ├─ 函数字节码                         │
│    ├─ 闭包变量                           │
│    └─ 装饰器信息                         │
│                                          │
│ 2. 参数                                 │
│    ├─ 小对象：直接内联序列化             │
│    └─ 大对象：ObjectID 引用 (20字节)     │
│                                          │
│ 3. 资源需求                             │
│    ├─ num_cpus, num_gpus                │
│    └─ 自定义资源 (GPU_MEM, etc)          │
│                                          │
│ 4. 调度元数据                           │
│    ├─ 任务依赖关系 (ObjectID 列表)       │
│    ├─ 调度策略 (SPREAD / PACK)           │
│    └─ 超时 / 重试配置                    │
└──────────────────────────────────────────┘
```

#### 4.3.2 为什么必须序列化，不能传递指针？

分布式系统的本质约束：
- **跨机器**：进程地址空间完全独立，指针毫无意义
- **容错**：Worker 崩溃后，可以在其他节点重放函数定义
- **多语言**：Python 函数可以被 Java Worker 执行（序列化格式中立）

---

### 4.4 Worker 节点 Raylet 任务执行全链路

从 Driver 提交任务到 Worker 执行的完整旅程：

```
[Driver Python]
    │
    ├─► 1. @ray.remote 装饰函数
    │
    ├─► 2. 调用 .remote() 提交任务
    │
    ▼
[CoreWorker C++]
    │
    ├─► 3. NormalTaskSubmitter::SubmitTask
    │     ├─ DependencyResolver 解析依赖
    │     └─ 等待对象就绪
    │
    ├─► 4. 向本地 Raylet 请求 Worker 租约 (RequestLease RPC)
    │
    ▼
[Raylet 调度器]
    │
    ├─► 5. ClusterResourceScheduler 节点选择
    │     ├─ 资源匹配检查
    │     ├─ 亲和性调度
    │     └─ 选择目标 Worker
    │
    ├─► 6. 若没有空闲 Worker，启动新 Python 进程
    │
    ▼
[Worker 进程启动]
    │
    ├─► 7. 初始化 C++ CoreWorker
    │
    ├─► 8. TaskReceiver 接收任务 gRPC
    │
    ▼
[Python 执行层]
    │
    ├─► 9. cloudpickle.loads() 反序列化函数定义
    │
    ├─► 10. 从 Plasma 获取参数对象（零拷贝）
    │
    ├─► 11. 执行用户函数体
    │
    └─► 12. 结果写入 Plasma，返回 ObjectID
```

---

### 4.5 五大核心进程的控制关系图谱

```
┌─────────────────────────────────────────────────────────────┐
│              用户 Python 进程 (Driver)                        │
│  - 用户代码                                                   │
│  - ray.init() / ray.shutdown()                                │
│  - @ray.remote 装饰器                                         │
│  - ObjectRef 引用计数                                         │
└────────────┬──────────────────────────────────────────────────┘
             │
             │ 父进程 → 启动和控制
             │
    ┌────────┴────────┬──────────────────────────────────┐
    │                 │                                  │
    ▼                 ▼                                  ▼
[GCS Server]     [Raylet 进程]                     [API Server]
  (C++)            (C++)                              (Python)
  全局元数据        本地调度器                          Dashboard
                    │
                    │ 启动和管理
                    │
          ┌─────────┴─────────┐
          │                   │
          ▼                   ▼
    [Worker 进程]       [Dashboard Agent]
      (Python)            (Python)
      执行任务             指标收集
```

---

### 4.6 深入理解核心的五个方向

掌握前面的流程分析后，可以朝这五个方向继续深入：

| 方向 | 核心问题 | 关键入口文件 |
|------|---------|-------------|
| **对象存储 Plasma** | 零拷贝如何实现？引用计数如何工作？ | `src/ray/object_manager/plasma/store.h` |
| **调度器算法** | 任务怎么分配到 Worker？死锁检测？ | `src/ray/raylet/scheduling/cluster_task_manager.cc` |
| **Actor 生命周期** | Actor 故障恢复、Direct Call 优化 | `src/ray/core_worker/actor_handle.h` |
| **CoreWorker 事件循环** | 单线程如何处理数千并发任务？ | `src/ray/core_worker/core_worker.h` |
| **分布式 GC** | 对象何时被真正删除？ | `src/ray/core_worker/reference_count.h` |

---

### 4.7 验证理解的三道测试题

能清晰回答这三个问题，说明你真正理解了 Ray 核心：

#### 问题 1：为什么 `ray.get(x)` 几乎不会阻塞 GIL？

<details>
<summary>点击查看答案</summary>

**答案**：
`ray.get()` 的等待逻辑在 C++ 层的 `CoreWorker::Get()` 中实现，使用 Boost.Asio 的异步事件循环。
- Python 线程只是在等待一个条件变量（不持有 GIL）
- 对象就绪时通过回调唤醒 Python 线程
- 整个等待过程 GIL 是释放的，其他 Python 线程可正常运行

</details>

#### 问题 2：为什么 Actor 方法调用比普通任务快 2-3 倍？

<details>
<summary>点击查看答案</summary>

**答案**：
普通任务走完整调度链路：`Driver → GCS → Raylet → Worker`

而 **Direct Actor Call** 跳过了中间层：
- Actor 创建后，Driver 直接持有 Worker 的 gRPC 地址
- 后续方法调用：`Driver → Worker` 直接通信
- 跳过了 GCS 查询、Raylet 调度、租约申请等步骤
- 这就是 Ray Actor 高性能的核心原因

</details>

#### 问题 3：Worker 进程 OOM 被 Kill 后，正在执行的任务状态去哪了？

<details>
<summary>点击查看答案</summary>

**答案**：
任务状态存储在 **两处**：
1. **Driver 侧 CoreWorker**：持有任务的引用和状态
2. **GCS TaskManager**：全局任务状态表

当 Worker OOM 被 Kill：
- Raylet 检测到 Worker 死亡，向 GCS 报告
- GCS 将任务状态标记为 `FAILED` / `RETRYING`
- Driver 的 `wait` 回调被触发
- 如果配置了重试，任务会被重新调度到其他 Worker
- 整个过程对用户透明（除了日志警告）

</details>

---

## 5. 资源管理与调度器

---

### 5.1 核心设计原则：静态声明 + 动态借贷

| 维度 | 设计 | 说明 |
|------|------|------|
| **节点资源总量** | ✅ **静态** | `ray start` 时通过 `--num-cpus`、`--num-gpus`、`--memory` 声明，启动后不可变 |
| **任务资源分配** | ✅ **动态借贷** | 任务开始时「借」资源，完成时「还」资源 |
| **物理隔离** | ⚠️ **软限制** | Ray 只是记账，不做真正的物理隔离（除 cgroup 模式外） |

---

### 5.2 资源账本数据结构

**关键文件**: `src/ray/common/scheduling/resource_set.h:80`

核心判断算子：
```cpp
/// Check whether this set is a subset of another one.
/// If A <= B, it means for each resource, 
/// its value in A is less than or equal to that in B.
bool operator<=(const ResourceSet &other) const;
```

**节点资源初始化**: `src/ray/raylet/scheduling/local_resource_manager.cc:32-53`

```cpp
LocalResourceManager::LocalResourceManager(
    scheduling::NodeID local_node_id,
    const NodeResources &node_resources,  // 传入的资源配置
    ...) {
  // 关键断言：初始时刻总容量 = 可用容量
  RAY_CHECK(node_resources.total == node_resources.available);
  
  // 一次性赋值到成员变量，此后不再从外部读取
  local_resources_.available = NodeResourceInstanceSet(node_resources.total);
  local_resources_.total = NodeResourceInstanceSet(node_resources.total);
}
```

**设计局限证据**:
- `local_resources_.total` 只在构造时设一次
- 整个类中没有 `UpdateTotalResources()` 方法
- 只有借（Allocate）和还（Free）操作，没有修改总量的操作

---

### 5.3 调度可行性判断：IsSchedulable

**关键文件**: `src/ray/raylet/scheduling/cluster_resource_scheduler.cc:113-123`

```cpp
bool ClusterResourceScheduler::IsSchedulable(
    const ResourceRequest &resource_request,
    scheduling::NodeID node_id) const {
  // 核心判断：任务需求 <= 节点可用资源
  return cluster_resource_manager_->HasAvailableResources(
             node_id,
             resource_request,
             /*ignore_object_store_memory_requirement*/ ...) &&
         NodeAvailable(node_id);
}
```

---

### 5.4 INFEASIBLE 任务的生命周期

**典型场景**：任务 `num_cpus=16`，但所有节点最大只有 8 核

```
1. 任务提交到 GCS
   ↓
2. GetBestSchedulableNode() 遍历所有节点
   ├─ Node A: 16 CPUs <= 可用 CPUs？❌ 不满足
   └─ Node B: 16 CPUs <= 可用 CPUs？❌ 不满足
   ↓
3. best_node_id = Nil()  ← 没有找到合适节点
   ↓
4. *is_infeasible = true  ← 标记为"不可行"
   ↓
5. 任务在 GCS 中无限等待排队
```

**用户可见的表现**：
- `ray.get()` 永远不会返回
- Dashboard 显示红色的 "Infeasible" 标记
- 日志每 5 秒打印 `There are N pending tasks with infeasible ...`
- **不会抛出异常！**

**恢复机制**：后续加入更大容量的节点时，任务会自动调度。

---

### 5.5 三种资源类型的语义差异

| 资源类型 | 单位 | 调度语义 | 是否超售 | 物理隔离 |
|---------|------|---------|---------|---------|
| **CPU** | 核数 | 逻辑并发槽位 | ✅ 可以超售（配置 `num_cpus` > 实际核数） | ❌ 无隔离 |
| **GPU** | 卡数 | 物理卡映射 | ❌ 不建议超售 | ❌ 无隔离 |
| **memory** | 字节 | 内存保留量 | ❌ 超售导致 OOM | ❌ 软限制 |
| **object_store_memory** | 字节 | Plasma 共享内存 | ❌ 硬限制 | ✅ 隔离 |

---

### 5.6 memory 参数的双重含义

#### 层 1：调度约束（总是生效）
```python
@ray.remote(memory=8 * 1024**3)  # 需要 8GB 内存
def task():
    pass
```
- Raylet 会检查节点的**可用内存账本**是否足够
- 足够才会调度到该节点

#### 层 2：Worker 内存预留（需特殊配置）
如果启用 **cgroup 资源隔离**：
```bash
ray start --head --enable-resource-isolation \
          --system-reserved-cpu=2 \
          --system-reserved-memory=32000000000
```
- Ray 会创建 cgroup 限制 Worker 的实际内存使用
- 这是真正的硬隔离

---

### 5.7 异构集群的运维痛点与解决方案

#### ❌ 痛点 1：容器化场景的资源漂移
```yaml
# Kubernetes Pod 资源限制可以动态调整
resources:
  limits:
    cpu: "16"
    memory: "64Gi"
```
**问题**：K8s limit 变化时，Raylet 不会自动刷新，账本与实际长期不一致

#### ❌ 痛点 2：混部场景的动态腾挪
- 白天：在线服务占用 80%，Ray 只能用 20%
- 半夜：在线缩容，Ray 可以用 80%
- Ray 当前不支持按时间窗口动态调整声明值

#### ✅ 解决方案 A：Sidecar 自动校准模式
每台机器运行一个小守护进程：
```python
# sidecar.py - 每个节点每分钟运行
while True:
    actual_cpus = psutil.cpu_count()
    actual_memory = psutil.virtual_memory().available
    
    ray_resources = ray.nodes()[0]["Resources"]
    declared_cpus = ray_resources.get("CPU", 0)
    
    # 偏差超过阈值时自动更新
    if abs(actual_cpus - declared_cpus) > 0.1:
        ray.autoscaler.sdk.request_resources(num_cpus=actual_cpus)
        logger.info(f"Updated CPU from {declared_cpus} to {actual_cpus}")
    
    time.sleep(60)
```

#### ✅ 解决方案 B：标签驱动调度（适合 GPU 异构）
不要依赖标准资源字段，用自定义标签表达异构性：
```bash
# 不要这么做（维护成本高）
ray start --num-cpus=32 --num-gpus=8

# 应该这么做（标签驱动）
ray start --resources={"zone": "us-west-1", "gpu_model": "A100", "ram_64g": 1}
```

调度时：
```python
@ray.remote(resources={"gpu_model:A100": 0.001})  # 软亲和
def run_on_a100():
    pass
```

---

### 5.8 自动资源检测机制

Ray 支持自动检测，不需要每个节点手动配置：

**CPU 自动检测**（std::thread::hardware_concurrency）
**内存自动检测**（取可用内存的 80% 作为保守值）
**GPU 自动检测**（通过 NVML 调用，自动识别型号并打标签）

```bash
# 最简启动，所有资源自动检测
ray start --head
```

---

### 5.9 常见陷阱与最佳实践

| 陷阱 | 现象 | 规避方法 |
|------|------|---------|
| **任务 > 单机最大容量** | 任务永远 Infeasible 卡住 | 使用 Placement Group 或拆分成更小任务 |
| **内存"账用完了"但系统还有空闲** | 任务排队但机器很空 | memory 参数设为实际峰值的 1.2-1.5 倍，监控实际内存而非只看 Ray 账本 |
| **超线程导致超售** | 任务都很慢但 CPU 显示只用了 50% | 手动 `--num-cpus=物理核心数`，不要相信逻辑核数 |

---

### 5.10 核心设计洞察

> Ray 的资源管理是"**基于承诺的调度**"——节点承诺自己有多少资源，任务声明自己需要多少，调度器检查承诺是否可兑现。
>
> 它是**软约束不是硬隔离**，理解这点可以避免 80% 的 Ray 使用困惑。

---

## 附录：关键文件索引

### Python 层

| 文件 | 作用 | 章节引用 |
|------|------|---------|
| `python/ray/scripts/scripts.py` | CLI 入口，ray start 命令 | [1.1 入口层](#11-入口层scriptspy) |
| `python/ray/_private/node.py` | Node 类，进程编排器 | [1.2 进程编排层](#12-进程编排层nodepy) |
| `python/ray/_private/services.py` | C++ 进程启动包装 | [1.3 进程启动层](#13-进程启动层servicespy) |
| `python/ray/remote_function.py` | RemoteFunction 类 | [2.1 @ray.remote 完整流程](#21-rayremote-完整流程) |
| `python/ray/_private/external_storage.py` | 对象溢出外部存储 | [3.4 ExternalStorage 抽象与实现](#34-externalstorage-抽象与实现) |
| `python/ray/data/_internal/datasource/sql_datasource.py` | SQL 数据源并行读取 | [3.5 外部数据源集成](#35-外部数据源集成ray-data-datasource) |

### C++ 层

| 文件 | 作用 | 章节引用 |
|------|------|---------|
| `src/ray/gcs/gcs_server.h` | GCS Server 核心类 | [1.4.1 GCS Server 架构](#141-gcs-server-架构) |
| `src/ray/raylet/raylet.h` | Raylet 核心类 | [1.4.2 Raylet 内部架构](#142-raylet-内部架构) |
| `src/ray/raylet/node_manager.h` | 节点管理器 | [1.4.2 Raylet 内部架构](#142-raylet-内部架构) |
| `src/ray/core_worker/core_worker.h` | CoreWorker 核心类 | [2.1 @ray.remote 完整流程](#21-rayremote-完整流程) |
| `src/ray/object_manager/object_manager.h` | 对象传输管理器 | [3.2 对象传输与本地远程复制机制](#32-对象传输与本地远程复制机制) |
| `src/ray/object_manager/plasma/store.h` | Plasma 共享内存存储 | [3.1 Plasma 对象存储基础架构](#31-plasma-对象存储基础架构) |

---

*文档生成时间: 2024-04-25*
*重构时间: 2024-04-25 - 按调用链组织并建立交叉引用*
*新增章节时间: 2024-04-27 - 新增对象存储与外部存储集成*
*结构整理时间: 2024-04-27 - 统一数字编号，使用 [toc] 自动目录*
*新增核心洞察: 2024-04-28 - 新增第4章"核心架构洞察"，含进程边界、任务本质、控制关系图谱*
