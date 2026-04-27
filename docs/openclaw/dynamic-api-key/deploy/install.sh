#!/bin/bash
#
# 动态 API Key Provider 插件安装脚本
#
# 使用方法:
#   ./deploy/install.sh /path/to/openclaw/repo
#

set -euo pipefail

REPO_DIR="${1:-$(pwd)}"
PLUGIN_NAME="dynamic-api-key-provider"
PLUGIN_SRC_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
EXT_DIR="$REPO_DIR/extensions/$PLUGIN_NAME"

echo "========================================"
echo "  动态 API Key Provider 插件安装"
echo "========================================"
echo ""
echo "源码目录: $PLUGIN_SRC_DIR"
echo "目标目录: $EXT_DIR"
echo ""

# 1. 检查目录
if [ ! -d "$REPO_DIR/.git" ]; then
  echo "❌ 错误: $REPO_DIR 不是 Git 仓库"
  exit 1
fi

# 2. 创建插件目录
echo "📁 创建插件目录..."
mkdir -p "$EXT_DIR/src"
mkdir -p "$EXT_DIR/deploy"

# 3. 复制文件
echo "📋 复制插件文件..."
cp "$PLUGIN_SRC_DIR/openclaw.plugin.json" "$EXT_DIR/"
cp "$PLUGIN_SRC_DIR/src/index.ts" "$EXT_DIR/src/"
cp "$PLUGIN_SRC_DIR/deploy/config.example.json" "$EXT_DIR/deploy/"

# 4. 创建 package.json
echo "📦 创建 package.json..."
cat > "$EXT_DIR/package.json" << 'EOF'
{
  "name": "dynamic-api-key-provider",
  "version": "1.0.0",
  "description": "运行时动态注入 API Key 的 Provider 插件",
  "type": "module",
  "main": "src/index.ts",
  "keywords": [
    "openclaw",
    "openclaw-plugin",
    "openclaw-provider"
  ],
  "author": "",
  "license": "MIT",
  "devDependencies": {
    "openclaw": "workspace:*"
  }
}
EOF

# 5. 创建 tsconfig.json
echo "⚙️ 创建 tsconfig.json..."
cat > "$EXT_DIR/tsconfig.json" << 'EOF'
{
  "extends": "../../tsconfig.json",
  "compilerOptions": {
    "outDir": "dist",
    "rootDir": "src"
  },
  "include": ["src/**/*"]
}
EOF

echo ""
echo "✅ 插件文件已复制完成!"
echo ""
echo "下一步:"
echo ""
echo "  1. 安装依赖:"
echo "     cd $REPO_DIR"
echo "     pnpm install"
echo ""
echo "  2. 构建:"
echo "     pnpm build"
echo ""
echo "  3. 配置插件:"
echo "     mkdir -p ~/.openclaw"
echo "     cp $EXT_DIR/deploy/config.example.json ~/.openclaw/config.json"
echo "     # 编辑配置文件，设置你的密钥管理服务地址"
echo ""
echo "  4. 验证安装:"
echo "     openclaw plugins list"
echo "     openclaw doctor"
echo ""
echo "========================================"
