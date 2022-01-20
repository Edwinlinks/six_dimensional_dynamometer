//
// Created by huakang on 2021/4/12.
//

#include "modbus_rtu.h"

int main(int argc, char **argv) {
  uint16_t data[5]{1, 2, 3, 4, 5};
  ModbusRtu modbus_rtu("/dev/pts/4", 1, 9600, 'N', 8, 1);
  modbus_rtu.writeRegisters(0, 5, data);
  modbus_rtu.readRegisters(0, 5);
  modbus_rtu.print(2, 3);
  return 0;
}
