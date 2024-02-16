/*
 * 74HC595_165.h
 *
 *  Created on: Feb 16, 2024
 *      Author: funtik_alt_d
 */

#ifndef INC_74HC595_165_H_
#define INC_74HC595_165_H_
#define LSBFIRST 1
#define MSBFIRST 2

#include "stm32f4xx_hal.h"

//функция для передачи 1 байта данных в 74НС595, dataPIN пин для данных, dataPORT порт пина данных, clockPIN пин для синхроимпульсов, clockPORT порт пина синхроимпульсов, bitOrder направление передачи
//LSBFIRST, MSBFIRST, value байт данных для передачи
void shiftOut(uint16_t dataPIN, GPIO_TypeDef *dataPORT, uint16_t clockPIN,
		GPIO_TypeDef *clockPORT,
		uint8_t bitOrder, uint8_t value);

//функция для приёма 1 байта данных из 74НС165, dataPIN пин для данных, dataPORT порт пина данных, clockPIN пин для синхроимпульсов, clockPORT порт пина синхроимпульсов, bitOrder направление передачи
//LSBFIRST, MSBFIRST
uint8_t shiftIn(uint16_t dataPIN, GPIO_TypeDef *dataPORT, uint16_t clockPIN,
		GPIO_TypeDef *clockPORT,
		uint8_t bitOrder);


#endif /* INC_74HC595_165_H_ */
