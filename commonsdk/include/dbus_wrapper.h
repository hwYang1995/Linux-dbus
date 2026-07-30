#ifndef DBUS_WRAPPER_H
#define DBUS_WRAPPER_H

#include <dbus/dbus.h>

/**
 * @brief 初始化 D-Bus 会话总线连接（自动重连）
 * @return 0=成功, -1=失败
 */
int dbus_init(void);

/**
 * @brief 发送状态信息到指定 D-Bus 接口
 * @param service_name 服务名 (e.g., "org.example.CarDisplay")
 * @param object_path 对象路径 (e.g., "/org/example/DisplayManager")
 * @param interface 接口名 (e.g., "org.example.Display.State")
 * @param signal_name 信号名 (e.g., "ScreenInitialized")
 * @param status_msg 状态字符串 (e.g., "OK" or "ERROR_TIMEOUT")
 * @return 0=成功, -1=失败
 */
int dbus_send_status(const char* service_name,
                     const char* object_path,
                     const char* interface,
                     const char* signal_name,
                     const char* status_msg);

/**
 * @brief 获取当前 D-Bus 连接（供外部注册监听等使用）
 * @return 连接指针，未初始化时返回 NULL
 */
DBusConnection* dbus_get_connection(void);

/**
 * @brief 清理 D-Bus 资源
 */
void dbus_cleanup(void);

#endif // DBUS_WRAPPER_H