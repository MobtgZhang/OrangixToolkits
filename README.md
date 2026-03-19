# Orangix Toolkits

Orangix UI 组件库 + 系统应用集合。

## UI 组件库 (liborangix-toolkit)

实现 Citrus Design Language 的 Qt 组件：

- **GlassPanel** — Aero 毛玻璃面板
- **BlurBackground** — 实时模糊背景容器
- **AnimatedButton** — hover 发光 + press 缩放动画按钮
- **NotificationToast** — 滑入式通知弹窗
- **SearchBar** — 聚焦展开搜索栏
- **SideBar** — 导航侧边栏

## 构建

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/qt6
make -j$(nproc)
```

## 依赖

- Qt 6.x (Core, Gui, Widgets)
- CMake 3.16+
- C++17 编译器
