cmake_minimum_required(VERSION 3.16)
project(Dynamometer)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
find_package(Modbus REQUIRED)

include_directories(
        include
        ${MODBUS_INCLUDE_DIR}
)

add_executable(force_sensor src/Dynamometer.cpp src/modbus_rtu.cpp)
target_link_libraries(force_sensor ${MODBUS_LIBRARIES})
