# LLM API Key 读取流程分析

## 概述

OpenClaw采用多层级、优先级机制读取LLM Provider的API Key，支持多种认证方式：
- Auth Profiles（优先级最高）
- 环境变量（Env Vars）
- 配置文件直接配置
- AWS SDK认证（Bedrock专用）
- 本地Provider合成认证（无需真实Key）

## 核心文件位置

| 文件 | 功能 |
|------|------|
| `src/config/io.ts` | 配置文件IO、环境变量替换、配置缓存 |
| `src/agents/model-auth.ts` | API Key解析核心逻辑、优先级路由 |
| `src/plugins/provider-api-key-auth.ts` | Provider API Key认证方法创建 |
| `src/config/types.secrets.ts` | Secret引用类型处理 |

## 配置读取时机

### 1. 启动时加载

```
CLI命令/Gateway启动
    ↓
loadConfig() [src/config/io.ts:2193]
    ↓
resolveConfigEnvVars() → 解析 ${ENV_VAR} 语法
    ↓
validateConfigObjectWithPlugins()
    ↓
applyModelDefaults() → 应用模型默认配置
    ↓
配置缓存 (configCache) → 缓存200ms避免重复读取
```

### 2. 运行时刷新

- 支持通过 `setRuntimeConfigSnapshot()` 设置运行时配置快照
- `writeConfigFile()` 写入后触发刷新处理程序
- `OPENCLAW_CONFIG_CACHE_MS` 控制缓存时长（默认200ms）

## API Key 解析流程（核心）

### resolveApiKeyForProvider() - 主入口

```
调用 resolveApiKeyForProvider({ provider, cfg, profileId, ... })
    │
    ├─→ 【优先级1】 指定 Profile ID → 直接读取对应 Profile
    │
    ├─→ 【优先级2】 Auth Profile 遍历（按优先级排序）
    │    └─→ resolveAuthProfileOrder()
    │         └─→ 尝试每个Profile，第一个成功即返回
    │
    ├─→ 【优先级3】 环境变量
    │    └─→ resolveEnvApiKey()
    │         ├─→ ANTHROPIC_API_KEY, OPENAI_API_KEY, etc.
    │         └─→ Shell环境变量回退机制（可选）
    │
    ├─→ 【优先级4】 配置文件 models.providers.*.apiKey
    │    └─→ getCustomProviderApiKey()
    │         └─→ 支持 SecretRef 语法
    │
    ├─→ 【优先级5】 本地Provider合成认证
    │    └─→ 检测到 baseUrl 指向 localhost/127.0.0.1
    │         └─→ 返回合成的 marker（无需真实Key）
    │
    └─→ 【优先级6】 AWS SDK认证（Bedrock专用）
         ├─→ AWS_BEARER_TOKEN_BEDROCK
         ├─→ AWS_ACCESS_KEY_ID + AWS_SECRET_ACCESS_KEY
         └─→ AWS_PROFILE + 默认凭证链
```

## API Key 验证的两层机制

### 关键结论
**API Key 的正确性只会在真正调用大模型时才会被验证！**

配置加载、消息接收时只做"存在性验证"，不做"正确性验证"。

### 1. 配置加载/消息接收时 - 存在性验证

```
配置加载 / CLI启动 / 收到消息
    ↓
resolveApiKeyForProvider()
    ↓
按优先级查找Key来源
    ↓
检查Key是否存在、格式是否合法
    ↓
✅ 返回找到的Key（**不验证是否正确**）
❌ 抛出 "找不到认证" 错误（完全没有Key）
```

**关键点**：
- `resolveApiKeyForProvider` 只检查 **"有没有Key"**，不检查 **"Key对不对"**
- 不会发起任何HTTP请求去验证Key的有效性
- 只要Key存在（或环境变量有值）就通过

### 2. 实际调用LLM时 - 正确性验证

```
收到用户消息 → 准备调用大模型
    ↓
getApiKeyForModel() 获取Key（存在性验证）
    ↓
✅ 有Key → 组装 HTTP 请求头 Authorization: Bearer <key>
    ↓
发起真实 HTTP 请求到 Provider API
    ↓
Provider 返回响应:
    ├─→ 200 OK → Key正确，继续
    ├─→ 401 Unauthorized → 包装为 FailoverError(reason="auth")
    ├─→ 403 Forbidden → 包装为 FailoverError(reason="auth_permanent")
    └─→ 其他错误 → 相应的 failover 处理
```

### 验证时机对照表

| 阶段 | 验证内容 | 是否真正验证正确性 | 错误处理 |
|------|----------|-------------------|----------|
| **配置加载/CLI启动** | Key是否存在 | ❌ 否 | 启动失败，提示配置 |
| **`openclaw doctor`** | 检查是否有配置Key | ❌ 否 | 给出诊断建议 |
| **收到用户消息** | Key是否存在 | ❌ 否 | 快速返回错误 |
| **发起LLM API调用** | Key是否真实有效 | ✅ 是，通过Provider API验证 | 触发Failover机制，尝试下一个Profile/降级 |

### 设计原因

1. **性能**：每次消息都验证Key会增加API Round-Trip延迟
2. **成本**：验证Key通常需要消耗真实API配额
3. **Failover机制**：失败后可以自动切换Profile/Fallback，属于运行时容错设计

### 特殊情况：Live Test

只有 `pnpm test:live` 这类真实API测试时，才会在测试阶段主动验证Key正确性：

```typescript
// 真实发起测试请求，验证Key是否有效
const auth = await resolveApiKeyForProvider({ provider, cfg });
// → 然后用这个Key发起真实API调用测试
```

## 认证存储层级

### 1. Auth Profiles 系统

```
~/.openclaw/agents/<agentId>/auth-profiles.json
    ↓
{
  "profiles": {
    "anthropic:default": {
      "type": "api_key",
      "secret": "sk-ant-...",
      "metadata": {}
    },
    "openai:default": { ... }
  }
}
```

- 每个Agent独立的认证配置
- 支持多种认证类型：`api_key`, `oauth`, `token`
- Profile ID格式：`provider:profileName`

### 2. 配置文件中的API Key

```json
{
  "models": {
    "providers": {
      "anthropic": {
        "apiKey": "${ANTHROPIC_API_KEY}"
      },
      "openai": {
        "apiKey": "sk-..."
      }
    }
  }
}
```

### 3. 环境变量直接读取

支持的环境变量（Shell环境变量回退）：
- `ANTHROPIC_API_KEY`
- `OPENAI_API_KEY`
- `DEEPSEEK_API_KEY`
- `GEMINI_API_KEY`
- 等等...

## 关键机制详解

### 1. 环境变量替换

```typescript
// src/config/io.ts:1330
resolveConfigEnvVars(resolvedIncludes, env, {
  onMissing: (w) => envWarnings.push(w)
})
```

- 配置文件中支持 `${VAR_NAME}` 语法
- 缺失的环境变量仅产生警告，不导致启动失败（降级模式）
- 写回配置文件时保留 `${VAR_NAME}` 引用，不写真实值

### 2. SecretRef 机制

```typescript
// src/config/types.secrets.ts
type SecretRef = {
  $secret: string;      // 引用路径
  $encoding?: string;   // base64等
}
```

- 支持从外部文件/系统读取密钥
- 避免明文存储在配置中

### 3. Shell环境变量回退

```typescript
// src/config/io.ts:1390
loadShellEnvFallback({
  enabled: true,
  env: deps.env,
  expectedKeys: SHELL_ENV_EXPECTED_KEYS,
  // ...
})
```

- 可选机制，通过配置启用
- 解决容器化部署中环境变量传递问题

### 4. 本地Provider无需认证

检测条件：
- `baseUrl` 指向 `localhost`, `127.0.0.1`, `::1`
- 配置了 `api` 和 `models`
- 未显式配置 `apiKey`

→ 自动返回 `CUSTOM_LOCAL_AUTH_MARKER`，无需真实密钥

## 调用链路示例

### 场景1：模型推理时获取Key

```
agent执行推理
    ↓
callModel() / runInference()
    ↓
getApiKeyForModel({ model, cfg, ... }) [model-auth.ts:606]
    ↓
resolveApiKeyForProvider()
    ↓
按优先级尝试各来源 → 返回第一个有效Key
    ↓
注入到HTTP请求头 Authorization: Bearer <key>
```

### 场景2：配置认证时写入Key

```
openclaw models auth <provider>
    ↓
createProviderApiKeyAuthMethod().run()
    ↓
交互式提示输入API Key
    ↓
构建 Api Key Credential
    ↓
upsertAuthProfile() 写入 auth-profiles.json
```

### 场景3：配置文件读取包含环境变量引用

```
loadConfig()
    ↓
读取 openclaw.json: { "anthropic": { "apiKey": "${ANTHROPIC_API_KEY}" } }
    ↓
resolveConfigEnvVars() 替换 ${VAR} 为真实值
    ↓
使用时通过 resolveUsableCustomProviderApiKey() 验证
```

## 安全特性

### 1. 文件权限

```
配置目录：0o700 (drwx------)
配置文件：0o600 (-rw-------)
```

- `tightenStateDirPermissionsIfNeeded()` 自动修正权限
- 写入时使用临时文件 + 原子重命名避免损坏

### 2. 审计日志

- 所有配置写入操作记录审计日志：`config-audit.jsonl`
- 包含：时间戳、PID、前后哈希、可疑原因等
- 异常大小变化、元数据缺失、gateway模式变更均触发警告

### 3. 备份机制

```
writeConfigFile()
    ↓
maintainConfigBackups()
    ↓
保留最近N份备份（轮转机制）
```

### 4. 写回保护

配置文件中的 `${ENV_VAR}` 引用在写回时**被保留**，不会被解析后的真实值替换：
- 读取时解析真实值用于运行
- 写入时通过 `restoreEnvVarRefs()` 恢复引用语法
- 避免明文密钥意外持久化

## 常见问题与边界情况

### 1. 环境变量缺失处理

- 非关键配置引用缺失的环境变量 → 仅警告，继续运行
- 关键Provider认证失败 → 抛出清晰错误，带修复提示

### 2. Docker/容器化部署

- 权限问题（EACCES）→ 给出 chown 修复建议
- 环境变量传递 → Shell环境变量回退机制

### 3. 多Agent隔离

- 每个Agent有独立的 `auth-profiles.json`
- 调用时通过 `agentDir` 参数隔离

### 4. Gateway模式

- Gateway有独立的认证存储
- 客户端API通过Gateway协议获取认证，本地不存密钥

## 性能考量

1. **配置缓存**：默认200ms缓存，避免频繁磁盘IO
2. **惰性解析**：环境变量引用只在真正使用时解析
3. **Profile优先级**：按顺序尝试，第一个成功立即返回

## 调试与排查

启用认证调试日志：
```bash
OPENCLAW_LOG_LEVEL=debug openclaw ...
```

关键日志标记：
- `[xai-auth]` - 认证决策追踪
- `Config overwrite` - 配置写入审计
- `Config observe anomaly` - 配置异常检测
