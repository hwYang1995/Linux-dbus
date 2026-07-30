# 1. 编译 tools 层 → 生成 libdbus_wrapper.a
cd tools && make && make install

# 2. 编译 bsp 层 → 生成 libscreen_bsp.so
cd ../bsp && make && make install

# 3. 编译 framework 层 → 生成 display_framework 可执行文件
cd ../framework && mkdir -p build && cd build && cmake .. && make