import { defineProviderPlugin } from "openclaw/plugin-sdk";
import type {
  ProviderResolveSyntheticAuthContext,
  ProviderResolveConfigApiKeyContext,
  ProviderPrepareRuntimeAuthContext,
} from "openclaw/plugin-sdk/provider";

/**
 * 缓存条目结构
 */
interface KeyCacheEntry {
  key: string;
  expiresAt: number;
}

/**
 * 插件配置结构
 */
interface PluginConfig {
  keyManagerUrl?: string;
  cacheTtl?: number;
  fallbackKeys?: string[];
}

// 内存缓存 - Key 仅在内存中，不持久化
const keyCache = new Map<string, KeyCacheEntry>();

/**
 * 从密钥管理服务动态获取 API Key
 *
 * 可替换为实际的密钥管理系统：
 * - HashiCorp Vault
 * - AWS Secrets Manager
 * - Azure Key Vault
 * - 企业内部密钥管理服务
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
      // 超时保护，避免阻塞用户请求
      signal: AbortSignal.timeout(5000),
    });

    if (!response.ok) {
      console.warn(
        `[dynamic-auth] Key manager returned ${response.status} for ${provider}`
      );
      return null;
    }

    const data = await response.json();
    return data.apiKey || data.key || null;
  } catch (error) {
    console.warn(
      `[dynamic-auth] Failed to fetch key for ${provider}:`,
      error instanceof Error ? error.message : String(error)
    );
    return null;
  }
}

/**
 * 获取缓存的 Key 或刷新
 *
 * 实现：
 * 1. 首先尝试从内存缓存获取
 * 2. 缓存未命中或过期时，从 Key Manager 拉取
 * 3. Manager 不可用时，回退到备用 Key 列表
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
    const freshKey = await fetchApiKeyFromManager(
      provider,
      config.keyManagerUrl
    );
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
    const fallbackIndex =
      Math.floor(now / 60000) % config.fallbackKeys.length;
    return config.fallbackKeys[fallbackIndex];
  }

  return null;
}

/**
 * 动态 API Key Provider 插件
 *
 * 通过 resolveSyntheticAuth 钩子完全接管认证流程
 * 实现"配置留空 + 运行时动态注入"
 */
export default defineProviderPlugin({
  /**
   * resolveSyntheticAuth - 合成认证钩子
   *
   * 🔑 优先级最高，在所有其他认证方式之前执行
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
      console.debug(
        `[dynamic-auth] Successfully injected key for ${provider}`
      );
      return { apiKey };
    }

    // 返回 undefined 让系统继续尝试其他认证方式
    // （环境变量、配置文件、Profile 等）
    return undefined;
  },

  /**
   * resolveConfigApiKey - 配置 API Key 解析钩子
   *
   * 在配置文件解析阶段调用，用于处理自定义的 Key 格式
   *
   * 支持标记语法：
   * - "dynamic://anthropic"
   * - "dynamic://openai"
   *
   * 返回空字符串表示继续到 resolveSyntheticAuth 阶段
   */
  resolveConfigApiKey(
    context: ProviderResolveConfigApiKeyContext
  ): string | undefined {
    const { provider, apiKeyConfig } = context;

    if (
      typeof apiKeyConfig === "string" &&
      apiKeyConfig.startsWith("dynamic://")
    ) {
      console.debug(
        `[dynamic-auth] resolveConfigApiKey for ${provider} with dynamic marker`
      );
      // 返回空字符串让系统继续到 resolveSyntheticAuth 阶段
      // 系统会认为"有配置"，但实际 Key 由 resolveSyntheticAuth 注入
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
    _context: ProviderPrepareRuntimeAuthContext
  ): Promise<void> {
    const { provider } = _context;

    console.debug(`[dynamic-auth] prepareRuntimeAuth for ${provider}`);

    // 可扩展的认证处理逻辑：
    //
    // 1. 添加时间戳签名
    //    context.extraHeaders = {
    //      "X-Timestamp": Date.now().toString(),
    //      "X-Signature": calculateSignature(credential.apiKey)
    //    }
    //
    // 2. 检查 Key 是否即将过期并刷新
    //    if (isKeyExpiringSoon(credential.apiKey)) {
    //      await refreshKeyInBackground(provider);
    //    }
    //
    // 3. 记录认证审计日志
    //    auditLog('api_key_used', { provider, requestId: ... })
  },

  /**
   * buildMissingAuthMessage - 自定义认证缺失提示
   *
   * 当所有认证方式都失败时，给用户友好的提示
   */
  buildMissingAuthMessage(context: { provider: string }) {
    return {
      message: `
动态 API Key 插件已启用但无法获取有效密钥

Provider: ${context.provider}

可能原因：
1. 密钥管理服务不可达或超时
2. 备用 Key 列表为空或全部失效
3. 插件配置不正确或未启用

修复步骤：
1. 检查插件配置:
   openclaw config show plugins.dynamic-api-key-provider

2. 验证密钥管理服务状态:
   curl -I https://key-manager.internal/health

3. 查看详细日志:
   OPENCLAW_LOG_LEVEL=debug openclaw run --model ${context.provider}:...

4. 测试纯环境变量回退:
   ANTHROPIC_API_KEY=sk-ant-xxx openclaw run --model anthropic:sonnet-4.6
      `.trim(),
    };
  },
});
