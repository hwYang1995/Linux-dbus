#include "display_manager.h"
#include "dbus_wrapper.h"
#include <stdio.h>

/* D-Bus 信号回调（内部，桥接到公共接口） */
static DBusHandlerResult _on_screen_signal(DBusConnection* conn,
                                           DBusMessage* msg,
                                           void* user_data) {
    (void)conn;
    (void)user_data;

    if (dbus_message_get_type(msg) != DBUS_MESSAGE_TYPE_SIGNAL)
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    DBusMessageIter args;
    if (!dbus_message_iter_init(msg, &args))
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    if (dbus_message_iter_get_arg_type(&args) != DBUS_TYPE_STRING)
        return DBUS_HANDLER_RESULT_NOT_YET_HANDLED;

    const char* status;
    dbus_message_iter_get_basic(&args, &status);

    /* 转发给公共业务接口 */
    handle_screen_status(status);
    return DBUS_HANDLER_RESULT_HANDLED;
}

int display_manager_init(void) {
    if (dbus_init() != 0) return -1;

    /* 获取 D-Bus 连接，注册监听 BSP 层发送的屏幕状态信号 */
    DBusConnection* conn = dbus_get_connection();
    if (!conn) return -1;

    dbus_bus_add_match(conn,
        "type='signal',interface='org.example.Display.State'",
        NULL);
    dbus_connection_add_filter(conn,
        (DBusHandleMessageFunction)_on_screen_signal,
        NULL, NULL);

    return 0;
}

void handle_screen_status(const char* status) {
    printf("[Framework] 收到屏幕状态: %s\n", status);

    /* 此处可扩展业务逻辑（如触发 UI 渲染） */
}
