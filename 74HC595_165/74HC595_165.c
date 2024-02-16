/*
 * 74HC595_165.c
 *
 *  Created on: Feb 16, 2024
 *      Author: funtik_alt_d
 */

#include "74HC595_165.h"

void shiftOut(uint16_t dataPIN, GPIO_TypeDef *dataPORT, uint16_t clockPIN,
		GPIO_TypeDef *clockPORT,
		uint8_t bitOrder, uint8_t value) {
	uint8_t i;
	for (i = 0; i < 8; ++i) {
		if (bitOrder == LSBFIRST) {
			HAL_GPIO_WritePin(dataPORT, dataPIN, !!(value & (1 << i)));
		} else {
			HAL_GPIO_WritePin(dataPORT, dataPIN, !!(value & (1 << (7 - i))));
		}

		HAL_GPIO_WritePin(clockPORT, clockPIN, GPIO_PIN_SET);
		HAL_GPIO_WritePin(clockPORT, clockPIN, GPIO_PIN_RESET);
	}
}


uint8_t shiftIn(uint16_t dataPIN, GPIO_TypeDef *dataPORT, uint16_t clockPIN,
		GPIO_TypeDef *clockPORT,
		uint8_t bitOrder) {
	uint8_t i;
	uint8_t value;
	for (i = 0; i < 8; ++i) {
		HAL_GPIO_WritePin(clockPORT, clockPIN, GPIO_PIN_SET);
		if (bitOrder == LSBFIRST) {
			value |= HAL_GPIO_ReadPin(dataPORT, dataPIN) << i;
		} else {
			value |= HAL_GPIO_ReadPin(dataPORT, dataPIN) << (7 - i);
		}
		HAL_GPIO_WritePin(clockPORT, clockPIN, GPIO_PIN_RESET);
	}
	return value;
}
