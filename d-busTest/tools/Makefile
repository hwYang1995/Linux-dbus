# ================= Tools 层 Makefile =================
# 引入公共配置
include ../common.mk

# 项目编译配置
CFLAGS = -Iinclude -O2 -Wall -fPIC
CFLAGS += $(DBUS_CFLAGS)

# 项目文件（编译产物放在本地 build 目录，install 时再拷贝到 PREFIX）
TARGET = build/libdbus_wrapper.a
SRCS   = dbus_wrapper.c
OBJS   = $(SRCS:.c=.o)
HEADERS = dbus_wrapper.h

# ================= 构建规则 =================
all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	mkdir -p build
	ar -rcs $@ $^

# ================= 安装规则 =================
install: $(TARGET) $(HEADERS)
	mkdir -p $(DESTDIR)$(includedir)
	install -m 644 $(HEADERS) $(DESTDIR)$(includedir)
	mkdir -p $(DESTDIR)$(libdir)
	install -m 644 $(TARGET) $(DESTDIR)$(libdir)

uninstall:
	rm -f $(addprefix $(DESTDIR)$(includedir)/, $(notdir $(HEADERS)))
	rm -f $(DESTDIR)$(libdir)/libdbus_wrapper.a

# ================= 清理规则 =================
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf build

.PHONY: all clean install uninstall
