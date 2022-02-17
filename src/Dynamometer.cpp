//
// Created by luotinkai on 2022/2/17.
//
#include "Dynamometer.h"

int main(int argc, char **argv){

    ModbusRtu *mb = new ModbusRtu(port, slave_id, baud, parity, data_bit, stop_bit);
    // RTU
    mb->setSerialMode(MODBUS_RTU_RS485);

    uint16_t *date{};
    double forceX_1, forceX_2, forceY_1, forceY_2, forceZ_1, forceZ_2;
    double torqueX_1, torqueX_2, torqueY_1, torqueY_2, torqueZ_1, torqueZ_2;
    double force_x_axis, force_y_axis, force_z_axis;
    double torque_x_axis, torque_y_axis, torque_z_axis;

    while (TRUE){
        usleep(200*1000);
        mb->Flush();
        date = mb->readRegisters(address, number);
        forceX_1 = (date[1] <<8) | (date[2]);
        forceX_2 = (date[3] <<8) | (date[4]);
        forceY_1 = (date[5] <<8) | (date[6]);
        forceY_2 = (date[7] <<8) | (date[8]);
        forceZ_1 = (date[9] <<8) | (date[10]);
        forceZ_2 = (date[11] <<8) | (date[12]);

        force_x_axis = calculate(forceX_1, forceX_2);
        force_y_axis = calculate(forceY_1, forceY_2);
        force_z_axis = calculate(forceZ_1, forceZ_2);

        torqueX_1 = parseTorque(forceX_1);
        torqueX_2 = parseTorque(forceX_2);
        torqueY_1 = parseTorque(forceY_1);
        torqueY_2 = parseTorque(forceY_2);
        torqueZ_1 = parseTorque(forceZ_1);
        torqueZ_2 = parseTorque(forceZ_2);

        torque_x_axis = calculate(torqueX_1, torqueX_2);
        torque_y_axis = calculate(torqueY_1, torqueY_2);
        torque_z_axis = calculate(torqueZ_1, torqueZ_2);

        outputForce(force_x_axis, force_y_axis, force_z_axis);
        outputTorque(torque_x_axis, torque_y_axis, torque_z_axis);

    }
    /* Free the memory */
    free(date);
    return 0;
}
