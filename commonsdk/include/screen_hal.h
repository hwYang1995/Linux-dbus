#ifndef SCREEN_HAL_H
#define SCREEN_HAL_H

/**
 * @brief 屏幕硬件初始化
 * @return 0=成功, 非0=错误码
 */
int screen_hal_init(void);

/**
 * @brief 通过 D-Bus 上报初始化状态
 * @param status 状态字符串
 */
void screen_report_status(const char* status);

#endif // SCREEN_HAL_H