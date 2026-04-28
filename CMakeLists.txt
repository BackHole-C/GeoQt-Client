cmake_minimum_required(VERSION 3.16)

# 项目名称：GeoQt-Client (极地地理信息系统)
# 版本：0.1
# 语言：CXX (C++)
project(GeoQt-Client VERSION 0.1 LANGUAGES CXX)

# 启用自动处理：UI文件(.ui)、元对象代码(moc)、资源文件(.qrc)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 设置 C++ 标准为 C++17 (本项目使用了 std::variant, std::optional 等特性)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找依赖：Qt6 或 Qt5 (优先 Qt6)
# 核心组件：Widgets (界面), LinguistTools (多语言翻译工具)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# 定义翻译源文件 (中文)
set(TS_FILES GeoQt-Client_zh_CN.ts)

# 资源文件
set(RESOURCES resources.qrc)

# 项目源码列表
set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        mapcanvas.cpp
        mapcanvas.h
        logindialog.cpp
        logindialog.h
        ${TS_FILES}
        ${RESOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # Qt 6 目标创建
    qt_add_executable(GeoQt-Client
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET GeoQt-Client APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    # 创建翻译文件编译规则 (.ts -> .qm)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    # Qt 5 兼容逻辑
    if(ANDROID)
        add_library(GeoQt-Client SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(GeoQt-Client
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# 链接 Qt Widgets 库
target_link_libraries(GeoQt-Client PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# 针对各平台的特定配置 (如 iOS/macOS 的 Bundle ID, Windows 的可执行类型)
# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.GeoQt-Client)
endif()
set_target_properties(GeoQt-Client PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 安装规则配置
include(GNUInstallDirs)
install(TARGETS GeoQt-Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Qt 6 结束可执行文件定义
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(GeoQt-Client)
endif()
