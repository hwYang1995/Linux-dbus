#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

/**
 * @brief 初始化显示管理器（注册 D-Bus 信号接收）
 * @return 0=成功, -1=失败
 */
int display_manager_init(void);

/**
 * @brief 处理屏幕状态变更（由 BSP 层回调）
 * @param status 状态字符串 (e.g., "INIT_OK")
 */
void handle_screen_status(const char* status);

#endif // DISPLAY_MANAGER_H