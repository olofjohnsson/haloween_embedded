cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(ghost_zipline)

target_sources(app PRIVATE
src/main.c
src/application/application.c
src/bluetooth/bluetooth.c
)
