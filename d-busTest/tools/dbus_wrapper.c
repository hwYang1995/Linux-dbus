#include "dbus_wrapper.h"
#include <stdio.h>
#include <unistd.h>

static DBusConnection* g_conn = NULL;

int dbus_init(void) {
    DBusError err;
    dbus_error_init(&err);
    
    // 尝试连接会话总线（支持自动重连）
    for (int i = 0; i < 3; i++) {
        g_conn = dbus_bus_get_private(DBUS_BUS_SESSION, &err);
        if (g_conn) break;
        dbus_error_free(&err);
        sleep(1); // 车载环境需容忍总线启动延迟
    }
    
    if (!g_conn || dbus_error_is_set(&err)) {
        fprintf(stderr, "DBus 初始化失败: %s\n", err.message);
        dbus_error_free(&err);
        return -1;
    }
    
    dbus_connection_set_exit_on_disconnect(g_conn, FALSE);
    return 0;
}

DBusConnection* dbus_get_connection(void) {
    return g_conn;
}

int dbus_send_status(const char* service_name,
                     const char* object_path,
                     const char* interface,
                     const char* signal_name,
                     const char* status_msg) {
    if (!g_conn) return -1;
    
    DBusMessage* msg = dbus_message_new_signal(object_path, interface, signal_name);
    if (!msg) return -1;
    
    DBusMessageIter args;
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &status_msg)) {
        dbus_message_unref(msg);
        return -1;
    }
    
    dbus_bool_t ret = dbus_connection_send(g_conn, msg, NULL);
    dbus_message_unref(msg);
    dbus_connection_flush(g_conn); // **关键：立即发送，避免车载网络延迟**
    return ret ? 0 : -1;
}

void dbus_cleanup(void) {
    if (g_conn) {
        dbus_connection_close(g_conn);
        dbus_connection_unref(g_conn);
        g_conn = NULL;
    }
}