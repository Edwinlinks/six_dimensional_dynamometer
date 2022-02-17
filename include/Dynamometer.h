//
// Created by luotinkai on 2022/2/17.
//

#pragma once

#include <unistd.h>
#include <iostream>
#include <modbus.h>
#include "modbus_rtu.h"

const int slave_id = 1;
const char *port = "/dev/ttyUSB0";
const int baud = 115200;
const char parity = 'N';
const int data_bit = 8;
const int stop_bit = 1;
const uint16_t address = 0x01f4;
const int number = 16;
const double length = 0.032;

double calculate(double parameter_1, double parameter_2){
    double result = parameter_1 - parameter_2;
    return result;
}

double parseTorque(double force){
    double torque = force * length;
    return torque;
}

void outputForce(double force_x_axis, double force_y_axis, double force_z_axis){
    std::cout << "force_x_axis" << "=" << force_x_axis << std::endl;
    std::cout << "force_x_axis" << "=" << force_y_axis << std::endl;
    std::cout << "force_x_axis" << "=" << force_z_axis << std::endl;
}

void outputTorque(double torque_x_axis, double torque_y_axis, double torque_z_axis){
    std::cout << "force_x_axis" << "=" << torque_x_axis << std::endl;
    std::cout << "force_x_axis" << "=" << torque_y_axis << std::endl;
    std::cout << "force_x_axis" << "=" << torque_z_axis << std::endl;
}
