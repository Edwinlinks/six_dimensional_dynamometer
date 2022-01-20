cmake_minimum_required(VERSION 3.16)
project(modbus_class)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_module)
find_package(Modbus REQUIRED)

include_directories(
        ${MODBUS_INCLUDE_DIR}
        ./include
)

add_library(modbus_rtu src/modbus_rtu.cpp)
target_link_libraries(modbus_rtu ${MODBUS_LIBRARIES})
add_executable(test_force_sensor src/test_force_sensor.cpp)
target_link_libraries(test_force_sensor ${MODBUS_LIBRARIES})
