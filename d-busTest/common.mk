# ================= 公共配置（被各子项目 Makefile 引入）=================
# 使用方式：在子项目 Makefile 中 include $(dir $(lastword $(MAKEFILE_LIST)))../common.mk
# 或者：   include ../../common.mk（根据子项目深度调整路径）

# 安装根目录（默认为项目私有路径，支持外部覆盖）
PREFIX ?= ../../commonsdk

# 头文件和库的标准子目录（符合 GNU 布局规范）
includedir = $(PREFIX)/include
libdir     = $(PREFIX)/lib

# 本机编译器
CC = gcc

# D-Bus 头文件路径（本机 x86_64）
DBUS_CFLAGS = -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include

# D-Bus 链接库
DBUS_LDFLAGS = -ldbus-1
