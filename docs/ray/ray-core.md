# Ray Core 核心流程分析

本文档聚合 Ray 核心流程，按主题分类记录。

---

## 目录

[toc]

---

## ray start 完整执行流程

### 概述

`ray start` 命令支持 **Head 节点** 和 **Worker 节点** 两种模式，共用同一个 `start()` 函数（约 500 行代码），通过 `--head` 参数分支执行不同逻辑。

---

## 核心文件：python/ray/scripts/scripts.py

**位置**: 第 679-1180 行

这是 `ray start` 的入口文件，负责 CLI 参数解析、流程分支逻辑、Node 实例化、用户交互输出。

### 一、CLI 参数设计

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

### 二、执行流程总览

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

### 三、通用阶段详解

#### 1. 参数解析与验证

**关键技术点**:

```python
# 双重标签解析：字符串 + YAML 文件
labels_from_file = parse_node_labels_from_yaml_file(labels_file)
labels_from_string = parse_node_labels_string(labels)  # 新格式: key1=val1,key2=val2
labels_dict = {**labels_from_file, **labels_from_string}  # 字符串优先级更高

# 资源隔离配置
resource_isolation_config = ResourceIsolationConfig(
    enable_resource_isolation=enable_resource_isolation,
    cgroup_path=cgroup_path,
    system_reserved_cpu=system_reserved_cpu,
    system_reserved_memory=system_reserved_memory,
)
```

#### 2. RayParams 对象构建

**关联文件**: `python/ray/_private/parameter.py`

RayParams 是**所有配置的唯一容器**，包含：
- 30+ 个基础配置字段
- 资源隔离配置
- Dashboard 相关配置
- 系统级配置（`_system_config`）

#### 3. 扩展点：RAY_START_HOOK

```python
if ray_constants.RAY_START_HOOK in os.environ:
    load_class(os.environ[ray_constants.RAY_START_HOOK])(ray_params, head)
```

允许在真正启动前注入自定义逻辑（测试、监控、审计等）。

### 四、Head 节点流程 (`--head`)

```
ray start --head --port=6379
    ↓
1. 设置 GCS 端口（默认 6379）
    ↓
2. ✅ 冲突检测：防止端口被占用
    │  - 检查默认地址是否已在运行
    │  - 已运行则抛出 ConnectionError
    ↓
3. 创建 Node 实例 (head=True)
    ↓
4. 打印 Dashboard 地址和使用说明
    ↓
5. 写入 gcs_address 到临时文件
    ↓
6. --block 模式：进入监控循环
```

**关键设计：冲突检测**

```python
# 在启动前检查是否已有 Ray 集群在运行
default_address = build_address(ray_params.node_ip_address, port)
bootstrap_address = services.find_bootstrap_address(temp_dir)
if default_address == bootstrap_address:
    raise ConnectionError("Ray is already running...")
```

### 五、Worker 节点流程

```
ray start --address=head-node:6379
    ↓
1. ✅ 必须指定 --address，否则直接 abort
    ↓
2. ✅ Head-only 参数检查
    │  禁止 Worker 指定：
    │  --port, --redis-shard-ports, --include-dashboard
    ↓
3. 规范化 GCS 地址
    ↓
4. 获取本机 IP 地址（需要连接到 GCS 后自动探测）
    ↓
5. 创建 Node 实例 (head=False)
    ↓
6. 版本检查：确保 Worker 与 Head 版本一致
    ↓
7. 写入 gcs_address 到临时文件
    ↓
8. --block 模式：进入监控循环
```

**关键设计：Worker 自动 IP 探测**

```python
# Worker 需要连接到 GCS 后才能确定自己应该用哪个网卡
ray_params.update_if_absent(
    node_ip_address=services.get_node_ip_address(bootstrap_address)
)
```

### 六、--block 模式详解

当指定 `--block` 时，进程**不会退出**，而是进入无限循环：

```python
while True:
    time.sleep(1)
    deceased = node.dead_processes()
    
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

## 核心文件：python/ray/_private/node.py

Node 类是**进程编排器**，负责所有子进程的生命周期管理。

### 一、类职责

| 职责 | 说明 |
|------|------|
| **进程启动** | Head 专属服务、Raylet、Agent 等 |
| **进程监控** | 检测子进程异常退出 |
| **配置同步** | Worker 从 GCS 拉取系统配置 |
| **生命周期** | 集群启动、关闭、清理 |

### 二、关键方法矩阵

| 方法 | Head | Worker | 作用 |
|------|------|--------|------|
| `__init__()` | ✅ | ✅ | 初始化，调用下面两个方法 |
| `start_head_processes()` | ✅ | ❌ | GCS、Monitor、API Server |
| `start_ray_processes()` | ✅ | ✅ | Raylet、Agent、Log Monitor |
| `dead_processes()` | ✅ | ✅ | 获取已死亡的子进程 |
| `kill_all_processes()` | ✅ | ✅ | 杀死所有子进程 |
| `check_version_info()` | ❌ | ✅ | Worker 版本校验 |

### 三、start_head_processes() 详解

**位置**: 第 1344 行

```python
def start_head_processes(self):
    self.start_gcs_server()              # 核心！启动 GCS
    self._write_cluster_info_to_kv()     # 写入元数据
    
    if not self._ray_params.no_monitor:
        self.start_monitor()             # 自动扩缩容监控
    
    if self._ray_params.ray_client_server_port:
        self.start_ray_client_server()   # 客户端连接服务
    
    self.start_api_server()              # Dashboard + REST API
```

**启动顺序原则**:
1. **GCS Server 必须第一个启动**，其他所有服务都依赖 GCS 进行通信和状态存储
2. 启动顺序严格按照依赖关系排列

---

### 四、Node.start_gcs_server() 方法详解

**位置**: 第 1113 行

这是 Head 节点启动 GCS Server 的包装方法：

```python
def start_gcs_server(self):
    # 前置断言：确保只启动一次
    gcs_server_port = self._ray_params.gcs_server_port
    assert gcs_server_port > 0
    assert self._gcs_address is None, "GCS server is already running."
    assert self._gcs_client is None, "GCS client is already connected."

    # 1. 日志文件命名（唯一化）
    stdout_log_fname, stderr_log_fname = self.get_log_file_names(
        "gcs_server", unique=True, create_out=True, create_err=True
    )
    
    # 2. 调用 services.start_gcs_server() 启动 C++ 进程
    process_info = ray._private.services.start_gcs_server(
        self.redis_address,
        log_dir=self._logs_dir,
        stdout_filepath=stdout_log_fname,
        stderr_filepath=stderr_log_fname,
        session_name=self.session_name,
        redis_username=self._ray_params.redis_username,
        redis_password=self._ray_params.redis_password,
        config=self._config,
        fate_share=self.kernel_fate_share,
        gcs_server_port=gcs_server_port,
        metrics_agent_port=self._ray_params.metrics_agent_port,
        node_ip_address=self._node_ip_address,
    )
    
    # 3. 注册进程到 all_processes 字典（用于监控和清理）
    assert ray_constants.PROCESS_TYPE_GCS_SERVER not in self.all_processes
    self.all_processes[ray_constants.PROCESS_TYPE_GCS_SERVER] = [
        process_info,
    ]
    
    # 4. 保存 GCS 地址供其他组件使用
    self._gcs_address = build_address(self._node_ip_address, gcs_server_port)
```

**关键设计要点**:

| 设计点 | 说明 |
|--------|------|
| **前置断言** | 防止重复启动 GCS，确保单例 |
| **日志唯一化** | `unique=True` 确保每次启动生成不同的日志文件，不覆盖历史 |
| **Fate Share 机制** | `kernel_fate_share` 确保父进程退出时 GCS 自动清理 |
| **进程注册** | 所有进程注册到 `all_processes` 字典，统一监控和生命周期管理 |

---

### 五、start_ray_processes() 详解

**位置**: 第 1373 行

Head 和 Worker 节点都需要执行此方法：

```python
def start_ray_processes(self):
    # [Worker 节点专属] 先从 GCS 拉取系统配置
    if not self.head:
        gcs_options = ray._raylet.GcsClientOptions.create(...)
        global_state = ray._private.state.GlobalState()
        global_state._initialize_global_state(gcs_options)
        new_config = global_state.get_system_config()
        
        # 配置一致性校验：本地配置必须是 GCS 配置的子集
        assert self._config.items() <= new_config.items(), (
            "The system config from GCS is not a superset of the local"
            " system config. There might be a configuration inconsistency"
        )
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
    
    # 5. 启动 Raylet（核心！本地调度器和对象存储）
    self.start_raylet(plasma_directory, fallback_directory, object_store_memory)
```

**关键设计：Worker 配置同步机制**

Worker 节点必须从 GCS 拉取系统配置，确保整个集群配置一致：
- 使用 `GlobalState` 客户端连接 GCS
- 拉取后进行子集校验，确保本地配置没有冲突
- 冲突时直接抛出异常，防止启动不一致的节点

---

### 六、Node.start_raylet() 方法详解

**位置**: 第 1147 行

这是 Node 类中参数最多的方法之一，负责启动 Raylet 进程：

```python
def start_raylet(
    self,
    plasma_directory: str,
    fallback_directory: str,
    object_store_memory: int,
    use_valgrind: bool = False,
    use_profiler: bool = False,
):
```

**方法内部分为 4 个阶段**：

#### 阶段 1：日志文件准备

为 Raylet 及其内部的 Agent 进程分别准备日志文件：

```python
# Raylet 主进程日志
raylet_stdout_filepath, raylet_stderr_filepath = self.get_log_file_names(
    PROCESS_TYPE_RAYLET, unique=True, create_out=True, create_err=True
)

# Dashboard Agent 日志
dashboard_agent_stdout_filepath, dashboard_agent_stderr_filepath = \
    self.get_log_file_names(PROCESS_TYPE_DASHBOARD_AGENT, ...)

# Runtime Env Agent 日志
runtime_env_agent_stdout_filepath, runtime_env_agent_stderr_filepath = \
    self.get_log_file_names(PROCESS_TYPE_RUNTIME_ENV_AGENT, ...)
```

#### 阶段 2：资源隔离配置

```python
# 收集系统进程 PID，用于 Cgroup 资源隔离
self.resource_isolation_config.add_system_pids(
    self._get_system_processes_for_resource_isolation()
)
```

#### 阶段 3：调用 services.start_raylet() 启动 C++ 进程

**传递 30+ 个参数**，完整参数列表：

```python
process_info = ray._private.services.start_raylet(
    # 地址与标识
    self.redis_address,                # Redis 地址（可选外部 Redis）
    self.gcs_address,                  # GCS 服务地址
    self._node_id,                     # 本节点唯一 ID
    self._node_ip_address,             # 本节点 IP
    
    # Socket 通信
    self._ray_params.node_manager_port,
    self._raylet_socket_name,          # Raylet 本地 socket
    self._plasma_store_socket_name,    # Plasma 存储 socket
    
    # 路径配置
    self.cluster_id.hex(),
    self._ray_params.worker_path,
    self._ray_params.setup_worker_path,
    self._temp_dir,
    self._session_dir,
    self._runtime_env_dir,
    self._logs_dir,
    
    # 资源与存储
    self.get_resource_and_label_spec(),
    plasma_directory,
    fallback_directory,
    object_store_memory,
    
    # 会话与角色
    self.session_name,
    is_head_node=self.is_head(),
    
    # 端口范围
    min_worker_port=self._ray_params.min_worker_port,
    max_worker_port=self._ray_params.max_worker_port,
    worker_port_list=self._ray_params.worker_port_list,
    object_manager_port=self._ray_params.object_manager_port,
    
    # Agent 端口
    metrics_agent_port=self._ray_params.metrics_agent_port,
    runtime_env_agent_port=self._ray_params.runtime_env_agent_port,
    metrics_export_port=self._metrics_export_port,
    dashboard_agent_listen_port=self._ray_params.dashboard_agent_listen_port,
    
    # 调试选项
    use_valgrind=use_valgrind,
    use_profiler=use_profiler,
    ray_debugger_external=self._ray_params.ray_debugger_external,
    
    # 日志路径
    raylet_stdout_filepath=raylet_stdout_filepath,
    raylet_stderr_filepath=raylet_stderr_filepath,
    dashboard_agent_stdout_filepath=...,
    dashboard_agent_stderr_filepath=...,
    runtime_env_agent_stdout_filepath=...,
    runtime_env_agent_stderr_filepath=...,
    
    # 高级选项
    huge_pages=self._ray_params.huge_pages,
    fate_share=self.kernel_fate_share,
    max_bytes=self.max_bytes,
    backup_count=self.backup_count,
    env_updates=self._ray_params.env_vars,
    node_name=self._ray_params.node_name,
    webui=self._webui_url,
    resource_isolation_config=self.resource_isolation_config,
)
```

#### 阶段 4：进程注册

```python
assert ray_constants.PROCESS_TYPE_RAYLET not in self.all_processes
self.all_processes[ray_constants.PROCESS_TYPE_RAYLET] = [process_info]
```

---

### 七、进程启动关键参数解析

| 参数 | 作用 | 设计意图 |
|------|------|---------|
| `fate_share` | 进程命运共享 | 父进程退出时自动清理子进程，防止孤儿进程 |
| `unique=True` | 日志文件唯一化 | 每次重启生成新日志，不覆盖历史，便于排查 |
| `is_head_node` | 节点角色标识 | Raylet 内部根据此参数决定是否启用 Head 专属功能 |
| `resource_isolation_config` | Cgroup 配置 | 限制 Ray 进程的 CPU/内存使用，防止影响系统 |
| `huge_pages` | 大页内存开关 | 提升对象存储性能，减少 TLB 失效 |

---

### 八、all_processes 进程字典

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

**作用**:
- `dead_processes()` 从此字典查询异常退出的进程
- `kill_all_processes()` 从此字典获取所有进程并杀死
- `ray stop` 命令最终调用此机制清理所有进程

---

## 核心文件：python/ray/_private/services.py

底层进程启动函数的集合，提供所有 C++ 进程的 Python 包装。

### 一、可执行文件路径映射

**位置**: 第 52-56 行

```python
RAYLET_EXECUTABLE = os.path.join(
    RAY_PATH, "core", "src", "ray", "raylet", "raylet" + EXE_SUFFIX
)
GCS_SERVER_EXECUTABLE = os.path.join(
    RAY_PATH, "core", "src", "ray", "gcs", "gcs_server" + EXE_SUFFIX
)
```

这些路径对应 Bazel 编译输出，打包在 Python wheel 中。

### 二、start_gcs_server() 详解

**位置**: 第 1452 行

```python
def start_gcs_server(
    redis_address: str,
    log_dir: str,
    ...
    gcs_server_port: Optional[int] = None,
):
    command = [
        GCS_SERVER_EXECUTABLE,
        f"--log_dir={log_dir}",
        f"--config_list={serialize_config(config)}",
        f"--gcs_server_port={gcs_server_port}",
        f"--node-ip-address={node_ip_address}",
        f"--session-name={session_name}",
        f"--ray-commit={ray.__commit__}",
    ]
    
    # Redis 相关参数
    if redis_address:
        command += [
            f"--redis_address={redis_ip_address}",
            f"--redis_port={redis_port}",
        ]
    
    process_info = start_ray_process(
        command,
        ray_constants.PROCESS_TYPE_GCS_SERVER,
        ...
    )
    return process_info
```

**关键参数**:
- `--config_list`: 序列化后的系统配置
- `--ray-commit`: Git commit hash，用于版本校验
- `redis_address`: 可选的外部 Redis 地址

### 三、start_raylet() 详解

**位置**: 第 1536 行

**函数签名**（30+ 个参数）：

```python
def start_raylet(
    redis_address: str,
    gcs_address: str,
    node_id: str,
    node_ip_address: str,
    node_manager_port: int,
    raylet_name: str,
    plasma_store_name: str,
    cluster_id: str,
    worker_path: str,
    setup_worker_path: str,
    temp_dir: str,
    session_dir: str,
    resource_dir: str,
    log_dir: str,
    resource_and_label_spec,
    plasma_directory: str,
    fallback_directory: str,
    object_store_memory: int,
    session_name: str,
    is_head_node: bool,
    resource_isolation_config: ResourceIsolationConfig,
    min_worker_port: Optional[int] = None,
    max_worker_port: Optional[int] = None,
    worker_port_list: Optional[List[int]] = None,
    object_manager_port: Optional[int] = None,
    redis_username: Optional[str] = None,
    redis_password: Optional[str] = None,
    metrics_agent_port: Optional[int] = None,
    metrics_export_port: Optional[int] = None,
    dashboard_agent_listen_port: Optional[int] = None,
    runtime_env_agent_port: Optional[int] = None,
    ...
):
```

**设计特点**:
- 参数数量极多（30+），反映了 Raylet 的复杂性
- 包含资源隔离、端口管理、路径配置等所有底层细节
- 所有配置最终通过命令行参数传递给 C++ 进程

### 四、通用进程启动机制：start_ray_process()

所有 C++ 进程都通过此函数启动，统一处理：

```python
def start_ray_process(
    command: List[str],
    process_type: str,
    stdout_file=None,
    stderr_file=None,
    fate_share=None,
):
    # 1. 环境变量设置
    # 2. 进程创建 subprocess.Popen
    # 3. Fate Share 机制（父进程死亡时子进程自动死亡）
    # 4. 返回 ProcessInfo 对象
```

**Fate Share 机制**：
- Ray 的核心设计，确保父进程退出时所有子进程自动清理，防止孤儿进程

---

## @ray.remote 任务提交流程

### 概述

详细追踪 `@ray.remote` 装饰器从 Python 函数定义到任务提交、调度、执行、返回结果的完整调用链。

### 一、Python 语法层：装饰器阶段

#### 1. `@ray.remote` 装饰器入口

**关键文件**: `python/ray/_private/worker.py` (第 3552 行)

```python
@PublicAPI
def remote(
    *args, **kwargs
) -> Union[ray.remote_function.RemoteFunction, ray.actor.ActorClass]:
```

**执行流程**:
1. 当用 `@ray.remote` 装饰一个函数或类时
2. 如果是函数 → 创建 `RemoteFunction` 对象
3. 如果是类 → 创建 `ActorClass` 对象

### 二、Python 层：RemoteFunction 初始化

**关键文件**: `python/ray/remote_function.py` (第 41 行)

```python
class RemoteFunction:
    def __init__(self, language, function, function_descriptor, task_options):
```

**关键点**:
- `self.remote` 方法是实际调用 `.remote()` 时的入口
- 此时函数并未真正执行，只是被包装

### 三、调用 `.remote()` 提交任务

**关键文件**: `python/ray/remote_function.py` (第 314 行)

```python
def _remote(self, args=None, kwargs=None, ...):
    """Submit the remote function for execution."""
```

**提交流程**:
1. 检查 worker 连接状态
2. 函数序列化与导出（第一次调用时）
3. 创建函数描述符
4. 序列化函数（pickle）
5. 导出函数到 GCS
6. 调用 core_worker.submit_task (C++ 边界)

### 四、C++ 层：任务提交

**关键文件**: `src/ray/core_worker/task_submission/normal_task_submitter.h`

```cpp
class NormalTaskSubmitter {
public:
    void SubmitTask(TaskSpecification task_spec);
private:
    DependencyResolver resolver_;
    TaskManagerInterface &task_manager_;
    std::shared_ptr<RayletClientInterface> local_raylet_client_;
};
```

### 五、调度层：Raylet 任务调度

**关键文件**: `src/ray/raylet/node_manager.h`

**调度流程**:
```
RequestLease RPC → Raylet
  ↓
1. ClusterResourceScheduler 检查资源可用性
  ↓
2. 找到可用节点后，检查是否有匹配的 worker 进程
  ↓
3. 若没有现成 worker: 启动新的 Python 进程
  ↓
4. 返回租约（包含目标 worker 的地址）
```

### 六、完整流程架构图

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

## GCS Server 深度架构分析

### 概述

GCS（Global Control Store）是 Ray 的全局状态管理中心，所有元数据都存储在这里。

**关键文件**: `src/ray/gcs/gcs_server.h`

### GcsServer 核心组件

```cpp
class GcsServer {
private:
    // 节点管理
    std::unique_ptr<GcsNodeManager> gcs_node_manager_;
    
    // Actor 管理（核心！）
    std::unique_ptr<GcsActorManager> gcs_actor_manager_;
    
    // Job 管理
    std::unique_ptr<GcsJobManager> gcs_job_manager_;
    
    // Worker 管理
    std::unique_ptr<GcsWorkerManager> gcs_worker_manager_;
    
    // 放置组管理
    std::unique_ptr<GcsPlacementGroupManager> gcs_placement_group_manager_;
    
    // 任务管理
    std::unique_ptr<GcsTaskManager> gcs_task_manager_;
    
    // 资源管理
    std::unique_ptr<GcsResourceManager> gcs_resource_manager_;
    
    // 集群资源调度器（全局调度）
    std::unique_ptr<ClusterResourceScheduler> cluster_resource_scheduler_;
    
    // 租约管理
    std::unique_ptr<ClusterLeaseManager> cluster_lease_manager_;
    
    // KV 存储
    std::unique_ptr<GcsKVManager> gcs_kv_manager_;
    
    // gRPC 服务
    std::unique_ptr<rpc::GrpcServer> rpc_server_;
};
```

### GCS 启动完整流程

**文件**: `src/ray/gcs/gcs_server.cc`

```
GcsServer::Start()
  ↓
1. 初始化存储后端（Redis / 内存）
   ↓
2. 初始化各 Manager（按依赖顺序）
   ├── GcsNodeManager
   ├── GcsResourceManager
   ├── GcsActorManager    ← Actor 生命周期管理
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

## Actor 创建完整流程

### 概述

Actor 是 Ray 的有状态计算抽象，创建流程涉及多个组件协同。

### 调用链追踪

```
用户代码: @ray.remote class MyActor: pass
  ↓
1. Python 层: ActorClass 实例化
   文件: python/ray/actor.py
  ↓
2. 调用 .remote() 创建 Actor
   ↓
3. CoreWorker::CreateActor（C++ 边界）
   文件: src/ray/core_worker/core_worker.cc
  ↓
4. 向 GCS 发送 RegisterActorRequest
   文件: src/ray/gcs/gcs_server/gcs_actor_manager.cc
  ↓
5. GcsActorManager 调度 Actor 到合适节点
   ├── 检查资源需求
   ├── 选择合适的 Raylet
   └── 记录 Actor 状态（PENDING → SCHEDULED）
  ↓
6. 目标 Raylet 创建 Worker 进程
   文件: src/ray/raylet/node_manager.cc
  ↓
7. Worker 进程中初始化 Actor
   ├── 反序列化 Actor 类
   ├── 执行 __init__ 方法
   └── 向 GCS 报告 Actor READY
  ↓
8. 返回 ActorHandle 给用户
```

### 关键状态转换

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

## Raylet 内部架构

### 概述

Raylet 是每个节点上的本地调度器，负责：
- 本地资源管理
- Worker 进程池管理
- 任务调度
- 对象管理

**关键文件**: `src/ray/raylet/raylet.h`

### 核心组件

| 组件 | 作用 | 关键文件 |
|------|------|---------|
| `NodeManager` | 节点资源管理、任务调度、Worker 生命周期 | `node_manager.h` |
| `WorkerPool` | Worker 进程池，管理空闲/忙碌的 Worker | `worker_pool.h` |
| `ClusterResourceScheduler` | 全局资源视图、节点选择 | `cluster_resource_scheduler.h` |
| `LocalResourceManager` | 本地资源核算 | `local_resource_manager.h` |
| `ObjectManager` | 对象传输、拉取/推送 | `object_manager.h` |
| `AgentManager` | Dashboard Agent 管理 | `agent_manager.h` |

### Worker 进程类型

| 类型 | 作用 | 数量 |
|------|------|------|
| Python Worker | 执行普通任务/Actor | 动态增减 |
| Java Worker | 执行 Java 任务 | 动态增减 |
| CoreWorker | C++ 核心层（每个进程 1 个） | 每个进程 1 个 |
| Driver | 用户主进程（Python/Java） | 每个 Job 1 个 |

---

## 关键文件索引

### Python 层

| 文件 | 作用 |
|------|------|
| `python/ray/scripts/scripts.py` | CLI 入口 |
| `python/ray/_private/node.py` | Node 类，进程编排 |
| `python/ray/_private/services.py` | 服务启动与进程管理 |
| `python/ray/remote_function.py` | RemoteFunction 类 |

### C++ 层

| 文件 | 作用 |
|------|------|
| `src/ray/gcs/gcs_server.h` | GCS Server 核心类 |
| `src/ray/raylet/raylet.h` | Raylet 核心类 |
| `src/ray/raylet/node_manager.h` | 节点管理器 |
| `src/ray/core_worker/core_worker.h` | CoreWorker 核心类 |
| `src/ray/core_worker/task_submission/normal_task_submitter.h` | 任务提交器 |

---

*文档生成时间: 2024-04-25*
