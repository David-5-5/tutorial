# 动态 API Key Provider 插件方案

## 概述

本方案展示如何通过自定义 Provider 插件完全接管 OpenClaw 的 API Key 获取逻辑，实现"配置留空 + 运行时动态注入"的认证模式。

**核心优势：**
- ✅ 无需在配置文件中存储明文 API Key
- ✅ 运行时动态获取/刷新/轮换 Key
- ✅ 支持多租户、密钥管理服务集成
- ✅ 统一的认证审计和流量控制

---

## 目录结构

```
code-analysis/dynamic-api-key/
├── README.md                    # 本文档
├── openclaw.plugin.json         # 插件清单
├── src/
│   └── index.ts                 # 插件入口
├── deploy/
│   ├── install.sh               # 安装脚本
│   └── config.example.json      # 配置示例
└── docs/
    ├── architecture.md          # 架构详解
    └── troubleshooting.md       # 故障排查
```

---

## 完整代码实现

### 1. 插件清单 `openclaw.plugin.json`

```json
{
  "id": "dynamic-api-key-provider",
  "name": "Dynamic API Key Provider",
  "version": "1.0.0",
  "description": "运行时动态注入 API Key 的 Provider 插件",
  "type": "provider",

  "pluginSdkVersion": "^0.98.0",

  "providers": [
    {
      "id": "anthropic",
      "name": "Anthropic (Dynamic Key)",
      "capabilities": ["chat", "tools", "thinking"]
    },
    {
      "id": "openai",
      "name": "OpenAI (Dynamic Key)",
      "capabilities": ["chat", "tools", "vision"]
    }
  ],

  "configSchema": {
    "type": "object",
    "properties": {
      "keyManagerUrl": {
        "type": "string",
        "description": "密钥管理服务地址"
      },
      "cacheTtl": {
        "type": "number",
        "description": "Key 缓存时长（秒）",
        "default": 300
      },
      "fallbackKeys": {
        "type": "array",
        "description": "备用 Key 列表"
      }
    }
  }
}
```

### 2. 插件入口 `src/index.ts`

```typescript
import { defineProviderPlugin } from "openclaw/plugin-sdk";
import type {
  ProviderResolveSyntheticAuthContext,
  ProviderResolveConfigApiKeyContext,
  ProviderPrepareRuntimeAuthContext,
} from "openclaw/plugin-sdk/provider";

interface KeyCacheEntry {
  key: string;
  expiresAt: number;
}

interface PluginConfig {
  keyManagerUrl?: string;
  cacheTtl?: number;
  fallbackKeys?: string[];
}

// 内存缓存
const keyCache = new Map<string, KeyCacheEntry>();

/**
 * 从密钥管理服务动态获取 API Key
 * 可替换为：HashiCorp Vault、AWS Secrets Manager、内部服务等
 */
async function fetchApiKeyFromManager(
  provider: string,
  keyManagerUrl: string
): Promise<string | null> {
  try {
    const response = await fetch(`${keyManagerUrl}/api/v1/keys/${provider}`, {
      headers: {
        "X-Request-ID": crypto.randomUUID(),
      },
      timeout: 5000,
    });

    if (!response.ok) {
      console.warn(`[dynamic-auth] Key manager returned ${response.status} for ${provider}`);
      return null;
    }

    const data = await response.json();
    return data.apiKey || data.key || null;
  } catch (error) {
    console.warn(`[dynamic-auth] Failed to fetch key for ${provider}:`, error);
    return null;
  }
}

/**
 * 获取缓存的 Key 或刷新
 */
async function getCachedOrRefreshKey(
  provider: string,
  config: PluginConfig
): Promise<string | null> {
  const cacheEntry = keyCache.get(provider);
  const now = Date.now();

  // 缓存命中且未过期
  if (cacheEntry && now < cacheEntry.expiresAt) {
    return cacheEntry.key;
  }

  // 尝试从 Key Manager 获取
  if (config.keyManagerUrl) {
    const freshKey = await fetchApiKeyFromManager(provider, config.keyManagerUrl);
    if (freshKey) {
      keyCache.set(provider, {
        key: freshKey,
        expiresAt: now + (config.cacheTtl || 300) * 1000,
      });
      return freshKey;
    }
  }

  // 回退到备用 Key 列表（轮询方式）
  if (config.fallbackKeys && config.fallbackKeys.length > 0) {
    const fallbackIndex = Math.floor(now / 60000) % config.fallbackKeys.length;
    return config.fallbackKeys[fallbackIndex];
  }

  return null;
}

export default defineProviderPlugin({
  /**
   * resolveSyntheticAuth - 合成认证钩子
   *
   * 优先级最高，在所有其他认证方式之前执行
   * 返回非空值即可完全接管认证流程
   *
   * 调用时机：配置规范化、消息接收时
   */
  async resolveSyntheticAuth(
    context: ProviderResolveSyntheticAuthContext
  ): Promise<{ apiKey: string } | undefined> {
    const { provider, config } = context;

    console.debug(`[dynamic-auth] resolveSyntheticAuth for ${provider}`);

    const pluginConfig = config?.plugins?.["dynamic-api-key-provider"] as
      | PluginConfig
      | undefined;

    if (!pluginConfig) {
      return undefined;
    }

    const apiKey = await getCachedOrRefreshKey(provider, pluginConfig);

    if (apiKey) {
      console.debug(`[dynamic-auth] Successfully injected key for ${provider}`);
      return { apiKey };
    }

    // 返回 undefined 让系统继续尝试其他认证方式
    return undefined;
  },

  /**
   * resolveConfigApiKey - 配置 API Key 解析钩子
   *
   * 在配置文件解析阶段调用，用于处理自定义的 Key 格式
   * 优先级：配置中的 apiKey 字段被此钩子处理
   */
  resolveConfigApiKey(
    context: ProviderResolveConfigApiKeyContext
  ): string | undefined {
    const { provider, apiKeyConfig } = context;

    // 支持特殊格式："dynamic://provider-name"
    if (typeof apiKeyConfig === "string" && apiKeyConfig.startsWith("dynamic://")) {
      console.debug(`[dynamic-auth] resolveConfigApiKey for ${provider} with dynamic marker`);
      // 返回空字符串让系统继续到 resolveSyntheticAuth 阶段
      // 或者在这里直接返回真实 Key
      return "";
    }

    return undefined;
  },

  /**
   * prepareRuntimeAuth - 运行时认证准备钩子
   *
   * 在真正发起 API 调用前最后一次机会调整认证
   * 可用于：签名、临时 Token、Header 注入等
   */
  async prepareRuntimeAuth(
    context: ProviderPrepareRuntimeAuthContext
  ): Promise<void> {
    const { provider, credential } = context;

    console.debug(`[dynamic-auth] prepareRuntimeAuth for ${provider}`);

    // 可以在这里添加额外的认证处理：
    // - 添加时间戳签名
    // - 注入额外的 HTTP Header
    // - 检查 Key 是否即将过期并刷新
    // - 记录认证审计日志
  },

  /**
   * buildMissingAuthMessage - 自定义认证缺失提示
   */
  buildMissingAuthMessage(context: { provider: string }) {
    return {
      message: `
动态 API Key 插件已启用但无法获取有效密钥

可能原因：
1. 密钥管理服务 (${context.provider}) 不可达
2. 备用 Key 列表为空或全部失效
3. 插件配置不正确

修复步骤：
1. 检查插件配置: openclaw config show plugins.dynamic-api-key-provider
2. 验证密钥管理服务状态
3. 查看日志: OPENCLAW_LOG_LEVEL=debug openclaw ...
      `.trim(),
    };
  },
});
```

---

## 部署指南

### 前置条件

1. OpenClaw v0.98.0+
2. Node.js 22+
3. pnpm 或 npm

### 步骤 1: 安装插件

```bash
# 1. 将插件复制到 extensions 目录
cp -r code-analysis/dynamic-api-key/* extensions/dynamic-api-key-provider/

# 2. 安装插件依赖
cd extensions/dynamic-api-key-provider
pnpm install

# 3. 返回根目录并构建
cd ../..
pnpm build
```

### 步骤 2: 配置插件

创建或编辑 `~/.openclaw/config.json`:

```json
{
  "models": {
    "providers": {
      "anthropic": {
        "apiKey": "dynamic://anthropic"
      },
      "openai": {
        "apiKey": "dynamic://openai"
      }
    }
  },
  "plugins": {
    "entries": {
      "dynamic-api-key-provider": {
        "enabled": true,
        "config": {
          "keyManagerUrl": "https://key-manager.internal",
          "cacheTtl": 300,
          "fallbackKeys": [
            "sk-ant-fallback-1",
            "sk-ant-fallback-2"
          ]
        }
      }
    }
  }
}
```

### 步骤 3: 验证安装

```bash
# 检查插件是否加载
openclaw plugins list

# 检查模型配置
openclaw models list

# 运行诊断
openclaw doctor
```

### 步骤 4: 测试认证

```bash
# 启用调试日志查看认证流程
OPENCLAW_LOG_LEVEL=debug openclaw run --model anthropic:claude-sonnet-4.6
```

---

## 使用场景

### 场景 1: 密钥管理服务集成

适用于企业级密钥管理系统（HashiCorp Vault, AWS Secrets Manager, Azure Key Vault）。

**优势：**
- 密钥集中管理、自动轮换
- 细粒度权限控制
- 完整的审计日志

### 场景 2: 多租户/多项目隔离

不同团队/项目使用不同的 API Key，按流量动态分配。

```typescript
// 扩展示例：按 Agent ID 路由 Key
async resolveSyntheticAuth(context) {
  const { provider, agentDir } = context;
  const agentId = path.basename(agentDir);
  
  // 根据 Agent ID 获取对应的 Key
  return getKeyForAgent(provider, agentId);
}
```

### 场景 3: Key 池与负载均衡

多个 API Key 组成池，按轮询/权重方式分配，实现负载均衡和配额管理。

### 场景 4: 临时凭证与 OAuth

对接 OAuth2.0 或 STS 服务获取短期访问凭证。

---

## 调用时序图

```
用户消息到达
    ↓
resolveApiKeyForProvider()
    ↓
[优先级 1] Auth Profile
    ↓ (无匹配)
[优先级 2] 插件 resolveSyntheticAuth() ← 我们的插件在这里
    ↓ (返回 Key)
验证 Key 存在性 ✓
    ↓
准备 API 调用
    ↓
prepareRuntimeAuth() ← 最后一次调整机会
    ↓
真正发起 HTTP 请求
    ↓
Provider 验证 Key 正确性
    ↓
返回响应 / 401 触发 Failover
```

---

## 完整认证优先级

```
┌─────────────────────────────────────────────────┐
│ 1. 指定 Profile ID                  (最高优先级) │
├─────────────────────────────────────────────────┤
│ 2. Auth Profile 遍历                            │
├─────────────────────────────────────────────────┤
│ 3. 插件 resolveSyntheticAuth()    ← 我们的插件  │
├─────────────────────────────────────────────────┤
│ 4. 环境变量 (ANTHROPIC_API_KEY)                │
├─────────────────────────────────────────────────┤
│ 5. 配置文件 apiKey                              │
├─────────────────────────────────────────────────┤
│ 6. 本地 Provider 合成认证                       │
├─────────────────────────────────────────────────┤
│ 7. AWS SDK 认证 (Bedrock 专用)     (最低优先级) │
└─────────────────────────────────────────────────┘
```

---

## 最佳实践

### 1. 缓存策略

- **必须启用缓存**：避免每次请求都调用 Key Manager
- **合理 TTL**：5-15 分钟（根据安全要求调整）
- **后台刷新**：接近过期时异步刷新，不阻塞用户请求

### 2. 降级方案

- **备用 Key 列表**：主服务不可用时的降级
- **本地缓存持久化**：即使重启也能使用缓存的 Key
- **渐进式降级**：从动态 → 静态 → 错误提示

### 3. 可观测性

```typescript
// 建议添加的指标
console.info(`[dynamic-auth] key_used provider=${provider} source=${source} latency=${latency}ms`);
console.warn(`[dynamic-auth] key_refresh provider=${provider} reason=${reason}`);
```

### 4. 安全加固

- Key Manager 通信必须使用 HTTPS
- 开启双向 TLS 认证
- 内存中的 Key 不写入日志
- 定期轮换 Key

---

## 常见问题

**Q: 插件返回的 Key 会被持久化吗？**
A: 不会。`resolveSyntheticAuth` 返回的 Key 仅在内存中使用，不会写入配置文件或磁盘。

**Q: 如果插件获取 Key 失败会怎样？**
A: 系统会自动降级，继续尝试后续的认证方式（环境变量、配置文件等）。

**Q: 如何调试认证流程？**
A: 使用 `OPENCLAW_LOG_LEVEL=debug` 启动，搜索 `[dynamic-auth]` 和 `[xai-auth]` 日志标记。

**Q: 可以同时为多个 Provider 注入 Key 吗？**
A: 可以。插件会接收 `provider` 参数，根据不同 Provider 返回对应的 Key。

---

## 参考源码位置

| 功能 | 文件 |
|------|------|
| 合成认证钩子 | `src/plugins/provider-runtime.ts:498-506` |
| API Key 解析核心 | `src/agents/model-auth.ts` |
| Provider 插件 SDK | `src/plugin-sdk/provider-entry.ts` |
| 配置规范化 | `src/agents/models-config.providers.secrets.ts` |

---

## 下一步

1. 根据实际密钥管理服务修改 `fetchApiKeyFromManager()`
2. 添加错误处理和重试逻辑
3. 集成监控和告警
4. 编写单元测试

**文档版本**: 1.0.0  
**最后更新**: 2026-04-27
