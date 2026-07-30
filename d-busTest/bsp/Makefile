# ================= BSP 层 Makefile =================
# 引入公共配置
include ../common.mk

# 项目编译配置
CFLAGS = -Iinclude -fPIC -O2 -Wall
CFLAGS += -I$(includedir)
CFLAGS += $(DBUS_CFLAGS)

LDFLAGS = -shared

# 输出动态库名称（编译产物放在本地 build 目录，install 时再拷贝到 PREFIX）
TARGET = build/libscreen_bsp.so

# 源文件
SRCS = src/screen_hal.c
OBJS = $(SRCS:.c=.o)
HEADERS = include/screen_hal.h

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p build
	$(CC) $(LDFLAGS) -o $@ $^ $(DBUS_LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET) $(HEADERS)
	mkdir -p $(DESTDIR)$(includedir)
	install -m 644 $(HEADERS) $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(libdir)
	install -m 644 $(TARGET) $(DESTDIR)$(libdir)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf build

.PHONY: all install clean
