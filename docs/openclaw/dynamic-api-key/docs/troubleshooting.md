# 故障排查指南

## 常见问题诊断

---

### 问题 1: 插件未被加载

**现象**: `openclaw plugins list` 中看不到 `dynamic-api-key-provider`

**排查步骤**:

```bash
# 1. 检查插件目录是否存在
ls -la extensions/dynamic-api-key-provider/

# 2. 检查插件清单格式
cat extensions/dynamic-api-key-provider/openclaw.plugin.json | jq .

# 3. 查看插件加载日志
OPENCLAW_LOG_LEVEL=debug openclaw plugins list 2>&1 | grep -i plugin

# 4. 重新构建
pnpm build
```

**可能原因**:
- 插件目录不在 `extensions/` 下
- `openclaw.plugin.json` 格式错误
- TypeScript 编译错误
- `type` 字段不是 `"provider"`

---

### 问题 2: 插件返回 Key 但仍然报错

**现象**: 日志显示成功注入 Key，但调用失败

**排查步骤**:

```bash
# 1. 启用调试日志查看完整流程
OPENCLAW_LOG_LEVEL=debug openclaw run --model anthropic:sonnet-4.6 2>&1 \
  | grep -E '(dynamic-auth|xai-auth|api_key|authorization)'

# 2. 检查 Key 是否正确
# 注意: 不要在生产环境打印真实 Key!
console.debug(`Key prefix: ${apiKey.slice(0, 10)}...`);

# 3. 测试 Key 是否有效
curl -X POST https://api.anthropic.com/v1/messages \
  -H "Content-Type: application/json" \
  -H "x-api-key: YOUR_KEY" \
  -d '{"model":"claude-3-sonnet-20240229","max_tokens":1024,"messages":[{"role":"user","content":"Hi"}]}'
```

**可能原因**:
- Key 本身无效或已过期
- Key 没有对应模型的访问权限
- 网络代理问题
- 速率限制（429 Too Many Requests）

---

### 问题 3: Key Manager 超时

**现象**: 日志显示 "Key manager returned 500" 或 "timeout"

**排查步骤**:

```bash
# 1. 测试网络连通性
curl -I --max-time 5 https://key-manager.internal/health

# 2. 测试 API 端点
curl -v "https://key-manager.internal/api/v1/keys/anthropic"

# 3. 检查 DNS
dig key-manager.internal

# 4. 检查代理设置
env | grep -i proxy
```

**优化建议**:
- 增加超时时间（当前 5s）
- 配置备用 Key 列表
- 实现本地缓存持久化

---

### 问题 4: 插件返回 undefined，继续使用配置文件 Key

**现象**: 预期使用动态 Key，但实际使用了配置文件中的静态 Key

**排查步骤**:

```bash
# 1. 检查插件是否启用
openclaw config show plugins.entries.dynamic-api-key-provider

# 2. 检查配置是否正确
# 应该看到 "apiKey": "dynamic://anthropic"
openclaw config show models.providers.anthropic

# 3. 查看插件返回值
OPENCLAW_LOG_LEVEL=debug openclaw ... 2>&1 \
  | grep -A5 -B5 'resolveSyntheticAuth'
```

**可能原因**:
- 插件未启用
- 插件配置缺失
- Key Manager 返回 null 且无备用 Key
- 配置文件中没有使用 `dynamic://` 标记

---

### 问题 5: Gateway 模式下不工作

**现象**: CLI 模式正常，但 Gateway 模式下报错

**排查步骤**:

1. 检查 Gateway 配置目录：`~/.openclaw/gateway/`
2. 确认 Gateway 配置中启用了插件
3. 检查 Gateway 日志：`~/.openclaw/gateway/logs/`
4. 重启 Gateway 服务

```bash
# Gateway 配置示例
{
  "plugins": {
    "entries": {
      "dynamic-api-key-provider": {
        "enabled": true,
        "config": {
          "keyManagerUrl": "..."
        }
      }
    }
  }
}
```

---

## 日志分析

### 正常流程日志

```
[dynamic-auth] resolveSyntheticAuth for anthropic
[dynamic-auth] Successfully injected key for anthropic
[xai-auth] Using synthetic auth for anthropic, source: plugin
[dynamic-auth] prepareRuntimeAuth for anthropic
```

### 异常流程日志

```
# Key Manager 超时
[dynamic-auth] Failed to fetch key for anthropic: The operation was aborted.

# 备用 Key 回退
[dynamic-auth] Falling back to key pool for anthropic

# 完全失败
[dynamic-auth] No valid key found for anthropic, returning undefined
[xai-auth] Trying environment variable ANTHROPIC_API_KEY
[xai-auth] Trying config file apiKey
[xai-auth] All auth methods failed
```

---

## 诊断命令

### 1. 插件状态检查

```bash
#!/bin/bash
# scripts/check-plugin.sh

echo "=== Plugin Status ==="
openclaw plugins list | grep dynamic

echo ""
echo "=== Config Check ==="
openclaw config show plugins.entries.dynamic-api-key-provider

echo ""
echo "=== Provider Config ==="
openclaw config show models.providers.anthropic.apiKey
```

### 2. 认证流程测试

```bash
OPENCLAW_LOG_LEVEL=debug openclaw run \
  --model anthropic:claude-sonnet-4.6 \
  --message "Hi" \
  --no-stream 2>&1 | grep -E '(dynamic-auth|xai-auth|error|Error)'
```

### 3. Key 有效性测试

```typescript
// src/agents/model-auth.spec.ts
// 添加单元测试验证动态 Key 流程

it("should use dynamic api key from plugin", async () => {
  const result = await resolveApiKeyForProvider({
    provider: "anthropic",
    cfg: configWithPluginEnabled,
  });
  expect(result.source).toBe("synthetic");
  expect(result.apiKey).toStartWith("sk-ant-");
});
```

---

## 常见错误码

| HTTP 状态 | 原因 | 解决方案 |
|-----------|------|----------|
| **401** | Key 无效或已撤销 | 1. 检查 Key Manager 返回值<br>2. 验证备用 Key<br>3. 触发缓存刷新 |
| **403** | 权限不足 | 检查 Key 是否有对应模型访问权限 |
| **429** | 速率限制 | 1. 实现 Key 池负载均衡<br>2. 增加重试机制 |
| **500** | Provider 服务端错误 | 等待并重试，检查 Provider 状态页 |
| **502/503/504** | Provider 不可用 | 触发 Failover 切换到备用 Provider |

---

## 性能问题排查

### 高延迟

```bash
# 检查 Key Manager 响应时间
time curl -o /dev/null -s -w "%{http_code} %{time_total}s\n" \
  "https://key-manager.internal/api/v1/keys/anthropic"

# 查看缓存命中率
# 日志中 "Successfully injected key" vs "Failed to fetch key" 的比例
```

**优化**:
- 增加 TTL（缓存时长）
- 实现后台刷新机制
- 部署本地 Key Manager 代理

---

## 联系支持

如果以上步骤无法解决问题，请收集以下信息：

1. OpenClaw 版本：`openclaw --version`
2. 插件版本：`cat extensions/dynamic-api-key-provider/openclaw.plugin.json | jq .version`
3. 调试日志：`OPENCLAW_LOG_LEVEL=debug openclaw ... 2>&1 | tee debug.log`
4. 配置摘要：`openclaw config show | grep -A10 dynamic`
