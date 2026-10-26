# SPDX-License-Identifier: Apache-2.0
cmake_minimum_required(VERSION 3.20.0)
 
# Xóa toàn bộ flash trước mỗi lần nạp; thao tác này xóa cả dữ liệu người dùng.
# Kết nối Under Reset giúp ST-LINK truy cập MCU khi firmware đang chạy.
set(BOARD_RUNNER_ARGS_stm32cubeprogrammer
    "--frequency=4000;--conn-modifiers=mode=UR"
    CACHE STRING "STM32CubeProgrammer connection settings"
    FORCE
)

# Tìm Zephyr (đã được đăng ký bằng lệnh "west zephyr-export")
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
 
project(bkit_blinky)
 
# Khai báo các file nguồn của ứng dụng
target_sources(app PRIVATE src/main.c)
