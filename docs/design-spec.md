# OrangixToolkits - 组件设计规范

## 1. GlassPanel

### 属性
- `blurRadius`: qreal (default: 20.0)
- `tintColor`: QColor (default: rgba(255,255,255,0.15))
- `borderColor`: QColor (default: rgba(255,255,255,0.3))
- `cornerRadius`: int (default: 12)

### 渲染层次
1. 模糊层（背景内容模糊）
2. 着色层（半透明颜色叠加）
3. 边框层（1px 高光边框）
4. 顶部高光线（0.5px 白色）

## 2. AnimatedButton

### 状态
| 状态 | 背景 | 缩放 | 阴影 |
|------|------|------|------|
| Normal | transparent | 1.0 | none |
| Hover | rgba(255,255,255,0.08) | 1.02 | soft glow |
| Pressed | rgba(255,255,255,0.15) | 0.98 | none |
| Disabled | rgba(128,128,128,0.05) | 1.0 | none |

### 动画
- hover 过渡：150ms ease-out
- press 过渡：80ms ease-in

## 3. NotificationToast

### 布局
```
┌───────────────────────────────┐
│ [icon]  Title                 │
│         Description text...   │
│                     [Action]  │
└───────────────────────────────┘
```

### 尺寸
- 宽度：320px
- 最小高度：64px
- 圆角：12px
- 右侧边距：16px（距屏幕边缘）
- 顶部边距：48px（在 Top Bar 下方）

### 动画
- 弹入：从右侧滑入 300ms ease-out
- 消失：向右滑出 200ms ease-in
- 自动消失：5秒后

## 4. SearchBar

### 尺寸
- 高度：36px
- 圆角：18px（全圆角）

### 样式
- 默认：rgba(255,255,255,0.08) 背景
- 聚焦：宽度展开动画 + 边框发光

## 5. 通用间距

所有组件遵循 4px 基础栅格：
- 内边距：8px / 12px / 16px
- 组件间距：8px / 12px / 16px / 24px
- 节区间距：24px / 32px
