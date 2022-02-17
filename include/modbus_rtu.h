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
  uint16_t *readRegisters(const int start_address, const int register_number);
  void setSerialMode(int mode);
  void Flush();

 private:
  modbus_t *modbus_{};
};
