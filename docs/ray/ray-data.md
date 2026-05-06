# Ray Data 核心分析

本文档按核心文件和调用链组织 Ray Data 核心流程分析，通过交叉引用建立完整的知识体系。

---

[toc]

---

## 1. Ray Data 总体架构

Ray Data 是 Ray 生态中的分布式数据处理库，专为机器学习工作流设计。它提供了统一的 API 来加载、转换、处理和保存大规模数据集，无缝集成 Ray Train、Ray Tune 和 Ray Serve。

### 1.1 核心设计理念

| 设计理念 | 说明 |
|---------|------|
| **Lazy Execution** | 算子调用时不立即执行，而是构建执行计划 |
| **Streaming Execution** | 数据分块流式处理，避免全量加载内存 |
| **Block-based Architecture** | 数据以 Block 为单位进行分布式处理 |

### 1.2 核心目录结构

```
python/ray/data/
├── dataset.py              # Dataset 对外 API（280KB，核心文件）
├── read_api.py             # 数据读取 API（183KB）
├── iterator.py             # 数据迭代器（183KB）
├── context.py              # 执行上下文配置
├── block.py                # Block 抽象定义
├── aggregate.py            # 聚合函数
├── grouped_data.py         # 分组数据操作
├── preprocessor.py         # 数据预处理器
├── expressions.py          # 表达式 API
├── _internal/
│   ├── plan.py             # 执行计划（25KB）
│   ├── execution/
│   │   ├── streaming_executor.py      # 流式执行器（36KB）
│   │   ├── streaming_executor_state.py# 执行状态管理
│   │   ├── resource_manager.py        # 资源管理器
│   │   └── operators/                 # 物理算子
│   ├── logical/                        # 逻辑算子层
│   ├── planner/                        # 计划优化器
│   ├── datasource/                     # 数据源实现
│   └── stats.py                        # 统计指标
├── datasource/             # 对外数据源接口
├── preprocessors/          # 各种预处理器实现
└── tests/                  # 测试用例
```

### 1.3 架构分层

Ray Data 采用 5 层架构设计：

```
┌─────────────────────────────────┐
│   Dataset API (用户交互层)       │
│   dataset.py, read_api.py       │
├─────────────────────────────────┤
│   Logical Plan (逻辑计划层)      │
│   _internal/logical/            │
├─────────────────────────────────┤
│   Execution Plan (执行计划层)    │
│   _internal/plan.py             │
├─────────────────────────────────┤
│   Streaming Executor (执行层)    │
│   _internal/execution/          │
├─────────────────────────────────┤
│   Physical Operators (算子层)    │
│   _internal/execution/operators/│
└─────────────────────────────────┘
```

---

## 2. Dataset API 层

**文件位置**: `python/ray/data/dataset.py`

Dataset 是用户直接交互的入口，提供了类似 Pandas 的声明式 API。

### 2.1 类设计与核心成员

```python
@PublicAPI
class Dataset:
    def __init__(
        self,
        plan: ExecutionPlan,
        logical_plan: LogicalPlan,
    ):
        self._plan = plan              # 执行计划（物理）
        self._logical_plan = logical_plan  # 逻辑计划
        self._current_executor: Optional["Executor"] = None
```

**设计要点**:
1. **构造函数不公开** - 用户通过 `ray.data.read_*()` 工厂方法创建
2. **双计划架构** - 同时持有逻辑计划和执行计划
3. **不可变设计** - 所有转换方法返回新的 Dataset 对象（通过 `copy()`）
4. **Lazy 执行** - 只构建 DAG，触发 Action 时才真正执行

### 2.2 API 分组架构

Dataset 使用常量定义 API 分组（第 155-163 行）：

| 分组常量 | 分组名称 | 代表方法 |
|---------|---------|---------|
| `BT_API_GROUP` | Basic Transformations | `map`, `map_batches`, `filter`, `add_column` |
| `SSR_API_GROUP` | Sorting, Shuffling and Repartitioning | `sort`, `random_shuffle`, `repartition` |
| `SMJ_API_GROUP` | Splitting, Merging, Joining | `split`, `union`, `join`, `zip` |
| `GGA_API_GROUP` | Grouped and Global aggregations | `groupby`, `sum`, `mean`, `min`, `max` |
| `CD_API_GROUP` | Consuming Data | `count`, `take`, `iter_rows`, `to_pandas` |
| `IOC_API_GROUP` | I/O and Conversion | `write_parquet`, `write_csv`, `to_arrow_refs` |
| `IM_API_GROUP` | Inspecting Metadata | `schema`, `columns`, `num_blocks` |
| `E_API_GROUP` | Execution | `materialize`, `explain`, `stats` |
| `EXPRESSION_API_GROUP` | Expressions | 列表达式计算 |

### 2.3 核心 API 分类详解

#### 2.3.1 基础转换（Lazy，不执行）

**代表方法**: `map()`, `map_batches()`, `flat_map()`, `filter()`

```python
def map(
    self,
    fn: Callable[[Dict[str, Any]], Dict[str, Any]],
    *,
    compute: Optional[ComputeStrategy] = None,  # Task / Actor 选择
    num_cpus: Optional[float] = None,            # 资源配置
    num_gpus: Optional[float] = None,
    concurrency: Optional[Union[int, Tuple]] = None,  # Actor 并发数
    **ray_remote_args,
) -> "Dataset":
    """Lazy: 只构建 MapRows 逻辑算子，不立即执行"""
```

**关键技术点**:
- **返回新 Dataset** - 通过 `copy()` 创建新实例，原对象不变
- **ComputeStrategy** - 支持 Task 模式（默认）或 Actor 模式（有状态）
- **资源隔离** - 每个 UDF 可独立配置 CPU/GPU

#### 2.3.2 全局混洗（All-to-All）

**代表方法**: `sort()`, `random_shuffle()`, `repartition()`

**关键技术点**:
- **Map + Reduce 两阶段** - 先分片采样，再全局排序
- **Exchange 算子** - 跨节点数据传输，网络开销大
- **SortKey 抽象** - 支持多列排序、升降序配置

#### 2.3.3 Action 算子（触发执行）

**代表方法**: `count()`, `take()`, `materialize()`, `iter_rows()`

```python
def count(self) -> int:
    """触发执行：构建 Count 算子并执行"""
    return self._execute_with_count(Count(self._logical_plan.dag))

def materialize(self) -> "MaterializedDataset":
    """全量执行并缓存所有 Block 到对象存储"""
```

**执行触发点**:
- 所有 `iter_*` 系列方法
- 所有 `to_*` 转换方法
- 所有 `write_*` 输出方法
- `count()`, `take()`, `show()` 等立即返回结果的方法

#### 2.3.4 I/O 方法

**代表方法**: `write_parquet()`, `write_csv()`, `write_json()` 等 10+ 种

**设计模式**:
- 每种格式对应一个 `Datasink` 类（如 `ParquetDatasink`）
- `Write` 逻辑算子封装写入操作
- 支持 `SaveMode`: `append`, `overwrite`, `error`, `ignore`

### 2.4 Dataset 调用链构建机制

**核心模式**: 链式调用 + 不可变对象

```
用户调用:
  ds = ray.data.read_parquet("path")  # Read 算子
       .map_batches(fn)               # MapBatches 追加
       .filter(pred)                   # Filter 追加
       .count()                        # Count 触发执行
```

**内部实现**:
1. **Copy 新对象** - 每个转换方法先调用 `Dataset.copy()` 创建新实例
2. **追加逻辑算子** - 在新实例的 `_logical_plan` 上追加 Operator
3. **返回新实例** - 原对象完全不变，支持分支处理

```python
# copy 方法实现（第 265 行）
@staticmethod
def copy(ds: "Dataset", _deep_copy: bool = False, _as: Optional[type] = None) -> "Dataset":
    """创建新 Dataset 实例，共享计划对象"""
    if _deep_copy:
        return _as(ds._plan.deep_copy(), ds._logical_plan)
    else:
        return _as(ds._plan.copy(), ds._logical_plan)
```

### 2.5 ComputeStrategy 多执行模式

`map_batches` 支持三种执行模式：

| 模式 | 实现 | 适用场景 | 关键参数 |
|------|------|---------|---------|
| **Task 模式** | 普通 Ray 任务 | 无状态处理，启动快 | 默认 |
| **Actor Pool 模式** | Actor 池复用 | 有状态初始化（模型加载） | `compute=ActorPoolStrategy(size=8)` |
| **Actor 自动扩缩容** | Actor 动态增减 | 负载波动场景 | `concurrency=(1, 10)` |

**关键参数**（第 457-489 行 `map_batches` 签名）:
- `batch_size` - 批大小，性能调优关键
- `batch_format` - "pandas", "pyarrow", "numpy" 三种格式
- `zero_copy_batch` - 零拷贝批量读取优化
- `concurrency` - Actor 并发数（min, max）

### 2.6 数据消费模式

Dataset 支持多种消费方式，满足不同场景：

#### 2.6.1 迭代器模式（推荐）

```python
# 逐行迭代
for row in ds.iter_rows():
    process(row)

# 逐批迭代（推荐，性能好）
for batch in ds.iter_batches(batch_size=256):
    process_batch(batch)

# PyTorch 格式
for batch in ds.iter_torch_batches(batch_size=32):
    train_step(batch)
```

**关键技术**: `DataIteratorImpl` - 流式拉取，内存友好

#### 2.6.2 全量转换模式

```python
# 全部拉取到本地（注意内存！）
df = ds.to_pandas()          # → Pandas DataFrame
table = ds.to_arrow()        # → Arrow Table
refs = ds.to_arrow_refs()    # → List[ObjectRef]（分布式）
```

#### 2.6.3 外部系统集成

支持直接转换到：
- Dask / Modin / Mars 分布式 DataFrame
- Spark DataFrame
- TensorFlow Dataset (`to_tf()`)
- PyTorch DataLoader (`to_torch()`)

### 2.7 执行调试与诊断 API

| 方法 | 作用 |
|------|------|
| `explain()` | 打印逻辑计划 + 物理计划（见第 6102 行） |
| `stats()` | 执行统计：耗时、吞吐量、内存等 |
| `schema()` | 查看数据结构（不触发执行） |
| `num_blocks()` | Block 数量（并行度指标） |
| `size_bytes()` | 数据总大小 |

### 2.8 MaterializedDataset 子类

当 Dataset 完全执行后，可转换为 `MaterializedDataset`：
- Block 全部在 Plasma 对象存储中
- 可重复消费，不需要重新计算
- 支持 `random_access_dataset` 索引查询

### 2.9 Read API - 数据源读取接口

**文件位置**: `python/ray/data/read_api.py`（183KB，第二大文件）

Read API 是 Ray Data 的**入口层**，提供 20+ 种数据源的统一读取接口。

#### 2.9.1 数据源分类

| 类别 | 代表方法 | 对应 Datasource 类 |
|------|---------|-------------------|
| **列式存储** | `read_parquet`, `read_iceberg`, `read_lance` | `ParquetDatasource`, `IcebergDatasource` |
| **行式存储** | `read_csv`, `read_json`, `read_avro` | `CSVDatasource`, `ArrowJSONDatasource` |
| **半结构化** | `read_webdataset` | `WebDatasetDatasource` |
| **二进制/媒体** | `read_images`, `read_video`, `read_audio` | `ImageDatasource`, `VideoDatasource` |
| **数组格式** | `read_numpy`, `read_tfrecords` | `NumpyDatasource`, `TFRecordDatasource` |
| **数据库** | `read_sql`, `read_bigquery`, `read_mongo`, `read_clickhouse` | `SQLDatasource`, `BigQueryDatasource` |
| **数据湖** | `read_hudi`, `read_delta` | `HudiDatasource`, `DeltaSharingDatasource` |
| **内存数据** | `from_items`, `from_pandas`, `from_arrow`, `from_blocks` | `RangeDatasource` |
| **外部生态** | `from_huggingface`, `from_dask`, `from_spark`, `from_torch` | 直接转换为 Blocks |

#### 2.9.2 核心设计模式：Datasource 抽象

所有数据源统一实现 `Datasource` 基类，提供：

```python
# 核心方法协议
class Datasource:
    def create_reader(self, **read_args) -> Reader:
        """创建 Reader 实例，准备读取任务"""
        
    def prepare_read(self, parallelism: int, **read_args) -> List[ReadTask]:
        """生成并行读取任务列表 - 最核心的方法"""
        
    def on_read_complete(self, read_tasks: List[ReadTask]) -> None:
        """读取完成后的回调"""
```

**关键设计点**（第 67-68 行 `Read` 逻辑算子）：
```python
# 所有 read_*() 方法最终生成 Read 逻辑算子
Read(datasource, parallelism, read_args)
```

#### 2.9.3 并行读取机制

**两步读取架构**：

```
Step 1: Driver 端（本地执行）
  ↓
  read_parquet("s3://bucket/*")
  ↓
  1. 调用 datasource.create_reader()
  2. 列出所有文件 / 分区
  3. 按文件大小分片，生成 N 个 ReadTask
  4. 返回 Read 逻辑算子（Lazy，不执行）

Step 2: Executor 端（分布式执行）
  ↓
  每个 ReadTask 在独立 Ray Task 中执行
  ↓
  1. Worker 拉取文件分片
  2. 解析为 Arrow/Pandas Block
  3. 写入 Plasma 对象存储
  ↓
  输出 N 个 Block
```

**自动并行度推断**（第 72 行 `_autodetect_parallelism`）:
- 默认: `target_max_block_size = 512MB`
- 按文件大小估算所需 Block 数
- 受限于集群可用 CPU 数

#### 2.9.4 内存数据读取

`from_items`, `from_pandas`, `from_arrow` 等方法是**特殊情况**：
- 不需要分布式读取
- 直接在 Driver 端分割为 Blocks
- 调用 `FromItems`, `FromPandas`, `FromArrow` 等逻辑算子
- 直接返回 `MaterializedDataset`（已物化）

```python
# from_blocks 直接创建物化数据集（第 128-154 行）
def from_blocks(blocks: List[Block]):
    block_refs = [ray.put(block) for block in blocks]
    from_blocks_op = FromBlocks(block_refs, meta)
    return MaterializedDataset(execution_plan, logical_plan)
```

#### 2.9.5 高级特性

| 特性 | 说明 | 关键实现 |
|------|------|---------|
| **分区推断** | 自动识别 Hive 风格目录分区 | `Partitioning` 类 |
| **Schema 推断** | 采样前 N 个文件推断 Schema | 在 `prepare_read` 阶段执行 |
| **谓词下推** | Iceberg/Parquet 支持行过滤 | 底层引擎直接下推 |
| **列裁剪** | 只读取需要的列，减少 IO | `columns` 参数 |
| **文件元数据缓存** | 避免重复 list S3 等操作 | `FileMetadataProvider` 抽象 |

### 2.10 Write API - 数据写出接口

**文件位置**: `dataset.py` 第 3781-5100 行

与 Read API 对称，Ray Data 提供 10+ 种写出格式的统一接口。

#### 2.10.1 写出格式一览

| 类别 | 代表方法 | 对应 Datasink 类 |
|------|---------|-------------------|
| **列式存储** | `write_parquet`, `write_iceberg`, `write_lance` | `ParquetDatasink`, `IcebergDatasink` |
| **行式存储** | `write_csv`, `write_json` | `CSVDatasink`, `JSONDatasink` |
| **二进制/媒体** | `write_images`, `write_numpy` | `ImageDatasink`, `NumpyDatasink` |
| **机器学习** | `write_tfrecords`, `write_webdataset` | `TFRecordDatasink`, `WebDatasetDatasink` |
| **数据库** | `write_sql`, `write_bigquery`, `write_mongo`, `write_clickhouse`, `write_snowflake` | `SQLDatasink`, `MongoDatasink` |

#### 2.10.2 核心设计模式：Datasink 抽象

所有写出源实现 `Datasink` 基类（第 112 行 `dataset.py` import）：

```python
# 核心写出协议
class Datasink:
    def write(self, blocks: List[ObjectRef[Block]], **kwargs) -> WriteResult:
        """将 Blocks 写出到目标系统"""
        
    def on_write_complete(self, write_results: List[WriteResult]) -> None:
        """写出完成后的回调"""
```

**对应逻辑算子**（第 84 行 `Read` 的对称算子）：
```python
# Write 逻辑算子封装写出操作
Write(datasink, ds._logical_plan.dag)
```

#### 2.10.3 分布式写入机制

**并行写出流程**：
```
用户调用 ds.write_parquet("s3://bucket/output")
    ↓
1. 触发 Dataset 执行（Lazy → 执行）
   ↓
2. 每个 Block 对应一个写出 Task
   ↓
3. Worker 分布式并行写出
   ├── 每个 Task 写一个或多个文件
   ├── 文件名自动编号: part-00000.parquet
   └── 支持按列分区写入
    ↓
4. 返回 WriteResult 汇总
```

#### 2.10.4 SaveMode：写入冲突策略

**第 112 行 `SaveMode` 枚举**：
```python
from ray.data.datasource import SaveMode
```

| 模式 | 行为 | 适用场景 |
|------|------|---------|
| `ERROR` | 目录已存在则报错（默认） | 安全写入，防止覆盖 |
| `OVERWRITE` | 覆盖已有目录 | 重跑场景 |
| `APPEND` | 追加到已有目录 | 增量写入 |
| `IGNORE` | 目录已存在则跳过 | 幂等写入场景 |

#### 2.10.5 高级写出特性

| 特性 | 说明 | 关键参数 |
|------|------|---------|
| **按列分区写出** | Hive 风格分区目录 | `partition_cols` |
| **文件数控制** | 调整并行度控制文件数 | `repartition()` + write |
| **文件名模板** | 自定义输出文件名 | `filename_provider` |
| **行组大小** | Parquet 行组优化 | `row_group_size_bytes` |
| **分桶写出** | 按哈希分桶输出 | `bucket_col` |

#### 2.10.6 Read/Write 对称性设计

Ray Data 的 I/O 设计高度对称：

| 方向 | 核心抽象 | 逻辑算子 |
|------|---------|---------|
| **读** | `Datasource` + `ReadTask` | `Read` 算子 |
| **写** | `Datasink` + `WriteTask` | `Write` 算子 |

这种对称性带来的好处：
- 新增一种格式只需同时实现 `Datasource` + `Datasink`
- 统一的错误处理和重试机制
- ETL 流程表达简洁：`read -> transform -> write`

---

## 3. Logical Plan（逻辑计划层）

**文件位置**: `python/ray/data/dataset.py`

Dataset 是用户直接交互的入口，提供了类似 Pandas 的声明式 API。

### 2.1 典型使用流程

```python
import ray

# 1. 创建 Dataset（Lazy，不立即执行）
ds = ray.data.read_parquet("s3://bucket/data")  # -> Read 逻辑算子

# 2. 转换操作（继续构建 Logical Plan）
ds = ds.map_batches(lambda df: df[df["value"] > 0])  # -> MapBatches 逻辑算子
ds = ds.filter(lambda row: row["label"] != -1)       # -> Filter 逻辑算子
ds = ds.repartition(100)                             # -> Repartition 逻辑算子

# 3. 触发执行（Action 操作）
result = ds.count()           # 触发执行 -> Count 算子
materialized = ds.materialize()  # 全量执行并缓存
```

### 2.2 API 分类

| 类别 | 代表方法 | 对应逻辑算子 |
|------|---------|------------|
| 基础转换 | `map_batches()`, `map_rows()`, `flat_map()`, `filter()` | MapBatches, MapRows, FlatMap, Filter |
| 排序/混洗 | `sort()`, `random_shuffle()`, `repartition()` | Sort, RandomShuffle, Repartition |
| 拆分/合并 | `split()`, `union()`, `zip()`, `train_test_split()` | StreamingSplit, Union, Zip |
| 聚合 | `groupby()`, `sum()`, `mean()`, `max()`, `min()` | Aggregate |
| 消费 | `count()`, `take()`, `iter_rows()`, `iter_batches()` | Count, Limit |
| 写入 | `write_parquet()`, `write_csv()`, `write_json()` | Write |

### 2.3 explain() 调试工具

查看完整执行计划是理解 Ray Data 执行的关键：

```python
print(ds.explain())
```

示例输出：
```
-------- Logical Plan --------
Count
+- Filter
   +- MapBatches
      +- ReadParquet

-------- Physical Plan --------
CountOperator[Count]
+- FilterOperator[Filter]
   +- MapOperator[MapBatches]
      +- InputDataBuffer[ReadParquet]
```

---

## 3. Logical Plan（逻辑计划层）

**文件位置**: `python/ray/data/_internal/logical/`

当用户调用 Dataset 的转换方法时，Ray Data 并不会立即执行，而是构建一个逻辑算子 DAG。

### 3.1 逻辑算子 DAG 构建

```
用户调用链:
  read_parquet() -> map_batches() -> filter() -> count()

生成的 Logical Plan DAG:
  Read (DataSource) -> MapBatches (UDF) -> Filter (Predicate) -> Count
```

### 3.2 逻辑算子类型

| 算子类型 | 说明 | 包含算子 |
|---------|------|---------|
| **InputDataOperator** | 输入数据算子 | InputData |
| **Read** | 读取数据源算子 | Read |
| **MapOperator** | 逐元素转换 | MapBatches, MapRows, Filter, FlatMap, Project |
| **AllToAllOperator** | 全局混洗操作 | Sort, RandomShuffle, Repartition, Aggregate |
| **NAryOperator** | 多输入合并 | Union, Zip |
| **WriteOperator** | 写入数据 | Write |
| **终端算子** | 触发执行 | Count, Limit |

---

## 4. Execution Plan（执行计划层）

**文件位置**: `python/ray/data/_internal/plan.py`

`ExecutionPlan` 是连接逻辑计划和物理执行的桥梁。

### 4.1 核心职责

1. **逻辑优化**：算子融合（Fusion）、谓词下推、投影下推
2. **物理计划生成**：将 Logical Operator 转换为 Physical Operator
3. **执行调度**：创建 StreamingExecutor 并调度执行

### 4.2 ExecutionPlan 核心方法

```python
class ExecutionPlan:
    def create_executor(self) -> StreamingExecutor:
        """创建流式执行器"""
        return StreamingExecutor(self._context, self.get_dataset_id())
    
    def explain(self) -> str:
        """打印逻辑计划和物理计划"""
        logical_plan = self._logical_plan
        physical_plan = get_execution_plan(self._logical_plan)
        return logical_plan_str + physical_plan_str
```

---

## 5. Streaming Executor（流式执行层）

**文件位置**: `python/ray/data/_internal/execution/streaming_executor.py`

`StreamingExecutor` 是 Ray Data 的执行核心，采用**独立线程 + 事件循环**的调度模型。

### 5.1 调度模型

```
                                     ┌─────────────────────────────┐
                                     │   StreamingExecutor 线程     │
                                     │                             │
  Main Thread                        │  ┌───────────────────────┐  │
───────────┐                         │  │  Scheduling Loop      │  │
           │  execute()              │  │  ┌─────────────────┐  │  │
           └─────────────────────────────> │ ray.wait()       │  │  │
                                         │  │ 处理完成任务     │  │  │
OutputIterator <─── yield blocks ──────── │ 选择下一个算子运行 │  │  │
                                         │  └─────────────────┘  │  │
                                         └───────────────────────┘  │
                                                                  │
     ┌──────────┐    ┌──────────┐    ┌──────────┐                   │
     │  Worker  │    │  Worker  │    │  Worker  │ <──────────────────┘
     └────┬─────┘    └────┬─────┘    └────┬─────┘
          │                │                │
          └────────────────┴────────────────┘
                   Ray Task Pool
```

### 5.2 核心执行机制

| 机制 | 说明 | 关键函数 |
|------|------|---------|
| **拓扑构建** | 构建算子执行拓扑 | `build_streaming_topology()` |
| **资源管理** | 管理 CPU/GPU/内存预算 | `ResourceManager` |
| **调度循环** | 事件驱动的任务调度 | `ray.wait()`, `process_completed_tasks()` |
| **算子选择** | 根据资源和背压选择算子 | `select_operator_to_run()` |
| **背压控制** | 限制算子队列长度，防止 OOM | `target_max_block_overflow` |

### 5.3 背压机制

- 限制每个算子的队列长度（默认 200 个 blocks）
- 防止上游生产速度远超下游消费导致 OOM
- 可配置：`DataContext.target_max_block_overflow`

---

## 6. Physical Operators（物理算子层）

**文件位置**: `python/ray/data/_internal/execution/operators/`

### 6.1 算子分类

| 算子类型 | 代表类 | 用途 |
|---------|--------|------|
| **输入源** | `InputDataBuffer` | 缓存输入数据 blocks |
| **Map类** | `MapOperator` | 逐块转换，无状态 |
| **Actor Map类** | `ActorPoolMapOperator` | 使用 Actor 池执行有状态 UDF |
| **AllToAll类** | `AllToAllOperator` | shuffle、sort、repartition |
| **N-Ary类** | `ZipOperator`, `UnionOperator` | 多输入合并 |
| **Output** | `OutputOperator` | 输出结果 |

### 6.2 ActorPoolMapOperator

这是 Ray Data 最强大的特性之一，特别适合：
- GPU 推理（模型加载一次，多次复用）
- 有状态处理
- 昂贵的初始化操作

```python
ds = ds.map_batches(
    inference_fn,
    compute=ray.data.ActorPoolStrategy(size=8),  # 8个 Actor 并行
    batch_size=256,
    num_gpus=1  # 每个 Actor 占用 1 个 GPU
)
```

---

## 7. Block 系统

### 7.1 Block 抽象

**文件位置**: `python/ray/data/block.py`

Ray Data 的数据以 `Block` 为单位存储和传输，每个 Block 是：
- 一个 Arrow Table、Pandas DataFrame 或 NumPy 数组
- 大小通常在 128MB ~ 512MB 之间（可配置）
- 是分布式调度的最小单位

### 7.2 BlockAccessor 接口

`BlockAccessor` 提供统一的 Block 操作接口：

```python
class BlockAccessor:
    def num_rows(self) -> int: ...
    def size_bytes(self) -> int: ...
    def schema(self) -> Schema: ...
    def slice(self, start: int, end: int) -> Block: ...
    def to_pandas(self) -> pandas.DataFrame: ...
    def to_arrow(self) -> pyarrow.Table: ...
    def to_numpy(self, column: str) -> np.ndarray: ...
```

### 7.3 Block 实现类

| 实现类 | 说明 |
|--------|------|
| `ArrowBlockAccessor` | Arrow Table 格式（默认） |
| `PandasBlockAccessor` | Pandas DataFrame 格式 |
| `TensorBlockAccessor` | 张量数据支持 |

### 7.4 RefBundle

**文件位置**: `python/ray/data/_internal/execution/interfaces/ref_bundle.py`

`RefBundle` 是 Block 在执行流中的载体，包含：
- `blocks: List[Tuple[ObjectRef[Block], BlockMetadata]]`
- 元数据：行数、大小、schema 等

---

## 8. DataContext（全局配置中心）

**文件位置**: `python/ray/data/context.py`

`DataContext` 是 Ray Data 的全局配置管理器，控制着执行的方方面面。

### 8.1 常用配置

```python
from ray.data.context import DataContext

ctx = DataContext.get_current()

# Block 大小配置
ctx.target_max_block_size = 512 * 1024 * 1024  # 512MB
ctx.target_min_block_size = 16 * 1024 * 1024   # 16MB

# 错误处理
ctx.max_errored_blocks = 0  # 允许的错误 block 数（0=不允许）

# 执行配置
ctx.execution_options.verbose_progress = True

# 自动扩缩容配置
ctx.autoscaling_config = {
    "max_autoscale_workers": 100,
    "min_autoscale_workers": 1
}

# 背压配置
ctx.target_max_block_overflow = 200  # 算子队列最大长度
ctx.enable_fusion = True  # 启用算子融合优化
```

---

## 9. 典型执行流程

让我们追踪一个完整的执行路径：

```python
import ray

# 步骤 1: 创建 Dataset（构建 Logical Plan）
ds = ray.data.read_parquet("data.parquet")  # ReadOperator
ds = ds.map_batches(lambda df: df * 2)      # MapBatchesOperator
ds = ds.filter(lambda row: row["x"] > 0)    # FilterOperator

# 步骤 2: 触发执行（Action）
result = ds.count()  # 这里开始真正执行
```

### 9.1 执行时序

```
1. User calls ds.count()
   ↓
2. Dataset.count() creates Count logical operator
   ↓
3. ExecutionPlan.execute() is called
   ↓
4. Logical optimizer runs (operator fusion, etc.)
   ↓
5. Physical plan generated: InputDataBuffer -> MapOperator -> FilterOperator -> CountOperator
   ↓
6. StreamingExecutor created and started on a separate thread
   ↓
7. Topology built, resource manager initialized
   ↓
8. Scheduling loop runs:
   - Read tasks submitted first
   - As read tasks complete, map tasks submitted
   - As map tasks complete, filter tasks submitted
   - Results flow through the pipeline
   ↓
9. OutputIterator yields results to user
   ↓
10. Executor shuts down when done
```

---

## 10. 核心特性总结

| 特性 | 说明 | 关键文件 |
|------|------|---------|
| **延迟执行** | 算子调用构建 DAG，Action 触发执行 | `plan.py`, `dataset.py` |
| **流式执行** | 数据分块流式处理，内存友好 | `streaming_executor.py` |
| **算子融合** | 相邻 Map 算子合并，减少任务开销 | `planner/fusion.py` |
| **背压控制** | 上游速率适配下游消费能力 | `backpressure_policy/` |
| **Actor 池** | 有状态任务复用 Actor，避免重复初始化 | `actor_pool_map_operator.py` |
| **自动扩缩容** | 根据负载自动调整 Actor 数量 | `actor_autoscaler/` |
| **进度追踪** | 详细的执行进度条和统计指标 | `progress_bar.py`, `stats.py` |

---

## 11. 测试用例参考

### 11.1 基础功能测试

| 测试文件 | 大小 | 测试内容 |
|---------|------|---------|
| `test_consumption.py` | 72KB | 数据消费方式测试：`iter_rows()`, `iter_batches()`, `to_tf()`, `to_torch()` |

### 11.2 算子测试

| 测试文件 | 大小 | 测试内容 |
|---------|------|---------|
| `test_actor_pool_map_operator.py` | 28KB | Actor 池的创建、扩缩容、错误处理，有状态 UDF 的执行 |

### 11.3 执行器测试

| 测试文件 | 大小 | 测试内容 |
|---------|------|---------|
| `test_backpressure_e2e.py` | 11KB | 背压机制正确工作、内存使用控制 |

### 11.4 资源管理测试

| 测试文件 | 大小 | 测试内容 |
|---------|------|---------|
| `test_autoscaler.py` | 11KB | Actor 自动扩缩容逻辑、资源利用率优化 |
