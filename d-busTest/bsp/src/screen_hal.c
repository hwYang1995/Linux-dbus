#include "screen_hal.h"
#include "dbus_wrapper.h"
#include <string.h>
#include <unistd.h>

int screen_hal_init(void) {
    // 1. 执行屏幕硬件初始化（此处简化为模拟操作）
    printf("[BSP] 初始化屏幕控制器...\n");
    sleep(2); // 模拟硬件延迟
    
    // 2. 上报状态（成功/失败由实际硬件决定）
    const char* status = (rand() % 2 == 0) ? "INIT_OK" : "ERROR_TIMEOUT";
    screen_report_status(status);
    return (strcmp(status, "INIT_OK") == 0) ? 0 : -1;
}

void screen_report_status(const char* status) {
    // 调用 D-Bus 封装库发送状态
    dbus_send_status(
        "org.example.CarDisplay",          // 服务名
        "/org/example/DisplayManager",     // 对象路径
        "org.example.Display.State",       // 接口名
        "ScreenInitialized",               // 信号名
        status                            // 状态字符串
    );
}