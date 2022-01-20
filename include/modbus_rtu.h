//
// Created by huakang on 2021/4/12.
//

#pragma once

#include <iostream>
#include <cstring>
#include <cerrno>
#include <modbus.h>

class ModbusRtu {
 public:
  ModbusRtu(const char *port,
            const int slave_id,
            const int baud,
            const char parity,
            const int data_bit,
            const int stop_bit);
  ~ModbusRtu();
  int readRegisters(const int start_address, const int register_number);
  int writeRegisters(const int start_address, const int register_number, const uint16_t *data);
  void print(const int start_address, const int stop_address);

 private:
  uint16_t *read_registers_array_{}, *write_registers_data_{};
  modbus_t *modbus_{};
};
