#include "display_manager.h"
#include "screen_hal.h"
#include "dbus_wrapper.h"
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

static volatile bool g_running = true;

static void _on_signal(int sig) {
    (void)sig;
    g_running = false;
}

int main(void) {
    signal(SIGINT,  _on_signal);
    signal(SIGTERM, _on_signal);

    /* 1. 启动 Framework 层：初始化 D-Bus 并注册信号监听 */
    printf("[Main] 启动显示框架...\n");
    if (display_manager_init() != 0) {
        fprintf(stderr, "[Main] 框架初始化失败\n");
        return -1;
    }

    /* 2. 初始化 BSP 层：屏幕硬件上电并上报状态 */
    printf("[Main] 触发 BSP 屏幕初始化...\n");
    int ret = screen_hal_init();
    if (ret != 0) {
        fprintf(stderr, "[Main] 屏幕初始化失败\n");
    }

    /* 3. 主事件循环：轮询 D-Bus 消息 */
    printf("[Main] 进入事件循环 (Ctrl+C 退出)...\n");
    DBusConnection* conn = dbus_get_connection();
    while (g_running) {
        dbus_connection_read_write_dispatch(conn, 100); /* 100ms 超时 */
    }

    /* 4. 清理退出 */
    printf("\n[Main] 正在退出...\n");
    dbus_cleanup();
    return 0;
}
