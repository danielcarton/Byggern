/*
 * CAN_control.h
 *
 * Created: 06/10/2022 13:15:59
 *  Author: danie
 */ 


#ifndef CAN_MODULE_CONTROLLER_H_
#define CAN_MODULE_CONTROLLER_H_


void CAN_module_activate_cs(void);

void CAN_module_deactivate_cs(void);

void CAN_module_reset(void);

void CAN_module_init();

uint8_t CAN_module_read(uint8_t addr);

void CAN_module_write(uint8_t data, uint8_t addr);

void CAN_module_request_send(uint8_t temp);

uint8_t CAN_module_read_status(void);

void CAN_module_bit_modify(uint8_t addr, uint8_t bit, uint8_t data);

void CAN_module_reset(void);

#endif /* CAN_CONTROL_H_ */