# Orangix Toolkits - 架构设计文档

## 1. 项目概述

OrangixToolkits 包含两个核心部分：
1. **Orangix UI Kit** — 统一的 Qt 组件库，实现 Citrus Design Language
2. **Orangix Apps** — 基于 UI Kit 的系统应用

## 2. UI 组件库（Orangix UI Kit）

### 核心组件

| 组件 | 说明 | 特色 |
|------|------|------|
| GlassPanel | 毛玻璃面板 | Aero 风格半透明+模糊 |
| BlurBackground | 模糊背景容器 | GPU 加速高斯模糊 |
| AnimatedButton | 动画按钮 | hover 发光 + 按下反馈 |
| GlowButton | 发光按钮 | 柔和光晕效果 |
| NotificationToast | 通知弹窗 | 右上角弹入 + 自动消失 |
| RoundedCard | 圆角卡片 | 统一阴影 + 圆角 |
| SearchBar | 搜索栏 | 圆角 + 聚焦动画 |

### 设计规范常量
```cpp
namespace Orangix::Style {
    constexpr int RadiusSmall = 8;
    constexpr int RadiusMedium = 12;
    constexpr int RadiusLarge = 16;
    constexpr int RadiusXLarge = 20;

    constexpr int AnimHover = 150;   // ms
    constexpr int AnimPanel = 200;   // ms
    constexpr int AnimWindow = 250;  // ms

    const QColor BrandOrange("#FF8C42");
    const QColor BrandDark("#2D2D2D");
}
```

## 3. 系统应用

### 3.1 Orangix Files（文件管理器）
- 双栏布局（侧边栏 + 内容区）
- 面包屑导航
- 图标视图 / 列表视图 / 详情视图
- 文件预览面板
- Aero 风格侧边栏（毛玻璃）

### 3.2 Orangix Terminal（终端）
- GPU 加速渲染
- 毛玻璃半透明背景
- 标签页支持
- 分屏
- 主题系统

### 3.3 Orangix Settings（设置中心）
- 分类侧边栏
- 外观设置（壁纸、主题、颜色）
- 显示设置（分辨率、多屏）
- 网络设置
- 用户管理
- 系统信息

### 3.4 Orangix Launcher（应用启动器）
- 全屏启动器（类似 macOS Launchpad）
- 搜索过滤
- 应用分类
- 最近使用

## 4. 模块架构

```
OrangixToolkits/
├── src/
│   ├── components/      # UI Kit 核心组件
│   │   ├── GlassPanel.h/cpp
│   │   ├── BlurBackground.h/cpp
│   │   ├── AnimatedButton.h/cpp
│   │   ├── NotificationToast.h/cpp
│   │   └── OrangixStyle.h
│   ├── widgets/         # 复合组件
│   │   ├── SideBar.h/cpp
│   │   └── SearchBar.h/cpp
│   └── apps/
│       ├── file-manager/
│       ├── terminal/
│       ├── settings/
│       └── launcher/
├── resources/
│   └── icons/
└── docs/
```

## 5. 编译方式

UI Kit 编译为共享库 `liborangix-toolkit.so`，系统应用链接该库。

## 6. 依赖

- Qt 6.x（Core, Gui, Widgets）
- OrangixDesktop（BlurEffect, AnimationHelper 可复用）
