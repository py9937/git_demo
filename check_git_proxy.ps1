Write-Host "🔍 正在检查 Git 和系统代理配置..." -ForegroundColor Cyan

# 检查 Git 全局代理配置
$globalHttp = git config --global --get http.proxy
$globalHttps = git config --global --get https.proxy

# 检查 Git 本地代理配置
$localHttp = git config --local --get http.proxy
$localHttps = git config --local --get https.proxy

# 环境变量代理
$envHttp = $env:HTTP_PROXY
$envHttps = $env:HTTPS_PROXY

# 显示配置
Write-Host "`n🌐 Git 全局配置:"
Write-Host "  http.proxy  = $globalHttp"
Write-Host "  https.proxy = $globalHttps"

Write-Host "`n📁 当前仓库本地配置:"
Write-Host "  http.proxy  = $localHttp"
Write-Host "  https.proxy = $localHttps"

Write-Host "`n💻 环境变量:"
Write-Host "  HTTP_PROXY  = $envHttp"
Write-Host "  HTTPS_PROXY = $envHttps"

# 检查 VS Code 设置（可选）
$settingsPath = "$env:APPDATA\Code\User\settings.json"
if (Test-Path $settingsPath) {
    Write-Host "`n🛠️ VS Code 设置:"
    $vscodeSettings = Get-Content $settingsPath | Out-String
    if ($vscodeSettings -match '"http\.proxy"\s*:\s*"([^"]+)"') {
        $proxy = $Matches[1]
        Write-Host "  VS Code http.proxy = $proxy"
    } else {
        Write-Host "  未设置 http.proxy"
    }
}

# 提示是否清除代理
$shouldClean = Read-Host "`n❓ 是否要清除所有代理配置？(y/n)"
if ($shouldClean -eq "y") {
    Write-Host "`n🧹 正在清除代理配置..." -ForegroundColor Yellow

    git config --global --unset http.proxy
    git config --global --unset https.proxy
    git config --local --unset http.proxy
    git config --local --unset https.proxy

    Remove-Item Env:HTTP_PROXY -ErrorAction SilentlyContinue
    Remove-Item Env:HTTPS_PROXY -ErrorAction SilentlyContinue

    Write-Host "✅ 已清除 Git 配置和环境变量中的代理设置。" -ForegroundColor Green
} else {
    Write-Host "⚠️ 未进行任何清除操作。" -ForegroundColor DarkYellow
}

Write-Host "`n✅ 检查完成。" -ForegroundColor Cyan