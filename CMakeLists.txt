cmake_minimum_required(VERSION 3.16)
project(OrangixToolkits VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# === Orangix UI Kit (shared library) ===

set(TOOLKIT_SOURCES
    src/components/GlassPanel.cpp
    src/components/BlurBackground.cpp
    src/components/AnimatedButton.cpp
    src/components/NotificationToast.cpp
    src/widgets/SearchBar.cpp
    src/widgets/SideBar.cpp
)

set(TOOLKIT_HEADERS
    src/components/OrangixStyle.h
    src/components/GlassPanel.h
    src/components/BlurBackground.h
    src/components/AnimatedButton.h
    src/components/NotificationToast.h
    src/widgets/SearchBar.h
    src/widgets/SideBar.h
)

set(RESOURCES
    resources/icons.qrc
)

add_library(orangix-toolkit SHARED ${TOOLKIT_SOURCES} ${TOOLKIT_HEADERS} ${RESOURCES})

target_include_directories(orangix-toolkit PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(orangix-toolkit PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

set_target_properties(orangix-toolkit PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 0
    OUTPUT_NAME orangix-toolkit
)

install(TARGETS orangix-toolkit LIBRARY DESTINATION lib)
install(FILES ${TOOLKIT_HEADERS} DESTINATION include/orangix-toolkit)
