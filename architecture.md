# GeoQt-Client (极地地理信息系统) 技术架构文档 (v1.0)

## 1. 项目概述
GeoQt-Client 是一个基于 C++17 和 Qt 6 框架开发的桌面级 GIS 客户端。

## 2. 核心模块分解

### 2.1 地图引擎模块 (Map Engine)
- **渲染核心**: 基于 `QPainter` 的瓦片图层合并与覆盖物绘制。
- **坐标系统**: 
  - 经纬度坐标 (WGS84/GCJ02/BD09)
  - 瓦片坐标 (Z/X/Y)
  - 屏幕像素坐标
- **交互控制**: 实现平移 (Pan)、缩放 (Zoom)、可视区域计算。

### 2.2 网络与缓存模块 (Network & Cache)
- **通信层**: 使用 `QNetworkAccessManager` 进行异步瓦片请求及 API 调用。
- **缓存策略**:
  - **内存缓存**: `QCache<QString, QPixmap>` (上限 2048 张)。
  - **请求去重**: `QSet<QString>` 记录正在请求中的瓦片 ID。
  - **空瓦片抑制**: `QSet<QString>` 标记 `m_emptyTiles`，避免对 404/无效区域重复请求。

### 2.3 地理服务集成 (Geo Services)
- **API 适配器**:
  - 高德/百度 API: 地理编码、路径规划 (4 种模式)、POI 搜索。
  - Nominatim: 开源逆地理编码支持。
- **数据管理**: 基于 `std::variant` 统一管理 Marker、Polyline、Polygon、Rectangle、Circle。

### 2.4 坐标转换算法 (Coordinate Transformation)
- 实现 WGS84 (原始 GPS)、GCJ02 (国测局/火星坐标)、BD09 (百度坐标) 的精确互转。

## 3. 技术栈
- **语言**: C++17 (利用 `std::variant`, `std::optional` 等特性)
- **UI 框架**: Qt 6.2+ (Gui, Widgets, Network)
- **构建工具**: CMake 3.16+

## 4. 目录结构设计建议
```text
GIS/
├── src/
│   ├── main.cpp
│   ├── ui/                 # 界面相关 (MainWindow, SidePanel)
│   ├── engine/             # 地图引擎 (MapCanvas, TileManager)
│   ├── network/            # 异步网络封装 (GeoClient)
│   ├── utils/              # 坐标转换、几何算法
│   └── models/             # 数据图元定义 (std::variant 结构)
├── assets/                 # 图标、样式表
└── CMakeLists.txt
```
