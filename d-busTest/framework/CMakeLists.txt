cmake_minimum_required(VERSION 3.10)
project(CarDisplayFramework)

# ================= 公共路径配置 =================
# SDK 输出目录（与 Makefile 的 PREFIX 保持一致）
set(COMMONSDK_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../commonsdk")

# 编译器配置（本机编译，如需交叉编译可在此覆盖）
# set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
# set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# 头文件搜索路径
include_directories(
    include
    ${COMMONSDK_DIR}/include
    /usr/include/dbus-1.0
    /usr/lib/x86_64-linux-gnu/dbus-1.0/include
)

# 编译中间件
add_executable(display_framework
    src/main.c
    src/display_manager.c
)

# 链接预编译库（由 tools 层和 BSP 层提供）
target_link_libraries(display_framework PRIVATE
    ${COMMONSDK_DIR}/lib/libdbus_wrapper.a
    ${COMMONSDK_DIR}/lib/libscreen_bsp.so
    dbus-1
)
