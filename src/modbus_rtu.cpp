//
// Created by huakang on 2021/4/12.
//

#include "modbus_rtu.h"

ModbusRtu::ModbusRtu(const char *port,
                     const int slave_id,
                     const int baud,
                     const char parity,
                     const int data_bit,
                     const int stop_bit) {

  modbus_ = modbus_new_rtu(port, baud, parity, data_bit, stop_bit);
  if (modbus_set_slave(modbus_, slave_id) == -1)
    std::cout << stderr << "Unable to set slave ID: " << modbus_strerror(errno) << std::endl;

  modbus_set_debug(modbus_, TRUE); // set debug
  if (modbus_connect(modbus_) == -1) {
    std::cout << stderr << "Connection failed: " << modbus_strerror(errno) << std::endl;
    modbus_free(modbus_);
  }
}

int ModbusRtu::readRegisters(const int start_address, const int register_number) {
  read_registers_array_ = new uint16_t[register_number];
  int rc = modbus_read_registers(modbus_, start_address, register_number, read_registers_array_);
  if (rc != register_number) {
    std::cout << "Error modbus_read_registers" << std::endl;
    std::cout << stderr << modbus_strerror(errno) << std::endl;
    return -1;
  } else
    std::cout << "Read registers successfully!" << std::endl;
}

int ModbusRtu::writeRegisters(const int start_address, const int register_number, const uint16_t *data) {
  int rc = modbus_write_registers(modbus_, start_address, register_number, data);
  if (rc != register_number) {
    std::cout << "Error modbus_write_registers" << std::endl;
    std::cout << stderr << modbus_strerror(errno) << std::endl;
    return -1;
  } else
    std::cout << "Write registers successfully!" << std::endl;
}

void ModbusRtu::print(const int start_address, const int stop_address) {
  if (start_address > stop_address)
    std::cout << "start address can not more than stop address!" << std::endl;
  else {
    for (int i = start_address; i <= stop_address; i++)
      std::cout << "address" << i << " = " << read_registers_array_[i] << "  ";
  }
}

ModbusRtu::~ModbusRtu() {
  modbus_close(modbus_);
  modbus_free(modbus_);
}
