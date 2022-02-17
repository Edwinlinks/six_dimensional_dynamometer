//
// Created by huakang on 2021/2/3.
//
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <iostream>
#include <cstring>
#include <cerrno>
#include <modbus.h>

const int server_id = 1;
const char *port = "/dev/ttyUSB0";
const int baud = 115200;
const char parity = 'N';
const int data_bit = 8;
const int stop_bit = 1;
const int address = 0x01f4;
const int number = 16;
int main(int argc, char **argv){
  modbus_t *mb;
  int rc;
  uint16_t *tab_rp_reg, *tab_rq_reg;
  tab_rp_reg = (uint16_t *)malloc((number+1) * sizeof(uint16_t));
  memset(tab_rp_reg, 0, (number+1) * sizeof(uint16_t));
  tab_rq_reg = (uint16_t *)malloc((number+1) * sizeof(uint16_t));
  memset(tab_rq_reg, 0, (number+1) * sizeof(uint16_t));

  // RTU
  mb = modbus_new_rtu(port, baud, parity, data_bit, stop_bit);
  if (modbus_set_slave(mb, server_id) == -1){
    std::cout << stderr << "Unable to set slave ID: " << modbus_strerror(errno) << std::endl;
    return -1;
  }
  modbus_set_debug(mb, TRUE); // set debug

  // read information form force sensor
  modbus_rtu_set_serial_mode (mb, MODBUS_RTU_RS485);
  while (TRUE){
      if (modbus_connect(mb) == -1){
          std::cout << stderr << "Connection failed: " << modbus_strerror(errno) << std::endl;
          modbus_free(mb);
          return -1;
      }
      usleep(200*1000);
      modbus_flush(mb);
      rc = modbus_read_registers(mb, address, number, tab_rq_reg);
      if (rc == -1){
          std::cout << "Error modbus_read_registers" << std::endl;
          std::cout << stderr << modbus_strerror(errno) << std::endl;
          return -1;
      }
      for (int i = 0; i < rc; i++){
          std::cout << "reg" << i << "=" << tab_rq_reg[i] << "  ";
          std::cout << "rc" << rc << std::endl;
          uint16_t g1 = (tab_rq_reg[4] <<8) | (tab_rq_reg[5]);
          uint16_t g2 = (tab_rq_reg[6] <<8) | (tab_rq_reg[7]);
          printf("g1 = %d/n",g1);
          printf("g2 = %d/n",g2);
      }

  }
  // close the connection
  close:
    /* Free the memory */
    free(tab_rp_reg);
    // free(tab_rp_registers);

    /* Close the connection */
    modbus_close(mb);
    modbus_free(mb);
  return 0;
}
