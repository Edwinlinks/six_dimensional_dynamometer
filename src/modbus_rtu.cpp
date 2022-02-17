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

uint16_t *ModbusRtu::readRegisters(const int start_address, const int register_number) {
  uint16_t *read_date = (uint16_t *)malloc((register_number + 1) * sizeof(uint16_t));
  int rc = modbus_read_registers(modbus_, start_address, register_number, read_date);
  if (rc = register_number) {
    std::cout << "Read registers successfully!" << std::endl;
    return read_date;
  } else
    std::cout << "Error modbus_read_registers" << std::endl;
    std::cout << stderr << modbus_strerror(errno) << std::endl;
}

void ModbusRtu::setSerialMode(int mode) {
    modbus_rtu_set_serial_mode (modbus_, mode);
}

void ModbusRtu::Flush() {
    modbus_flush(modbus_);
}

ModbusRtu::~ModbusRtu() {
  modbus_close(modbus_);
  modbus_free(modbus_);
}
