# 架构详解

## 核心设计思想

### 1. 无侵入设计

**目标**：不修改 OpenClaw 核心代码，仅通过插件机制实现功能

**实现方式**：
- 使用 Provider Plugin SDK 定义的标准钩子
- 依赖注入（Dependency Injection）方式获取配置
- 返回标准格式的认证信息

**好处**：
- 与核心解耦，版本兼容好
- 可独立开发、测试、部署
- 不影响其他插件和 Provider

---

### 2. 渐进式降级策略

```
优先级从高到低:

  1. 插件动态注入  ← 我们在这里
      ↓ (失败)
  2. Auth Profiles
      ↓ (失败)
  3. 环境变量
      ↓ (失败)
  4. 配置文件
      ↓ (失败)
  5. 本地 Provider 合成
      ↓ (失败)
  6. AWS SDK 认证
      ↓ (失败)
  7. 友好的错误提示 ✨
```

**关键**：插件返回 `undefined` 表示"我不处理，交给下一级"

---

### 3. 内存优先策略

| 特性 | 说明 |
|------|------|
| **内存缓存** | Key 仅存储在 `Map<string, KeyCacheEntry>` |
| **不落盘** | 从不写入 `config.json` 或任何文件 |
| **进程隔离** | 进程重启后缓存自动清空 |
| **无副作用** | 不修改用户配置文件 |

---

## 钩子执行时序

### 阶段 1: 配置加载

```
loadConfig()
    ↓
resolveConfigEnvVars()
    ↓
normalizeConfig()
    ↓
resolveProviderConfigApiKeyWithPlugin() ← 我们的钩子 2
    ↓
配置缓存 (configCache)
```

### 阶段 2: 消息接收

```
收到用户消息
    ↓
getApiKeyForModel()
    ↓
resolveApiKeyForProvider()
    ↓
遍历 Profile 列表
    ↓
resolveProviderSyntheticAuthWithPlugin() ← 我们的钩子 1 ✨
    ↓
返回 { apiKey } 或 undefined
```

### 阶段 3: 实际调用

```
准备发起 HTTP 请求
    ↓
prepareProviderRuntimeAuth() ← 我们的钩子 3
    ↓
注入额外 Header / 签名
    ↓
真正调用 Provider API
    ↓
返回响应 / 401 触发 Failover
```

---

## 关键代码位置（OpenClaw 核心）

### 1. 合成认证钩子分发

**文件**: `src/plugins/provider-runtime.ts:498-506`

```typescript
export function resolveProviderSyntheticAuthWithPlugin(params: {
  provider: string;
  config?: OpenClawConfig;
  workspaceDir?: string;
  env?: NodeJS.ProcessEnv;
  context: ProviderResolveSyntheticAuthContext;
}) {
  return resolveProviderRuntimePlugin(params)?.resolveSyntheticAuth?.(params.context) ?? undefined;
}
```

**调用方**: `src/agents/models-config.providers.secrets.ts`

```typescript
// 在规范化配置时检查是否有合成认证
const syntheticAuth = resolveProviderSyntheticAuthWithPlugin({
  provider: providerName,
  config,
  workspaceDir,
  env,
  context: { provider: providerName, config, agentDir },
});
```

### 2. API Key 解析核心流程

**文件**: `src/agents/model-auth.ts`

```typescript
export async function resolveApiKeyForProvider(params: {
  provider: string;
  cfg: OpenClawConfig;
  profileId?: string;
  agentDir?: string;
  // ...
}): Promise<{
  apiKey: string;
  source: "profile" | "env" | "config" | "synthetic" | "aws";
}> {
  // 优先级 1: 指定 Profile ID
  // 优先级 2: 遍历 Auth Profiles
  // 优先级 3: 环境变量
  // 优先级 4: 配置文件
  // 优先级 5: 合成认证 (Plugin Hook)  ← 我们在这里
  // 优先级 6: AWS SDK
}
```

---

## 插件与核心的交互边界

```
┌─────────────────────────────────────────────────────────────┐
│                    OpenClaw Core                             │
├─────────────────────────────────────────────────────────────┤
│  src/agents/model-auth.ts                                    │
│     ↓ resolveApiKeyForProvider()                             │
├─────────────────────────────────────────────────────────────┤
│  src/plugins/provider-runtime.ts                             │
│     ↓ resolveProviderSyntheticAuthWithPlugin()               │
└──────────────────────────┬──────────────────────────────────┘
                           │
              Provider Plugin SDK 边界
                           │
┌──────────────────────────▼──────────────────────────────────┐
│              我们的插件 (extensions/dynamic-api-key)         │
├─────────────────────────────────────────────────────────────┤
│  resolveSyntheticAuth()  ← 返回 { apiKey } 或 undefined     │
│  resolveConfigApiKey()   ← 处理 dynamic:// 标记              │
│  prepareRuntimeAuth()    ← 运行时准备                        │
└─────────────────────────────────────────────────────────────┘
```

---

## 缓存设计

### 缓存结构

```typescript
Map<string, KeyCacheEntry>
     │
     └─ key: "anthropic"
     └─ value: {
          key: "sk-ant-...",
          expiresAt: 1714200300000  // TTL 5分钟
        }
```

### 缓存策略

1. **写时刷新**：缓存未命中时同步拉取，阻塞当前请求
2. **后台刷新**（待实现）：接近过期时异步刷新，不阻塞
3. **回退机制**：拉取失败时使用备用 Key 列表

---

## 安全考量

### 1. Key 传输安全

| 阶段 | 安全措施 |
|------|----------|
| **Key Manager → 插件** | HTTPS + mTLS + 请求签名 |
| **插件内存中** | 明文存储（进程隔离） |
| **插件 → Provider API** | Authorization: Bearer + HTTPS |

### 2. 审计日志

建议添加：
```typescript
console.info(JSON.stringify({
  event: "api_key_used",
  provider,
  source: "dynamic",
  requestId: context.requestId,
  timestamp: new Date().toISOString(),
}));
```

### 3. 密钥轮换

支持两种方式：
1. **主动轮换**：Key Manager 发布新 Key，TTL 后生效
2. **被动轮换**：收到 401 时立即失效缓存并重新拉取

---

## 性能指标

| 操作 | 耗时 | 说明 |
|------|------|------|
| 缓存命中 | < 1ms | 内存 Map 查找 |
| Key Manager 拉取 | 50-200ms | 网络开销 |
| 备用 Key 回退 | < 1ms | 直接返回 |

**建议**：设置合理的 TTL（5-15分钟），平衡安全与性能。

---

## 可扩展性

### 扩展点 1: 多租户路由

```typescript
async resolveSyntheticAuth(context) {
  const { agentDir } = context;
  const tenantId = extractTenantId(agentDir);
  return getKeyForTenant(provider, tenantId);
}
```

### 扩展点 2: Key 池与负载均衡

```typescript
async resolveSyntheticAuth(context) {
  const pool = getKeyPool(provider);
  return pool.roundRobin();  // 轮询
  // return pool.weighted();  // 权重
  // return pool.leastUsed(); // 最少使用
}
```

### 扩展点 3: 配额管理

```typescript
async resolveSyntheticAuth(context) {
  const key = getCachedKey(provider);
  if (getQuotaUsage(key) > 0.9) {
    await rotateKeyInBackground(provider);
  }
  return key;
}
```
